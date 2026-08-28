#include "Matrices.h"
#include <stdio.h>

Matrix *create_Matrix(int rows, int cols)
{

    assert(rows > 0 && cols > 0);

    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->rows = rows;
    matrix->cols = cols;

    size_t totalsize = (size_t)rows * cols;

    matrix->data = malloc((totalsize * sizeof(double)));

    for (int i = 0; i < rows * cols; i++)
    {
        matrix->data[i] = 0;
    }

    return matrix;
}

Matrix *matrix_dot(Matrix *matrix_A, Matrix *matrix_B)
{
    if (matrix_A == NULL || matrix_B == NULL)
        return NULL;

    // printf("mata rows -> %d mata cols -> %d \n matb rows -> %d matb cols-> %d\n",matrix_A->rows,matrix_A->cols,matrix_B->rows,matrix_B->cols);

    assert(matrix_A->cols == matrix_B->rows);

    Matrix *result_matrix = create_Matrix(matrix_A->rows, matrix_B->cols);

    for (int i = 0; i < matrix_A->rows; i++)
    {

        for (int j = 0; j < matrix_B->rows; j++)
        {

            /// matrix_B->rows === matrix_A->cols
            int index_A = (i * matrix_A->cols) + j;

            for (int k = 0; k < matrix_B->cols; k++)
            {

                int index_B = (j * matrix_B->cols) + k;

                int result_index = (i * matrix_B->cols) + k;

                result_matrix->data[result_index] += matrix_A->data[index_A] * matrix_B->data[index_B];
            }
        }
    }
    return result_matrix;
}

Matrix *matrix_add(Matrix *matrix_A, Matrix *matrix_B)
{
    if (matrix_A == NULL || matrix_B == NULL)
        return NULL;
    assert(matrix_A->cols == matrix_B->cols && matrix_A->rows == matrix_B->rows);

    Matrix *result_matrix = create_Matrix(matrix_A->rows, matrix_B->cols);

    for (int i = 0; i < matrix_A->rows; i++)
    {
        for (int j = 0; j < matrix_A->cols; j++)
        {
            int index = i * matrix_A->cols + j;
            result_matrix->data[index] = matrix_A->data[index] + matrix_B->data[index];
        }
    }
    return result_matrix;
}

Matrix *matrix_add_1D_to_2D(Matrix *matrix_A, Matrix *matrix_B)
{
    if (matrix_A == NULL || matrix_B == NULL)
        return NULL;
    assert(matrix_A->rows == matrix_B->rows);

    Matrix *result_matrix = create_Matrix(matrix_A->rows, matrix_A->cols);

    for (int i = 0; i < matrix_A->rows; i++)
    {
        for (int j = 0; j < matrix_A->cols; j++)
        {
            int index_A = j + i * matrix_A->cols;
            result_matrix->data[index_A] = matrix_A->data[index_A] + matrix_cell_get(i, 0, matrix_B);
        }
    }
    return result_matrix;
}

int matrix_cell_set(double value, int i, int j, Matrix *matrix)
{
    if (matrix == NULL)
        return -1;
    int index = i * matrix->cols + j;
    assert(i >= 0 && i < matrix->rows);
    assert(j >= 0 && j < matrix->cols);

    matrix->data[index] = value;
    return 1;
}

double matrix_cell_get(int i, int j, Matrix *matrix)
{
    // printf("input rows=%d cols=%d, index=%d\n", matrix->rows, matrix->cols, i);
    assert(matrix != NULL);

    int index = i * matrix->cols + j;
    assert(i >= 0 && i < matrix->rows);
    assert(j >= 0 && j < matrix->cols);

    return matrix->data[index];
}

Matrix *matrix_multiply_scalar(double scale, Matrix *matrix)
{
    if (matrix == NULL)
        return NULL;

    int rows = matrix->rows;
    int cols = matrix->cols;

    Matrix *res_matrix = create_Matrix(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int index = i * cols + j;

            res_matrix->data[index] = matrix->data[index] * scale;
        }
    }
    return res_matrix;
}

