#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int main(int argc, char **argv) {
	if (argc != 2) return 0;

	std::ifstream fileStream(argv[1]);
	if (fileStream.is_open()) {
		const std::unordered_map<std::string, int> digitCharacters = {
			{ "1", 1 }, { "one", 1 },
			{ "2", 2 }, { "two", 2 },
			{ "3", 3 }, { "three", 3 },
			{ "4", 4 }, { "four", 4 },
			{ "5", 5 }, { "five", 5 },
			{ "6", 6 }, { "six", 6 },
			{ "7", 7 }, { "seven", 7 },
			{ "8", 8 }, { "eight", 8 },
			{ "9", 9 }, { "nine", 9 }
		};

		int firstDigit = -1, lastDigit = -1, sum = 0, idx = 0;
		std::string fileStreamLine;
		std::map<int, int> digits;
		while(std::getline(fileStream, fileStreamLine)) {
			for (const auto& kv : digitCharacters) {
				idx = fileStreamLine.find(kv.first);
				if (idx == -1) continue;
				digits[idx] = kv.second;

				idx = fileStreamLine.rfind(kv.first);
				digits[idx] = kv.second;
			}
			
			if (digits.begin() != digits.end()) {
				firstDigit = digits.begin()->second;
			}

			if (digits.rbegin() != digits.rend()) {
				lastDigit = digits.rbegin()->second;
			}

			if (lastDigit < 0) {
				lastDigit = firstDigit;
			}
			
			sum += firstDigit * 10 + lastDigit;
			digits.clear();
		}

		std::cout << sum << std::endl;
		fileStream.close();
	}


	return 0;
}
