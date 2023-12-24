#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Symbol {
  int x;
  char value;
  bool isGear;
  int firstAdjacentNumber;
  int secondAdjacentNumber;

  int getAdjacentMinX() {
    return x == 0 ? 0 : x - 1;
  }

  int getAdjacentMaxX() {
    return x + 1;
  }
};

struct Number {
  int x;
  int value;
  int length;

  int getAdjacentMinX() {
    return x == 0 ? 0 : x - 1;
  }

  int getAdjacentMaxX() {
    return x + length;
  }
};

int getNumberLength(int value) {
  if (value <= 0) return 0;
  if (value < 10) return 1;
  if (value < 100) return 2;
  if (value < 1000) return 3;
  if (value < 10000) return 4;
  return 0;
}


std::unordered_map<int, std::vector<Symbol>> symbolsByLine;
std::unordered_map<int, std::vector<Number>> numbersByLine;

bool isNumberAdjacent(Number number, int minX, int maxX) {
  int numberMin = number.x;
  int numberMax = number.x + number.length - 1;

  if (numberMin >= minX && numberMin <= maxX) {
    return true;
  }

  if (numberMin <= maxX && numberMax >= minX) {
    return true;
  }

  return false;
}

void tryGetGearNumbers(int& firstNumber, int& secondNumber, int symbolMin, int symbolMax, std::vector<Number> numbers) {
  for (Number number : numbers) {
    if (!isNumberAdjacent(number, symbolMin, symbolMax)) continue;

    if (firstNumber == 0) {
      firstNumber = number.value;
      continue;
    }

    if (secondNumber == 0) {
      secondNumber = number.value;
      break;
    }
  }
}

int getGearRatio(int x1, int x2, int y) {
  int firstNumber = 0, secondNumber = 0;

  // search for adjacent number above
  if (y > 0) {
    auto numberIt = numbersByLine.find(y - 1);
    if (numberIt != numbersByLine.end()) {
      tryGetGearNumbers(firstNumber, secondNumber, x1, x2, numberIt->second);
    }
  }

  if (firstNumber > 0 && secondNumber > 0) {
    std::cout << firstNumber << " * " << secondNumber << std::endl;
    return firstNumber * secondNumber;
  }

  // search for adjacent number on same line
  auto numberIt = numbersByLine.find(y);
  if (numberIt != numbersByLine.end()) {
    tryGetGearNumbers(firstNumber, secondNumber, x1, x2, numberIt->second);
  }

  if (firstNumber > 0 && secondNumber > 0) {
    std::cout << firstNumber << " * " << secondNumber << std::endl;
    return firstNumber * secondNumber;
  }
  
  // search for adjacent number below
  numberIt = numbersByLine.find(y + 1);
  if (numberIt != numbersByLine.end()) {
    tryGetGearNumbers(firstNumber, secondNumber, x1, x2, numberIt->second);
  }

  return firstNumber * secondNumber;
}

int main(int argc, char** argv) {
  if (argc != 2) return 0;

  std::ifstream fileStream(argv[1]);
  if (fileStream.is_open()) {
    int sum = 0;
    std::string fileStreamLine;
    char lineChar;

    int x = 0, y = 0, number = 0, numberLength = 0;
    while (std::getline(fileStream, fileStreamLine)) {
        for (x = 0; x < fileStreamLine.size(); x++) {
        lineChar = fileStreamLine.at(x);

        // check if space symbol
        if (lineChar == '.') {
          // check if we need to push a number
          if (number > 0) {
            numberLength = getNumberLength(number);
            Number nb = { x - numberLength, number, numberLength };
            numbersByLine[y].push_back(nb);
            number = 0;
          }

          continue;
        }

        // check if symbol
        int symbolValue = lineChar - '0';
        if (symbolValue < 0 || symbolValue > 9) {
          // check if we need to push a number
          if (number > 0) {
            numberLength = getNumberLength(number);
            Number nb = { x - numberLength, number, numberLength };
            numbersByLine[y].push_back(nb);
            number = 0;
          }

          // add the symbol or gear
          Symbol sb = { x, lineChar, lineChar == '*', 0, 0 };
          symbolsByLine[y].push_back(sb);
          continue;
        }

        // add number digit
        number *= 10;
        number += symbolValue;
      }

      // check if number is at end of line
      if (number > 0) {
        numberLength = getNumberLength(number);
        Number nb = { x - numberLength, number, numberLength };
        numbersByLine[y].push_back(nb);
        number = 0;
      }

      y++;
    }

    // go through each line and identify the gear parts
    for (int i = 0; i < y; i++) {
      auto symbolIt = symbolsByLine.find(i);
      if (symbolIt == symbolsByLine.end()) continue;

      for (Symbol symbol : symbolIt->second) {
        if (!symbol.isGear) continue;
        sum += getGearRatio(symbol.getAdjacentMinX(), symbol.getAdjacentMaxX(), i);
      }
    }

    std::cout << sum << std::endl;
    fileStream.close();
  }

  return 0;
}
