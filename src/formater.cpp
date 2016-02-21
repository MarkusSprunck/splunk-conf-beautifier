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

#include "formater.h"
#include "formater_parameter.h"
#include "formater_replace.h"
#include "layer_counter.h"
#include "formater_mark_html.h"
#include "string_utils.h"
#include "line_status.h"

formater::formater() :
m_sResult("ok"),
m_bCreateHtml(true),
m_commands(getCommand()),
m_replacePatternsPreprocessing(getReplacePrepocessing()),
m_replacePatternsPostprocessing(getReplacePostprocessing()),
m_replacePatternsHtml(getReplaceHtml()) {
}

void formater::run(const string& inputFile) {
    // create text file
    m_bCreateHtml = false;
    importAllLines(inputFile, m_Lines);
    for_each(m_Lines.begin(), m_Lines.end(), trimLeft);
    for_each(m_Lines.begin(), m_Lines.end(), trimRight);
    removeEmptyAll();
    formatPre();
    wrapLines("[");
    wrapLines("]");
    wrapLines("|");
    wrapLines(",");
    formatPost();
    string outputFileResult = string(inputFile).append(".result");
    exportAllLines(outputFileResult);
    cout << string("create 'file://").append(outputFileResult).append("' ").append(m_sResult) << endl;

    // create html file
    m_bCreateHtml = true;

    // import all lines
    importAllLines(inputFile, m_Lines);
    for_each(m_Lines.begin(), m_Lines.end(), trimLeft);
    for_each(m_Lines.begin(), m_Lines.end(), trimRight);
    removeEmptyAll();
    formatPre();
    wrapLines("[");
    wrapLines("]");
    wrapLines("|");
    wrapLines(",");
    formatPost();
    createHtmlDocument();
    string outputFileHtml = string(inputFile).append(".html");
    exportAllLines(outputFileHtml);
    cout << string("create 'file://").append(outputFileHtml).append("' ").append(m_sResult) << endl;
}

void formater::importAllLines(const string& file, list<string>& m_Lines) {
    fstream fin(file.c_str(), ios_base::in);
    if (fin.fail()) {
        m_sResult = "file open failed";
    } else {
        m_Lines.clear();
        string line;
        while (getline(fin, line) && (!fin.fail())) {
            if (m_bCreateHtml) {
                formater_replace::repeated_replace(line, "&", "&amp");
                formater_replace::repeated_replace(line, "<", "&lt");
                formater_replace::repeated_replace(line, ">", "&gt");
            }
            m_Lines.push_back(line);
        }
        fin.close();
    }
}

void formater::exportAllLines(const string& file) {
    if (0 == m_sResult.compare("ok")) {
        fstream fout(file.c_str(), ios_base::out | ios_base::trunc);
        if (fout.fail()) {
            m_sResult = "file create failed";
        } else {
            for_each(m_Lines.begin(), m_Lines.end(), trimRight);
            copy(m_Lines.begin(), m_Lines.end(), ostream_iterator<string>(fout, "\n"));
        }
    }
}

void formater::createHtmlDocument() {
    // add line breaks at the end of each line
    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        basic_stringstream<char> psz2;
        *iter = psz2.str().append(*iter).append("</p>");
    }

    // add css styles at the top of the document
    string css_settings;
    css_settings.append("<style TYPE='text/css'> <!-- ")
            .append("p { line-height: 100%; } ")
            .append("body { font-family: 'courier new'; line-height: 100%; } ")
            .append("--> </style>");
    m_Lines.push_front(css_settings.c_str());
}

void formater::formatPre() {
    line_status ls;
    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        // encode strings with base64 to avoid formating
        parseLine(*iter, ls, true);

        // replace pattern
        *iter = replacePattern(m_replacePatternsPreprocessing, *iter, 1);
    }
    for_each(m_Lines.begin(), m_Lines.end(), trimRight);
}

