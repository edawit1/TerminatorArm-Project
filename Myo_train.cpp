// Entry point for Myo data training
// Entry point for Myo data training

#include "floatfann.h"
#include "fann_cpp.h"

#include <ios>
#include <iostream>
#include <iomanip>

int main()
{
	const unsigned int num_input = 80;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 20;
	const float desired_error = (const float) -1;  //Default- 0.001
	const unsigned int max_epochs = 500000;
	const unsigned int epochs_between_reports = 500;

	struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_train_on_file(ann, "C:\\Users\\Ayotunde\\Documents\\Visual Studio 2013\\Projects\\fann-master\\fann-master\\examples\\Myo.data", max_epochs, epochs_between_reports, desired_error);

	fann_save(ann, "Myo.net");

	fann_destroy(ann);

	system("pause");
	return 0;
}
