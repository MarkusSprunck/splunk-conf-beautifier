/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

// using namespace std;


#include "include/std_typedef.h"

std::string base64_encode(const std::string &in) {
    std::string out;
    int val = 0, valb = -6;
    for (char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8)>>(valb + 8))&0x3F]);
    }
    while (out.size() % 4) out.push_back('=');
    return out;
}

std::string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) {
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    }
    int val = 0, valb = -8;
    for (char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(static_cast<char> (((val >> valb)&0xFF)));
            valb -= 8;
        }
    }
    return out;
}

void trimRight(std::string & s) {  // NOLINT(runtime/references)
    index_string anf = s.find_last_not_of(" \t\r\n");
    if (std::string::npos != anf)
        s = s.substr(0, anf + 1);
    else
        s.erase();
}

void trimLeft(std::string & s) {  // NOLINT(runtime/references)
    index_string anf = s.find_first_not_of(" \t\r\n");
    if (std::string::npos != anf)
        s = s.substr(anf);
    else
        s.erase();
}

std::vector<std::string> &split(const std::string &s, char delim,
        std::vector<std::string> &elems) {  // NOLINT(runtime/references)
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {  // NOLINT(runtime/references)
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool invalidChar(char c) {
    return !(c >= 0 && c < 128);
}

void stripUnicode(std::string & str) {  // NOLINT(runtime/references)
    str.erase(std::remove_if(str.begin(), str.end(), invalidChar), str.end());
}
