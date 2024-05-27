import subprocess
import shutil
import argparse

parser = argparse.ArgumentParser(
                    prog='summarizer',
                    description='Summarize a folder full of CSVs into a single csv',
                    epilog='Thanks 4 using me!')

parser.add_argument('--base', required=True, type = str, help="Directory in which the wavs directory can be found")
parser.add_argument('--name', default = "mm_dd_hhhmm", type = str, help="name of the session (default=mm_dd_hhhmm)")
parser.add_argument('--thresh', default = .6, type = float, help="Probability threshold of calls kept (default=.6)")
args = parser.parse_args()

base = args.base
name = args.name
threshold = args.thresh

shutil.rmtree(f"./annotations/annot_{name}/", ignore_errors = True)

com_det = ["batdetect2", "detect", f"{base}wavs/wavs_{name}/", f"./annotations/annot_{name}/", f"{threshold}", "--time_expansion_factor", "10"]
com_sum = ["python", "Annotation_generation/summarizer.py", "--name", f"{name}", "--output", "annotations/", "--input", f"./annotations/annot_{name}/"]

process = subprocess.Popen(com_det)
process.wait()
if process.returncode != 0:
    print("Error running generation")
    exit()
process = subprocess.Popen(com_sum)
process.wait()
shutil.rmtree(f"./annotations/annot_{name}/")