Matrix *matrix_transpose(Matrix *matrix)
{
    if (matrix == NULL)
        return NULL;

    int cols = matrix->cols;
    int rows = matrix->rows;

    Matrix *transposed_matrix = create_Matrix(cols, rows);

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            int index_t = i * rows + j;

            int index_normal = j * cols + i;

            transposed_matrix->data[index_t] = matrix->data[index_normal];
        }
    }
    return transposed_matrix;
}

void matrix_zero(Matrix *matrix)
{
    assert(matrix != NULL);

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix_cell_set(0, i, j, matrix);
        }
    }
}

void matrix_apply_activation(Matrix *result_Matrix, Matrix *matrix, double (*activation)(double val))
{

    assert(matrix != NULL);
    assert(result_Matrix->cols == matrix->cols && result_Matrix->rows == matrix->rows);

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {

            int index = i * matrix->cols + j;

            result_Matrix->data[index] = activation(matrix->data[index]);
        }
    }
}

Matrix *matrix_hadamard_product(Matrix *matrix_A, Matrix *matrix_B)
{
    if (matrix_A == NULL || matrix_B == NULL)
        return NULL;
    assert(matrix_A->cols == matrix_B->cols && matrix_A->rows == matrix_B->rows);

    Matrix *result_matrix = create_Matrix(matrix_A->rows, matrix_B->cols);

    for (int i = 0; i < matrix_A->rows; i++)
    {
        for (int j = 0; j < matrix_A->cols; j++)
        {
            int index = i * matrix_A->cols + j;
            result_matrix->data[index] = matrix_A->data[index] * matrix_B->data[index];
        }
    }
    return result_matrix;
}

Matrix *matrix_sum_axis(Matrix *matrix, int batch_size)
{
    assert(matrix != NULL);

    Matrix *result_matrix = create_Matrix(matrix->rows, 1);

    for (int i = 0; i < matrix->rows; i++)
    {
        result_matrix->data[i] = 0;
        for (int j = 0; j < matrix->cols; j++)
        {
            result_matrix->data[i] += matrix->data[i * matrix->cols + j] / (double)batch_size;
        }
    }
    return result_matrix;
}

void swap_columns(Matrix *matrix, int col1, int col2)
{
    int rows = matrix->rows;

    for (int i = 0; i < rows; i++)
    {
        double temp = matrix_cell_get(i, col1, matrix);
        matrix_cell_set(matrix_cell_get(i, col2, matrix), i, col1,
                        matrix);
        matrix_cell_set(temp, i, col2, matrix);
    }
}

void shuffle_columns(Matrix *input, Matrix *labels)
{

    assert(input->cols == labels->cols);
    int cols = input->cols;
    for (int i = cols - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        if (i != j)
        {
            swap_columns(input, i, j);
            swap_columns(labels, i, j);
        }
    }
}

Matrix *get_input(Matrix *input, int *indices, int batch_size)
{
    Matrix *batch = create_Matrix(input->rows, batch_size);

    for (int samp = 0; samp < batch_size; samp++)
    {
        int index = indices[samp];
        // printf("idx[%d] = %d\n", samp, index);
        for (int i = 0; i < input->rows; i++)
        {
            matrix_cell_set(matrix_cell_get(i, index, input), i, samp, batch);
        }
    }
    return batch;
}
Matrix *get_output(Matrix *labels, int *indices, int batch_size)
{

    Matrix *batch = create_Matrix(labels->rows, batch_size);
    for (int samp = 0; samp < batch_size; samp++)
    {
        int index = indices[samp];
        for (int i = 0; i < labels->rows; i++)
        {
            matrix_cell_set(matrix_cell_get(i, index, labels), i, samp, batch);
        }
    }
    return batch;
}
void free_matrix(Matrix *matrix)
{
    if (matrix == NULL)
        return;
    free(matrix->data);
    free(matrix);
    matrix = NULL;
}

int *argmax(Matrix *matrix)
{

    int *results = malloc(sizeof(int) * matrix->cols);

    for (int j = 0; j < matrix->cols; j++)
    {
        int max_int = -1;
        double max_val = -1;

        for (int i = 0; i < matrix->rows; i++)
        {
            double val = matrix_cell_get(i, j, matrix);
            if (val > max_val)
            {
                max_val = val;
                max_int = i;
            }
        }
        results[j] = max_int;
    }
    return results;
}