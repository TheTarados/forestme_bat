import scipy.io.wavfile as wf
import numpy as np
import os
from scipy import signal
import argparse


def bin_reader(path):
    with open(path, mode='rb') as file: # b is important -> binary
        fileContent = file.read()
    return np.frombuffer(fileContent, dtype=np.uint16)

parser = argparse.ArgumentParser(
                    prog='bin_to_wavs',
                    description='Takes a binary file of 16 bytes audio and slices it into wavs',
                    epilog='Thanks 4 using me!')

parser.add_argument('--input', required=True, type = str, help="Input binary file")
parser.add_argument('--base', required=True, type = str, help="Directory in which the wavs directory can be found")
parser.add_argument('--decimate', default = "n", type = str, help="y/n if y, decimate such that wavs are of the audible spectrum (default=n)")
parser.add_argument('--name', default = "mm_dd_hhhmm", type = str, help="name of the session (default=mm_dd_hhhmm)")
parser.add_argument('--start', default = 0, type = float, help="Time in second at which to start conversion (default=0)")
parser.add_argument('--step', default = 1, type = float, help="Length of wavs (default=1)")
parser.add_argument('--end', default = -1, type = float, help="Second at which to end conversion (default=-1 -> full file)")
parser.add_argument('--fs', default = 300e3, type = float, help="Sampling frequency (default=300e3)")
args = parser.parse_args()

DECIMATE =False

base =args.base
name = args.name
in_path = args.input
out_path =  f"{base}wavs/wavs_{name}/"

if not os.path.exists(out_path):
    os.makedirs(out_path)

fs = int(args.fs)
start = args.start
end = args.end
if end == -1:
    end = os.path.getsize(in_path)/fs/2
step = args.step
samples = int(step*fs)

print("Launching")
i = 0
with open(in_path, mode='rb') as file: # b is important -> binary
    file.seek(int(start*fs)*2)
    while step*i+start<end:
        many_to_read = samples if step*(i+1)+start< end else int(fs*(end-start-step*i))
        fileContent = file.read(samples*2)
        to_save = np.frombuffer(fileContent, dtype=np.uint16).astype(float)
        
        to_save -= np.mean(to_save)
        to_save = to_save.astype(np.int16)
        

        if DECIMATE:
            to_save = signal.decimate(to_save,10)
            to_save = to_save.astype(np.int16)
            
        wf.write(out_path+str(int(i))+".wav", fs//10, to_save)
        i+=1
        if len(to_save)*(1+DECIMATE*9)!=samples:
            print("Finished")   
            break

