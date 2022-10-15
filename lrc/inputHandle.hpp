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

#pragma once

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <tuple>

using namespace std;

tuple<char *, int, int, bool> preprocess(string str);

string calculate(string num1, string num2, string biOperator);

string calculate(string num, string unaOperator);

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <tuple>

/// @brief Convert string to char[] with in-progress validity check
/// @param str: string
/// @return array: char[]
char *str2charl(string str);

/// @brief Input early check + preprocessing
/// @param str: string, main() argv[1] or argv[2]
/// @return tuple<string arrayHead, int arrayTail, int pLocation, bool
/// isNegative>
///   @retval arrayHead: the input number, or its decimal part
///   @retval arrayTail: ths power part, if input by scientific notation
///   @retval pLocation: decimal point position
///   @retval isNegative: the parity
tuple<string, int, int, bool> preprocess(string str);

/// @brief Fill the digits with 0 to facilitate subsequent calculations,
/// inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param num1: multiplier
/// @param num2: multiplier
/// @return length: max of length(num1) length(num2)
int addZeros(string &num1, string &num2);

/// @brief add two string bit by bit, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param s1
/// @param s2
/// @return string
string strAdd(string s1, string s2);

/// @brief minus two string bit by bit, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param s1
/// @param s2
/// @return string
string strMinus(string s1, string s2);

/// @brief Karatsuba algorithm, inspired by the article
/// https://www.geeksforgeeks.org/karatsuba-algorithm-for-fast-multiplication-using-divide-and-conquer-algorithm/
/// @param str1
/// @param str2
/// @return string
string karatsuba(string str1, string str2);

string funcDivide(string num1, string num2);

string funcMod(string num1, string num2);

string funcAdd(string num1, string num2);

string funcExp(string num1, string num2);