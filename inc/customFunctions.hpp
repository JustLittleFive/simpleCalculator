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

#include "StandardLibraryHeaderFile.hpp"

using namespace std;

// calculator's input processing functions
bool validChecker(vector<string> &seglist);
vector<string> initializer(string input);
list<string> suffixed(vector<string> seglist);
tuple<string, int, int, bool> preprocess(string str);

//core component functions
int addZeros(string &num1, string &num2);
int addZerosR(string &num1, string &num2);
string strAdd(string s1, string s2);
string strMinus(string s1, string s2);

// calculator mode overload functions
string calculator(list<string> suffixList);
string calculate(string num, string unaOperator);
string calculate(string num1, string num2, string biOperator);

// operation execution functions
string funcAdd(string num1, string num2);
string funcSub(string num1, string num2);
string karatsuba(string str1, string str2);
string funcDivide(string num1, string num2);
string funcExp(string num1, string num2);
string funcMod(string num1, string num2);
