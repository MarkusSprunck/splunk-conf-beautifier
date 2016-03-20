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

// #include "std_typedef.h"

 #include <cstdint> //or <stdint.h>
 #include <limits>
#include <vector>

using namespace std;

class line_status {
public:

    enum eStatus {
        IN_CODE, IN_MACRO, IN_SINGLE_QUOTE, IN_DOUBLE_QUOTE
    };

protected:

    enum eFlagIndex {
        STATUS, INDEX_COUNT, BRACKETS_COUNT, NUMBER_OF_ELEMENTS
    };

    vector<std::int32_t> status_current, status_once;

public:
    line_status();

    const bool inCode(void);
    const bool inMacro(void);
    const bool inDoubleQuoteString(void);
    const bool inSingleQuoteString(void);
    const bool inBrackets(void);

    std::int32_t GetStatus();

    void SetActiveBrackets(void);
    void SetActiveCode(void);
    void SetActiveMacro(void);
    void SetActiveDoubleQuoteString(void);
    void SetActiveSingleQuoteString(void);

    std::int32_t GetBracketsCount(void); // count valid for all lines
    std::int32_t GetLayerCount(void); // count valid for all lines
    std::int32_t GetLayerCountOnce(void); // count valid for the current line 
    std::int32_t GetLayerCountTotal(void); // sum of all counts

    void SetLayerCount(std::int32_t layer);
    void SetLayerCountOnce(std::int32_t layer);
    void SetBracketsCount(std::int32_t count);

};

