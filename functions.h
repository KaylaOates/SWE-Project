#pragma once
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////TESTING FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool compareFile(istreambuf_iterator<char> file1B, istreambuf_iterator<char> file2B, istreambuf_iterator<char> file1E, istreambuf_iterator<char> file2E); //compares two files, used for testing CSV files

////////////////////////////////////////////////////////TESTING FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
