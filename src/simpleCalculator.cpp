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
#include <map>
#include <string>
#include <vector>
#include <stack>

using namespace std;

const string symbol = "+-*()/%^!$";

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

  // sqrt and negative sign transfer
  string invaildSymbolCombo = "+-*/^";
  for (int i = 0; i < seglist.size(); i++) {
    // std::cout << i << ": " << seglist[i] << endl;
    if (seglist[i].compare("sqrt") == 0) {
      if (i < seglist.size() - 1 && symbol.find(seglist[i+1]) == string::npos) {
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
      }
      else {
        std::cout << "Invalid input!" << endl;
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

  stack<string> suffix;
  stack<string> symbolStack;
  for(int i = 0; i < seglist.size(); i++){
    if(symbol.find(seglist[i]) == string::npos){
      
    }
  }

  std::cout << endl;
  std::cout << "finish" << endl;
  return 0;
}