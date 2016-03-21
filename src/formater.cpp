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

#include <algorithm>
#include <string>
#include <list>
#include <map>

#include "../src/include/string_utils.h"
#include "../src/include/formater.h"
#include "../src/include/formater_replace.h"
#include "../src/include/line_status.h"

const map_string getReplacePrepocessing() {
    map_string replace;
    replace[")"] = " ) ";
    replace["("] = " ( ";
    replace[","] = " , ";
    return replace;
}

const map_string getReplacePostprocessing() {
    map_string replace;
    replace[" ("] = "(";
    replace["  "] = " ";
    replace[" ,"] = ",";
    replace["  ,"] = " ,";
    replace[" )"] = ")";
    replace["( "] = "(";
    replace[") `"] = ")`";
    replace[",  "] = ", ";
    replace[")  "] = ") ";
    return replace;
}

enum eCommand {
    INCREMENT = 1, DECREMENT = 2, INCREMENTONCE = 4, DOUBLE_INCREMENTONCE = 8
} ;

const map_command getCommand() {
    map_command command;
    command["|"] = INCREMENTONCE;
    command[","] = INCREMENTONCE;
    command["["] = INCREMENT;
    command["]"] = INCREMENTONCE | DECREMENT;
    return command;
}

class layer_counter {
    line_status* ls;
    const string* line;

 public:
    layer_counter(line_status* line_status, const string& line) : ls(line_status), line(&line) {
    }

    void operator()(const pair_command& p1) {
        if (string::npos != line->find(p1.first)) {
            if (INCREMENTONCE == (INCREMENTONCE & p1.second) && 20 > (*ls).GetLayerCount()) {
                (*ls).SetLayerCountOnce((*ls).GetLayerCountOnce() + 1);
            }

            if (DOUBLE_INCREMENTONCE == (DOUBLE_INCREMENTONCE & p1.second) && 20 > (*ls).GetLayerCount()) {
                (*ls).SetLayerCountOnce((*ls).GetLayerCountOnce() + 2);
            }

            if (INCREMENT == (INCREMENT & p1.second) && 10 > (*ls).GetLayerCount()) {
                (*ls).SetLayerCount((*ls).GetLayerCount() + 1);
            }

            if (DECREMENT == (DECREMENT & p1.second) && 1 <= (*ls).GetLayerCount()) {
                (*ls).SetLayerCount((*ls).GetLayerCount() - 1);
            }
        }
    }
} ;

formater::formater() :
result("ok"),
spl_keywords(getCommand()),
replacePatternPreprocessing(getReplacePrepocessing()),
replacePatternPostprocessing(getReplacePostprocessing()) {
}

void formater::run(const string& inputFile) {
    cout << "import file " << inputFile << endl;
    importAllLines(inputFile, lines);
    if ("ok" == result) {
        string outputFileResult = string(inputFile).append(".result");
        string pattern1("savedsearches.conf");
        string pattern2("savedsearches.conf.formated");
        string pattern3("macros.conf");
        string pattern4("macros.conf.formated");
        if (inputFile == pattern1) {
            outputFileResult = "savedsearches.conf.formated";
            cout << "format file " << pattern1 << endl;
            format("search =");
        } else if (inputFile == pattern2) {
            outputFileResult = "savedsearches.conf";
            cout << "format file " << pattern2 << endl;
            unformat("search =");
        } else if (inputFile == pattern3) {
            outputFileResult = "macros.conf.formated";
            cout << "format file " << pattern3 << endl;
            format("definition =");
        } else if (inputFile == pattern4) {
            outputFileResult = "macros.conf";
            cout << "format file " << pattern4 << endl;
            unformat("definition =");
        } else {
            cout << "not formated file " << inputFile << endl;
            return;
        }

        cout << string("create 'file://").append(outputFileResult).append("' ").append(result) << endl;
        exportAllLines(outputFileResult);
        cout << "ready" << endl;
    }
}

void formater::importAllLines(const string& file, list<string>& m_Lines) {
    fstream fin(file.c_str(), ios_base::in);
    if (fin.fail()) {
        result = "ERROR: file open failed";
        cout << result << endl;
        return;
    }

    m_Lines.clear();
    string line;
    while (getline(fin, line) && (!fin.fail())) {
        string line_copy = line;
        stripUnicode(line_copy);
        if (line_copy.length() != line.length()) {
            result = "ERROR: file contains non ascii character";
            cout << result << endl;
            return;
        }
        trimRight(line);
        m_Lines.push_back(line);
    }

    fin.close();
}

void formater::exportAllLines(const string& file) {
    // read existing file content
    std::ifstream t(file);
    std::stringstream oldContent;
    oldContent << t.rdbuf();

    // create new  file content
    std::ostringstream newContent;
    std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(newContent, "\n"));

    if (oldContent.str() == newContent.str()) {
        cout << "no change, store not needed" << endl;
    } else if (0 == result.compare("ok")) {
        fstream fout(file.c_str(), ios_base::out | ios_base::trunc);
        if (fout.fail()) {
            result = "ERROR: file create failed";
            cout << result << endl;
            return;
        }
        fout << newContent.str();
    }
}

void formater::format(string pattern) {
    line_status ls;
    for (list <string>::iterator iter = lines.begin(); iter != lines.end(); iter++) {
        // reset state for next line
        ls.SetLayerCountOnce(0);

        string line = *iter;
        if (line.substr(0, pattern.size()) == pattern) {
            // encode strings with base64 to avoid formating
            parseLine(line, ls, true);

            // replace pattern
            line = replacePattern(replacePatternPreprocessing, line, 1);

            // calcualte layer based on commands
            for_each(spl_keywords.begin(), spl_keywords.end(), layer_counter(&ls, line));

            // remove some strings
            line = replacePattern(replacePatternPostprocessing, line, 5);

            // decode strings with base64 to avoid formating
            parseLine(line, ls, false);

            *iter = line;
        }
    }
}

