#pragma once
/**
 * Copyright (C) 2016, Markus Sprunck
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 *
 * - The name of its contributor may be used to endorse or promote
 *   products derived from this software without specific prior
 *   written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <map>
#include <list>
#include <queue>
#include <string>
#include <iostream>
#include <iterator> 
#include <ostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

typedef map<string, long> map_command;
typedef pair<string, long> pair_command;
typedef map<string, string> map_string;
typedef pair<string, string> pair_string;

#include "std_typedef.h"

static const string g_sVersion = "splunk-conf-beautifier v0.5";

class line_status;

class formater {
public:
    explicit formater();

    void run(const string& inputFile);

protected:

    // file input & output
    void importAllLines(const string& file, list<string>& m_Lines);
    void exportAllLines(const string& file);

    // each line
    void format(string pattern);
    void unformat(string pattern);
    string replacePattern(map_string pattern, string line, int iterations);

    // single line
    bool parseLine(string &line, line_status& ls, bool encode);
    void replaceSubstrings(const index_string& begin, index_string& end, string &s);

    // succsses information
    string result;

    // file content
    list<string> lines;

    // commands for each 'string pattern'
    map<string, long> spl_keywords;

    // string replace map
    map<string, string> replacePatternPreprocessing, replacePatternPostprocessing;

};
