CC = gcc
CFLAGS = -Wall -g -ICustom_Matrices -IFunctions -INeural_Network_Model -ILoader -ITrainer

CORE_SRCS = Custom_Matrices/Matrices.c \
            Functions/ActivationFunctions.c \
            Functions/Initializations.c \
            Functions/LossFunctions.c \
            Neural_Network_Model/Layer.c \
            Neural_Network_Model/Model.c \
			Neural_Network_Model/Printing_Model.c \
			Loader/Loader.c \
			Neural_Network_Model/Printing_Model.c \
			Trainer/Trainer.c \
			Neural_Network_Model/Layer.c 


main: main.c $(CORE_SRCS)
	$(CC) $(CFLAGS) $^ -o main

test_matrices: Custom_Matrices/Matrices_Test.c Custom_Matrices/Matrices.c
	$(CC) $(CFLAGS) $^ -o test_matrices

test_loss: Functions/LossFunctions_Test.c Functions/LossFunctions.c Custom_Matrices/Matrices.c
	$(CC) $(CFLAGS) $^ -o test_loss -lm

test_loader: Loader/Loader_Test.c Functions/LossFunctions.c Custom_Matrices/Matrices.c Loader/Loader.c Neural_Network_Model/Printing_Model.c
	$(CC) $(CFLAGS) $^ -o test_loader -lm

test_model: Neural_Network_Model/Model_Test.c \
			Neural_Network_Model/Model.c \
			Neural_Network_Model/Layer.c \
			Custom_Matrices/Matrices.c\
			Functions/LossFunctions.c \
			Functions/Initializations.c \
			Functions/ActivationFunctions.c \
			Neural_Network_Model/Printing_Model.c
	$(CC) $(CFLAGS) $^ -o test_model -lm

test_trainer: Trainer/Trainer_Test.c \
			Neural_Network_Model/Model.c \
			Neural_Network_Model/Layer.c \
			Custom_Matrices/Matrices.c\
			Functions/LossFunctions.c \
			Functions/Initializations.c \
			Functions/ActivationFunctions.c \
			Loader/Loader.c \
			Neural_Network_Model/Printing_Model.c \
			Trainer/Trainer.c \


	$(CC) $(CFLAGS) $^ -o test_trainer -lm

clean:
	rm -f main test_matrices test_loss test_trainer test_model test_loader