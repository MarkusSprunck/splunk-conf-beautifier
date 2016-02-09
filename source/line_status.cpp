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

#include "line_status.h"

line_status::line_status(void) :
current(INDEX_COUNT),
last(INDEX_COUNT),
before_last(INDEX_COUNT) {
    current[MACRO] = 0;
    current[STATUS] = CODE;
    last = current;
}

void line_status::storeLastFlags() {
    before_last = last;
    last = current;
}

const bool line_status::inCode(void) {
    return (CODE == current[STATUS]);
}

const bool line_status::inString(void) {
    return (STRINGS == current[STATUS]);
}

const bool line_status::inCharacter(void) {
    return (CHARACTER == current[STATUS]);
}

void line_status::SetActiveCode(void) {
    current[STATUS] = CODE;
}

void line_status::SetActiveMacro(void) {
    current[STATUS] = MACRO;
}

void line_status::SetActiveCommend(void) {
    current[STATUS] = COMMENT;
}

void line_status::SetActiveString(void) {
    current[STATUS] = STRINGS;
}

void line_status::SetActiveCharacter(void) {
    current[STATUS] = CHARACTER;
}

string line_status::GetHtmlFontTag(unsigned long id) {
    const string sFontCode = "</FONT><FONT face=\"courier new\" color=\"black\" size=\"-1\">";
    const string sFontCharacter = "</FONT><FONT face=\"courier new\" color=\"orange\" size=\"-1\">";
    const string sFontComment = "</FONT><FONT face=\"courier new\" color=\"grey\" size=\"-1\">";
    const string sFontString = "</FONT><FONT face=\"courier new\" color=\"orange\" size=\"-1\">";
    const string sFontNumber = "</FONT><FONT face=\"courier new\" color=\"lightgrey\" size=\"-1\">";
    const string g_sFont[] = {sFontComment, sFontString, sFontCharacter, sFontCode, sFontNumber};
    if (id <= 4)
        return g_sFont[id];
    else
        return "";
}

void line_status::insertHtmlFont(index_string& pos, string& s) {
    s.insert(pos, GetHtmlFontTag(current[STATUS]));
    pos += GetHtmlFontTag(current[STATUS]).length();
}

void line_status::IncrementMacro(void) {
    current[MACRO]++;
}

void line_status::DecrementMacro(void) {
    current[MACRO]--;
}

long line_status::GetLayerCount(void) {
    return current[MACRO];
}

const bool line_status::inMacro(void) {
    return (1 <= current[MACRO]);
}



