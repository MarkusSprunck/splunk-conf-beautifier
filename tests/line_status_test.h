/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   line_status_test.h
 * Author: Markus
 *
 * Created on 19. Februar 2016, 18:13
 */

#ifndef LINE_STATUS_TEST_H
#define LINE_STATUS_TEST_H

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

using namespace std;
#include <cppunit/extensions/HelperMacros.h>

class line_status_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(line_status_test);
    CPPUNIT_TEST(test_default_values);
    CPPUNIT_TEST(test_set_simple_values);
    CPPUNIT_TEST(test_set_active_macro);
    CPPUNIT_TEST(test_set_active_string);
    CPPUNIT_TEST(test_set_active_code);
    CPPUNIT_TEST_SUITE_END();

public:
    line_status_test();
    virtual ~line_status_test();
    void setUp();
    void tearDown();

private:
    void test_default_values();
    void test_set_simple_values();
    void test_set_active_macro();
    void test_set_active_string();
    void test_set_active_code();
      
    
    
};

#endif /* LINE_STATUS_TEST_H */

