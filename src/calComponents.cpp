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

/// @brief Fill the digits with 0 to facilitate subsequent calculations, but for
/// decimal inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param num1: multiplier
/// @param num2: multiplier
/// @return length: max of length(num1) length(num2)
int addZerosR(string &num1, string &num2) {
  int l1 = num1.size();
  int l2 = num2.size();
  if (l1 > l2) {
    for (int i = 0; i < l1 - l2; i++) {
      num2 = (num2 + '0');
    }
  } else {
    for (int i = 0; i < l2 - l1; i++) {
      num1 = (num1 + '0');
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
