#include <Model.h>

Model* create_Model(int input_size,int number_of_hidden_layers,int* layer_sizes,int output_size,
    double(*activation_function)(double val),double(*dactivation_function)(double val),
    Matrix* (*Mat_dactivation_function)(Matrix* matrix),
    void (*initializationFunction)(int input,int output,Matrix* matrix)
){

    assert(number_of_hidden_layers > 0);
    
    size_t length = 0;
    
    while(layer_sizes[length] != -1)length++;

    assert(length == number_of_hidden_layers);


    Layer* layers = malloc(sizeof(Layer) * (1+number_of_hidden_layers));

    layers[0] = *create_Layer(input_size,layer_sizes[0],activation_function,dactivation_function,Mat_dactivation_function,initializationFunction);

    
    for(int i = 0 ; i < length -1; i--){
        layers[i+1] = *create_Layer(layer_sizes[i],layer_sizes[i+1],activation_function,dactivation_function,Mat_dactivation_function,initializationFunction);
    }

    layers[length] = *create_Layer(layer_sizes[length-1],output_size,activation_function,dactivation_function,Mat_dactivation_function,initializationFunction);

    Model* model = malloc(sizeof (Model));

    model->input_size=input_size;

    int* clayer_sizes = malloc(sizeof(int) * number_of_hidden_layers);

    memcpy(clayer_sizes,layer_sizes,sizeof(int) * number_of_hidden_layers);
    model->layer_sizes = clayer_sizes;
    model->number_of_hidden_layers = length;
    model->output_size = output_size;
    model->layers = layers;

    return model;
}


double forward(Matrix* input, Model* Model,Matrix* reference){


    Matrix* WxI = matrix_dot(Model->layers[0].weights,input);

    Model->layers[0].z = matrix_add(WxI,Model->layers[0].biases);

    matrix_apply_activation(Model->layers[0].activations,Model->layers[0].z,Model->layers[0].activation_function);

    free(WxI);
    for(int i = 1 ; i <= Model->number_of_hidden_layers ; i++){
        Matrix* WxI = create_Matrix(Model->layers[i].weights->rows,Model->layers[i-1].activations->cols);

        WxI = matrix_dot(Model->layers[i].weights,Model->layers[i-1].activations);
    
        Model->layers[i].z = matrix_add(WxI,Model->layers[i].biases);
    
        matrix_apply_activation(Model->layers[i].activations,Model->layers[i].z,Model->layers[i].activation_function);

        free(WxI);
    }

    double error = MSE(Model->layers[Model->number_of_hidden_layers].activations,reference);

    return error;
    
}

void backward(Matrix* input,Model* model,Matrix* reference,double learning_rate){

    assert(model != NULL && reference != NULL);

        int L = model->number_of_hidden_layers;
        Matrix* dcost =  dMSE(model->layers[L].activations,reference);



        Matrix* do_dz = model->layers[L].Mat_dactivation_function(
            model->layers[L].activations);
        

        Matrix* dz_dw = matrix_transpose(model->layers[L-1].activations);
        
        
        Matrix* do_dz_x_dl_do  =  matrix_hadamard_product(dcost,do_dz);
        
        model->layers[L].dbiases = matrix_sum_axis(do_dz_x_dl_do);

        
        model->layers[L].dweights = matrix_dot(do_dz_x_dl_do,dz_dw);
        
        Matrix* stepw = matrix_multiply_scalar(-learning_rate,model->layers[L].dweights);
        Matrix* stepb = matrix_multiply_scalar(-learning_rate,model->layers[L].dbiases);

        Matrix* newW = matrix_add(model->layers[L].weights,stepw);
        Matrix* newb = matrix_add(model->layers[L].biases,stepb);

        free(model->layers[L].weights);
        free(model->layers[L].biases);

        model->layers[L].biases = newb;
        model->layers[L].weights = newW;

        free(dz_dw);
        free(model->layers[L].delta);
        model->layers[L].delta = do_dz_x_dl_do;
        free(stepw);
        free(stepb);  
        free(do_dz);      

    for(int i = L -1 ; i >= 1 ; i--){
        step(model->layers[i+1].delta
            ,model->layers[i+1].weights,model->layers[i-1].activations,&model->layers[i],learning_rate);
        printf("layer %d done\n",(i+1));
    }
    step(model->layers[1].delta
        ,model->layers[1].weights,input,&model->layers[0],learning_rate);
        // printf("mult went fine\n");

}

void step(Matrix* deltai_plus_1,Matrix* weight_i_plus_1,Matrix* prev_activations,Layer* layer,double learning_rate){
    
    layer->dactivations = layer->Mat_dactivation_function(layer->activations);

    Matrix* trans_weights =matrix_transpose(weight_i_plus_1);

    // printf("delta row -> %d delta col -> %d \n weight row -> %d weigh col -> %d\n",deltai_plus_1->rows,deltai_plus_1->cols,weight_i_plus_1->rows,weight_i_plus_1->cols);
    Matrix* first_half = matrix_dot(trans_weights,deltai_plus_1);
    
    layer->delta = matrix_hadamard_product(first_half,layer->dactivations);

    
    layer->dbiases = matrix_sum_axis(layer->delta);

    Matrix* trans_activations = matrix_transpose(prev_activations);

    layer->dweights = matrix_dot(layer->delta,trans_activations);


    Matrix* stepw = matrix_multiply_scalar(-learning_rate,layer->dweights);
    Matrix* stepb = matrix_multiply_scalar(-learning_rate,layer->dbiases);

    Matrix* newW = matrix_add(layer->weights,stepw);
    Matrix* newb = matrix_add(layer->biases,stepb);


    
    free(layer->weights);
    free(layer->biases);

    layer->biases = newb;
    layer->weights = newW;

    free(stepw);
    free(stepb); 
    free(trans_weights);
    free(first_half);
    free(layer->dactivations);
}