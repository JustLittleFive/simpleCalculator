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

// #include <inputHandle.hpp>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const string symbol = "+-*/^$!%()";
const string biOperator = "+-*/^%";

map<string, string> customVarible;

string calculate(string, string);
string calculate(string, string, string);

int calcuLevel(string symbol) {
  if (symbol.compare("+") == 0 || symbol.compare("-") == 0) {
    return 1;
  } else if (symbol.compare("*") == 0 || symbol.compare("/") == 0) {
    return 2;
  } else if (symbol.compare("$") == 0 || symbol.compare("^") == 0) {
    return 3;
  } else if (symbol.compare("!") == 0 || symbol.compare("%") == 0) {
    return 4;
  }
  return 0;
}

int main() {
  std::cout << "Welcome to simple calculator! Type exit to end calculate. "
               "\nPlease input your expression: "
            //  "\nhint: negative numbers please add parentheses: "
            << endl;

  // Read input string and convert to vector.
  string input = "";
  cin >> input;
  while (input.compare("exit") == 0) {
    // assign function
    if (int equalSymbol = input.find("=")) {
      string variable = input.substr(0, equalSymbol);
      string expression = input.substr(equalSymbol + 1, input.length());
      if (!regex_match(variable, regex("A-z")) ||
          customVarible.find(variable) != customVarible.end()) {
        std::cout << "Invalid input!" << endl;
        continue;
      } else {
        customVarible.insert(pair<string, string>(variable, expression));
        //  TODO: expression calculate
      }
    }

    // general situation
    vector<string> seglist;
    size_t prev = 0, pos;
    while ((pos = input.find_first_of(symbol, prev)) != string::npos) {
      // std::cout << "pos = " << pos << " prev = " << prev << endl;
      if (pos > prev) {
        seglist.push_back(input.substr(prev, pos - prev));
        seglist.push_back(input.substr(pos, 1));
      } else if (pos == prev) {
        seglist.push_back(input.substr(pos, 1));
      }
      prev = pos + 1;
    }
    if (prev < input.length()) {
      seglist.push_back(input.substr(prev, string::npos));
    }
    // for (int i = 0; i < seglist.size(); i++) {
    //   std::cout << seglist[i];
    // }
    // std::cout << endl;

    bool validCheck = true;
    // sqrt / negative sign transfer
    for (int i = 0; i < seglist.size(); i++) {
      // std::cout << i << ": " << seglist[i] << endl;
      if (seglist[i].compare("sqrt") == 0) {
        if (i < seglist.size() - 1 &&
            symbol.find(seglist[i + 1]) == string::npos) {
          // std::cout << "hit!" << endl;
          seglist[i] = "$";
          seglist.erase(seglist.begin() + i + 1);
          seglist.erase(seglist.begin() + i + 2);
        } else {
          std::cout << "Invalid input!" << endl;
          validCheck = false;
          break;
        }
      }
      if (seglist[i].compare("-") == 0 &&
          (i == 0 || biOperator.find(seglist[i - 1]) != string::npos)) {
        if (i < seglist.size() - 1 &&
            biOperator.find(seglist[i + 1]) == string::npos) {
          seglist[i + 1] = "-" + seglist[i + 1];
          seglist.erase(seglist.begin() + i);
          i--;
        } else {
          std::cout << "Invalid input!" << endl;
          validCheck = 0;
          break;
        }
      }
    }
    if (!validCheck) {
      continue;
    }
    // input check
    for (int i = 0; i < seglist.size(); i++) {
      if (!regex_match(
              seglist[i],
              regex("(\\-){0,1}([0-9]+)(\\.[0-9]+){0,1}(\\e[0-9]+){0,1}",
                    regex::icase)) &&
          symbol.find(seglist[i]) == string::npos) {
        map<string, string>::iterator l_it;
        l_it = customVarible.find(seglist[i]);
        if (l_it == customVarible.end()) {
          cout << "Invalid input!" << endl;
          validCheck = false;
          break;
        }
      }
    }
    if (!validCheck) {
      continue;
    }
    // format check
    for (int i = 0; i < seglist.size() - 1; i++) {
      if (i == 0 && symbol.find(seglist[i]) != string::npos) {
        cout << "Invalid input!" << endl;
        validCheck = false;
        break;
      }
      if (symbol.find(seglist[i]) != string::npos &&
          seglist[i + 1].compare("-") != 0) {
        cout << "Invalid input!" << endl;
        validCheck = false;
        break;
      }
      if (i > 0 && symbol.find(seglist[i - 1]) != string::npos &&
          symbol.find(seglist[i]) != string::npos &&
          symbol.find(seglist[i + 1]) != string::npos) {
        cout << "Invalid input!" << endl;
        validCheck = false;
        break;
      }
    }
    if (!validCheck) {
      continue;
    }
    // for (int i = 0; i < seglist.size() - 1; i++) {
    //   if (seglist[i].compare("-") == 0) {
    //     if ((i == 0 || symbol.find(seglist[i - 1]) != string::npos) &&
    //         i < seglist.size() - 1 &&
    //         symbol.find(seglist[i + 1]) == string::npos) {
    //       seglist[i + 1] = "-" + seglist[i + 1];
    //       seglist.erase(seglist.begin() + i);
    //       i--;
    //     }
    //   }
    // }
    // for (int i = 0; i < seglist.size(); i++) {
    //   std::cout << seglist[i];
    // }

    // Infix expression to suffix expression
    list<string> suffix;        // s2
    stack<string> symbolStack;  // s1
    for (int i = 0; i < seglist.size(); i++) {
      if (symbol.find(seglist[i]) == string::npos) {
        suffix.push_back(seglist[i]);
      }
      if (seglist[i].compare("(") == 0) {
        symbolStack.push(seglist[i]);
      } else if (seglist[i].compare(")") == 0) {
        while (symbolStack.top().compare("(") != 0) {
          suffix.push_back(symbolStack.top());
          symbolStack.pop();
        }
        symbolStack.pop();
      } else {
        while (!symbolStack.empty() &&
               calcuLevel(seglist[i]) < calcuLevel(symbolStack.top())) {
          suffix.push_back(symbolStack.top());
          symbolStack.pop();
        }
        symbolStack.push(seglist[i]);
      }
    }
    while (!symbolStack.empty()) {
      suffix.push_back(symbolStack.top());
      symbolStack.pop();
    }

    // Calculate start
    stack<string> calStack;
    for (int i = 0; i < seglist.size(); i++) {
      if (symbol.find(seglist[i]) == string::npos) {
        calStack.push(seglist[i]);
        continue;
      }
      if (biOperator.find(seglist[i]) != string::npos) {
        string val1 = calStack.top();
        calStack.pop();
        string val2 = calStack.top();
        calStack.pop();
        calStack.push(calculate(val1, val2, seglist[i]));
      } else {
        string val = calStack.top();
        calStack.pop();
        calStack.push(calculate(val, seglist[i]));
      }
    }

    std::cout << endl;
    std::cout << "finish" << endl;
  }
  return 0;
}