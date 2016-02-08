#pragma once
//
// file: line_status.h
//
#include "std_typedef.h"

class line_status {

    enum eStatusValue {
        COMMENT, STRINGS, CHARACTER, CODE, NONE
    };

    enum eBoolValue {
        IS_FALSE, IS_TRUE
    };

    enum eFlagIndex {
        STATUS, MACRO, INDEX_COUNT
    };

    vector<long> current, last, before_last;

public:
    line_status();

    void storeLastFlags(void);

    const bool inCode(void);
    const bool inMacro(void);
    const bool inString(void);
    const bool inCharacter(void);
    const bool inComment(void);
    const bool inCommentLast(void);
    const bool inCommentBlock(void);

    void SetActiveCode(void);
    void SetActiveCommend(void);
    void SetActiveString(void);
    void SetActiveCharacter(void);

    static string GetHtmlFontTag(unsigned long id = line_status::NONE);
    void insertHtmlFont(index_string& pos, string& s);

    void IncrementMacro(void);
    void DecrementMacro(void);

    long GetLayerCount(void);
};

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
