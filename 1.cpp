#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) return 0;

	std::ifstream fileStream(argv[1]);
	if (fileStream.is_open()) {
		int firstDigit = -1, lastDigit = -1, sum = 0;
		char calibrationChar; int calibrationCharValue;

		while(fileStream) {
			calibrationChar = fileStream.get();
			if (calibrationChar == '\n') {
				if (lastDigit < 0) lastDigit = firstDigit;
				sum += firstDigit * 10 + lastDigit;
				firstDigit = -1;
				lastDigit = -1;
				continue;
			}

			calibrationCharValue = calibrationChar - '0';
			if (calibrationCharValue > 9) continue;

			if (firstDigit < 0) {
				firstDigit = calibrationCharValue;
				continue;
			}

			lastDigit = calibrationCharValue;
		}

		if (firstDigit > 0) {
			if (lastDigit < 0) lastDigit = firstDigit;
			sum += firstDigit * 10 + lastDigit;
		}

		std::cout << sum << std::endl;
	}

	return 0;
}
