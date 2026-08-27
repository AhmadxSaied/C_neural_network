#include <Loader.h>

int main(){
    char* train_URL = "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-train-image.txt";
    char* test_URL = "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-test-image.txt";
    char* test_label_URL = "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-test-target.txt";
    char* train_label_URL = "/home/ahmed/Desktop/Main/projects/C_Neural_network/Trainer/archive/mnist_text_train_test/mnist-train-target.txt";
    
    Loader* loader = create_Loader(test_URL,test_label_URL,train_URL,train_label_URL);

    // load_train_samples(loader,784,60000);
    load_training_labels(loader,60000);
}