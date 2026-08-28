#include <Trainer.h>

int *get_indices(int b, int batch_size)
{
    int *indices = malloc(sizeof(int) * batch_size);
    for (int i = 0; i < (batch_size); i++)
    {
        indices[i] = b + i;
    }
    return indices;
}

Trainer *create_trainer(Model *model, Loader *loader, int epochs, int input_size, int input_samples, int test_samples, double learning_weight)
{
    assert(model != NULL && loader != NULL && epochs >= 0);

    Trainer *trainer = malloc(sizeof(Trainer));

    trainer->model = model;

    trainer->loader = loader;
    trainer->input_data = load_train_samples(trainer->loader, input_size, input_samples);
    trainer->test_data = load_test_samples(trainer->loader, input_size, test_samples);

    trainer->input_target = load_training_labels(trainer->loader, input_samples);
    trainer->test_target = load_test_labels(trainer->loader, test_samples);

    trainer->epochs = epochs;
    trainer->learning_weight = learning_weight;

    return trainer;
}

void Train(Trainer *trainer, int input_samples)
{

    int epochs = trainer->epochs;
    int n = 0;
    // printf("Hello");
    int total = 0;
    int correct = 0;
    int batches = input_samples / trainer->model->batch_size;

    while (n < epochs)
    {
        double epoch_error = 0;
        shuffle_columns(trainer->input_data, trainer->input_target);
        int inner_total = 0;
        int inner_correct = 0;
        for (int b = 0; b < batches; b++)
        {

            int start_col = b * trainer->model->batch_size;
            int *indices = get_indices(start_col, trainer->model->batch_size);
            Matrix *input_sample = get_input(trainer->input_data, indices, trainer->model->batch_size);
            Matrix *output_sample = get_output(trainer->input_target, indices, trainer->model->batch_size);

            double error = forward(input_sample, trainer->model, output_sample);
            int *prediction = backward(input_sample, trainer->model, output_sample, trainer->learning_weight);
            int *tru = argmax(output_sample);

            epoch_error += error;

            if (isnan(error))
            {
                printf("NaN detected at layer %d, sample count %d\n", b, b);
                print_Model(trainer->model);
                exit(1);
            }
            for (int i = 0; i < trainer->model->batch_size; i++)
            {
                // printf("i=%d: tru=%d, pred=%d\n", i, tru[i], prediction[i]);
                if (tru[i] == prediction[i])
                {
                    inner_correct++;
                }
                inner_total++;
            }
            free_matrix(input_sample);
            free_matrix(output_sample);
            free(indices);
            free(prediction);
            free(tru);
        }
        trainer->learning_weight /= 1.01;

        correct += inner_correct;
        total += inner_total;
        printf("ratio : %d / %d \n", inner_correct, inner_total);
        printf("epochs: %d, avg_error: %lf\n", n, epoch_error / batches);
        n++;
    }
    printf("accuracy: %.2f%%\n", 100.0 * correct / total);
}

void Test(Trainer *trainer, int test_samples)
{

    // printf("Hello");
    int total = 0;
    int correct = 0;
    int batches = test_samples / trainer->model->batch_size;

    for (int b = 0; b < batches; b++)
    {

        int start_col = b * trainer->model->batch_size;
        int *indices = get_indices(start_col, trainer->model->batch_size);
        Matrix *input_sample = get_input(trainer->test_data, indices, trainer->model->batch_size);
        Matrix *output_sample = get_output(trainer->test_target, indices, trainer->model->batch_size);

        forward(input_sample, trainer->model, output_sample);

        for (int col = 0; col < trainer->model->batch_size; col++)
        {
            int *colholder = malloc(sizeof(int));
            colholder[0] = col;
            Matrix *one_output = get_output(trainer->model->layers[trainer->model->number_of_hidden_layers].activations, colholder, 1);
            Matrix *one_target = get_output(output_sample, colholder, 1);

            int *predicted = argmax(one_output);
            int *actual = argmax(one_target);

            if (predicted[0] == actual[0])
                correct++;
            total++;

            free_matrix(one_output);
            free_matrix(one_target);
            free(colholder);
            free(predicted);
            free(actual);
        }

        free_matrix(input_sample);
        free_matrix(output_sample);
        free(indices);
    }

    printf("accuracy: %.2f%%\n", 100.0 * correct / total);
}

void free_Trainer(Trainer *trainer)
{
    if (trainer == NULL)
        return;
    free_Model(trainer->model);
    free_matrix(trainer->input_data);
    free_matrix(trainer->input_target);
    free_matrix(trainer->test_data);
    free_matrix(trainer->test_target);
    free_Loader(trainer->loader);

    free(trainer);
}