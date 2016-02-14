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
 * File:   string_util_test.cpp
 * Author: Markus Sprunck
 *
 * Created on 14.02.2016, 11:06:08
 */

#include "string_util_test.h"

#include "../src/string_utils.h"



CPPUNIT_TEST_SUITE_REGISTRATION(string_util_test);

string_util_test::string_util_test() {
}

string_util_test::~string_util_test() {
}

void string_util_test::setUp() {
}

void string_util_test::tearDown() {
}

void string_util_test::test_trimLeft_simple() {
    // given
    string value = "  abc";
    string expected = "abc";

    // when 
    trimLeft(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, value);
}

void string_util_test::test_trimLeft_not_trim_right() {
    // given
    string value = "  abc ";
    string expected = "abc ";

    // when 
    trimLeft(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, value);
}

void string_util_test::test_trimLeft_empty_string() {
    // given
    string value = "";
    string expected = "";

    // when 
    trimLeft(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, value);
}

void string_util_test::test_trimRight_simple() {
    // given
    string value = "abc ";
    string expected = "abc";

    // when 
    trimRight(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, value);
}

void string_util_test::test_trimRight_not_trim_left() {
    // given
    string value = "  abc  ";
    string expected = "  abc";

    // when 
    trimRight(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, value);
}

void string_util_test::test_trimRight_empty_string() {
    // given
    string value = "";
    string expected = "";

    // when 
    trimRight(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, value);
}

void string_util_test::test_encode() {
    // given
    string value = "1234567890AaBbCc ,.-!";
    string expected = "MTIzNDU2Nzg5MEFhQmJDYyAsLi0h";

    // when 
    string result = base64_encode(value);
    // cout << "'" << result << "'" << endl;

    // then
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void string_util_test::test_decode() {
    // given
    string value = "MTIzNDU2Nzg5MEFhQmJDYyAsLi0h";
    string expected = "1234567890AaBbCc ,.-!";

    // when 
    string result = base64_decode(value);

    // then
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

