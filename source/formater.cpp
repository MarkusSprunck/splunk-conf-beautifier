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
#include "layer_counter.h"
#include "formater_replace.h"
#include "formater_mark_html.h"

formater::formater() :
m_sResult("ok"),
m_bCreateHtml(true),
m_commands(getCommand()),
m_replacePatterns(getReplace()),
m_replacePatternsHtml(getReplaceHtml()) {
}

void formater::run(const string& inputFile) {
    importLines(inputFile, m_Lines);

    m_bCreateHtml = false;
    wrapLines();
    removeEmptyAll();
    formatAll();
    string outputFileResult = string(inputFile).append(".result");
    exportLines(outputFileResult);
    cout << string("create 'file://").append(outputFileResult).append("' ").append(m_sResult) << endl;

    m_bCreateHtml = true;
    formatAll();
    appendLineNumbersToHtmlAll();
    string outputFileHtml = string(inputFile).append(".html");
    exportLines(outputFileHtml);
    cout << string("create 'file://").append(outputFileHtml).append("' ").append(m_sResult) << endl;
}

void formater::importLines(const string& file, list<string>& m_Lines) {
    fstream fin(file.c_str(), ios_base::in);
    if (fin.fail())
        m_sResult = "file open failed";
    else {
        string line;
        while (getline(fin, line) && (!fin.fail())) {

            // replace '&' for html file
            if (m_bCreateHtml)
                formater_replace::repeated_replace(line, "&", "&amp");

            formater::trimRight(line);
            m_Lines.push_back(line);
        }
        fin.close();
    }
}

void formater::exportLines(const string& file) {
    if (0 == m_sResult.compare("ok")) {
        fstream fout(file.c_str(), ios_base::out | ios_base::trunc);

        if (fout.fail())
            m_sResult = "file create failed";
        else
            copy(m_Lines.begin(), m_Lines.end(), ostream_iterator<string>(fout, "\n"));
    }
}

void formater::appendLineNumbersToHtmlAll() {
    long l = 0;
    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        basic_stringstream<char> psz2;
        //  psz2 << line_status::GetHtmlFontTag();
        //  psz2.fill('0');
        //  psz2.width(4);
        //  psz2 << ++l << "&nbsp;&nbsp;";
        *iter = psz2.str().append(*iter).append("<br/>");
    }

    string s = "<P align=\"right\">";
    s.append(line_status::GetHtmlFontTag());
    s.append(g_sVersion);
    s.append("<br/>by Markus Sprunck<br/>");
    m_Lines.push_back(s);
}

void formater::formatAll() {
    line_status ls;
    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        parseLine(*iter, ls);
        for_each(m_commands.begin(), m_commands.end(), layer_counter(&ls, *iter));
        createIndenting(*iter, ls);
        ls.storeLastFlags();
    }
    for_each(m_Lines.begin(), m_Lines.end(), formater::trimRight);
}

bool formater::parseLine(string &line, line_status& ls) {
    index_string indexStart = 0;
    index_string index = 0;

    if (m_bCreateHtml) {
        line = for_each(m_replacePatternsHtml.begin(), m_replacePatternsHtml.end(), formater_replace(line));
        ls.insertHtmlFont(index, line);
    }

    do {
        if (ls.inCode()) {
            switch (line[index]) {
                case '"':
                {
                    replaceSubstrings(indexStart, index, line);
                    ls.SetActiveString();
                    if (m_bCreateHtml)
                        ls.insertHtmlFont(index, line);
                    break;
                }
                case '\'':
                {
                    replaceSubstrings(indexStart, index, line);
                    ls.SetActiveCharacter();
                    if (m_bCreateHtml)
                        ls.insertHtmlFont(index, line);
                    break;
                }
            }

            if (index == (line.length() - 1)) {
                replaceSubstrings(indexStart, index, line);
                ls.SetActiveCode();
                indexStart = index;
            }
        } else {
            if (ls.inString()) {
                if ((index > 1) && (line[index] == '"')) {
                    ls.SetActiveCode();
                    if (m_bCreateHtml) {
                        ls.insertHtmlFont(++index, line);
                        index--;
                    }
                    indexStart = index;
                }
            } else if (ls.inCharacter()) {
                if ((line[index] == '\'')) {
                    ls.SetActiveCode();
                    if (m_bCreateHtml) {
                        ls.insertHtmlFont(++index, line);
                        index--;
                    }
                    indexStart = index;
                }
            }
        }
    } while (++index <= line.size());

    if (ls.inString())
        m_sResult = "invalid string";
    else if (ls.inCharacter())
        m_sResult = "invalid character";

    return false;
}

void formater::createIndenting(string &line, line_status& ls) {
    for (int i = 0; i < ls.GetLayerCount(); i++) {
        line.insert(0, "    ");
    }
}

void formater::replaceSubstrings(const index_string& begin, index_string& end, string &s) {
    if (begin != string::npos && end != string::npos && begin < end) {
        string midNeu;
        string mid = s.substr(begin, end - begin + 1).c_str();

        if (m_bCreateHtml)
            midNeu = for_each(m_commands.begin(), m_commands.end(), formater_mark_html(mid));
        else
            midNeu = for_each(m_replacePatterns.begin(), m_replacePatterns.end(), formater_replace(mid));

        s = s.substr(0, begin).append(midNeu).append(s.substr(end + 1, string::npos).c_str());
        end = begin + midNeu.length() - 1;
    }
}

void formater::removeEmptyAll() {
    bool bLineEmpty = false;
    bool bLineRemoved = false;
    bool bLastLineEmpty = false;
    bool bIsNotFirstLine = false;
    bool bLastLineBracket = false;

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

void formater::wrapLines() {

    list<string> result;

    for (list <string>::iterator iter = m_Lines.begin(); iter != m_Lines.end(); iter++) {
        string line = *iter;
        if (1 <= line.size()) {
            bool isFirstTimeProcessed = false;
            bool isNewLineNeeded = false;
            do {
                index_string last = 0;
                index_string anf = line.find_first_of('|', last);
                if (anf != string::npos) {
                    if (!isFirstTimeProcessed) {
                        string lineAnfang = line.substr(0, anf);
                        result.push_back(lineAnfang);
                        isFirstTimeProcessed = true;

                    } else {
                        string startLine = "|" + line.substr(last, anf);
                        last = anf;
                        result.push_back(startLine);
                    }

                    line = line.substr(anf + 1, line.size());
                    isNewLineNeeded = true;

                } else {
                    if (!isFirstTimeProcessed) {
                        result.push_back(line);
                    } else {
                        result.push_back("|" + line);
                    }
                    isNewLineNeeded = false;
                    isFirstTimeProcessed = true;
                }
            } while (isNewLineNeeded);
        }
    }

    m_Lines = result;
}

void formater::trimLeft(string &s) {
    index_string anf = s.find_first_not_of(" \t");
    if (string::npos != anf)
        s = s.substr(anf);
    else
        s.erase();
}

void formater::trimRight(string &s) {
    index_string anf = s.find_last_not_of(" \t\r");
    if (string::npos != anf)
        s = s.substr(0, anf + 1);
    else
        s.erase();
}


