import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as wf
import pyfilterbank as pf
from scipy.signal import resample
import sys
np.set_printoptions(threshold=sys.maxsize)


already_computed_freqs = {}
def get_freqs(mmat, len_vec, fs, n_mel_bin):
    a = (len_vec, fs, n_mel_bin)
    if a in already_computed_freqs.keys():
        return already_computed_freqs[a]
    freqs = []
    for i in range(len(mmat)):
        for k in range(1, len(mmat[i])-1):
            if mmat[i][k-1]< mmat[i][k] and mmat[i][k+1] < mmat[i][k]:
                freqs.append(np.fft.rfftfreq(2*(len_vec-1), 1/fs)[k])
    already_computed_freqs[a] = freqs
    return freqs


from numpy.linalg import lstsq
ramp = lambda u: np.maximum( u, 0 )
step = lambda u: ( u > 0 ).astype(float)
def get_model( fun_log ):
    """https://datascience.stackexchange.com/a/32833"""
    initialBreakpoints = [900, 5e3, 10e3, 15e3, 20e3, 27e3, 30e3]
    X = np.arange(2**15)
    Y = fun_log(X)
    nIterationMax = 1000

    breakpoints = np.sort( np.array(initialBreakpoints) )

    dt = np.min( np.diff(X) )
    ones = np.ones_like(X)

    for i in range( nIterationMax ):
        # Linear regression:  solve A*p = Y
        Rk = [ramp( X - xk ) for xk in breakpoints ]
        Sk = [step( X - xk ) for xk in breakpoints ]
        A = np.array([ ones, X ] + Rk + Sk )
        p =  lstsq(A.transpose(), Y, rcond=None)[0] 

        # Parameters identification:
        a, b = p[0:2]
        ck = p[ 2:2+len(breakpoints) ]
        dk = p[ 2+len(breakpoints): ]

        # Estimation of the next break-points:
        newBreakpoints = breakpoints - dk/ck 

        # Stop condition
        if np.max(np.abs(newBreakpoints - breakpoints)) < dt/5:
            break

        breakpoints = newBreakpoints
    else:
        print( 'maximum iteration reached' )
    # Compute the final segmented fit:
    Xsolution = np.insert( np.append( breakpoints, max(X) ), 0, min(X) )
    ones =  np.ones_like(Xsolution) 
    Rk = [ c*ramp( Xsolution - x0 ) for x0, c in zip(breakpoints, ck) ]

    Ysolution = a*ones + b*Xsolution + np.sum( Rk, axis=0 )

    Ysolution[0] = 0
    Ysolution[-1] = 2**15-1
    return Xsolution, Ysolution
model = get_model(lambda x: 15*2**11+np.log2((1+x)/2**15) * 2**11)
def piecewise_linear(x, model):
    x_values, y_values = model
    idx = np.searchsorted(x_values, x, side="right") - 1
    idx = np.clip(idx, 0, len(x_values) - 2)
    x1, x2 = x_values[idx], x_values[idx + 1]
    y1, y2 = y_values[idx], y_values[idx + 1]
    
    slope = (y2 - y1) / (x2 - x1)
    return y1 + slope * (x - x1)
def true_approx_log(x):
    if(x<2000):
        if(x<290):
            if(x<37):
                return x*312
            else:
                return x*24+10656
	        
        else:
            if(x<840):
                return x*5+16166
            else:
                return x*2+18686
	        
	    
    else:
        if(x<8200):
            if(x<4050):
                return x+20686
            else:
                return (x>>1)+22711
	        
        else:
            if(x<14904):
                return (x>>2)+24761
            else:
                return (x>>3)+26624
	        
        
def vec_approx_log(vec, model):
    return np.vectorize(lambda x: true_approx_log(x))(vec)    
dic_opt = {}  

def test_opti(array, n_bit, str_index, test_optimality):
    if test_optimality:
        if array.max()>2**n_bit-1:
            print(f"PROBLEM {str_index}: {np.abs(array).max()} > {2**n_bit-1}")
        
        if array.min()<-2**n_bit:
            print(f"PROBLEM {str_index}: {np.min(array)} < {-2**n_bit}")
        
        if np.ceil(np.log2(1+np.abs(array).max())) > n_bit-1 and str_index not in dic_opt.keys():
                print(f"SHOULD APPEAR AT LEAST ONCE FOR OPTIMALITY ({str_index})")
                dic_opt[str_index] = True


