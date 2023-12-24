#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Symbol {
  int x;
  char value;
};

struct Number {
  int x;
  int y;
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

int getSumForLine(Number& number, std::vector<Symbol>& symbols) {
  int sum = 0;
  for (const Symbol symbol : symbols) {
    if (symbol.x >= number.getAdjacentMinX() && symbol.x <= number.getAdjacentMaxX()) {
      sum += number.value;
    }
  }
  return sum;
}

int main(int argc, char** argv) {
  if (argc != 2) return 0;

  std::ifstream fileStream(argv[1]);
  if (fileStream.is_open()) {
    int sum = 0;
    std::string fileStreamLine;
    char lineChar;

    std::unordered_map<int, std::vector<Symbol>> symbolsByLine;
    std::vector<Number> numbers;
    int x = 0, y = 0, number = 0, numberLength = 0;
    while (std::getline(fileStream, fileStreamLine)) {
        for (x = 0; x < fileStreamLine.size(); x++) {
        lineChar = fileStreamLine.at(x);

        // check if space symbol
        if (lineChar == '.') {
          // check if we need to push a number
          if (number > 0) {
            numberLength = getNumberLength(number);
            Number nb = { x - numberLength, y, number, numberLength };
            numbers.push_back(nb);
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
            Number nb = { x - numberLength, y, number, numberLength };
            numbers.push_back(nb);
            number = 0;
          }

          // add the symbol
          Symbol sb = { x, lineChar };
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
        Number nb = { x - numberLength, y, number, numberLength };
        numbers.push_back(nb);
        number = 0;
      }

      y++;
    }

    for (Number number : numbers) {
      // get symbols on previous line
      if (number.y > 0) {
        auto symbolsIt = symbolsByLine.find(number.y - 1);
        if (symbolsIt != symbolsByLine.end()) {
          sum += getSumForLine(number, symbolsIt->second);
        }
      }

      // get symbols on the same line
      auto symbolsIt = symbolsByLine.find(number.y);
      if (symbolsIt != symbolsByLine.end()) {
        sum += getSumForLine(number, symbolsIt->second);
      }

      // get symbols on the next line
      if (number.y < y) {
        auto symbolsIt = symbolsByLine.find(number.y + 1);
        if (symbolsIt != symbolsByLine.end()) {
          sum += getSumForLine(number, symbolsIt->second);
        }
      }
    }

    std::cout << sum << std::endl;
    fileStream.close();
  }

  return 0;
}
