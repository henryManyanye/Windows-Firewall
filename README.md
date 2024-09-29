HERE'S how it works:
1. It blocks all outbound traffic
2. It only allows outbound traffic, on all network interfaces, to sites that a user selects

NOTES:
make sure that there are no third party firewall managers installed. In my case there was a MacAfee manager that came with the operating system. My firewall started working after i uninstalled it.

ALSO RUN THE EXE FILE AS ADMINISTRATOR



HOW TO COMPILE FOR THE x86 COMMAND LINE:
	csc -platform:x86  userInterface.cs

	cl -LD resolvePath.cpp

	cl /EHsc preUserInterface.cpp


HOW TO RUN THE FIREWALL:
	preUserInterface.exe WHICH IN TURN STARTS firewall.exe
	

	DON'T RUN 32 BIT EXECUTABLES ON A 64 BIT MACHINE BECAUSE SHELL LINK RESOLVING CODE WILL PRODUCE FAKE RESULTS

 TO DO:
 	class icons pg 159 [Windows and Messages]
 	class background brush pg 159 [Windows and Messages]
 		SetSysColors function pg 680 [Windows and Messages (2)]

 	AddFontResourceExA function
 	EnumFontFamiliesExA function