def treat_spec(audio_vecs, fs, n_mel_bin, do_print = False, test_optimality = True, denoize = True):
    
    #audio_vecs *= 2**4
    test_opti(audio_vecs, 15, "post_full_bit", test_optimality)
    temp = audio_vecs.copy()
    audio_vecs = audio_vecs.astype(np.int16)

    #if do_print:print("Post conversion:", audio_vecs)


    #multiply by Hann window
    quant_hamm = (np.hamming(len(audio_vecs[0]))*2**15).astype(np.int16)
    audio_vecs = (audio_vecs.astype(np.int32) * quant_hamm.astype(np.int32))//2**15

    test_opti(audio_vecs, 15, "post_mult", test_optimality)

    audio_vecs = audio_vecs.astype(np.int16)
    
    if do_print: print("Post multiplication:",np.array2string( audio_vecs, separator=",")) 

    #fft
    vecs = np.fft.rfft(audio_vecs, axis = 1)
    vecs /= 2**9  #cmsis overflow avoidance
    
    revecs = vecs.real.astype(np.int16)
    imvecs = vecs.imag.astype(np.int16)
    vecs = (revecs + 1j*imvecs)
    
    if do_print: print("Post fft:", np.array2string(vecs, separator=","))
    

    vecs *= 2   #we can use some more bits

    
    test_opti(vecs.real, 15, "post_fft_real", test_optimality)
    test_opti(vecs.imag, 15, "post_fft_imag", test_optimality)

    vecs = np.abs(vecs)**2

    vecs /= 2**15   #q15_t renormalisation
    vecs /= 2  #cmsis overflow avoidance
    

    #if do_print: print("Post abs:", vecs)


    test_opti(vecs, 15, "post_abs", test_optimality)
    vecs = vecs.astype(np.int16)
    
    model = [[0,37,290,840,2000,4050,8200,14904,2**15],[0,10747.7555475,16762.6247023,19898.290156,22459.4031655,24543.3597331,26627.244282,28392.46593,30720.0901671]]
    log = lambda x: 15*2**11+np.log2((1+x)/2**15) * 2**11
    vecs = log(vecs)#vec_approx_log(vecs, model)
    
    test_opti(vecs, 15, "post_log", test_optimality)

    vecs = vecs.astype(np.int16)
    if do_print: print("Post log:", np.array2string(vecs, separator=","))
    
    band = [10e3, 120e3]

    mmat, tup = pf.melbank.compute_melmat(num_mel_bands=n_mel_bin, freq_min=band[0], freq_max=band[1], num_fft_bands=len(vecs[0]), sample_rate=fs)
    mmat = (mmat*2**15).astype(np.int16)
    spec = np.dot(mmat.astype(float), vecs.T.astype(float)).T
  
   

    spec //= 2**26
    #if np.ceil(np.log2(1+np.abs(spec).max())) > 6:
    #    print(list(temp[np.unravel_index(np.argmax(np.ceil(np.log2(1+np.abs(spec)))), spec.shape)[0]].astype(np.int16)))
    test_opti(spec, 7, "post_mat", test_optimality)
    spec = spec.astype(np.int8)
    if do_print: print("Post mat mul:",np.array2string(spec, separator=","))
    
    if denoize:#if we do only one vector, we wouldn't want to denoize
        spec -= np.mean(spec, axis = 0, dtype=np.int8)[None, ...] #denoize like it would be done on the device
    
    spec = np.transpose(spec, (1, 0))[:, ::-1] #put the spec in the right format
    return spec


