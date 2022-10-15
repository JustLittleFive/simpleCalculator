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

/**
 * @brief Initialize and execute calculator, manage variable-operator stacks
 *
 * @param suffixList : suffix expression
 * @return string : calculation results
 */
string calculator(list<string> suffixList) {
  stack<string> calStack;
  list<string>::iterator it;
  for (it = suffixList.begin(); it != suffixList.end(); it++) {
    if (symbol.find(*it) == string::npos) {
      if (customVarible.count(*it) > 0) {
        calStack.push(customVarible[*it]);
        continue;
      }
      calStack.push(*it);
      continue;
    }
    if (biOperator.find(*it) != string::npos) {
      string val1 = calStack.top();
      calStack.pop();
      string val2 = calStack.top();
      calStack.pop();
      string val = calculate(val1, val2, *it);
      calStack.push(val);
    } else {
      string val = calStack.top();
      calStack.pop();
      string valre = calculate(val, *it);
      calStack.push(valre);
    }
  }
  string result = calStack.top();
  calStack.pop();

  return result;
}

/**
 * @brief Unary operator evaluation function
 * 
 * @param num : variable
 * @param unaOperator : unary operator
 * @return string : result
 */
string calculate(string num, string unaOperator) {
  char op = unaOperator.at(0);
  switch (op) {
    case '$': {
      /* square root operator */
      tuple<string, int, int, bool> input;
      input = preprocess(num);
      if (get<3>(input)) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      int pLocate = get<2>(input);
      if (pLocate != 0) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      int e = get<1>(input);
      if (e != 0) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      string str = get<0>(input);
      long numOp = stol(str);
      double numRe = sqrt(numOp);
      return to_string(numRe);
      break;
    }
    case '!': {
      /* factorial operator */
      tuple<string, int, int, bool> input;
      input = preprocess(num);
      if (get<3>(input)) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      int pLocate = get<2>(input);
      if (pLocate != 0) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      int e = get<1>(input);
      if (e != 0) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      string str = get<0>(input);
      long long factorial = 1;
      long numOp = stol(str);
      for (int i = 1; i <= numOp; i++) {
        factorial *= i;
      }
      return to_string(factorial);
      break;
    }
    default: {
      cout << "Invalid input!" << endl;
      return NULL;
    }
  }
}

/**
 * @brief Binary operator calculation function
 * 
 * @param num1 : variable 1
 * @param num2 : variable 2
 * @param biOperator : binary operator
 * @return string : result
 */
string calculate(string num1, string num2, string biOperator) {
  char op = biOperator.at(0);
  switch (op) {
    case '+':
      return funcAdd(num1, num2);
      break;
    case '-':
      return funcSub(num2, num1);
      break;
    case '*':
      return karatsuba(num1, num2);
      break;
    case '/':
      return funcDivide(num2, num1);
      break;
    case '^':
      return funcExp(num1, num2);
      break;
    case '%':
      return funcMod(num2, num1);
      break;

    default:
      cout << "Invalid input!" << endl;
      return NULL;
  }
}
