/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   string_util_test.h
 * Author: Markus
 *
 * Created on 14.02.2016, 11:06:08
 */

#ifndef STRING_UTIL_TEST_H
#define STRING_UTIL_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class string_util_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(string_util_test);

    CPPUNIT_TEST(test_trimLeft_simple);
    CPPUNIT_TEST(test_trimLeft_not_trim_right);

    CPPUNIT_TEST_SUITE_END();

public:
    string_util_test();
    virtual ~string_util_test();
    void setUp();
    void tearDown();

private:
    void test_trimLeft_simple();
    void test_trimLeft_not_trim_right();
};

#endif /* STRING_UTIL_TEST_H */

