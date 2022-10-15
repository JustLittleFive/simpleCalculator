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

/// @brief Input preprocessing
/// @param str:  num in string type
/// @return tuple<string arrayHead, int arrayTail, int pLocation, bool
/// isNegative>
///   @retval arrayHead: the input number, or its decimal part
///   @retval arrayTail: ths power part, if input by scientific notation
///   @retval pLocation: decimal point position
///   @retval isNegative: the parity
tuple<string, int, int, bool> preprocess(string str) {
  tuple<string, int, int, bool> ret;
  bool isNegative = 0;
  if (str[0] == '-') {
    isNegative = 1;
    str.erase(0, 1);
  }

  int countE = count(str.begin(), str.end(), 'E');
  int counte = count(str.begin(), str.end(), 'e');
  int countP = count(str.begin(), str.end(), '.');
  int countN = count(str.begin(), str.end(), '-');

  int numType = 0;

  if ((countE + counte + countN + countP) == 0) {
    // input maybe int/long
    numType = 1;
  } else if (countP == 1 && (countE + counte + countN) == 0) {
    // input maybe float/double not in Scientific notation
    numType = 2;
  } else if ((countE + counte) == 1 && countP < 2 && countN < 2) {
    // input maybe float/double in Scientific notation
    numType = 3;
  } else {
    cout << "Invalid input!" << endl;
    return ret;
  }

  string arrayHead = "";
  int arrayTail = 0;
  int pLocation = 0;

  switch (numType) {
    case 1: {
      // array could be pure-num char list
      arrayHead = str;
      break;
    }
    case 2: {
      // use pLocation to record '.'s position
      int rpLocation = str.find('.');
      str.erase(rpLocation, 1);
      pLocation = str.length() - rpLocation;
      arrayHead = str;
      break;
    }
    case 3: {
      int rpLocation = str.find('.');
      int eLocation = str.find('e');
      if (eLocation == string::npos) {
        eLocation = str.find('E');
      }
      int nLocation = str.find('-');
      if (rpLocation < eLocation &&
          (nLocation == string::npos || (eLocation + 1) == nLocation)) {
        string strHead = str.substr(0, eLocation);
        if (rpLocation != string::npos) {
          strHead.erase(rpLocation, 1);
          pLocation = strHead.length() - rpLocation;
        }
        arrayHead = strHead;
        str.erase(eLocation, 1);
        string strTail = str.substr(eLocation, str.length());
        arrayTail = stoi(strTail);
        break;
      } else {
        cout << "Invalid input!" << endl;
        return ret;
      }
      break;
    }
    default: {
      cout << "Invalid input!" << endl;
      return ret;
    }
  }

  ret = make_tuple(arrayHead, arrayTail, pLocation, isNegative);
  return ret;
}

/**
 * @brief Determine operator precedence
 *
 * @param symbol: formula operator
 * @return int
 * @retval return priority. The operator priority is divided into four levels,
 * the high priority is the first to be popped off the stack
 */
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

/**
 * @brief Convert infix expression to suffix expression
 *
 * @param seglist: expression stored in vector in infix order
 * @return list<string>: expression stored in list in suffix order
 */
list<string> suffixed(vector<string> seglist) {
  list<string> suffix;
  stack<string> symbolStack;
  for (int i = 0; i < seglist.size(); i++) {
    if (symbol.find(seglist[i]) == string::npos) {
      suffix.push_back(seglist[i]);
      continue;
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
             calcuLevel(seglist[i]) <= calcuLevel(symbolStack.top())) {
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

  return suffix;
}

/**
 * @brief The input initializer, deconstruct formulas into parameters and
 * operators
 *
 * @param input
 * @return vector<string>
 */
vector<string> initializer(string input) {
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
  return seglist;
}

/**
 * @brief Input validity checker
 *
 * @param seglist
 * @return true
 * @return false
 */
bool validChecker(vector<string> &seglist) {
  bool validCheck = true;
  // Sqrt / negative sign transfer
  for (int i = 0; i < seglist.size(); i++) {
    if (seglist[i].compare("sqrt") == 0) {
      int lo = 0;
      if (i < seglist.size() - 1) {
        if (seglist[i + 1].compare("(") == 0) {
          for (int j = i + 1; j < seglist.size(); j++) {
            if (seglist[j].compare(")") == 0) {
              lo = j;
              break;
            }
          }
          if (lo != 0) {
            seglist[i] = "$";
          }
        }
        seglist[i] = "$";
      } else {
        std::cout << "sqrt sign transfer failure: Invalid input!" << endl;
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
        std::cout << " negative sign transfer failure: Invalid input!" << endl;
        validCheck = 0;
        break;
      }
    }
  }
  if (!validCheck) {
    return validCheck;
  }
  // Input variables / parenthesis pairing checker
  int count = 0;
  for (int i = 0; i < seglist.size(); i++) {
    if (!regex_match(seglist[i],
                     regex("(\\-){0,1}([0-9]+)(\\.[0-9]+){0,1}(\\e[0-9]+){0,1}",
                           regex::icase)) &&
        symbol.find(seglist[i]) == string::npos) {
      map<string, string>::iterator l_it;
      l_it = customVarible.find(seglist[i]);
      if (l_it == customVarible.end()) {
        cout << "regex_match failure: Invalid input!" << endl;
        validCheck = false;
        break;
      }
    }
    if (seglist[i].compare("(") == 0) {
      count++;
    } else if (seglist[i].compare(")") == 0) {
      count--;
    }
  }
  if (count != 0) {
    cout << "parenthesis pairing failure: Invalid input!" << endl;
    validCheck = false;
  }
  if (!validCheck) {
    return validCheck;
  }
  // Formula format checker
  for (int i = 0; i < seglist.size() - 1; i++) {
    if (i == 0 && biOperator.find(seglist[i]) != string::npos) {
      cout << "format check failure: Invalid input!" << endl;
      validCheck = false;
      break;
    }
    if (biOperator.find(seglist[i]) != string::npos &&
        seglist[i + 1].compare("-") != 0 &&
        biOperator.find(seglist[i + 1]) != string::npos) {
      cout << "format check failure: Invalid input!" << endl;
      validCheck = false;
      break;
    }
    if (seglist[i].compare("$") == 0 &&
        (biOperator.find(seglist[i + 1]) != string::npos ||
         unaOperator.find(seglist[i + 1]) != string::npos ||
         i == seglist.size() - 2)) {
      cout << "format check failure: Invalid input!" << endl;
      validCheck = false;
      break;
    }
    if (seglist[i + 1].compare("!") == 0 &&
        symbol.find(seglist[i]) != string::npos) {
      cout << "format check failure: Invalid input!" << endl;
      validCheck = false;
      break;
    }
    if (i > 0 && symbol.find(seglist[i - 1]) != string::npos &&
        symbol.find(seglist[i]) != string::npos &&
        symbol.find(seglist[i + 1]) != string::npos &&
        (seglist[i].compare("(") != 0 || seglist[i + 1].compare("$") != 0)) {
      cout << "format check failure: Invalid input!" << endl;
      validCheck = false;
      break;
    }
  }

  return validCheck;
}
