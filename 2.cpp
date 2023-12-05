#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14
#define GAME_DELIMITER ": "
#define GAME_SET_DELIMITER "; "

int main(int argc, char **argv) {
	if (argc != 2) return 0;

	std::ifstream fileStream(argv[1]);
	if (fileStream.is_open()) {
		int value = 0, sum = 0;
		int findIndex, gameIndex;
		bool validGameSet;

		std::string temp;
		std::string fileStreamLine;
		std::vector<std::string> gameSets, gameSetParts;
		while (std::getline(fileStream, fileStreamLine)) {
			findIndex = fileStreamLine.find(GAME_DELIMITER);
			if (findIndex == -1) continue;

			temp = fileStreamLine.substr(0, findIndex);
			gameIndex = stoi(temp.substr(5));

			temp = fileStreamLine.substr(findIndex + 2);
			findIndex = 0;
			gameSets.clear();
			while((findIndex = temp.find(GAME_SET_DELIMITER)) > -1) {
				gameSets.push_back(temp.substr(0, findIndex));
				temp = temp.substr(findIndex + 2);
			}
			gameSets.push_back(temp);

			findIndex = 0;
			for (auto it = gameSets.begin(); it != gameSets.end(); it++) {
				temp = *it;
				gameSetParts.clear();
				while((findIndex = temp.find(",")) > -1) {
					gameSetParts.push_back(temp.substr(0, findIndex));
					temp = temp.substr(findIndex + 2);
				}
				gameSetParts.push_back(temp);

				validGameSet = true;
				for (auto& gameSetPart : gameSetParts) {
					findIndex = gameSetPart.find(" red");
					if (findIndex > 0) {
						temp = gameSetPart.replace(findIndex, 4, "");
						value = stoi(temp);
						if (value > MAX_RED) {
							validGameSet = false;
							break;
						}
					}

					findIndex = gameSetPart.find(" green");
					if (findIndex > 0) {
						temp = gameSetPart.replace(findIndex, 6, "");
						value = stoi(temp);
						if (value > MAX_GREEN) {
							validGameSet = false;
							break;
						}
					}

					findIndex = gameSetPart.find(" blue");
					if (findIndex > 0) {
						temp = gameSetPart.replace(findIndex, 5, "");
						value = stoi(temp);
						if (value > MAX_BLUE) {
							validGameSet = false;
							break;
						}
					}
				}

				if (!validGameSet) {
					break;
				}
			}

			if (validGameSet) {
				sum += gameIndex;
			}
		}

		std::cout << sum << std::endl;
		fileStream.close();
	}

	return 0;
}
