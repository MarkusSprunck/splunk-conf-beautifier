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

/* 
 * File:   formater_test.cpp
 * Author: Markus
 * 
 * Created on 19. Februar 2016, 19:05
 */


#include "formater_test.h"
#include "string_compare.h"
#include <time.h>
#include "../src/formater.h"
#include "../src/string_utils.h"


CPPUNIT_TEST_SUITE_REGISTRATION(formater_test);

formater_test::formater_test() {
}

formater_test::~formater_test() {
}

void formater_test::setUp() {
}

void formater_test::tearDown() {
}

void formater_test::testMethod() {

    m_numberOk = m_number = 0;

    executeTest("./data/eval-if", "ok");
    executeTest("./data/join", "ok");
    executeTest("./data/subsearch", "ok");
    executeTest("./data/long", "ok");
    executeTest("./data/toString", "ok");
    executeTest("./data/simple", "ok");
    executeTest("./data/strings", "ok");
    executeTest("./data/strings-single-quote", "ok");
    executeTest("./data/append", "ok");
    executeTest("./data/to_string_commas_locale", "ok");
    executeTest("./data/to_string_commas_locale_hair_space_before_point", "ERROR: file contains non ascii character");
    executeTest("./data/not_existing_file", "ERROR: file open failed");

    cout << "   " << m_numberOk << " succeeded, ";
    cout << m_number - m_numberOk << " failed, ";

    CPPUNIT_ASSERT(m_number == m_numberOk);
}

void formater_test::executeTest(const string& name, const string expected) {

    m_number++;
    result = "ok";
    m_LinesSoll.clear();
    lines.clear();

    string quelle1 = name;
    quelle1.append(".txt");
    cout << "   run " << quelle1.c_str() << " expected=" << expected << endl;

    importAllLines(quelle1, lines);

    string quelle2 = name;
    quelle2.append("-expected.txt");
    if (0 == expected.compare("ok")) {
        importAllLines(quelle2, m_LinesSoll);
        for_each(m_LinesSoll.begin(), m_LinesSoll.end(), trimRight);
    } else if (0 == result.compare(expected)) {
        cout << " suceeded" << endl;
        m_numberOk++;
        return;
    }

    // formater - start
    for_each(lines.begin(), lines.end(), trimLeft);
    for_each(lines.begin(), lines.end(), trimRight);
    format();
    // formater - end

    if (0 != result.compare(expected))
        cout << " error: " << result << endl;
    else {
        bool result = true;
        if (0 == expected.compare("ok")) {
            if (m_LinesSoll.size() <= lines.size()) {
                result = equal(m_LinesSoll.begin(), m_LinesSoll.end(), lines.begin(), string_compare(true));
                if (!result) {
                    cout << endl << "[expected|actual]";
                }
            } else {
                result = equal(lines.begin(), lines.end(), m_LinesSoll.begin(), string_compare(true));
                if (!result) {
                    cout << endl << "[expected|actual]";
                }
            }
        }
        if (result) {
            m_numberOk++;
        }
        cout << ((result) ? " suceeded " : " failed ") << endl;
    }
};

