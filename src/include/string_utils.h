#pragma once

#include <string>
#include <vector>

using namespace std;

string base64_encode(const string &in);
string base64_decode(const string &in);

void trimLeft(string & s);
void trimRight(string & s);
std::vector<std::string> split(const std::string &s, char delim);

void stripUnicode(string & str);
