#pragma once

#include <string>

using namespace std;

string base64_encode(const string &in);
string base64_decode(const string &in);

void trimLeft(string & s);
void trimRight(string & s);
