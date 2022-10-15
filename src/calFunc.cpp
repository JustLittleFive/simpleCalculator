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
 * @brief Full precision addition
 *
 * @param num1
 * @param num2
 * @return string
 */
string funcAdd(string num1, string num2) {
  bool isNegative = false;
  // suppose a > 0; b > 0
  if (num1[0] != '-') {
    // a + b = a + b
    if (num2[0] == '-') {
      // a + (-b) = a - b
      num2.erase(0, 1);
      return funcSub(num1, num2);
    }
  } else {
    if (num2[0] != '-') {
      // -a + b = b - a
      num1.erase(0, 1);
      return funcSub(num2, num1);
    } else {
      // -a + (-b) = -(a + b)
      isNegative = true;
    }
  }
  string finalResult = "";
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);

  int pLocate1 = get<2>(input1);
  int pLocate2 = get<2>(input2);
  string s1 = get<0>(input1), s2 = get<0>(input2);
  int e1 = get<1>(input1), e2 = get<1>(input2);
  int exLocate = e1 - e2;
  if (exLocate > 0) {
    e1 = e2;
    pLocate1 = pLocate1 - exLocate;
    exLocate = e2;
  } else {
    e2 = e1;
    pLocate2 = pLocate2 - exLocate;
    exLocate = e1;
  }
  string intPart1, intPart2, decPart1, decPart2 = "";
  if (!pLocate1) {
    intPart1 = s1;
  } else {
    if (pLocate1 < 0) {
      for (pLocate1; pLocate1 < 0; pLocate1++) {
        s1 = s1 + "0";
      }
      intPart1 = s1;
    } else {
      intPart1 = s1.substr(0, s1.length() - pLocate1);
      decPart1 = s1.substr(s1.length() - pLocate1, s1.length());
    }
  }
  if (!pLocate2) {
    intPart2 = s2;
  } else {
    if (pLocate2 < 0) {
      for (pLocate2; pLocate2 < 0; pLocate2++) {
        s2 = s2 + "0";
      }
      intPart2 = s2;
    } else {
      intPart2 = s2.substr(0, s2.length() - pLocate2);
      decPart2 = s2.substr(s2.length() - pLocate2, s2.length());
    }
  }

  addZeros(intPart1, intPart2);
  int rplocation = addZerosR(decPart1, decPart2);
  s1 = intPart1 + decPart1;
  s2 = intPart2 + decPart2;
  finalResult = strAdd(s1, s2);
  if (rplocation != 0) {
    finalResult.insert(finalResult.length() - rplocation, ".");
  }
  if (isNegative) {
    finalResult = "-" + finalResult;
  }
  if (exLocate != 0) {
    finalResult = finalResult + "E" + to_string(exLocate);
  }

  return finalResult;
}

/**
 * @brief Full precision subtraction
 *
 * @param num1
 * @param num2
 * @return string
 */
