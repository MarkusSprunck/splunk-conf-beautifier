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

