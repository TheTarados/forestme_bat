import numpy as np
import spectrogram as sp
import csv
from tqdm import tqdm

def enum_specs(indexes, wavs_path, args):
    with open('./Annotation_generation/main.csv', newline='') as csvfile:
        rowreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
        rows = list(rowreader)
        csv_list = [rows[index] for index in indexes]

    for csv_info in csv_list:
        print("Treating "+csv_info[0])
        with open(f"./annotations/{csv_info[0]}", newline='') as csvfile:
            rowreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
            csv_list = list(rowreader)
        column_name = csv_list[0]
        csv_list = csv_list[1:]
        last_path, last_spec = None, None
        
        for call_info in tqdm(csv_list):
            path = f"{wavs_path}{csv_info[1]}/{call_info[0]}"
            if path != last_path:
                if last_path != None:
                    
                    yield spec

                    #spec.plot_true()
                spec = sp.Spectrogram(path, args)
            else:
                spec = last_spec
            spec.add_call(*call_info[3:7])
            
            last_path, last_spec = path, spec
    
def read_time_log(path):
    result = []
    with open(path) as fi:
            for l in fi.readlines():
                value = int(l)
                result.append(((value>>24)*60 + ((value>>16)&0xFF))*60 + ((value>>8)&0xFF) + ((255-(value&0xFF))/255))

    return np.array(result)