string funcSub(string num1, string num2) {
  // suppose a > 0, b > 0
  if (num1[0] != '-') {
    // a - b = a - b
    if (num2[0] == '-') {
      // a - (-b) = a + b
      num2.erase(0, 1);
      return funcAdd(num1, num2);
    }
  } else {
    if (num2[0] != '-') {
      // -a - b = (-a) + (-b)
      num2 = "-" + num2;
      return funcAdd(num2, num1);
    } else {
      // -a - (-b) = b - a
      num1.erase(0, 1);
      num2.erase(0, 1);
      return funcSub(num2, num1);
    }
  }
  string result;
  bool isNegative = false;
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);

  int pLocate1 = get<2>(input1);
  int pLocate2 = get<2>(input2);
  string s1 = get<0>(input1), s2 = get<0>(input2);
  int e1 = get<1>(input1), e2 = get<1>(input2);
  int exLocate = e1 - e2;
  if (exLocate > 0) {
    e1 = e2;
    pLocate1 = pLocate1 - exLocate;
    exLocate = e2;
  } else {
    e2 = e1;
    pLocate2 = pLocate2 - exLocate;
    exLocate = e1;
  }
  string intPart1, intPart2, decPart1, decPart2 = "";
  if (!pLocate1) {
    intPart1 = s1;
  } else {
    if (pLocate1 < 0) {
      for (pLocate1; pLocate1 < 0; pLocate1++) {
        s1 = s1 + "0";
      }
      intPart1 = s1;
    } else {
      intPart1 = s1.substr(0, s1.length() - pLocate1);
      decPart1 = s1.substr(s1.length() - pLocate1, s1.length());
    }
  }
  if (!pLocate2) {
    intPart2 = s2;
  } else {
    if (pLocate2 < 0) {
      for (pLocate2; pLocate2 < 0; pLocate2++) {
        s2 = s2 + "0";
      }
      intPart2 = s2;
    } else {
      intPart2 = s2.substr(0, s2.length() - pLocate2);
      decPart2 = s2.substr(s2.length() - pLocate2, s2.length());
    }
  }

  addZeros(intPart1, intPart2);
  int rplocation = addZerosR(decPart1, decPart2);
  s1 = intPart1 + decPart1;
  s2 = intPart2 + decPart2;
  if (s1 < s2) {
    s1.swap(s2);
    isNegative = true;
  }
  string finalResult = "";
  finalResult = strMinus(s1, s2);
  if (rplocation != 0) {
    finalResult.insert(finalResult.length() - rplocation, ".");
  }
  if (isNegative) {
    finalResult = "-" + finalResult;
  }
  if (exLocate != 0) {
    finalResult = finalResult + "E" + to_string(exLocate);
  }

  return finalResult;
}

/**
 * @brief 16 decimal precision division
 *
 * @param num2
 * @param num1
 * @return string
 */
string funcDivide(string num2, string num1) {
  string result = "";
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);
  int pLocate1 = get<2>(input1);
  int pLocate2 = get<2>(input2);
  string s1 = get<0>(input1), s2 = get<0>(input2);
  int e1 = get<1>(input1), e2 = get<1>(input2);
  int exLocate = e2 - e1;
  bool isNegative = false;
  if (get<3>(input1) != get<3>(input2)) {
    isNegative = true;
  }
  string str1 = get<0>(input1);
  string str2 = get<0>(input2);
  int divisor = stoi(str1);
  int index = 0;
  // extracting the part that is greater than the given divisor
  int dividend = str2[index] - '0';
  while (dividend < divisor) {
    if (index < str2.length() - 1) {
      dividend = dividend * 10 + (str2[++index] - '0');
    } else {
      if (pLocate2 - pLocate1 < 16) {
        str2 = str2 + "0";
        dividend = dividend * 10 + (str2[++index] - '0');
        if (exLocate > 0) {
          exLocate--;
        } else {
          pLocate2++;
        }
      }
    }
  }
  // iterating until all digits participate in the division
  while (str2.size() > index) {
    result += (dividend / divisor) + '0';
    // adding the next digit to the dividend
    dividend = (dividend % divisor) * 10 + str2[++index] - '0';
  }
  if (result.length() == 0) {
    return "0";
  }
  int rpLocation = pLocate2 - pLocate1;
  while (exLocate > rpLocation + 1 && rpLocation > 0) {
    exLocate--;
    rpLocation--;
  }
  if (rpLocation >= 0) {
    while (rpLocation >= result.length()) {
      result = "0" + result;
    }
  } else {
    for (rpLocation; rpLocation < 0; rpLocation++) {
      result = result + "0";
    }
  }
  if (rpLocation > 0) {
    result.insert(result.length() - rpLocation, ".");
  }
  if (isNegative) {
    result = "-" + result;
  }
  if (exLocate != 0) {
    result = result + "E" + to_string(exLocate);
  }
  return result;
}

/**
 * @brief Remainder function, currently does not support scientific notation or
 * decimals
 *
 * @param num2
 * @param num1
 * @return string
 */
string funcMod(string num2, string num1) {
  string result = "";
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);
  int pLocate1 = get<2>(input1);
  int pLocate2 = get<2>(input2);
  if (pLocate1 + pLocate2 != 0) {
    cout << "Unsupported input!" << endl;
    return NULL;
  }
  int e1 = get<1>(input1), e2 = get<1>(input2);
  if (e1 != 0 || e2 != 0) {
    cout << "Unsupported input!" << endl;
    return NULL;
  }
  string str1 = get<0>(input1);
  string str2 = get<0>(input2);
  bool isNegative = false;
  if (get<3>(input1)) {
    isNegative = true;
  }
  int moder = stoi(str1);
  int res = 0;
  for (int i = 0; i < str2.length(); i++) {
    res = (res * 10 + str2[i] - '0') % moder;
  }
  result = to_string(res);
  if (isNegative) {
    result = "-" + result;
  }
  return result;
}

