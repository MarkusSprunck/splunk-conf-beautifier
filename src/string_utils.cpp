
#include "std_typedef.h"

string base64_encode(const std::string &in) {
    string out;
    int val = 0, valb = -6;
    for (char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8)>>(valb + 8))&0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val = 0, valb = -8;
    for (char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}

void trimRight(string & s) {
    index_string anf = s.find_last_not_of(" \t\r\n");
    if (string::npos != anf)
        s = s.substr(0, anf + 1);
    else
        s.erase();
}

void trimLeft(string & s) {
    index_string anf = s.find_first_not_of(" \t\r\n");
    if (string::npos != anf)
        s = s.substr(anf);
    else
        s.erase();
}



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}