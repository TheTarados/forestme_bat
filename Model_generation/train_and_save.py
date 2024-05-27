import sys
import numpy as np
np.set_printoptions(threshold=sys.maxsize)
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow.keras import layers, models
import matplotlib.pyplot as plt
import argparse

def transform_data(dataset):
    return (dataset[...,None])


parser = argparse.ArgumentParser(
                    prog='otrain',
                    description='Will train a model and save it + save an 8-bit quantized version',
                    epilog='Thanks 4 using me!')

parser.add_argument('--model_name', default = "model", type = str, help="Name of the saved model (default=model)")
parser.add_argument('--filter1', default = 4, type = int, help="Number of filters for 1st convolution layer (default=4)")
parser.add_argument('--filter2', default = 4, type = int, help="Number of filters for 2nd convolution layer (default=4)")
parser.add_argument('--epoch', default = 20, type = int, help="Number of epoch to train the model (default=20)")
parser.add_argument('--kernel1', default = 3, type = int, help="Size of kernel of 1st convolutional layer (default=3)")
parser.add_argument('--kernel2', default = 3, type = int, help="Size of kernel of 2nd convolutional layer (default=3)")
parser.add_argument('--lr', default = 1e-3, type = float, help="Learning rate (default=1e-3)")
args = parser.parse_args()

N_EPOCH = args.epoch
L_RATE = args.lr

N_FILTER_1 = args.filter1
N_FILTER_2 = args.filter2

KERNEL_1 = args.kernel1
KERNEL_2 = args.kernel2


X, y = np.load(f"./trainfeat.npy"), np.load(f"./trainlab.npy")
X = transform_data(X)

input_shape = X[0].shape

model = models.Sequential()
model.add(layers.InputLayer( input_shape=input_shape))#, dtype = np.int8
model.add(layers.Conv2D(N_FILTER_1, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Conv2D(N_FILTER_2, (3, 3), activation='relu'))
model.add(layers.MaxPooling2D((2, 2)))
model.add(layers.Flatten())
model.add(layers.Dense(28, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

loss_fn = tf.keras.losses.BinaryCrossentropy()

model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate = L_RATE),
            loss=loss_fn)

history =model.fit(X, y, epochs=N_EPOCH)

tflite_model_file = f"{args.model_name}.keras"
model.save(tflite_model_file)
def representative_dataset():

    my_very_representative_dataset = np.random.choice((-128, 127), X.shape)
  
    img = tf.data.Dataset.from_tensor_slices(X.astype(np.float32)).batch(1)
    for i in img.take(len(my_very_representative_dataset)):
        yield [i]

converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = tf.lite.RepresentativeDataset(representative_dataset)
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.uint8
tflite_quant_model = converter.convert()
tflite_model_quant_file = f"{args.model_name}_quantized.tflite"
open(tflite_model_quant_file, "wb").write(tflite_quant_model)