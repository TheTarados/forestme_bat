import sys
import numpy as np
np.set_printoptions(threshold=sys.maxsize)
from keras.models import load_model
import sklearn.metrics
import matplotlib.pyplot as plt
import tensorflow as tf

import argparse

parser = argparse.ArgumentParser(
                    prog='eval_quant_model_on_test',
                    description='Evaluates quantized model on test set',
                    epilog='Thanks 4 using me!')
parser.add_argument('--model_path', type=str, help='Path to model', required=True)
args = parser.parse_args()


dataset_name = "."
x_test, y_test = np.load(f"{dataset_name}/testfeat.npy"), np.load(f"{dataset_name}/testlab.npy")

def transform_data(dataset):
    return dataset[...,None]

x_test = transform_data(x_test)

def run_tflite_model(x_test, tflite_file):
    interpreter = tf.lite.Interpreter(model_path=str(tflite_file))
    interpreter.allocate_tensors()
    input_details = interpreter.get_input_details()[0]
    output_details = interpreter.get_output_details()[0]
    input_scale, input_zero_point = input_details["quantization"]
    proba = np.zeros((len(x_test),), dtype=float)
    x_test_trans = x_test*int(1/input_scale)+input_zero_point
    for i in range(len(x_test)):
        image = x_test_trans[i]
        image = np.expand_dims(image, axis=0).astype(input_details["dtype"])
        interpreter.set_tensor(input_details["index"], image)
        interpreter.invoke()
        output = interpreter.get_tensor(output_details["index"])
        proba[i] = output[0,0]
    return proba



tflite_model_quant_file = args.model_path
    
proba = run_tflite_model(x_test, tflite_model_quant_file)

preds = proba/2**8

#print(preds)

print(run_tflite_model(np.array([np.zeros_like(x_test[0])]), tflite_model_quant_file))
    
print(f"AUC: {sklearn.metrics.roc_auc_score(y_test, preds)}\n AP: {sklearn.metrics.average_precision_score(y_test, preds)}")


precision, recall, thresholds = sklearn.metrics.precision_recall_curve(y_test, preds)

fig, ((ax1,ax2),(ax3,ax4)) = plt.subplots(2,2,figsize=(12,10))

ax1.plot(thresholds, precision[:-1], label= "Precision")
ax1.plot(thresholds, recall[:-1], label= "Recall")
ax1.set_ylabel("Metric [/]")
ax1.set_xlabel("Threshold [/]")
ax1.legend()

ax2.set_ylabel("Precision [/]")
ax2.set_xlabel("Recall [/]")
ax2.plot(recall, precision)
ax2.set_ylim(0,1)

fpr, tpr, thresholds = sklearn.metrics.roc_curve(y_test, preds)

ax3.plot(thresholds, fpr, label= "FPR")
ax3.plot(thresholds, tpr, label= "TPR")
ax3.set_ylabel("Metric [/]")
ax3.set_xlabel("Threshold [/]")
ax3.legend()

ax4.set_ylabel("TPR [/]")
ax4.set_xlabel("FPR [/]")
ax4.plot(fpr, tpr)

plt.tight_layout()
plt.show()