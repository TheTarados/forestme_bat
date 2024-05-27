
import numpy as np
import dataset_reader as dr
import argparse
from joblib import Parallel, delayed
parser = argparse.ArgumentParser(
                    prog='Spectrogram class',
                    description='Computes datasets',
                    epilog='Thanks 4 using me!')

parser.add_argument('--files', nargs='+', help='Files to tread as index in main.csv', required=True)
parser.add_argument('--base', type = str, help="Directory in which the wavs directory can be found", required=True)
parser.add_argument('--test', default = "n", type = str, help="y/n, is it the test set that we generate (default=n)")
parser.add_argument('--spec_size', default = 10, type = int, help="Number of melvec in a spectrogram (default=10)")
parser.add_argument('--spec_time', default = 9e-3, type = float, help="Time contained in 1 spectrogram (default=9e-3)")
parser.add_argument('--sample_window_size', default = 9, type = int, help="log_2 of fft size (default=9)")
parser.add_argument('--mel_bin', default = 20, type = int, help="Number of frequency bin (default=20)")
parser.add_argument('--n_shifts', default = 1, type = int, help="Number of spec per call (default=1, -1 means all possible specs)")
parser.add_argument('--spec_hop', default = None, type = int, help="Sample skipped between two spectrograms (default=None, Size of a vector)")
parser.add_argument('--seed', default = 0xDEADBEEF, type = int, help="Seed for random parts (default=0xDEADBEEF)")

args = parser.parse_args()


N_SPEC_PER_CALL = args.n_shifts

np.random.seed(args.seed)
factor_bias = 1
wavs_path = f"{args.base}wavs/"
files = [int(i) for i in args.files]

def treat_file(file):
    features = []
    labels = []
    missings = 0
    for spec in dr.enum_specs([file], wavs_path, args):
        tn, tp = spec.get_true_and_false()
        n_tp = 0
        for trues in tp:
            n_tp += min(len(trues), N_SPEC_PER_CALL)
        
        indices = np.random.choice(len(tn), min(factor_bias*n_tp*N_SPEC_PER_CALL+missings, len(tn)), replace=False)
        missings += factor_bias*n_tp*N_SPEC_PER_CALL-len(indices)
        features.append(tn[indices])
        labels.append(np.zeros(factor_bias*n_tp*N_SPEC_PER_CALL))
        for trues in tp:
            if len(trues) > 0:
                ind = np.random.choice(len(trues), min(len(trues), N_SPEC_PER_CALL), replace=False)
                features.append(trues[ind])
                
        labels.append(np.ones(n_tp*N_SPEC_PER_CALL))
        
    features = np.concatenate(features)
    labels = np.concatenate(labels)
    return features, labels

result =  Parallel(n_jobs=len(files))(delayed(treat_file)(i) for i in files)

features = [result[i][0] for i in range(len(result))]
labels = [result[i][1] for i in range(len(result))]

feats = np.concatenate([features[i] for i in range(len(features))])
labs = np.concatenate([labels[i] for i in range(len(labels))])

name = "test" if args.test == "y" else "train"
np.save(f"{name}feat.npy", feats)
np.save(f"{name}lab.npy", labs)