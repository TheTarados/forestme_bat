### How to use

To treat a file ```mm-dd-hhhmm```, run 
```
python Annotation_generation/bin_to_wavs.py --input ./mm-dd-hhhmm --base G:/
```
This will populate ```G:/wavs``` with .wav files which are slices of the ```mm-dd-hhhmm``` file.

To annotate those .wav files, run
```
python Annotation_generation/full_chain.py --name mm-dd-hhhmm --base G:/
```

The following line needs to be added to [main.csv](./main.csv):
```
mm_dd_hhhmm.csv wavs_mm_dd_hhhmm
```

This main.csv will be accessed by [Dataset_generation](../Dataset_generation/) to know where the data is stored. Note the index of this line as it will be used in both [Dataset_generation](../Dataset_generation/) and [Model_generation](../Model_generation/) to select specific data to separate train and test set.