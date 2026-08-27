# Pip No Install NN

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Makefile](https://img.shields.io/badge/makefile-%23000000.svg?style=for-the-badge&logo=gnu-bash&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green.svg?style=for-the-badge)

A lightweight, modular Neural Network library built entirely from scratch in **C**.

This library is built with modularity in mind. You can easily write your own C files and integrate them by simply following the provided header file interfaces.

---

## Modules Architecture

### 1. Custom Matrices (`Custom_Matrices`)

A highly optimized custom matrix representation that uses a **1D array under the hood** for better memory caching and performance.

**Matrix Structure:**

- `row`, `cols`, `data` (1D array)

**Essential Operations:**

- Matrix multiplication, addition, and broadcast addition
- Matrix transpose & Hadamard product
- Multiply by a scalar
- `argmax` function
- Getters, setters, and memory deallocation (`free`)

**Initialization:**

```c
Matrix* matrix = create_Matrix(cols, rows);
```

### 2. Core Functions (`Functions`)

Modular mathematical functions required for the neural network.

- **Activation Functions:** Sigmoid, ReLU
- **Loss Functions & Derivatives:** Mean Squared Error (MSE), Cross Entropy Loss
- **Weight Initializations:** He Initialization, Xavier Initialization

### 3. Custom Loader (`Loader`)

A utility module specifically built to read the MNIST dataset (text version).

- Expects the dataset path in `./Trainer/archive`

**Initialization:**

```c
Loader* loader = create_Loader(test_URL, test_label_URL, train_URL, train_label_URL);

```

### 4. Layer (`Neural_Network_Model`)

Holds the matrices needed for weights, biases, and intermediate calculations, along with function pointers to activations, derivatives, and initialization functions.

**Layer Properties:**

- Number of neurons
- `weights` & `biases`
- `z` (weighted sum) and `activation` (activation(weighted sum))
- `delta` (for backpropagation), `dweight`, & `dbiases`
- Function pointers for double and matrix derivative applications
- Creation and memory freeing (`free`) functions

**Initialization:**

```c
Layer* create_Layer(int layer_neurons, int nextlayer_neurons,int batch_size,double(*activation_function)(double val),double(*dactivation_function)(double val),Matrix* (*Mat_dactivation_function)(Matrix* matrix),
void (*initializationFunction)(int input,int output,Matrix* matrix))
```

### 5. Model (`Neural_Network_Model`)

The core struct that connects layers together and manages the forward/backward passes.

**Model Properties:**

- `input size`, `output size`
- `number of hidden layers` & sizes (using `-1` as a sentinel final value, e.g., `{X, X, X, -1}`)
- Array holding all layers
- `batch size`
- Loss function and its derivative
- **Operations:** Forward pass (returns error), Backward pass (backpropagation), Step function (matrix updates), and memory freeing.

**Initialization:**

```c
Model* create_Model(int input_size,int number_of_hidden_layers,int* layer_sizes,
    int output_size,int batch_size,
    double(*activation_function)(double val),double(*dactivation_function)(double val),
    Matrix* (*Mat_dactivation_function)(Matrix* matrix),
    void (*initializationFunction)(int input,int output,Matrix* matrix),
    double (*lossfunction)(Matrix* output,Matrix* reference),
    Matrix* (*dlossfunction)(Matrix* output,Matrix* reference)
)

```

### 6. Trainer (`Trainer`)

Manages the training loop, dataset loading, and model evaluation.

**Trainer Properties:**

- `model`, `epochs`, `learning rate`
- `loader`
- `input data`, `input labels` (Train)
- `test data`, `test labels` (Test)
- **Operations:** `Train()` (takes trainer and sample count), `Test()` (takes trainer and test sample count).

**Initialization:**

```c
Trainer* trainer = create_trainer(model, loader, EPOCHS, INPUT_SIZE, TRAIN_SAMPLES, LEARNING_RATE;

```

# Running test files

Makefile inside root file provides all possible compilation needed to run the tests

`How to run a test`

```bash
  make test_trainer test_loader test_model test_loss test_matrices
  make clean
```

---

# How to install

- clone the repo
- install the data you want to train on and add it to Trainer/archive
- make your main file and type make in your terminal

* run the object code

```bash
git clone <https://github.com/AhmadxSaied/C_Neural_network>
cd C_Neural_network
make
./Trainer_Test
```

- If you dont want make a main file you can type the bash bellow and run the model on mnist hand-drawn digits dataset.
- The model parameters are hand picked after several attempts
- The accuracy of the model is below
  - Batch size was 32 and trained on all data set
  - Training accuracy: 92.96%
  - Test accuracy: 96.10%

```bash
make test_trainer
./test_trainer
```

---

# Valgrind memory leak analysis for library

```bash
==303929== HEAP SUMMARY:
==303929==     in use at exit: 0 bytes in 0 blocks
==303929==   total heap usage: 2,035 allocs, 2,035 frees, 10,255,256 bytes allocated
```

---

## 📂 File Tree

```text
C_Neural_network
├── Custom_Matrices
│   ├── Matrices.c
│   ├── Matrices.h
│   └── Matrices_Test.c
├── Functions
│   ├── ActivationFunctions.c
│   ├── ActivationFunctions.h
│   ├── Initializations.c
│   ├── Initializations.h
│   ├── LossFunctions.c
│   ├── LossFunctions.h
│   └── LossFunctions_Test.c
├── Loader
│   ├── Loader.c
│   ├── Loader.h
│   └── Loader_Test.c
├── Neural_Network_Model
│   ├── Layer.c
│   ├── Layer.h
│   ├── Model.c
│   ├── Model.h
│   ├── Model_Test.c
│   ├── Printing_Model.c
│   └── Printing_Model.h
├── Trainer
│   ├── archive
│   ├── Trainer.c
│   ├── Trainer.h
│   └── Trainer_Test.c
├── .gitignore
├── README.md
└── makefile

```
