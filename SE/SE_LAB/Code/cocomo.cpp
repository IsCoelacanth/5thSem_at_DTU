#include <iostream>
#include <cmath>
float COCOMO[][4] = {
	2.4, 1.05, 2.5, 0.38,
	3.0, 1.12, 2.5, 0.35,
	3.6, 1.20, 2.5, 0.32
};
int main() {
	float loc;
	int type = 0;
	float E, D;
	std::cout << "Enter lines of code in 1000s: ";
	std::cin >> loc;
	if (loc > 50)
		type = 1;
	if (loc > 300)
		type = 2;

	E = COCOMO[type][0] * pow(loc, COCOMO[type][1]);
	D = COCOMO[type][2] * pow(E, COCOMO[type][3]);

	std::cout << "\nProject is ";
	switch (type) {
	case 0: {
		std::cout << "Organic";
		break;
	}
	case 1: {
		std::cout << "Semi detached";
		break;
	}
	case 2: {
		std::cout << "Embedded";
		break;
	}
	}
	std::cout << "\nE = " << E << "\nD = " << D << std::endl;

	return 0;
}
