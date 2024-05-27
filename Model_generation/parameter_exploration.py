import subprocess
import platform
import pandas as pd
import numpy as np

import argparse
parser = argparse.ArgumentParser(
                    prog='Spectrogram class',
                    description='Computes datasets',
                    epilog='Thanks 4 using me!')

parser.add_argument('--files', nargs='+', help='Files to tread as index in main.csv', required=True)
parser.add_argument('--base', type = str, help="Directory in which the wavs directory can be found", required=True)

args = parser.parse_args()
files = args.files
base = args.base

filter1s = [4]
filter2s = [4]
kernel1s = [3]
kernel2s = [3]

spec_sizes = [10]
mel_bins = [20]
sample_window_sizes = [9]
spec_times = np.array([9])*1e-3
seeds = [0xDEADBEEF, 0xABCDEFAB, 0xBACABACA, 0xACABACAB, 0xACABDEAD]
n_calls = [1]
ksplits = 20
retry = 5
epoch = 15

df = pd.DataFrame(columns = ["filter1", "filter2", "kernel1", "kernel2", "spec_size", "mel_bin", "sample_window_size", "spec_time","seed", "AP and AUC"])

# Check OS for command
pyt = "python" if platform.system() == "Windows" else "python3"
for sample_window_size in sample_window_sizes:
    for mel_bin in mel_bins:
        for spec_time in spec_times:
            for spec_size in spec_sizes:
                for n_call in n_calls:
                    for seed in seeds:
                        process = subprocess.Popen(["python", "./Dataset_generation/run_generation.py", "--files", *files, "--base",  str(base), "--spec_size", str(spec_size), "--mel_bin", str(mel_bin), "--sample_window_size", str(sample_window_size), "--spec_time", str(spec_time), "--n_shifts", str(n_call), "--seed", str(seed)])
                        process.wait()
                        if process.returncode != 0:
                            print("Error running generation")
                            exit()
                        for kernel2 in kernel2s:
                            for kernel1 in kernel1s:
                                for filter2 in filter2s:
                                    for filter1 in filter1s:
                                        print(f"Computing for {[filter1, filter2, kernel1, kernel2, spec_size, mel_bin, sample_window_size, spec_time ]}")
                                        process = subprocess.Popen(["python", "./Model_generation/train_kfold.py",  "--retry", str(retry), "--epoch", str(epoch), "--filter1", str(filter1), "--filter2", str(filter2), "--kernel1", str(kernel1), "--kernel2", str(kernel2), "--split", str(ksplits)], stdout=subprocess.PIPE, universal_newlines=True)
                                        process.wait()
                                        stdout, stderr = process.communicate()
                                        df.loc[len(df.index)] = [filter1, filter2, kernel1, kernel2, spec_size, mel_bin, sample_window_size, spec_time, seed, stdout.split("\n")[-1]]
                                        df.to_csv("./Enumerate result.csv")