# What is ForestMEvBat?

ForestMEvBat is the repository containing the code base produced for the Thomas ANTOINE's master thesis. The project is based on [ForestMEv2-public](https://forge.uclouvain.be/nbrusselmans/forestmev2-public) by Nicolas BRUSSELMANS. 

The project is separated between 4 folders:
- [Embedded_sw](Embedded_sw): the STM project to program the board
- [Annotation_generation](Annotation_generation): transform raw binary data into a usable sound clip dataset and generate annotations
- [Dataset_generation](Dataset_generation): contains all the logic to transform sound clips into a dataset
- [Model_generation](Model_generation): train and evaluate a model on the generated dataset

There is also [2D_serial_plotter.py](2D_serial_plotter.py) which can be used to plot the livestream of features generated by the system.

# How to use
## Embedded Software
The STM project can be opened with [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html). [batext.h](./Embedded_sw/Core/Inc/batext.h) contains compiler-level variables to control the behaviour of the system. Two modes are available:

+ Save raw audio: used to collect audio data, either on the microSD card on via the UART. In 
+ Execution: The system detects bat calls on the microphone and saves timestamps. Timestamps are printed via the UART when pushing the button 2.

In both cases, the system starts when pressing button 1.

[batext.c](./Embedded_sw/Core/Src/batext.c) contains all the code for features generation calls XCUBE-AI functions to apply inference.

## Machine learning framework

All python codes should be called from the command line, from the root of the project. Each file contains a readme explaining how to use it.

Use of [pipenv](https://pipenv.pypa.io/en/latest/) is advised, run ```pipenv install``` to install all dependencies of the project.

The framework has been tested on both Windows and Arch Linux.

A typical workflow to use the framework would be:
- Collect audio data in the form of multiple binary files
- Go to Annotation_generation to treat the audio data
- Go to Dataset_generation to generate a test set from a subset of the binary files (the other will serve as train sets)
- Use Model_generation to train on files not used for test set and evaluate on test set.
- Finally, return to Dataset_generation to evaluate the performance of the generated model using the simulator

Most scripts have multiple parameters which can be used to customize execution. Run ```script.py --help``` to see a list with a description.

Note that wavs that compose the dataset will be store in a single "wavs" folder. In our examples, we will use "G:/" as path but any valid path is accepted. In our example, there should thus be a valid "G:/wavs".