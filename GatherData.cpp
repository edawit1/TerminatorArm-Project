// Modified Version of emg-sample-data.cpp (Copyright (C) 2013-2014 Thalmic Labs Inc. Distributed under the Myo SDK license agreement, LICENSE.txt)
// Howard University Terminator Arm Senior Design 2015.

// Dependencies:
// 1. MyoConnect
// 2. Infile.txt (Containing dynamic final part of output data file)

// Description:
// This is used solely for gathering our EMG classifier data. The rest of the code for the project is separate from this.
// EMG streaming is only supported for one Myo at a time
// Terminator Myo MAC address: db-fa-0c-69-14-78 (Can be used alternatively instead of MyoConnect to attach our Myo to a Hub)
// http://diagnostics.myo.com/ provides diagnostic data of Myo (connected in MyoConnect) on a pc 
// NB: Replacing system("cls") is advised.

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "windows.h"   // contains Sleep library

#include <myo/myo.hpp>            // Myo default header library

// DataCollector class inheriting member functions from myo::DeviceListener
class DataCollector : public myo::DeviceListener {
public:
	DataCollector(): emgSamples()
	{}

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user
	void onUnpair(myo::Myo* myo, uint64_t timestamp)
	{
		// We've lost our Myo.
		// Let's clean up some leftover state.
		emgSamples.fill(0);
	}

	// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled
	void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
	{
		for (int i = 0; i < 8; i++) {
			emgSamples[i] = emg[i];
		}
	}

	void stayUnlocked(myo::Myo* myo)
	{}

	// The values of this array is set by onEmgData() above
	std::array<int8_t, 8> emgSamples;

	// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData()
	// For this application, the functions overridden above are sufficient
	std::string SerialIndex, update = "gesture";
	std::ofstream TerminatorFile;
	std::string filepath = "C:\\Users\\Ayotunde\\Google Drive\\Team Terminator\\Data Analysis\\EMGClassifierData\\TeamTerminatorData";  
	int NewLineflag = 0;

	// We define this function to write the current values that were updated by the on...() functions above
	void writeData(std::string gesture)
	{
		// Create and open dynamic outfile 
		std::string filename = filepath + SerialIndex + ".txt";  
		TerminatorFile.open(filename, std::ofstream::app);  
		
		// Write current gesture to outfile
		if (update != gesture){
			TerminatorFile << "\n" << gesture << "\n"; update = gesture;
		}

		// Clear the current line
		std::cout << '\r';
		// write out the EMG classifier data
		for (size_t i = 0; i < emgSamples.size(); i++) {
			std::ostringstream oss;
			oss << static_cast<int>(emgSamples[i]);
			std::string emgString = oss.str();
			
			if (NewLineflag == 1){
				TerminatorFile << "\n";
				NewLineflag = 0;
			}

			// Write to outfile
			TerminatorFile << emgString << " ";
		}
		NewLineflag = 1;
		std::cout << std::flush;
		TerminatorFile.close();       // flush buffer to outfile
	}
};


int main(int argc, char** argv)
{
	// Declare & open infile 
	std::ifstream Serialfile;    
	Serialfile.open("Infile.txt");

	// Define test gestures
	std::string gestures[12] = { "*REST/RELAX* position", "*(THUMB)* contraction", "*REST/RELAX* position", "*(INDEX fing.)* contraction", "*REST/RELAX* position",
		"*(MIDDLE fing.)* contraction", "*REST/RELAX* position", "*(RING fing.)* contraction", "*REST/RELAX* position",
		"*(PINKY fing.)* contraction", "*REST/RELAX* position", "*(HAND)* contraction" };

	// We catch any exceptions that might occur below -- see the catch statement for more details
	try {

		// First, we create a Hub without any application identifier, the Hub provides access to one or more Myos
		myo::Hub hub("");

		std::cout << "Attempting to find HU Terminator Myo..." << std::endl;

		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo immediately
		// waitForMyo() takes a timeout value in milliseconds. We try to find Terminator Myo for 10 seconds, and
		// if that fails, the function will return a null pointer
		myo::Myo* myo = hub.waitForMyo(10000);

		// If waitForMyo() returned a null pointer, we failed to find our Myo, so exit with an error message
		if (!myo) {
			throw std::runtime_error("Unable to find HU Terminator Myo! \nCheck MyoConnect!");
		}

		// We've found our Myo
		std::cout << "Connected to HU Terminator Myo!" << std::endl << std::endl;

		// Next we enable EMG streaming on the found Myo
		myo->setStreamEmg(myo::Myo::streamEmgEnabled);

		myo->unlockHold;

		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub
		DataCollector collector;
		
		// Generate index of subject for file writing purposes
		while (!Serialfile.eof())
		Serialfile >> collector.SerialIndex;

		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners
		hub.addListener(&collector);

		// Set console font parameters
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 16;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		std::cout << "Please follow the instructions to provide gestural data!" << std::endl;
		std::cout << "Allow a couple seconds while Terminator Myo warms up to arm... " << std::endl << std::endl;
		Sleep(3000);             // suspend execution of current/active thread for time-argument

		// Finally we enter our main loop.
		for (int i = 0; i < sizeof(gestures)/sizeof(*gestures); i++){
			system("cls");

			std::cout << std::endl; std::cout << "\t\t Perform:  " << gestures[i] << " for (3) secs" << std::endl;

			// Get current CPU time
			double startTime = GetTickCount();      
			double currentTime = 0;

			// Get data for 3 seconds
			while (currentTime <= 3000)
			{
				// In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds
				// In this case, we wish to update our display 50 times a second. (Myo provides EMG at 200Hz and IMU data at 50Hz and is unaffected by display rates)
				hub.run(1000/20);

				// After processing events, we call the writeData() function to write new data to our outfile
				collector.writeData(gestures[i]);

				// Update CPU time for iteration purposes
				currentTime = GetTickCount() - startTime;
			}
						
		}

		// Tidy up & End program
		std::cout << "Saving Data... " << std::endl;
		system("cls");
		std::cout << "\n     *****  Thank you for helping out HU Team Terminator!  *****\n\n";
		std::cout << "                           From Ayo & Mark!           \n\n";
		Sleep(3000);
		return 0;

	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}
}
