#include <Loader.h>

Loader *create_Loader(char *test_URL, char *test_label_URL, char *train_URL, char *train_label_URL)
{

    Loader *loader = malloc(sizeof(Loader));

    loader->test_URL = strdup(test_URL);
    loader->train_URL = strdup(train_URL);
    loader->train_label_URL = strdup(train_label_URL);
    loader->test_label_URL = strdup(test_label_URL);
    return loader;
}

Matrix *load_train_samples(Loader *loader, int input_size, int samples)
{
    char *URL = loader->train_URL;

    FILE *file = fopen(URL, "r");
    Matrix *result = NULL;
    if (file == NULL)
    {
        printf("File didnt open successfully");
    }
    else
    {

        double *data = malloc(sizeof(double) * input_size);
        int index = 0;
        double value = 0;
        result = create_Matrix(input_size, samples);
        int sample_num = 0;
        while (fscanf(file, "%lf%*[, \t\n]", &value) == 1)
        {

            data[index++] = value / 255.0;

            if (index == input_size)
            {

                if (sample_num >= samples)
                {
                    printf("Warning: more samples in file than expected (%d), stopping early\n", samples);
                    break;
                }

                for (int j = 0; j < input_size; j++)
                {
                    matrix_cell_set(data[j], j, sample_num, result);
                }
                index = 0;
                sample_num++;
            }
        }
        free(data);
    }
    fclose(file);

    // for(int j = 0 ; j < input_size;j++){
    //     printf("value: %lf\n",matrix_cell_get(j,0,result));
    // }
    return result;
}

Matrix *load_training_labels(Loader *loader, int samples)
{
    char *URL = loader->train_label_URL;

    FILE *file = fopen(URL, "r");
    Matrix *result = NULL;
    if (file == NULL)
    {
        printf("File didnt open successfully");
    }
    else
    {

        int index = 0;
        double value = 0;
        result = create_Matrix(10, samples);
        while (fscanf(file, "%lf%*[, \t\n]", &value) == 1)
        {

            if (index >= samples)
            {
                printf("Warning: more samples in file than expected (%d), stopping early\n", samples);
                break;
            }

            matrix_cell_set(1, (int)(value), index, result);
            index++;
        }
    }
    fclose(file);

    // for(int j = 0 ; j < 10;j++){
    //     printf("value: %lf\n",matrix_cell_get(j,0,result));
    // }
    return result;
}

Matrix *load_test_samples(Loader *loader, int input_size, int samples)
{
    char *URL = loader->test_URL;

    FILE *file = fopen(URL, "r");
    Matrix *result = NULL;
    if (file == NULL)
    {
        printf("File didnt open successfully");
    }
    else
    {

        double *data = malloc(sizeof(double) * input_size);
        int index = 0;
        double value = 0;
        result = create_Matrix(input_size, samples);
        int sample_num = 0;
        while (fscanf(file, "%lf%*[, \t\n]", &value) == 1)
        {

            data[index++] = value / 255.0;

            if (index == input_size)
            {

                if (sample_num >= samples)
                {
                    printf("Warning: more samples in file than expected (%d), stopping early\n", samples);
                    break;
                }

                for (int j = 0; j < input_size; j++)
                {
                    matrix_cell_set(data[j], j, sample_num, result);
                }
                index = 0;
                sample_num++;
            }
        }
        free(data);
    }
    fclose(file);

    // for(int j = 0 ; j < input_size;j++){
    //     printf("value: %lf\n",matrix_cell_get(j,0,result));
    // }
    return result;
}

Matrix *load_test_labels(Loader *loader, int samples)
{
    char *URL = loader->test_label_URL;

    FILE *file = fopen(URL, "r");
    Matrix *result = NULL;
    if (file == NULL)
    {
        printf("File didnt open successfully");
    }
    else
    {

        int index = 0;
        double value = 0;
        result = create_Matrix(10, samples);
        while (fscanf(file, "%lf%*[, \t\n]", &value) == 1)
        {

            if (index >= samples)
            {
                printf("Warning: more samples in file than expected (%d), stopping early\n", samples);
                break;
            }

            matrix_cell_set(1, (int)value, index, result);
            index++;
        }
    }
    fclose(file);

    // for(int j = 0 ; j < 10;j++){
    //     printf("value: %lf\n",matrix_cell_get(j,0,result));
    // }
    return result;
}
void free_Loader(Loader *loader)
{
    if (loader == NULL)
        return;

    free(loader->train_URL);
    free(loader->test_URL);
    free(loader->test_label_URL);
    free(loader->train_label_URL);
    free(loader);
}
