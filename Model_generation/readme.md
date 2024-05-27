To evaluate the performance in training on file 1 and 2 in [main.csv](../Annotation_generation/main.csv), run
```
python Model_generation/parameter_exploration.py --files 1 2 --base G:/
```
This will also generate the trainset. You can THEN run

```
python Model_generation/train_and_save.py
```
This will generate a .keras file of the model and a .tflite model of the quantized model.

To evaluate the model, run
```
python Model_generation/eval_model_on_test.py --model_path model.keras
```

To evaluate the quantized model, run
```
python Model_generation/eval_quant_model_on_test.py --model_path model_quantized.tflite 
```