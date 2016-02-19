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
    CPPUNIT_ASSERT(ls.GetOnce() == 0);
    CPPUNIT_ASSERT(ls.GetLayer() == 0);
    CPPUNIT_ASSERT(ls.GetLayerTotal() == 0);
    CPPUNIT_ASSERT(ls.GetCurrentStatus() == line_status::eStatusValue::CODE);
}

void line_status_test::test_set_simple_values() {
    // given
    line_status ls;

    // when
    ls.SetOnce(2);
    ls.SetLayer(3);
    ls.SetActiveMacro();

    // then
    CPPUNIT_ASSERT(ls.GetOnce() == 2);
    CPPUNIT_ASSERT(ls.GetLayer() == 3);
    CPPUNIT_ASSERT(ls.GetLayerTotal() == 5);
    CPPUNIT_ASSERT(ls.GetCurrentStatus() == line_status::eStatusValue::MACRO);
}

void line_status_test::test_set_active_macro() {
    // given
    line_status ls;

    // when
    ls.SetActiveMacro();

    // then
    CPPUNIT_ASSERT(ls.GetCurrentStatus() == line_status::eStatusValue::MACRO);
}

void line_status_test::test_set_active_code() {
    // given
    line_status ls;

    // when
    ls.SetActiveMacro();
    ls.SetActiveCode();

    // then
    CPPUNIT_ASSERT(ls.GetCurrentStatus() == line_status::eStatusValue::CODE);
}


void line_status_test::test_set_active_string() {
    // given
    line_status ls;

    // when
    ls.SetActiveString();

    // then
    CPPUNIT_ASSERT(ls.GetCurrentStatus() == line_status::eStatusValue::STRINGS);
}


