// Header file "Myo_Fann.h"
#include <iostream>
#include <stdio.h>
#include "C:\Users\Ayotunde\Documents\Visual Studio 2013\Projects\fann-master\fann-master\src\include\floatfann.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include "C:\Users\Ayotunde\Documents\Visual Studio 2013\Projects\fann-master\fann-master\src\include\fann_cpp.h"
#include <ios>
#include <iomanip>

using namespace std;

namespace Myo_Fann
{
	class TerminatorMyo_Fann
	{
	public:
		const static bool toCalibrate = 1;  // Set user mode i.e calibration w/user data or run on Stored data
		const static int datasize = 240;    // datasize for training and testing

		// Member functions
		static void Myo_Train();  // Trains ann w/ either Calibration or general user collected data
		static fann_type Myo_Test(fann_type input[datasize]);   // Uses trained "Myo.net" file 
	};
}
