Arm-Project
Control for a prosthetic arm
======================================================================
Read the following to understand the data in this folder.
======================================================================


A) EMGClassifierData: 
[Data uploaded automatically to Drive by code when a person/subject performs test]
This data takes the form "TeamTerminatorDataDebug.txt", "TeamTerminatorData1.txt",
"TeamTerminatorData2.txt" etc.
where:
"TeamTerminatorDataDebug.txt" contains test/debug data (should be excluded from DataAnalysis)
"TeamTerminatorData1.txt" for 1,2... contains data from a subject for:
Rest position, Thumb contraction, index finger contraction etc.

Each contains 8 numbers (rep. EMG classifier data) from the 8 EMG sensor pods
The EMGPodLabel.png photo attached shows how these 8 values correspond to the physical Myo device.


B) RawEMGPlots:
This contains plots of the raw EMG data from the Myo.
The folders contained are fists, thumb contractions etc.
The index of the plots in each subfolder e.g 1.png, 2.png etc. correspond with the 
index of the files in classifier data.
i.e 1.png in fists, thumb etc. corresponds to data from the same subject in 
TeamTerminatorData1.txt and 2.png corresponds to data in TeamTerminatorData2.txt etc.


The code that implements (A) above can be found on GitHub at
https://github.com/Tunscopi/TerminatorArm-Project/tree/MakeEditsHere

IMPORTANT: If you decide to tinker/play around with this code,
Please stay away from the master branch (the link above takes you to a branch where you can make edits)
Feel free to make a "PULL REQUEST" to me if you had significant edits/suggestions
You are also welcome to make another branch for yourself and request "to PULL/MERGE" later
 
NB: Violation of these conditions would lead to blocking of said user or making the repository private!

Contact me with any further questions!
ayotundeodejayi@yahoo.com
