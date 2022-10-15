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

#include <math.h>
#include <inputHandle.hpp>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include <vector>

using namespace std;
string calculate(string num, string unaOperator) {
  char op = unaOperator.at(0);
  switch (op) {
    case '$':
      /* code */
      if (num.find("e") != string::npos || num.find("E") != string::npos) {
        cout << "Unsupported input!" << endl;
        return NULL;
        break;
      }
      if (num.find(".") != string::npos) {
        double numOp = stod(num);
        numOp = sqrt(numOp);
        return to_string(numOp);
        break;
      }
      long numOp = stol(num);
      double numRe = sqrt(numOp);
      return to_string(numRe);
      break;
    case '!':
      /* code */
      if (num.find("e") != string::npos || num.find("E") != string::npos ||
          num.find(".") != string::npos) {
        cout << "Invalid input!" << endl;
        return NULL;
        break;
      }
      long factorial = 1;
      long numOp = stol(num);
      for (int i = 1; i <= numOp; i++) {
        factorial *= i;
      }
      return to_string(factorial);
      break;
    default:
      cout << "Invalid input!" << endl;
      return NULL;
  }
}

string calculate(string num1, string num2, string biOperator) {
    char op = biOperator.at(0);
    switch (op)
    {
    case '+':
        return funcAdd(num1,num2); // use new func name
        /* code */
        break;
    case '-':
        return strMinus(num1, num2); // use new func name, hint: num2 - num1
        /* code */
        break;
    case '*':
        return karatsuba(num1, num2);
        /* code */
        break;
    case '/':
        return funcDivide(num1, num2);
        /* code */
        break;
    case '^':
        return funcExp(num1, num2);
        /* code */
        break;
    case '%':
        return funcMod(num1, num2);
        /* code */
        break;
    
    default:
        cout << "Invalid input!" << endl;
        return NULL;
    }
}
