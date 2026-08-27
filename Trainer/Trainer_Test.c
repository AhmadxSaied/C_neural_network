#include <Trainer.h>
#include <Model.h>
#include <Loader.h>
#include <ActivationFunctions.h>
#include <Initializations.h>
#define INPUT_SIZE 784
#define HIDDEN_LAYERS 3
#define OUTPUT 10
#define TRAIN_URL  "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-train-image.txt"
#define TEST_URL  "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-test-image.txt"
#define TEST_LABEL_URL "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-test-target.txt"
#define TRAIN_LABEL_URL  "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-train-target.txt"
#define EPOCHS 30
#define TRAIN_SAMPLES 60000
#define TEST_SAMPLES 10000
#define LEARNING_RATE_MSE 0.001
#define LEARNING_RATE_CE 0.75
#define BATCH_SIZE 32
int main(){
    srand(time(NULL));
    int LAYERS[] = {64,32,16,-1};
    Model* model = create_Model(INPUT_SIZE,HIDDEN_LAYERS,LAYERS,OUTPUT,BATCH_SIZE,relu,drelu,dreluMat,He_Initialization,MSE,dMSE);

    char* train_URL = TRAIN_URL;
    char* test_URL = TEST_URL;
    char* test_label_URL = TEST_LABEL_URL;
    char* train_label_URL = TRAIN_LABEL_URL;
    

    Loader* loader = create_Loader(test_URL,test_label_URL,train_URL,train_label_URL);

    Trainer* trainer = create_trainer(model,loader,EPOCHS,INPUT_SIZE,TRAIN_SAMPLES,LEARNING_RATE_MSE);
    Train(trainer,TRAIN_SAMPLES);
    Test(trainer,TEST_SAMPLES);
    free_Trainer(trainer);
}