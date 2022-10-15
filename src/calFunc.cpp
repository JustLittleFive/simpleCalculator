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

using namespace std;

string funcAdd(string num1, string num2) {
  string result = "";
  int bit = -1;
  int i = num1.length() - 1;
  int j = num2.length() - 1;
  while (i != -1 && j != -1) {
    int val1 = num1[i] - 48;
    int val2 = num2[j] - 48;
    if (bit == -1) {
      if (val1 + val2 >= 10) {
        int digit = (val1 + val2) % 10;
        result.insert(0, 1, digit + 48);
        bit = (val1 + val2) / 10;
      } else {
        result.insert(0, 1, val1 + val2 + 48);
      }
    } else {
      if (val1 + val2 + bit >= 10) {
        int digit = (val1 + val2 + bit) % 10;
        result.insert(0, 1, digit + 48);
        bit = (val1 + val2 + bit) / 10;
      } else {
        result.insert(0, 1, val1 + val2 + bit + 48);
        bit = -1;
      }
    }
    i--;
    j--;
  }
  while (i == -1 && j != -1) {
    int val2 = num2[j] - 48;
    if (bit == -1) {
      result.insert(0, 1, num2[j]);
    } else {
      if (val2 + bit >= 10) {
        int digit = (val2 + bit) % 10;
        result.insert(0, 1, digit + 48);
        bit = (val2 + bit) / 10;
      } else {
        result.insert(0, 1, val2 + bit + 48);
        bit = -1;
      }
    }
    j--;
  }
  while (i != -1 && j == -1) {
    int val1 = num1[i] - 48;
    if (bit == -1) {
      result.insert(0, 1, num1[i]);
    } else {
      if (val1 + bit >= 10) {
        int digit = (val1 + bit) % 10;
        result.insert(0, 1, digit + 48);
        bit = (val1 + bit) / 10;
      } else {
        result.insert(0, 1, val1 + bit + 48);
        bit = -1;
      }
    }
    i--;
  }
  if (bit != -1) {
    result.insert(0, 1, bit + 48);
  }
  bit = -1;
  return result;
}

string sub(string num1, string num2) {
  string result;
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);
  int carrier = 0;
  int bitresult = 0;
  string fullResult = "";
  string finalResult = "";
  addZeros(s1, s2);
  for (int i = s1.length() - 1; i >= 0; i--) {
    bitresult = s1[i] - s2[i] - carrier;
    carrier = 0;

    if (bitresult < 0) {
      carrier = 1;
      bitresult = bitresult + 10;
    }

    fullResult.push_back(bitresult + '0');
  }
  for (int i = 0; i < fullResult.size(); i++) {
    finalResult.push_back(fullResult[fullResult.size() - i - 1]);
  }
  int pos = finalResult.find_first_not_of('0');
  if (pos != string::npos) {
    finalResult = finalResult.substr(pos, finalResult.size() - pos);
  } else {
    finalResult = "0";
  }
  return finalResult;
}

string funcDivide(string num1, string num2) {
  int dividend, divisor, remainder = 0;
  divisor = stoi(num1);
  for (int i = 0; i < num2.length(); i++) {
    dividend = (num2[i] - '0') + remainder * 10;
    if (dividend >= divisor) {
      remainder = dividend % divisor;
    } else {
      if (i != 0) cout << "0";
      remainder = dividend;
    }
  }
  dividend = (num2[num2.length() - 1] - '0') + remainder * 10;
  string result = to_string((double)dividend / (double)divisor) +
                  to_string((double)(dividend % divisor) / (double)divisor);
  return result;
}

string funcMod(string num1, string num2) {
  int dividend, divisor, remainder = 0;
  divisor = stoi(num1);
  for (int i = 0; i < num2.length(); i++) {
    dividend = (num2[i] - '0') + remainder * 10;
    if (dividend >= divisor) {
      remainder = dividend % divisor;
    } else {
      if (i != 0) cout << "0";
      remainder = dividend;
    }
  }
  dividend = (num2[num2.length() - 1] - '0') + remainder * 10;
  string result = to_string(dividend % divisor);
  return result;
}

string funcExp(string num1, string num2) {
  int local = num2.length() - 1;
  string result = num2;
  string temp = "0";
  int bitcount = 0;
  int bit = -1;
  string *arr = new string[num2.length()];
  int arr_i = 0;
  for (int i = 1; i < stoi(num1); i++) {
    while (local != -1) {
      int val1 = num2[local] - 48;
      int j = result.length() - 1;
      for (int k = 0; k < bitcount; k++) {
        arr[arr_i].insert(0, 1, '0');
      }
      while (j != -1) {
        int val2 = result[j] - 48;
        if (bit == -1) {
          if (val1 * val2 >= 10) {
            int digit = (val1 * val2) % 10;
            arr[arr_i].insert(0, 1, digit + 48);
            int digit2 = (val1 * val2) / 10;
            bit = digit2;
          } else {
            int digit = val1 * val2;
            arr[arr_i].insert(0, 1, digit + 48);
          }
        } else {
          if ((val1 * val2) + bit >= 10) {
            int digit = ((val1 * val2) + bit) % 10;
            arr[arr_i].insert(0, 1, digit + 48);
            int digit2 = ((val1 * val2) + bit) / 10;
            bit = digit2;
          } else {
            int digit = (val1 * val2) + bit;
            arr[arr_i].insert(0, 1, digit + 48);
            bit = -1;
          }
        }
        j--;
      }
      if (bit != -1) {
        arr[arr_i].insert(0, 1, bit + 48);
        bit = -1;
      }
      temp = funcAdd(temp, arr[arr_i]);
      bitcount++;
      arr_i++;
      local--;
    }
    bitcount = 0;
    result = temp;
    temp = "0";
    for (int i = 0; i < arr_i; i++) {
      arr[i] = "";
    }
    arr_i = 0;
    local = num2.length() - 1;
  }
  return result;
}