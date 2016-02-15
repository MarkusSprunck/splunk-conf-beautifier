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
 * File:   string_compare_test.cpp
 * Author: Markus
 * 
 * Created on 15. Februar 2016, 20:56
 */

#include <map>
#include <list>
#include <queue>
#include <string>
#include <iostream>
#include <iterator> 
#include <ostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


#include "string_compare_test.h"
#include "../src/string_compare.h"
#include "../src/string_utils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(string_compare_test);

string_compare_test::string_compare_test() {
}

string_compare_test::~string_compare_test() {
}

void string_compare_test::setUp() {
}

void string_compare_test::tearDown() {
    firstStringList.clear();
    secondStringList.clear();
}

void string_compare_test::test_compare_equal_strings() {

    // given
    string firstString = "1234567";
    string secondString = "abcde";
    firstStringList.push_front(firstString);
    firstStringList.push_back(secondString);
    secondStringList.push_front(firstString);
    secondStringList.push_back(secondString);

    // when
    bool result = equal(firstStringList.begin(), firstStringList.end(), secondStringList.begin(), string_compare());

    // then
    CPPUNIT_ASSERT(result);
}

void string_compare_test::test_compare_not_equal_strings() {

    // given
    string firstString = "1234567";
    string secondString = "abcde";
    string secondString_with_difference = "abcxde";
    firstStringList.push_front(firstString);
    firstStringList.push_back(secondString);
    secondStringList.push_front(firstString);
    secondStringList.push_back(secondString_with_difference);

    // when
    bool result = equal(firstStringList.begin(), firstStringList.end(), secondStringList.begin(), string_compare());

    // then
    CPPUNIT_ASSERT(!result);
}