class Spectrogram:

    SAFE_GUARD = 1 #in number of spectrograms

    N_BIT_SHIFT = 16-12

    IS_TRUE_DATA = True

    COMPRISED_CALL_FAC = 1 #How much of the call should be in a spec at least 

    BOARD_FS = 300e3
    
    def __init__(self, path, args):
        """
        If n_mel_bin is False, no mel transformation shall be applied
        """
        self.N_MEL_BIN = args.mel_bin
        
        self.SPEC_SIZE = args.spec_size  #bin
        self.SPEC_TIME = args.spec_time   #second
        self.SAMPLE_WINDOW_SIZE = 2**args.sample_window_size #2**9 for 512
        
        self.HOP_LENGTH = self.SPEC_TIME/self.SPEC_SIZE

        self.SPEC_HOP = args.spec_hop   #second
        if self.SPEC_HOP==None:
            self.SPEC_HOP = self.HOP_LENGTH*self.BOARD_FS

        fs, audio = wf.read(path)
        fs*=10 #dilation
        self.audio = audio.astype(float)
        self.audio = resample(audio, int(len(audio)*self.BOARD_FS/fs))
        self.calls = []

        self.path =path

    def add_call(self, start_time, end_time, low_freq, high_freq):
        self.calls.append([float(start_time), float(end_time), float(low_freq), float(high_freq)])

    def get_time_bin(self, time):
        return np.argmin(np.abs(time-self.times))

    def get_freq_bin(self, freq):
        return np.argmin(np.abs(freq-self.freqs))

    def plot_true(self):
        tn, tp = self.get_true_and_false()
        for spec in tp:
            plt.imshow(spec, aspect="auto")
            plt.show()

    
    def get_all_features(self):
        
        i_to_s = lambda x: int(x*self.SPEC_HOP)
        i_to_seuuuh = lambda x: int(x*self.HOP_LENGTH*self.BOARD_FS)
        #Compute how many spectrograms we can compute from the audio
        #n_specs = int(len(self.audio)/self.BOARD_FS/self.HOP_LENGTH)-self.SPEC_SIZE
        n_specs = int((len(self.audio)-int(self.SPEC_TIME*self.BOARD_FS)-self.SAMPLE_WINDOW_SIZE)/self.SPEC_HOP) +1
        result = np.empty((n_specs, self.N_MEL_BIN, self.SPEC_SIZE))
        for i in range(n_specs):
            audio = self.audio[i_to_s(i):i_to_s(i)+int(self.SPEC_TIME*self.BOARD_FS)+self.SAMPLE_WINDOW_SIZE].copy()#added +SAMPLE_WINDOW_SIZE for overlap with next vec
            #audio -= 2**11
            while np.abs(audio).max() < 2**14-1:
                audio *= 2
            audio_vecs = np.array([audio[i_to_seuuuh(j): i_to_seuuuh(j)+self.SAMPLE_WINDOW_SIZE] for j in range(self.SPEC_SIZE)])
         
            result[i] = treat_spec(audio_vecs, self.BOARD_FS, self.N_MEL_BIN, False, True)
        return result

    def get_true_and_false(self):
        wins = self.get_all_features()
        time_indexes = np.arange(len(wins))*self.SPEC_HOP/self.BOARD_FS #Give the "start" time of each spec

        label_times = np.zeros_like(time_indexes)
        tp = []
        for i in self.calls: 
            #set to 1 all the places where there are calls
            #print(i[0], i[1], time_indexes[-1] + self.SPEC_TIME + (i[1]-i[0])*(1-self.COMPRISED_CALL_FAC))
            mi = min(i[0], i[1] -self.SPEC_TIME)
            ma = max(i[0], i[1] -self.SPEC_TIME)
            with_call = np.logical_and(time_indexes>= mi, time_indexes <= ma)
            tp.append(wins[with_call])
            no_call = time_indexes <  mi - self.SAFE_GUARD * self.SPEC_TIME
            no_call = np.logical_or(no_call, time_indexes > ma + self.SAFE_GUARD * self.SPEC_TIME)
            no_call = np.logical_and(no_call, np.logical_not(with_call))
            #set 2 all the places where we think there are no call
            label_times[no_call] = 2

        tn = wins[label_times == 2]
        return tn, tp

    def get_ideal_answer(self):
        wins = self.get_all_features()
        time_indexes = np.arange(len(wins))*self.SPEC_HOP/self.BOARD_FS #Give the "start" time of each spec
        label_times = np.zeros_like(time_indexes)
        for i in self.calls: #we set to 1 all the places where there are callsmi = min(i[0], i[1] -self.SPEC_TIME)
            mi = min(i[0], i[1] -self.SPEC_TIME)
            ma = max(i[0], i[1] -self.SPEC_TIME)
            with_call = np.logical_and(time_indexes>= mi, time_indexes <= ma)
            label_times[with_call] = 1

        return label_times

    def get_calls(self):
        return np.array(self.calls)
    
    def spec_index_to_time(self, index):
        return index*self.SPEC_HOP/self.BOARD_FS

    def get_path(self):
        return self.path

    def __str__(self):
        return f"""
Path : {self.path}
Feature dim : ({self.SPEC_SIZE}, {self.N_MEL_BIN})
Overlap: {(self.SAMPLE_WINDOW_SIZE/self.BOARD_FS-self.HOP_LENGTH)/self.HOP_LENGTH}
Hop length: {self.HOP_LENGTH * self.BOARD_FS}
Total spec samplel length: {self.HOP_LENGTH *self.SPEC_SIZE * self.BOARD_FS}
"""

