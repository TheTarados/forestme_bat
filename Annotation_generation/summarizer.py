
import argparse

parser = argparse.ArgumentParser(
                    prog='summarizer',
                    description='Summarize a folder full of CSVs into a single csv',
                    epilog='Thanks 4 using me!')

parser.add_argument('--name', default = "", type = str, help="Name of the session file (default=\"\")")
parser.add_argument('--input', type = str, help="Input file")
parser.add_argument('--output', default = "", type = str, help="Output file (default=\"\")")
args = parser.parse_args()
name = args.name
path = args.input
from os import listdir

onlyfiles = [f for f in listdir(path) if f[-3:]=="csv"]

import csv

with open(f'{args.output}{name}.csv', 'w', newline='') as csvfile:
    spamwriter = csv.writer(csvfile, delimiter=' ',
                            quotechar='|', quoting=csv.QUOTE_MINIMAL)
    spamwriter.writerow(["file", "id","det_prob","start_time","end_time","high_freq","low_freq","class","class_prob"])
    for i in onlyfiles:
        with open(path+i, newline='') as readcsvfile:
            spamreader = csv.reader(readcsvfile, delimiter=',', quotechar='|')
            Temp = True
            for row in spamreader:
                if Temp:
                    Temp = False
                else:
                    spamwriter.writerow([i[:-4]]+row)