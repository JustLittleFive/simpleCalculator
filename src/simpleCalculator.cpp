/*
 Copyright (c) 2022 SUSTech - JustLittleFive

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "headerCollections.hpp"

using namespace std;

map<string, string> customVarible;

/**
 * @brief Main function, which allows assigning and updating variables to the
 * map.
 *
 * @return int
 */
int main() {
  std::cout << "Welcome to simple calculator! Type exit to end calculate. "
               "\nPlease input your expression: "
            << endl;

  bool flag = true;
  while (flag) {
    string input = "";
    getline(cin, input);

    // Exit conditions
    if (input.compare("exit") == 0) {
      flag = false;
      continue;
    }

    // Assign formula
    if (int equalSymbol = input.find("=") != string::npos) {
      string variable = input.substr(0, equalSymbol);
      string expression = input.substr(equalSymbol + 1, input.length());
      if (!regex_match(variable, regex("[A-z_-\\s]+"))) {
        std::cout << "custom assign failed: Invalid input!" << endl;
        continue;
      } else {
        vector<string> seglist = initializer(expression);
        bool validCheck = validChecker(seglist);
        if (!validCheck) {
          cout << "Please input valid formula: " << endl;
          continue;
        }
        list<string> suffix = suffixed(seglist);
        string value = calculator(suffix);
        if (customVarible.count(variable) == 0) {
          customVarible.insert(pair<string, string>(variable, value));
        } else {
          customVarible[variable] = value;
        }
      }
    }

    // General
    vector<string> seglist = initializer(input);
    bool validCheck = validChecker(seglist);
    if (!validCheck) {
      cout << "Please input valid formula: " << endl;
      continue;
    }
    list<string> suffix = suffixed(seglist);
    string result = calculator(suffix);
    cout << result << endl;
  }
  cout << "Calculator exit..." << endl;
  return 0;
}
