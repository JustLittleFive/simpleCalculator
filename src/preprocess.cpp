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

#include <inputHandle.hpp>

using namespace std;

/// @brief Convert string to char[]
/// @param str: string
/// @return array: char[]
char *str2charl(string str) {
  const char *input = str.c_str();
  int len = str.length();
  char *array = new char[len];
  for (int i = 0; i < len; i++) {
    array[i] = input[i];
  }
  return array;
}

/// @brief Input preprocessing
/// @param str:  num in string type
/// @return tuple<string arrayHead, int arrayTail, int pLocation, bool
/// isNegative>
///   @retval arrayHead: the input number, or its decimal part
///   @retval arrayTail: ths power part, if input by scientific notation
///   @retval pLocation: decimal point position
///   @retval isNegative: the parity
tuple<string, int, int, bool> preprocess(string str) {
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
    return;
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
        }
        pLocation = strHead.length() - rpLocation;
        arrayHead = strHead;
        str.erase(eLocation, 1);
        string strTail = str.substr(eLocation, str.length());
        arrayTail = stoi(str2charl(strTail));
        break;
      } else {
        cout << "Invalid input!" << endl;
        return;
      }
      break;
    }
    default: {
      cout << "Invalid input!" << endl;
      return;
    }
  }

  tuple<string, int, int, bool> ret =
      make_tuple(arrayHead, arrayTail, pLocation, isNegative);
  return ret;
}

/// @brief Fill the digits with 0 to facilitate subsequent calculations,
/// inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param num1: multiplier
/// @param num2: multiplier
/// @return length: max of length(num1) length(num2)
int addZeros(string &num1, string &num2) {
  int l1 = num1.size();
  int l2 = num2.size();
  if (l1 > l2) {
    for (int i = 0; i < l1 - l2; i++) {
      num2 = ('0' + num2);
    }
  } else {
    for (int i = 0; i < l2 - l1; i++) {
      num1 = ('0' + num1);
    }
  }
  return max(l1, l2);
}

/// @brief add two string bit by bit, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param s1
/// @param s2
/// @return string
string strAdd(string s1, string s2) {
  int carrier = 0;
  int bitresult = 0;
  string fullResult = "";
  string finalResult = "";
  addZeros(s1, s2);
  for (int i = s1.length() - 1; i >= 0; i--) {
    bitresult = s1[i] - '0' + s2[i] - '0' + carrier;
    carrier = 0;
    if (bitresult > 9) {
      carrier = 1;
      bitresult = bitresult - 10;
    }
    fullResult.push_back(bitresult + '0');
  }
  if (carrier == 1) {
    fullResult.push_back('1');
  }
  for (int i = 0; i < fullResult.size(); i++) {
    finalResult.push_back(fullResult[fullResult.size() - i - 1]);
  }
  // finalResult.push_back('\0');
  int pos = finalResult.find_first_not_of('0');
  if (pos != string::npos) {
    finalResult = finalResult.substr(pos, finalResult.size() - pos);
  } else {
    finalResult = "0";
  }
  return finalResult;
}

/// @brief minus two string bit by bit, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param s1
/// @param s2
/// @return string
string strMinus(string s1, string s2) {
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

/// @brief Karatsuba algorithm, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param str1
/// @param str2
/// @return string
string karatsuba(string str1, string str2) {
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

  return strAdd(strAdd(ac, adPbc), bd);
}