/**
 * @brief Power function. Support for negative exponential powers requires
 * Taylor expansion, which is currently not implemented.
 *
 * @param num1
 * @param num2
 * @return string
 */
string funcExp(string num1, string num2) {
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);
  if (get<3>(input1)) {
    cout << "Unsupported input!" << endl;
    return NULL;
  }
  int pLocate1 = get<2>(input1);
  int pLocate2 = get<2>(input2);
  if (pLocate1 + pLocate2 != 0) {
    cout << "Unsupported input!" << endl;
    return NULL;
  }
  int e1 = get<1>(input1), e2 = get<1>(input2);
  if (e1 != 0 || e2 != 0) {
    cout << "Unsupported input!" << endl;
    return NULL;
  }
  string str1 = get<0>(input1);
  string str2 = get<0>(input2);
  bool isNegative = false;
  if (stoi(str1) % 2 != 0) {
    isNegative = get<3>(input2);
  }
  int local = str2.length() - 1;
  string result = str2;
  string temp = "0";
  int bitcount = 0;
  int bit = -1;
  string *arr = new string[str2.length()];
  int arr_i = 0;
  for (int i = 1; i < stoi(str1); i++) {
    while (local != -1) {
      int val1 = str2[local] - 48;
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
    local = str2.length() - 1;
  }
  if (isNegative) {
    result = "-" + result;
  }
  return result;
}

/// @brief Multiply function by Karatsuba algorithm, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param str1
/// @param str2
/// @return string
string karatsuba(string num1, string num2) {
  string result = "";
  tuple<string, int, int, bool> input1;
  tuple<string, int, int, bool> input2;
  input1 = preprocess(num1);
  input2 = preprocess(num2);
  int pLocate1 = get<2>(input1);
  int pLocate2 = get<2>(input2);
  string s1 = get<0>(input1), s2 = get<0>(input2);
  int e1 = get<1>(input1), e2 = get<1>(input2);
  int exLocate = e2 + e1;
  bool isNegative = false;
  if (get<3>(input1) != get<3>(input2)) {
    isNegative = true;
  }
  string str1 = get<0>(input1);
  string str2 = get<0>(input2);
  int len = addZeros(str1, str2);

  if (len == 1) {
    return to_string(atoi(str1.c_str()) * atoi(str2.c_str()));
  }

  int subLen = len / 2;
  string a = str1.substr(0, subLen);
  string b = str1.substr(subLen, len - subLen);
  string c = str2.substr(0, subLen);
  string d = str2.substr(subLen, len - subLen);

  string ac = karatsuba(a, c);
  string bd = karatsuba(b, d);
  // string acPbd = strAdd(ac, bd);
  // string adPbc = strAdd(karatsuba(a, d), karatsuba(b, c));
  string aPbcPd = karatsuba(strAdd(a, b), strAdd(c, d));
  string adPbc = strMinus(aPbcPd, strAdd(ac, bd));

  int bitShift = len - subLen;
  for (int i = 0; i < bitShift * 2; i++) {
    ac = ac + '0';
  }
  for (int i = 0; i < bitShift; i++) {
    adPbc = adPbc + '0';
  }

  result = strAdd(strAdd(ac, adPbc), bd);

  int rpLocation = pLocate2 + pLocate1;
  while (exLocate > rpLocation + 1 && rpLocation > 0) {
    exLocate--;
    rpLocation--;
  }
  if (rpLocation >= 0) {
    while (rpLocation >= result.length()) {
      result = "0" + result;
    }
  } else {
    for (rpLocation; rpLocation < 0; rpLocation++) {
      result = result + "0";
    }
  }
  if (rpLocation > 0) {
    result.insert(result.length() - rpLocation, ".");
  }
  if (isNegative) {
    result = "-" + result;
  }
  if (exLocate != 0) {
    result = result + "E" + to_string(exLocate);
  }
  return result;
}
