#pragma once
//
// file: formater_test.h
//
class formater;
class formater_test : public formater {
public:
   formater_test();
   
private:
   void executeTest(const string& name, const string soll);
   
   list<string> m_LinesSoll;
   int m_number, m_numberOk;
   long m_time;
};

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
