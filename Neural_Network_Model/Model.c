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

    Layer* temp = create_Layer(input_size,layer_sizes[0],activation_function,dactivation_function,Mat_dactivation_function,initializationFunction);
    layers[0] = *temp;
    free(temp);
    
    for(int i = 0 ; i < length -1; i++){
        
        Layer* temp = create_Layer(layer_sizes[i],layer_sizes[i+1],activation_function,dactivation_function,Mat_dactivation_function,initializationFunction);
        layers[i+1] = *temp;
        free(temp);
    }

    Layer* templast = create_Layer(layer_sizes[length-1],output_size,activation_function,dactivation_function,Mat_dactivation_function,initializationFunction);
    layers[length] = *templast;
    free(templast);

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
    free_matrix(Model->layers[0].z);
    Model->layers[0].z = matrix_add(WxI,Model->layers[0].biases);

    matrix_apply_activation(Model->layers[0].activations,Model->layers[0].z,Model->layers[0].activation_function);

    free_matrix(WxI);
    for(int i = 1 ; i <= Model->number_of_hidden_layers ; i++){
        Matrix* WxI = matrix_dot(Model->layers[i].weights,Model->layers[i-1].activations);
    
        free_matrix(Model->layers[i].z);
        Model->layers[i].z = matrix_add(WxI,Model->layers[i].biases);
    
        matrix_apply_activation(Model->layers[i].activations,Model->layers[i].z,Model->layers[i].activation_function);

        free_matrix(WxI);
    }

    double error = MSE(Model->layers[Model->number_of_hidden_layers].activations,reference);

    return error;
    
}

int backward(Matrix* input,Model* model,Matrix* reference,double learning_rate){

    assert(model != NULL && reference != NULL);

        int L = model->number_of_hidden_layers;
        Matrix* dcost =  dMSE(model->layers[L].activations,reference);


        Matrix* do_dz = model->layers[L].Mat_dactivation_function(
            model->layers[L].activations);
        

        Matrix* dz_dw = matrix_transpose(model->layers[L-1].activations);
        
        
        Matrix* do_dz_x_dl_do  =  matrix_hadamard_product(dcost,do_dz);
        
        free_matrix(model->layers[L].dbiases);
        model->layers[L].dbiases = matrix_sum_axis(do_dz_x_dl_do);

        free_matrix(model->layers[L].dweights);
        model->layers[L].dweights = matrix_dot(do_dz_x_dl_do,dz_dw);
        
        Matrix* stepw = matrix_multiply_scalar(-learning_rate,model->layers[L].dweights);
        Matrix* stepb = matrix_multiply_scalar(-learning_rate,model->layers[L].dbiases);

        Matrix* newW = matrix_add(model->layers[L].weights,stepw);
        Matrix* newb = matrix_add(model->layers[L].biases,stepb);

        free_matrix(model->layers[L].weights);
        free_matrix(model->layers[L].biases);

        model->layers[L].biases = newb;
        model->layers[L].weights = newW;

        free_matrix(dz_dw);
        free_matrix(model->layers[L].delta);
        model->layers[L].delta = do_dz_x_dl_do;
        free_matrix(stepw);
        free_matrix(stepb);  
        free_matrix(do_dz);  
        free_matrix(dcost);

    for(int i = L -1 ; i >= 1 ; i--){
        step(model->layers[i+1].delta
            ,model->layers[i+1].weights,model->layers[i-1].activations,&model->layers[i],learning_rate);
        // printf("layer %d done\n",(i+1));
    }
    step(model->layers[1].delta
        ,model->layers[1].weights,input,&model->layers[0],learning_rate);

        return argmax(model->layers[L].activations);
}

void step(Matrix* deltai_plus_1,Matrix* weight_i_plus_1,Matrix* prev_activations,Layer* layer,double learning_rate){
    
    free_matrix(layer->dactivations);
    layer->dactivations = layer->Mat_dactivation_function(layer->activations);

    Matrix* trans_weights = matrix_transpose(weight_i_plus_1);

    // printf("delta row -> %d delta col -> %d \n weight row -> %d weigh col -> %d\n",deltai_plus_1->rows,deltai_plus_1->cols,weight_i_plus_1->rows,weight_i_plus_1->cols);
    Matrix* first_half = matrix_dot(trans_weights,deltai_plus_1);
    
    free_matrix(layer->delta);
    layer->delta = matrix_hadamard_product(first_half,layer->dactivations);

    free_matrix(layer->dbiases);
    layer->dbiases = matrix_sum_axis(layer->delta);

    Matrix* trans_activations = matrix_transpose(prev_activations);

    free_matrix(layer->dweights);
    layer->dweights = matrix_dot(layer->delta,trans_activations);


    Matrix* stepw = matrix_multiply_scalar(-learning_rate,layer->dweights);
    Matrix* stepb = matrix_multiply_scalar(-learning_rate,layer->dbiases);

    Matrix* newW = matrix_add(layer->weights,stepw);
    Matrix* newb = matrix_add(layer->biases,stepb);


    
    free_matrix(layer->weights);
    free_matrix(layer->biases);

    layer->biases = newb;
    layer->weights = newW;

    free_matrix(stepw);
    free_matrix(stepb); 
    free_matrix(trans_weights);
    free_matrix(first_half);
    free_matrix(trans_activations);
}

void free_Model(Model* model){
    if(model == NULL) return;
    
    int total_layers = model->number_of_hidden_layers + 1;
    for(int i = 0; i < total_layers; i++){

        free_Layer_contents(&model->layers[i]);
    }
    free(model->layers);
    free(model->layer_sizes); 
    free(model);
}