void formater::unformat(string pattern) {
    list<string> lines_result;

    bool inSearch = false;
    string search = "";
    for (list <string>::iterator iter = lines.begin(); iter != lines.end(); iter++) {
        string line = *iter;
        trimLeft(line);

        if (line.substr(0, pattern.size()) == pattern) {
            inSearch = true;
            search = line;
        } else if (inSearch) {
            search.append(line);
        }

        if (!inSearch) {
            lines_result.push_back(line);
        } else if (line.size() == 0 || std::distance(iter, lines.end()) == 1) {
            inSearch = false;
            lines_result.push_back(search);
            lines_result.push_back("");
        }
    }
    lines = lines_result;
}

string formater::replacePattern(map_string pattern, string s1, int iterations) {
    string line = s1;
    typedef map<string, string>::iterator it_type;
    for (it_type iterator = pattern.begin(); iterator != pattern.end(); iterator++) {
        for (int i = 0; i < iterations; i++) {
            string s2 = iterator->first;
            string s3 = iterator->second;
            index_string anf = line.find(s2, 0);
            while (string::npos != anf) {
                string right(line.substr(anf + s2.length(), string::npos));
                string left(line.substr(0, anf));
                line = left.append(s3).append(right);
                anf = line.find(s2, left.length());
            }
        }
    }
    return line;
}

bool formater::parseLine(string &line, line_status & ls, bool encode) {
    index_string indexStart = 0;
    index_string index = 0;

    do {
        if (ls.inCode()) {
            if (!encode && !ls.inBrackets() && (line[index] == ',' || line[index] == '|' || line[index] == '[')) {
                line.insert(index, "\r\n");
                index += 2;
                for (int i = 0; i <= ls.GetLayerCountTotal(); i++) {
                    line.insert(index, "   ");
                    index += 3;
                }
            }
            if (line[index] == '(') {
                ls.SetBracketsCount(ls.GetBracketsCount() + 1);
            }
            if (line[index] == '"') {
                ls.SetActiveDoubleQuoteString();
                indexStart = index;
            } else if (line[index] == '\'') {
                ls.SetActiveSingleQuoteString();
                indexStart = index;
            } else if (line[index] == '`') {
                ls.SetActiveMacro();
                indexStart = index;
            }
        } else if (ls.inDoubleQuoteString() || ls.inSingleQuoteString()) {
            if ((ls.inDoubleQuoteString() && line[index] == '"' && index > 1 && line[index - 1] != '\\') ||
                    (ls.inSingleQuoteString() && line[index] == '\'' && index > 1 && line[index - 1] != '\\')) {
                if (encode) {
                    int indexStart1 = indexStart + 1;
                    int string_length = (index - indexStart - 1);
                    string sub_string2 = line.substr(indexStart1, string_length);
                    string encoded2 = base64_encode(sub_string2);
                    line = line.replace(indexStart1, string_length, encoded2);
                    index -= sub_string2.length();
                    index += encoded2.length();
                } else {
                    int indexStart1 = indexStart + 1;
                    int string_length = (index - indexStart - 1);
                    string sub_string = line.substr(indexStart1, string_length);
                    string decoded = base64_decode(sub_string);
                    line = line.replace(indexStart1, string_length, decoded);
                    index -= sub_string.length();
                    index += decoded.length();
                }

                ls.SetActiveCode();
                indexStart = index;
            }
        } else if (ls.inMacro()) {
            if (line[index] == '`') {
                if (encode) {
                    int indexStart1 = indexStart + 1;
                    int string_length = (index - indexStart - 1);
                    string sub_string2 = line.substr(indexStart1, string_length);
                    string encoded2 = base64_encode(sub_string2);
                    line = line.replace(indexStart1, string_length, encoded2);
                    index -= sub_string2.length();
                    index += encoded2.length();
                } else {
                    int indexStart1 = indexStart + 1;
                    int string_length = (index - indexStart - 1);
                    string sub_string = line.substr(indexStart1, string_length);
                    string decoded = base64_decode(sub_string);
                    line = line.replace(indexStart1, string_length, decoded);
                    index -= sub_string.length();
                    index += decoded.length();
                }

                ls.SetActiveCode();
                indexStart = index;
            }
        }

        if (ls.inCode() && ls.inBrackets()) {
            if (line[index] == ')') {
                ls.SetBracketsCount(ls.GetBracketsCount() - 1);
            }
        }
    } while (++index <= line.size());

    if (ls.inDoubleQuoteString()) {
        result = "ERROR: invalid state - double quote string";
        cout << result << endl;
    }

    if (ls.inSingleQuoteString()) {
        result = "ERROR: invalid state - single quote string";
        cout << result << endl;
    }

    if (ls.inMacro()) {
        result = "ERROR: invalid state - macro";
        cout << result << endl;
    }

    if (ls.inBrackets()) {
        result = "ERROR: invalid state - brackets";
        cout << result << endl;
    }

    return false;
}

void formater::replaceSubstrings(const index_string& begin, index_string& end, string & s) {
    if (begin != string::npos && end != string::npos && begin < end) {
        string midNeu;
        string mid = s.substr(begin, end - begin + 1).c_str();

        midNeu = for_each(replacePatternPreprocessing.begin(),
                replacePatternPreprocessing.end(), formater_replace(mid));

        s = s.substr(0, begin).append(midNeu).append(s.substr(end + 1, string::npos).c_str());
        end = begin + midNeu.length() - 1;
    }
}


