import dataset_reader as dr
import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
import sklearn.metrics
import pandas as pd
import csv
import argparse

parser = argparse.ArgumentParser(
                    prog='run_eval',
                    description='Evaluates a model for its capabilities in a real system',
                    epilog='Thanks 4 using me!')

parser.add_argument('--file', type=int, help='File to tread as index in main.csv', required=True)
parser.add_argument('--base', type = str, help="Directory in which the wavs directory can be found", required=True)
parser.add_argument('--tim',default="n", type=str, help='y/n, if y, do evaluation based on timestamps, if n, do simulation with quantized model (default=n)')
parser.add_argument('--model_path', type=str, help='Path to quantized model or to timestamp file depending on tim', required=True)
parser.add_argument('--spec_size', default = 10, type = int, help="Number of melvec in a spectrogram (default=10)")
parser.add_argument('--spec_time', default = 9e-3, type = float, help="Time contained in 1 spectrogram (default=9-3)")
parser.add_argument('--sample_window_size', default = 9, type = int, help="log_2 of fft size (default=9)")
parser.add_argument('--mel_bin', default = 20, type = int, help="Number of frequency bin (default=20)")
parser.add_argument('--spec_hop', default = None, type = int, help="Sample skipped between two spectrograms (default=None, Size of a vector)")
parser.add_argument('--thresh', default = .5, type = float, help="Threshold applied on the model result  (default=.5)")
parser.add_argument('--seed', default = 0xDEADBEEF, type = int, help="Seed for random parts (default=0xDEADBEEF)")
args = parser.parse_args()

tflite_model_quant_file = args.model_path
def run_tflite_model(x_test, tflite_file):
    interpreter = tf.lite.Interpreter(model_path=str(tflite_file))
    interpreter.allocate_tensors()
    input_details = interpreter.get_input_details()[0]
    output_details = interpreter.get_output_details()[0]
    input_scale, input_zero_point = input_details["quantization"]
    proba = np.zeros((len(x_test),), dtype=float)
    x_test_trans = x_test*int(1/input_scale)+input_zero_point
    for i in range(len(x_test)):
        test_image = x_test_trans[i,...,None]
        test_image = np.expand_dims(test_image, axis=0).astype(input_details["dtype"])
        interpreter.set_tensor(input_details["index"], test_image)
        interpreter.invoke()
        output = interpreter.get_tensor(output_details["index"])
        proba[i] = output[0,0]
    return proba


board_pred = args.tim == "y"

files = [args.file]


np.random.seed(args.seed)
factor_bias = 1
wavs_path = f"{args.base}wavs/"
thresh = args.thresh

n_spec = 0
tp = 0
fp_opt = 0
fp_pes = 0
fn = 0
pos_pred= 0
sec = 0
all_detections = []

with open('./Annotation_generation/main.csv', newline='') as csvfile:
    rowreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    rows = list(rowreader)
    df_path = rows[files[0]][0]

df = pd.read_csv(f"./annotations/{df_path}", sep = " ", quotechar="|")
df_kept = df[df["det_prob"]>0.6]
for spec in dr.enum_specs(files, wavs_path, args):#[18]
    file_df = df[df["file"]==spec.get_path().split("/")[-1]]
    n_spec += 1
    if board_pred:
        detection_times = dr.read_time_log(args.model_path)
        full_time = df_kept["start_time"] + df_kept["file"].str.rstrip(".wav").astype("int")
        all_detections = detection_times
        sec = int(spec.get_path().split("/")[-1][:-4])
        detection_times -=sec
        
    else:
        preds = run_tflite_model(spec.get_all_features(),tflite_model_quant_file)
        preds = preds >= int(255*thresh)
        detection_times = [spec.spec_index_to_time(i) for i in range(len(preds)) if preds[i]]
        all_detections += list(np.array(detection_times)+int(spec.get_path().split("/")[-1].rstrip(".wav")))
        pos_pred += np.sum(preds)
    call_times = spec.get_calls()[:, [0,1]]
    
    attribution = np.ones(len(call_times))
    means = (call_times[:,1]+call_times[:,0])/2
    difs = (call_times[:,1]-call_times[:,0])/2
    df_means = (file_df["start_time"]+file_df["end_time"])/2
    df_difs = (file_df["end_time"]-file_df["start_time"])/2
    
    n_detect = 0
    for i in detection_times:
        testing_start = np.abs(i - means)-difs
        testing_stop = np.abs(i + args.spec_time - means)-difs
        kindness = 100e-3
        if np.min(testing_start) < kindness or np.min(testing_stop) < kindness:
            attribution[np.argmin(testing_start)] = 0
        elif i>0 and i<1:
            df_testing_start =  np.abs(i - df_means)-df_difs
            df_testing_stop =  np.abs(i - df_means)-df_difs
            start_calls = file_df[df_testing_start < kindness]
            stop_calls = file_df[df_testing_stop < kindness ]
            prob_call = max(np.max(start_calls["det_prob"]), np.max(stop_calls["det_prob"]))
            if pd.isna(prob_call):
                fp_opt += 1
                fp_pes += 1
            else:
                if prob_call < 0.4:
                    fp_opt += 1
                elif prob_call < 0.6:
                    fp_opt += (prob_call-0.6)*0.5/(0.4-0.6)

                if prob_call < 0.6:
                    fp_pes += 1
    fn += np.sum(attribution)
    tp += np.sum(1-attribution)
    
prec_opt = tp/(tp+fp_opt)
prec_pes = tp/(tp+fp_pes)
rec = tp/(tp+fn)

print(f"TP: {tp}, FN:  {fn}, FP:  {fp_opt}-{fp_pes}")
print(f"Prec: {round(prec_pes,2)}-{round(prec_opt,2)}, Recall:  {round(rec,2)}")
print(f"F1 score: {round(2/(1/rec+1/prec_pes),2)}-{round(2/(1/rec+1/prec_opt),2)}")
