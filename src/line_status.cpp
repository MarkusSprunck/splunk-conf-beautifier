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
#include "string_utils.h"

line_status::line_status(void) :
current(INDEX_COUNT),
last(INDEX_COUNT) {
    current[INDEX_COUNT] = 0;
    current[STATUS] = CODE;
    last = current;
}

void line_status::storeLastFlags() {
    last = current;
}

const bool line_status::inCode(void) {
    return (CODE == current[STATUS]);
}

const bool line_status::inMacro(void) {
    return (MACRO == current[STATUS]);
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

void line_status::SetActiveString(void) {
    current[STATUS] = STRINGS;
}

void line_status::SetActiveCharacter(void) {
    current[STATUS] = CHARACTER;
}

long line_status::GetLayer(void) {
    return current[INDEX_COUNT];
}

void line_status::SetLayer(int layer) {
    current[INDEX_COUNT] = layer;
}

long line_status::GetCurrentStatus() {
    return current[STATUS];
}



