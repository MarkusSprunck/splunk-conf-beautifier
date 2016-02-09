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

#include <time.h>
#include "formater.h"
#include "formater_test.h"
#include "line_compare.h"

formater_test::formater_test(void)
{
    m_numberOk = m_number = m_time = 0;

    cout << endl;
    executeTest("long", "ok");
    executeTest("toString", "ok");
    executeTest("simple", "ok");

    cout << endl;
    cout << m_numberOk << " succeeded, ";
    cout << m_number - m_numberOk << " failed, ";
    cout << m_time << " clocks" << endl;
}

void formater_test::executeTest(const string& name, const string soll)
{
    clock_t start = clock();
    m_number++;
    m_sResult = "ok";
    m_LinesSoll.clear();
    m_Lines.clear();

    string quelle1 = name;
    quelle1.append(".txt");
    importLines(quelle1, m_Lines);

    string quelle2 = name;
    quelle2.append("-expected.txt");
    if (0 == soll.compare("ok"))
    {
        importLines(quelle2, m_LinesSoll);
    }
    cout << "run " << quelle1.c_str();

    // formater - start
    m_bCreateHtml = false;
    wrapLines("|");
    wrapLines("latest");
    removeEmptyAll();
    formatAll();
    // formater - end

    if (0 != m_sResult.compare(soll))
        cout << " error: " << m_sResult << endl;
    else
    {
        bool m_sResult = true;
        if (0 == soll.compare("ok"))
        {
            if (m_LinesSoll.size() <= m_Lines.size())
            {
                m_sResult = equal(m_LinesSoll.begin(), m_LinesSoll.end(), m_Lines.begin(), line_compare());
                if (!m_sResult)
                    cout << endl << "[soll|ist]";
            }
            else
            {
                m_sResult = equal(m_Lines.begin(), m_Lines.end(), m_LinesSoll.begin(), line_compare());
                if (!m_sResult)
                {
                    cout << endl << "[ist|soll]";
                }
            }
        }
        if (m_sResult)
            m_numberOk++;

        clock_t mytime = clock() - start;
        m_time += mytime;
        cout << ((m_sResult) ? " suceeded, " : " failed, ") << mytime << " clock(s)" << endl;
    }
};
