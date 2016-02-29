// Myo_Fann.cpp "Implementation file"
#include "Myo_Fann.h"

namespace Myo_Fann
{
	void TerminatorMyo_Fann::Myo_Train()
	{// Trains the Neural Network "Myo.net"
		// Parameters
		const unsigned int num_input = 80;
		const unsigned int num_output = 1;
		const unsigned int num_layers = 3;
		const unsigned int num_neurons_hidden = 20;
		const float desired_error = (const float)-1;  //Default- 0.001
		const unsigned int max_epochs = 200000;
		const unsigned int epochs_between_reports = 500;

		struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

		fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
		fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

		// Trains w/ entire dataset or individual data
		if (TerminatorMyo_Fann::toCalibrate){
			fann_train_on_file(ann, "C:\\Users\\Ayotunde\\Documents\\Visual Studio 2013\\Projects\\fann-master\\fann-master\\examples\\MyoCal.data", max_epochs, epochs_between_reports, desired_error);
			std::cout << "Calibrating with user data! \n\n";
		}
		else{
			fann_train_on_file(ann, "C:\\Users\\Ayotunde\\Documents\\Visual Studio 2013\\Projects\\fann-master\\fann-master\\examples\\Myo.data", max_epochs, epochs_between_reports, desired_error);
			std::cout << "Calibrating with stored general data! \n\n";
		}
		fann_save(ann, "Myo.net");

		fann_destroy(ann);
	}

	fann_type TerminatorMyo_Fann::Myo_Test(fann_type input[80])
	{
		// Uses/Tests the Neural Network 
		fann_type *calc_out;

		struct fann *ann = fann_create_from_file("Myo.net");

		calc_out = fann_run(ann, input);

		return calc_out[0];
	}

}