void formater::formatPost() {
    line_status ls;
    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        string line = *iter;

        // calcualte layer based on commands
        for_each(m_commands.begin(), m_commands.end(), layer_counter(&ls, line));

        // set special color for commands 
        if (m_bCreateHtml) {
            line = for_each(m_commands.begin(), m_commands.end(), formater_mark_html(line));
        }

        // decode strings  
        parseLine(line, ls, false);

        // remove some strings
        line = replacePattern(m_replacePatternsPostprocessing, line, 5);

        // create indenting (but not for first line)
        if (m_Lines.begin() != iter) {
            createIndenting(line, ls);
        }

        // store current line
        *iter = line;

        // reset state for next line
        ls.SetOnce(0);
    }

    for_each(m_Lines.begin(), m_Lines.end(), trimRight);
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

    if (m_bCreateHtml && !encode) {
        insertHtmlFont(index, line, ls);
    }

    do {
        if (ls.inCode()) {
            if (line[index] == '"') {
                ls.SetActiveString();
                if (m_bCreateHtml && !encode) {
                    insertHtmlFont(index, line, ls);
                }
                indexStart = index; 
            } else if (line[index] == '\'') {
                ls.SetActiveCharacterString();
                if (m_bCreateHtml && !encode) {
                    insertHtmlFont(index, line, ls);
                }
                indexStart = index; 
            } else if (line[index] == '`') {
                ls.SetActiveMacro();
                if (m_bCreateHtml && !encode) {
                    insertHtmlFont(index, line, ls);
                }
                indexStart = index;
            }
        } else if (ls.inString() || ls.inCharacterString()) {
            if ((ls.inString() && line[index] == '"' && index > 1 && line[index - 1] != '\\') ||
                    (ls.inCharacterString() && line[index] == '\'' && index > 1 && line[index - 1] != '\\')) {
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
                if (m_bCreateHtml && !encode) {
                    insertHtmlFont(++index, line, ls);
                }
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
                if (m_bCreateHtml && !encode) {
                    insertHtmlFont(++index, line, ls);
                }
                indexStart = index;
            }
        }
    } while (++index <= line.size());

    if (ls.inString()) {
        m_sResult = "invalid string";
    }

    return false;
}

void formater::createIndenting(string &line, line_status & ls) {

    for (int i = 0; i < ls.GetLayerTotal(); i++) {
        line.insert(0, m_bCreateHtml ? "&nbsp;&nbsp;&nbsp;" : "    ");
    }

}

void formater::replaceSubstrings(const index_string& begin, index_string& end, string & s) {
    if (begin != string::npos && end != string::npos && begin < end) {
        string midNeu;
        string mid = s.substr(begin, end - begin + 1).c_str();

        if (m_bCreateHtml) {
            midNeu = for_each(m_commands.begin(), m_commands.end(), formater_mark_html(mid));
        } else {
            midNeu = for_each(m_replacePatternsPreprocessing.begin(), m_replacePatternsPreprocessing.end(), formater_replace(mid));
        }
        s = s.substr(0, begin).append(midNeu).append(s.substr(end + 1, string::npos).c_str());
        end = begin + midNeu.length() - 1;
    }
}

void formater::removeEmptyAll() {
    bool bLineEmpty = false;
    bool bLineRemoved = false;
    bool bIsNotFirstLine = false;

    do {
        bLineRemoved = false;
        string line;
        for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
            line = *iter;
            bLineEmpty = (string::npos == line.find_last_not_of(" "));
            bIsNotFirstLine = (iter != m_Lines.begin());

            if (!bIsNotFirstLine && bLineEmpty) {
                // Leerzeile in der ersten Zeile öffnen
                iter = m_Lines.erase(iter);
                line = *iter;
                bLineRemoved = true;
            }
        }
    } while (bLineRemoved);
}

void formater::wrapLines(string pattern) {
    list<string> result;

    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        string line = *iter;
        if (pattern.size() <= line.size()) {
            bool isFirstTimeProcessed = false;
            bool isNewLineNeeded = false;
            do {
                index_string last = 0;
                index_string anf = line.find(pattern);
                if (anf != string::npos) {
                    if (!isFirstTimeProcessed) {
                        string lineAnfang = line.substr(0, anf);
                        result.push_back(lineAnfang);
                        isFirstTimeProcessed = true;
                    } else {
                        string startLine = pattern + line.substr(last, anf);
                        last = anf;
                        result.push_back(startLine);
                    }

                    line = line.substr(anf + pattern.size(), line.size());
                    isNewLineNeeded = true;
                } else {
                    if (!isFirstTimeProcessed) {
                        result.push_back(line);
                    } else {
                        result.push_back(pattern + line);
                    }
                    isNewLineNeeded = false;
                    isFirstTimeProcessed = true;
                }
            } while (isNewLineNeeded);
        }
    }

    m_Lines = result;
}

string formater::GetHtmlFontTag(unsigned long id) {
    const string sFontCode = "</font>\n<font color=black>";
    const string sFontString = "</font>\n<font color=orange>";
    const string sFontCharacter = "</font>\n<font color=orange>";
    const string sFontMacro = "</font>\n<font color=#04B404>";
    const string g_sFont[] = {sFontCode, sFontString, sFontCharacter, sFontMacro};
    if (id <= 3)
        return g_sFont[id];
    else
        return "<FONT>";
}

void formater::insertHtmlFont(index_string& pos, string& s, line_status& ls) {
    s.insert(pos, GetHtmlFontTag(ls.GetCurrentStatus()));
    pos += GetHtmlFontTag(ls.GetCurrentStatus()).length();
}





