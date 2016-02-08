//
// file: formater_test.cpp
//
#include <time.h>
#include "formater.h"
#include "formater_test.h"
#include "line_compare.h"

formater_test::formater_test(void) {
    m_numberOk = m_number = m_time = 0;

    cout << endl;
    executeTest("toString", "ok");
    executeTest("simple", "ok");

    cout << endl;
    cout << m_numberOk << " succeeded, ";
    cout << m_number - m_numberOk << " failed, ";
    cout << m_time << " clocks" << endl;
}

void formater_test::executeTest(const string& name, const string soll) {
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
    if (0 == soll.compare("ok")) {
        importLines(quelle2, m_LinesSoll);
    }
    cout << "run " << quelle1.c_str();

    // formater - start
    m_bCreateHtml = false;
    wrapLines();
    removeEmptyAll();
    formatAll();
    // formater - end

    if (0 != m_sResult.compare(soll))
        cout << " error: " << m_sResult << endl;
    else {
        bool m_sResult = true;
        if (0 == soll.compare("ok")) {
            if (m_LinesSoll.size() <= m_Lines.size()) {
                m_sResult = equal(m_LinesSoll.begin(), m_LinesSoll.end(), m_Lines.begin(), line_compare());
                if (!m_sResult)
                    cout << endl << "[soll|ist]";
            } else {
                m_sResult = equal(m_Lines.begin(), m_Lines.end(), m_LinesSoll.begin(), line_compare());
                if (!m_sResult) {
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

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
