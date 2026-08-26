CC = gcc
CFLAGS = -Wall -g -ICustom_Matrices -IFunctions -INeural_Network_Model

CORE_SRCS = Custom_Matrices/Matrices.c \
            Functions/ActivationFunctions.c \
            Functions/Initializations.c \
            Functions/LossFunctions.c \
            Neural_Network_Model/Layer.c \
            Neural_Network_Model/Model.c \
			Neural_Network_Model/Printing_Model.c


main: main.c $(CORE_SRCS)
	$(CC) $(CFLAGS) $^ -o main

test_matrices: Custom_Matrices/Matrices_Test.c Custom_Matrices/Matrices.c
	$(CC) $(CFLAGS) $^ -o test_matrices

test_loss: Functions/LossFunctions_Test.c Functions/LossFunctions.c Custom_Matrices/Matrices.c
	$(CC) $(CFLAGS) $^ -o test_loss

test_model: Neural_Network_Model/Model_Test.c \
			Neural_Network_Model/Model.c \
			Neural_Network_Model/Layer.c \
			Custom_Matrices/Matrices.c\
			Functions/LossFunctions.c \
			Functions/Initializations.c \
			Functions/ActivationFunctions.c \
			Neural_Network_Model/Printing_Model.c
	$(CC) $(CFLAGS) $^ -o test_model -lm

clean:
	rm -f main test_matrices test_loss