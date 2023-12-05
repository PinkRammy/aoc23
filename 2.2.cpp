#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define GAME_DELIMITER ": "
#define GAME_SET_DELIMITER "; "

int main(int argc, char **argv) {
	if (argc != 2) return 0;

	std::ifstream fileStream(argv[1]);
	if (fileStream.is_open()) {
		int red = 0, green = 0, blue = 0, sum = 0, value = 0;
		int findIndex;
		
		std::string temp;
		std::string fileStreamLine;
		std::vector<std::string> gameSets, gameSetParts;
		while (std::getline(fileStream, fileStreamLine)) {
			findIndex = fileStreamLine.find(GAME_DELIMITER);
			if (findIndex == -1) continue;

			temp = fileStreamLine.substr(findIndex + 2);
			findIndex = 0;
			gameSets.clear();
			while((findIndex = temp.find(GAME_SET_DELIMITER)) > -1) {
				gameSets.push_back(temp.substr(0, findIndex));
				temp = temp.substr(findIndex + 2);
			}
			gameSets.push_back(temp);

			red = green = blue = 0;
			findIndex = 0;
			for (auto it = gameSets.begin(); it != gameSets.end(); it++) {
				temp = *it;
				gameSetParts.clear();
				while((findIndex = temp.find(",")) > -1) {
					gameSetParts.push_back(temp.substr(0, findIndex));
					temp = temp.substr(findIndex + 2);
				}
				gameSetParts.push_back(temp);

				for (auto& gameSetPart : gameSetParts) {
					findIndex = gameSetPart.find(" red");
					if (findIndex > 0) {
						temp = gameSetPart.replace(findIndex, 4, "");
						value = stoi(temp);
						if (value > red) {
							red = value;
						}
					}

					findIndex = gameSetPart.find(" green");
					if (findIndex > 0) {
						temp = gameSetPart.replace(findIndex, 6, "");
						value = stoi(temp);
						if (value > green) {
							green = value;
						}
					}

					findIndex = gameSetPart.find(" blue");
					if (findIndex > 0) {
						temp = gameSetPart.replace(findIndex, 5, "");
						value = stoi(temp);
						if (value > blue) {
							blue = value;
						}
					}
				}
			}

			sum += red * green * blue;
		}

		std::cout << sum << std::endl;
		fileStream.close();
	}

	return 0;
}
