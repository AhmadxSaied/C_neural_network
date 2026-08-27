#include <Model.h>
#include <Loader.h>
typedef struct trainer {
    Model* model;
    Matrix* input_data;
    Matrix* input_target;
    Matrix* output_data;
    Matrix* output_target;
    int epochs;
    Loader* loader;
} Trainer;


Trainer* create_trainer(Model* model,Loader* loader,int epochs,int input_size,int samples){
    assert(model != NULL && loader != NULL && epochs >= 0);


    Trainer* trainer = malloc(sizeof(Trainer));

    trainer->model = model;

    
    trainer->input_data = load_train_samples(loader,input_size,samples);
    trainer->output_data = load_test_samples(loader,input_size,samples);

    trainer->input_target = load_training_labels(loader,samples);
    trainer->output_target = load_test_labels(loader,samples);

    trainer->epochs = epochs;
}

void Train(Trainer* trainer){

    int epochs = trainer->epochs;

    while (epochs--)
    {
        
    }
    
}
