/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   formater_test.h
 * Author: Markus
 *
 * Created on 19. Februar 2016, 19:05
 */

#ifndef FORMATER_TEST_H
#define FORMATER_TEST_H


#include "../src/std_typedef.h"
#include "../src/formater.h"
#include <cppunit/extensions/HelperMacros.h>

class formater_test : public CPPUNIT_NS::TestFixture, public formater  {
    CPPUNIT_TEST_SUITE(formater_test);
    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST_SUITE_END();

public:
    formater_test();
    virtual ~formater_test();
    void setUp();
    void tearDown();

private:
    void testMethod();
    
private:
   void executeTest(const string& name, const string soll);
   
   list<string> m_LinesSoll;
   int m_number, m_numberOk;
};

#endif /* FORMATER_TEST_H */

