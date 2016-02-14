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


// useage: for_each(command.begin(), command.end(), formater_counter(&line_status, line));

#include "std_typedef.h"
#include "line_status.h"

using namespace std;

class layer_counter
{
    line_status* m_line_status;
    const string* m_line;

public:

    layer_counter(line_status* line_status, const string& line) : m_line_status(line_status), m_line(&line)
    {
    }

    // The function call to process the next element

    void operator()(const pair_command& p1)
    {
        if (string::npos != m_line->find(p1.first))
        {
            if (INCREMENT == (INCREMENT & p1.second) && 10 > (*m_line_status).GetLayer())
            {
                (*m_line_status).SetLayer(1 + (*m_line_status).GetLayer());
            }
           
            if (DECREMENT == (DECREMENT & p1.second) && 1 <= (*m_line_status).GetLayer())
            {
                (*m_line_status).SetLayer(1 - (*m_line_status).GetLayer());
            }
        }        
    }
};

