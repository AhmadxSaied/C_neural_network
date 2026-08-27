#include <Trainer.h>

Trainer* create_trainer(Model* model,Loader* loader,int epochs,int input_size,int samples,double learning_weight){
    assert(model != NULL && loader != NULL && epochs >= 0);


    Trainer* trainer = malloc(sizeof(Trainer));

    trainer->model = model;

    trainer->loader = loader;
    trainer->input_data = load_train_samples(trainer->loader,input_size,samples);
    trainer->output_data = load_test_samples(trainer->loader,input_size,samples);

    trainer->input_target = load_training_labels(trainer->loader,samples);
    trainer->output_target = load_test_labels(trainer->loader,samples);

    shuffle_columns(trainer->input_data,trainer->input_target);

    trainer->epochs = epochs;
    trainer->learning_weight = learning_weight;
    
    return trainer;
}

void Train(Trainer* trainer,int samples){

    int epochs = trainer->epochs;
    int i = 0;
    // printf("Hello");
    int total = 0;
    int correct = 0;
    while (i < epochs)
    {
     
        long long r1 = rand();
        long long r2 = rand();

        long long combined = (r1 * 327678LL + r2);
        int num = combined % trainer->input_data->cols;

        
        Matrix* input_sample = get_input(trainer->input_data,num);
        Matrix* output_sample = get_output(trainer->input_target,num);

        double error = forward(input_sample,trainer->model,output_sample);
        int prediction = backward(input_sample,trainer->model,output_sample,trainer->learning_weight);

        int tru = argmax(output_sample);

        if(isnan(error)){
            printf("NaN detected at layer %d, sample count %d\n", i, i);
            print_Model(trainer->model);
            exit(1);
        }
        if(prediction == tru)correct++;
        total++;
        if(i%1000 == 0){
            printf("error: %lf, predicted: %d and true label: %d\n",error,prediction,argmax(output_sample));
            trainer->learning_weight/=1.2;
        }
        i++;
        free_matrix(input_sample);
        free_matrix(output_sample);
    }
    printf("accuracy: %.2f%%\n", 100.0 * correct / total);
    
}


void free_Trainer(Trainer* trainer){
    if(trainer == NULL) return;
    free_Model(trainer->model);
    free_matrix(trainer->input_data);
    free_matrix(trainer->input_target);
    free_matrix(trainer->output_data);
    free_matrix(trainer->output_target);
    free_Loader(trainer->loader);

    free(trainer);
}