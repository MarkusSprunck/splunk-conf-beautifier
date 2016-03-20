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


#include "include\line_status.h"
#include "include\string_utils.h"

line_status::line_status(void) :
status_current(eFlagIndex::NUMBER_OF_ELEMENTS),
status_once(eFlagIndex::NUMBER_OF_ELEMENTS) {
    status_current[INDEX_COUNT] = 0;
    status_current[BRACKETS_COUNT] = 0;
    status_current[STATUS] = IN_CODE;
    status_once[INDEX_COUNT] = 0;
    status_once[STATUS] = IN_CODE;
}

const bool line_status::inCode(void) {
    return (IN_CODE == status_current[STATUS]);
}

const bool line_status::inMacro(void) {
    return (IN_MACRO == status_current[STATUS]);
}

const bool line_status::inDoubleQuoteString(void) {
    return (IN_DOUBLE_QUOTE == status_current[STATUS]);
}

const bool line_status::inSingleQuoteString(void) {
    return (IN_SINGLE_QUOTE == status_current[STATUS]);
}

const bool line_status::inBrackets(void) {
    return (0 < status_current[BRACKETS_COUNT]);
}

void line_status::SetActiveCode(void) {
    status_current[STATUS] = IN_CODE;
}

void line_status::SetActiveMacro(void) {
    status_current[STATUS] = IN_MACRO;
}

void line_status::SetActiveDoubleQuoteString(void) {
    status_current[STATUS] = IN_DOUBLE_QUOTE;
}

void line_status::SetActiveSingleQuoteString(void) {
    status_current[STATUS] = IN_SINGLE_QUOTE;
}

long line_status::GetBracketsCount(void) {
    return status_current[BRACKETS_COUNT];
}

long line_status::GetLayerCount(void) {
    return status_current[INDEX_COUNT];
}

long line_status::GetLayerCountTotal(void) {
    return status_current[INDEX_COUNT] + status_once[INDEX_COUNT];
}

void line_status::SetLayerCount(int layer) {
    status_current[INDEX_COUNT] = layer;
}

long line_status::GetStatus() {
    return status_current[STATUS];
}

long line_status::GetLayerCountOnce(void) {
    return status_once[INDEX_COUNT];
}

void line_status::SetLayerCountOnce(int layer) {
    status_once[INDEX_COUNT] = layer;
}

void line_status::SetBracketsCount(int count) {
    status_current[BRACKETS_COUNT] = count;
}
