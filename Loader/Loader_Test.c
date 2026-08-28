#include <Loader.h>
int main()
{
    char *train_URL = "URL";
    char *test_URL = "URL";
    char *test_label_URL = "URL";
    char *train_label_URL = "URL";

    Loader *loader = create_Loader(test_URL, test_label_URL, train_URL, train_label_URL);

    // load_train_samples(loader,784,60000);
    load_training_labels(loader, 60000);
}