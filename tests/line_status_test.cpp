/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   line_status_test.cpp
 * Author: Markus
 * 
 * Created on 19. Februar 2016, 18:13
 */

#include "line_status_test.h"

#include "../src/line_status.h"

CPPUNIT_TEST_SUITE_REGISTRATION(line_status_test);

line_status_test::line_status_test() {
}

line_status_test::~line_status_test() {
}

void line_status_test::setUp() {
}

void line_status_test::tearDown() {
}

void line_status_test::test_default_values() {

    // given
    line_status ls;

    // then
    CPPUNIT_ASSERT(ls.GetLayerCountOnce() == 0);
    CPPUNIT_ASSERT(ls.GetLayerCount() == 0);
    CPPUNIT_ASSERT(ls.GetLayerCountTotal() == 0);
    CPPUNIT_ASSERT(ls.GetStatus() == line_status::eStatus::IN_CODE);
}

void line_status_test::test_set_simple_values() {
    // given
    line_status ls;

    // when
    ls.SetLayerCountOnce(2);
    ls.SetLayerCount(3);
    ls.SetActiveMacro();

    // then
    CPPUNIT_ASSERT(ls.GetLayerCountOnce() == 2);
    CPPUNIT_ASSERT(ls.GetLayerCount() == 3);
    CPPUNIT_ASSERT(ls.GetLayerCountTotal() == 5);
    CPPUNIT_ASSERT(ls.GetStatus() == line_status::eStatus::IN_MACRO);
}

void line_status_test::test_set_active_macro() {
    // given
    line_status ls;

    // when
    ls.SetActiveMacro();

    // then
    CPPUNIT_ASSERT(ls.GetStatus() == line_status::eStatus::IN_MACRO);
}

void line_status_test::test_set_active_code() {
    // given
    line_status ls;

    // when
    ls.SetActiveMacro();
    ls.SetActiveCode();

    // then
    CPPUNIT_ASSERT(ls.GetStatus() == line_status::eStatus::IN_CODE);
}

void line_status_test::test_set_active_double_quote_string() {
    // given
    line_status ls;

    // when
    ls.SetActiveDoubleQuoteString();

    // then
    CPPUNIT_ASSERT(ls.GetStatus() == line_status::eStatus::IN_DOUBLE_QUOTE);
}

void line_status_test::test_set_active_single_quote_string() {
    // given
    line_status ls;

    // when
    ls.SetActiveSingleQuoteString();

    // then
    CPPUNIT_ASSERT(ls.GetStatus() == line_status::eStatus::IN_SINGLE_QUOTE);
}




