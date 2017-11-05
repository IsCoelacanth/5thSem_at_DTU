#include <iostream>
#include <cmath>

float FP[][3] = {
	3,  4,  6,
	4,  5,  7,
	3,  4,  6,
	7, 10, 15,
	5,  7, 10
};

int main() {
	float inp[5];
	int complex = 0;
	float ufp = 0, caf = 0;
	float influence[14];
	std::cout << "Enter inputs, outputs, enquiries, files, and external interfaces:\n";
	std::cin >> inp[0] >> inp[1] >> inp[2] >> inp[3] >> inp[4];

	std::cout << "Enter Complexity [0-low] [1-average] [2-high]:\n";
	std::cin >> complex;

	std::cout << "Answer following questions 0-5:\n";
	std::string questions[14] = {
		"Number of communication facilities to aid transfer or exchange of information with the application or system?",
		"How are distributed data and processing functions handled?",
		"Was response time or throughput required by the user?",
		"How heavily used is the current hardware platform where the application will be executed?",
		"How frequently are transactions executed daily, weekly, monthly, etc.?",
		"What percentage of the information is entered On-Line?",
		"Was the application designed for end-user efficiency?",
		"How many ILF's are updated by On-Line transaction?",
		"Does the application have extensive logical or mathematical processing?",
		"Was the application developed to meet one or many user's needs?",
		"How difficult is conversion and installation?",
		"How effective and/or automated are start-up, back-up, and recovery procedures?",
		"Was the application specifically designed, developed, and supported to be installed at multiple sites for multiple organizations?",
		"Was the application specifically designed, developed, and supported to facilitate change?"
	};
	for (int i = 0; i<14; i++) {
		std::cout << questions[i] << " ";
		std::cin >> influence[i];
	}


	for (int i = 0; i<5; i++) {
		ufp += FP[i][complex] * inp[i];
	}

	for (int i = 0; i<14; i++) {
		caf += influence[i];
	}
	caf *= 0.01;
	caf += 0.65;
	std::cout << "\nUFP = " << ufp << "\nCAF = " << caf << "\nFP = " << ufp*caf << std::endl;

	return 0;
}
