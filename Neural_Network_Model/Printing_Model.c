#include <Printing_Model.h>

void print_Matrix(Matrix *matrix, const char *label)
{
    if (matrix == NULL)
    {
        printf("    %s: NULL\n", label);
        return;
    }
    printf("    %s (%dx%d):\n", label, matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; i++)
    {
        printf("      ");
        for (int j = 0; j < matrix->cols; j++)
        {
            int index = i * matrix->cols + j;
            printf("%8.4f ", matrix->data[index]);
        }
        printf("\n");
    }
}

void print_Layer(Layer *layer, int layer_index)
{
    printf("  --- Layer %d ---\n", layer_index);
    print_Matrix(layer->weights, "weights");
    print_Matrix(layer->biases, "biases");
    print_Matrix(layer->z, "z");
    print_Matrix(layer->activations, "activations");
    print_Matrix(layer->dweights, "dweights");
    print_Matrix(layer->dbiases, "dbiases");
}

void print_Model(Model *model)
{
    if (model == NULL)
    {
        printf("Model is NULL\n");
        return;
    }
    printf("=== Model ===\n");
    printf("input_size: %d\n", model->input_size);
    printf("number_of_hidden_layers: %d\n", model->number_of_hidden_layers);
    printf("output_size: %d\n", model->output_size);

    printf("layer_sizes: [");
    for (int i = 0; i < model->number_of_hidden_layers; i++)
    {
        printf("%d", model->layer_sizes[i]);
        if (i < model->number_of_hidden_layers - 1)
            printf(", ");
    }
    printf("]\n");

    int total_layers = model->number_of_hidden_layers + 1; // +1 for output transition
    for (int i = 0; i < total_layers; i++)
    {
        print_Layer(&model->layers[i], i);
    }
    printf("=== End Model ===\n");
}