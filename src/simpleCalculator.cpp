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

#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const string symbol = "+-*/$^!%()";

map<string, string> customVarible;

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
  std::cout << "Welcome to simple calculator! \nPlease input your expression: "
            << endl;

  // Read input string and convert to vector.
  string input = "";
  cin >> input;
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

  // sqrt / negative sign transfer and input check
  string invaildSymbolCombo = "+-*/^";
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
        // continue;
      }
    }
    if (seglist[i].compare("-") == 0) {
      if (i < seglist.size() - 1 &&
          invaildSymbolCombo.find(seglist[i + 1]) == string::npos) {
        seglist[i + 1] = "-" + seglist[i + 1];
        seglist.erase(seglist.begin() + i);
        i--;
      } else {
        std::cout << "Invalid input!" << endl;
      }
    }
  }
  for (int i = 0; i < seglist.size(); i++) {
    if (!regex_match(seglist[i],
                     regex("(\\-){0,1}([0-9]+)(\\.[0-9]+){0,1}(\\e[0-9]+){0,1}",
                           regex::icase))) {
      map<string, string>::iterator l_it;
      l_it = customVarible.find(seglist[i]);
      if (l_it == customVarible.end()) {
        cout << "Invalid input!" << endl;
        // continue;
      }
    }
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
      // if (regex_match(
      //         seglist[i],
      //         regex("(\\-){0,1}([0-9]+)(\\.[0-9]+){0,1}(\\e[0-9]+){0,1}",
      //               regex::icase))) {
      // } else {
      //   cout << "Invalid input!" << endl;
      //   // continue;
      // }
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

  std::cout << endl;
  std::cout << "finish" << endl;
  return 0;
}