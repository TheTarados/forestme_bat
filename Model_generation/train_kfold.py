import sys
import numpy as np
np.set_printoptions(threshold=sys.maxsize)
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow.keras import layers, models
import matplotlib.pyplot as plt
from tqdm import tqdm
from sklearn.model_selection import KFold
from joblib import Parallel, delayed
import sklearn.metrics
import argparse

def transform_data(dataset):
    return (dataset[...,None])


parser = argparse.ArgumentParser(
                    prog='otrain',
                    description='Will train a model and return its AUC',
                    epilog='Thanks 4 using me!')

parser.add_argument('--filter1', default = 4, type = int, help="Number of filters for 1st convolution layer (default=4)")
parser.add_argument('--filter2', default = 4, type = int, help="Number of filters for 2nd convolution layer (default=4)")
parser.add_argument('--epoch', default = 20, type = int, help="Number of epoch to train the model (default=20)")
parser.add_argument('--kernel1', default = 3, type = int, help="Size of kernel of 1st convolutional layer (default=3)")
parser.add_argument('--kernel2', default = 3, type = int, help="Size of kernel of 2nd convolutional layer (default=3)")
parser.add_argument('--lr', default = 1e-3, type = float, help="Learning rate (default=1e-3)")
parser.add_argument('--split', default = 10, type = int, help="Number of K-Fold splits (default=10)")
parser.add_argument('--retry', default = 5, type = int, help="Number of times this is done (metrics mean and std are returned) (default=5)")
args = parser.parse_args()
N_EPOCH = args.epoch
L_RATE = args.lr

N_FILTER_1 = args.filter1
N_FILTER_2 = args.filter2

KERNEL_1 = args.kernel1
KERNEL_2 = args.kernel2

RETRAIN = False
PRINT_BOARD_DEBUG = False
X, y = np.load(f"./trainfeat.npy"), np.load(f"./trainlab.npy")
X = transform_data(X)


def run_kfold():
    probs = np.empty_like(y)
    answer = np.empty_like(y)
    i = 0

    N_SPLITS = args.split
    for train_index, test_index in tqdm(KFold(N_SPLITS, shuffle=True).split(X)):
        x_train, x_test = X[train_index], X[test_index]
        y_train, y_test = y[train_index], y[test_index]

        input_shape = x_train[0].shape

        model = models.Sequential()
        model.add(layers.InputLayer( input_shape=input_shape))#, dtype = np.int8
        model.add(layers.Conv2D(N_FILTER_1, (KERNEL_1, KERNEL_1), activation='relu'))
        model.add(layers.MaxPooling2D((2, 2)))
        model.add(layers.Conv2D(N_FILTER_2, (KERNEL_2, KERNEL_2), activation='relu'))
        model.add(layers.MaxPooling2D((2, 2)))
        model.add(layers.Flatten())
        model.add(layers.Dense(28, activation='relu'))
        model.add(layers.Dense(1, activation='sigmoid'))

        loss_fn = tf.keras.losses.BinaryCrossentropy()

        model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate = L_RATE),
                    loss=loss_fn,
                    metrics=[ tf.keras.metrics.AUC(name="ROC_Area"),
                                tf.keras.metrics.RecallAtPrecision(0.95, name = "Recall At 0.95 prec")])
        
        history =model.fit(x_train, y_train, epochs=N_EPOCH, verbose = 0)
        preds = model.predict(x_test)
        probs[i: i+len(preds)] = preds[:,0]
        answer[i: i+len(preds)] = y_test
        i+= len(preds)


            
    return (sklearn.metrics.roc_auc_score(answer, probs), sklearn.metrics.average_precision_score(answer, probs))

metrics = Parallel(n_jobs=args.retry)(delayed(run_kfold)() for _ in range(args.retry))
metrics = np.array(metrics)

AUC = metrics[:, 0]
AP = metrics[:, 1]
out= f"AP {AP.mean()}+-{AP.std()} AUC {AUC.mean()}+-{AUC.std()}"

sys.stdout.write(out)
sys.stdout.flush()

