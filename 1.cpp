#include <cstring>
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) return 0;

	const char* calibrationText = argv[1];
	size_t calibrationTextLength = strlen(calibrationText);
	size_t calibrationTextLastIndex = calibrationTextLength - 1;

	int firstDigit = -1, lastDigit = -1, sum = 0;
	char calibrationChar;
	int calibrationCharValue;
	for (size_t i = 0; i < calibrationTextLength; i++) {
		calibrationChar = calibrationText[i];
		if (calibrationChar == '\n' || i == calibrationTextLastIndex) {
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

	std::cout << sum << std::endl;
	return 0;
}
