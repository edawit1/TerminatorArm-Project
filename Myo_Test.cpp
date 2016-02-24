// Entry point for Myo data testing

#include <stdio.h>
#include "floatfann.h"
#include <iostream>
#include <fstream>
#include <string>

int submain()
{
	// Open and read datafile 
	std::ifstream datafile;
	datafile.open("C:\\Users\\Ayotunde\\Documents\\Visual Studio 2013\\Projects\\fann-master\\fann-master\\inputdata.txt");

	fann_type *calc_out;
	fann_type input[80];

	// Grab test data from infile
	for (int i = 0; i < 80; i++)
		datafile >> input[i];
	
	struct fann *ann = fann_create_from_file("Myo.net");

	calc_out = fann_run(ann, input);

	printf("Myo test results -> %f\n", calc_out[0]);
	
	std::cout << "\n" << std::endl;
	


	// Translate FANN gesture recognition efforts
	if (calc_out[0] <= 0.5) 
		std::cout << "\t\t ** Rest state! ** " << std::endl;
	if (calc_out[0] > 0.5 && calc_out[0] < 1.5) 
		std::cout << "\t\t ** Thumb Finger! **" << std::endl;
	if (calc_out[0] > 1.5 && calc_out[0] < 2.5) 
		std::cout << "\t\t ** Index Finger! **" << std::endl;
	if (calc_out[0] > 2.5 && calc_out[0] < 3.5) 
		std::cout << "\t\t ** Middle Finger! ** " << std::endl;
	if (calc_out[0] > 3.5 && calc_out[0] < 4.5) 
		std::cout << "\t\t ** Ring Finger! **" << std::endl;
	if (calc_out[0] > 4.5 && calc_out[0] < 5.5) 
		std::cout << "\t\t ** Pinky Finger! **" << std::endl;
	if (calc_out[0] >= 5.5) 
		std::cout << "\t\t ** Hand Gesture! **" << std::endl;
	
	std::cout << "\n" << std::endl;


	fann_destroy(ann);
	system("pause");
	return 0;
}