if __name__=="__main__":
    fs = 300e3
    n_mel_bin = 64
    np.random.seed(0)
    max_value = 2**11-1
    #f = lambda t: np.random.random(size = len(t))*max_value
    f = lambda t: np.sin(2*np.pi*20e3*t)*max_value+max_value
    
    t = np.arange(512)/fs

    audio_float = f(t)
    
    audio_float = [-1151, -512, -1919, -1983, -1727, -2367, -2495, -1920, -2431, -1727, -319, -1663, -1088, 0, -383, 127, 320, -320, -448, 256, -63, -511, 512, 447, -1151, 64, 0, -1279, -1023, -895, -3327, -1599, -1151, -2304, -1920, -1471, -2240, -3520, -1407, -2176, -2176, -703, -1215, -2751, -895, -511, -2688, -1024, -127, -1600, -384, 896, -1407, -1535, 896, -1407, -1407, 576, -512, -2175, -383, -511, -1920, 64, 64, -2175, -1024, 959, -1408, -1023, 2496, 448, -512, 2624, 2112, 0, 3007, 3008, -512, 1472, 3008, -511, -384, 2496, -511, -2943, 1599, 576, -2111, 575, 1600, -1408, 576, 3648, 447, 0, 4992, 3008, -383, 3648, 4543, -511, 832, 3647, -384, -1599, 1855, 383, -2623, 640, 1664, -2559, -511, 2624, -191, -1088, 3008, 2752, -2175, 1792, 4096, 768, 896, 3328, 2432, -1471, 575, 2624, -1279, -2047, 1472, 384, -3647, -1087, 896, -3135, -3072, 1920, 256, -2880, 384, 2560, -1920, -1536, 2879, 831, -3200, -511, 1855, -2687, -3648, 575, -63, -4479, -1600, 1279, -2239, -4351, 384, 576, -3648, -2496, 1599, -383, -3968, -384, 2432, -2431, -3327, 1343, 447, -4992, 
-2943, 1343, -2560, -6272, -512, 831, -4799, -3968, 1471, -1088, -5695, -1728, 2431, -2688, -4480, 960, 1919, -4160, -3135, 1599, 448, -4864, -3008, 1151, -1920, -5504, -1600, 1855, -3199, -5632, -383, 1343, -3520, -2880, 2176, 1023, -3520, -1536, 4479, 575, -4479, -1023, 3904, -1152, -4031, 1343, 3136, -3200, -4800, 128, 383, -5568, -5696, 767, -576, -5440, -4160, 895, -1599, -6464, -2112, 511, -2880, -4032, -1600, -576, -1599, -4672, -3136, -448, -576, -5056, -4671, -2368, -1088, -6208, -5696, -320, -2240, -5184, -4672, -576, -576, -4672, -5696, 639, -575, -5184, -5568, 128, 2432, -4416, -4672, -576, 128, -4160, -8768, -3392, 2176, -4672, -9536, -3136, 4096, -1344, -10048, -3008, 7552, 3455, -9280, -5184, 9855, 6527, -11328, -9088, 11072, 10880, -12608, -13888, 9472, 13376, -12160, -19072, 7488, 17536, -9088, -22528, 5247, 22592, 
-1919, -23680, -1023, 25407, 7551, -22208, -10496, 22336, 16832, -18048, -19520, 13696, 24320, -7232, -24768, 1280, 25280, 3007, -24832, -12928, 18496, 15680, -15040, -21440, 6208, 23040, 1151, -22912, -9600, 19456, 16512, -13888, -20096, 6975, 23424, 1408, -22656, -9536, 18048, 16128, -13759, -21120, 4799, 21376, 1920, -21504, -10303, 13952, 13888, -9408, -18048, -1152, 13696, 5696, -14208, -14208, 4544, 14464, 0, -15936, -8000, 8896, 9024, -7872, -15744, -3327, 8640, 2944, -10239, -11712, 639, 8192, 640, -11328, -9664, 2560, 6335, -2687, -11648, -5696, 4160, 4672, -3456, -7744, -3008, 2432, 1407, -3648, -7807, -5631, -128, 
-64, -5504, -8960, -5440, -575, -703, -4032, -6656, -3776, 575, 576, -2944, -6528, -4095, -1024, -1088, -3200, -6464, -6080, -2880, -1600, -3199, -9023, -7360, -2751, -3647, -5631, -8191, -6399, -3967, -2879, -63, -3392, -5248, -2431, 639, 1408, -5695, -6655, -2432, -1600, -1408, -5759, -7679, -7040, -4672, -895, -6208, -10688, -7104, -3712, -191, -4352, -8512, -4991, -1087, 2175, -576, -7296, -4416, -383, 2560, -1343, -8448, -5440, -2368, -2495, -1599, -6655, -8768, -6207, -1152, 2431, -6528, -9664, -384, 3968, 1344, -5631, -4672, 2431, 1152, 767, -256, -4800, -1919, 576, 704, -2175, -8064, -2943, 1471, -2879, -4799, -3455, 
0, 575, -4672, -383, 2496, -1535, -831, -511, 1279, 2431, -2880, 0, 383, -2111, 383, -1663, -2624, -1920, -3392, 384, -640, -3904, 0, -1599, -1407, 1727]
    audio_float = np.array(audio_float)+24832
    print(np.min(audio_float), np.max(audio_float))
    audio_float //= 2**4
    print(np.min(audio_float), np.max(audio_float))
    #plt.plot(audio_float)
    audio = np.array(audio_float, dtype=np.uint16)#np.random.randint(-2**7, 2**7, size=(512), dtype=np.int8)
    
    #plt.plot(audio)
    #plt.show()
    print(np.array2string(audio, separator=','))
    v = treat_spec((np.array([audio])-2**11)*2**4, fs, 20, do_print = True, test_optimality = False, denoize = False)[:,0]
    
    plt.figure(figsize=(5,4))
    plt.plot(v, label="Python computation")

    board_answer = [289,24,176,0,0,0,25,74,345,112,44,16,97,194,307,388,37,455,810,203,18,176,352,202,321,963,275,0,132,204,396,918,393,345,466,660,1572,487,378,461,542,858,998,1174,1199,1194,194,335,294,343,238,966,727,731,382,1010,1054,2036,696,923,2038,1039,680,2531]
    plt.plot(board_answer, label="On-board computation")
    plt.xscale("log")
    plt.legend()
    plt.xlabel("Bin frequency [Hz]")
    plt.ylabel("Bin value [/]")
    plt.tight_layout()
    plt.savefig("compar.png")

    def run_tflite_model(x_test, tflite_file):
        import tensorflow as tf
        interpreter = tf.lite.Interpreter(model_path=str(tflite_file))
        interpreter.allocate_tensors()
        input_details = interpreter.get_input_details()[0]
        output_details = interpreter.get_output_details()[0]
        input_scale, input_zero_point = input_details["quantization"]
        proba = np.zeros((len(x_test),), dtype=float)
        x_test_trans = x_test*int(1/input_scale)+input_zero_point
        for i in range(len(x_test)):
            test_image = x_test_trans[i]
            test_image = np.expand_dims(test_image, axis=0).astype(input_details["dtype"])
            interpreter.set_tensor(input_details["index"], test_image)
            interpreter.invoke()
            output = interpreter.get_tensor(output_details["index"])
            proba[i] = output[0,0]
        return proba
