//
// file: line_status.cpp
//
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



