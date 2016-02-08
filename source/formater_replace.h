#pragma once
//
// file: formater_replace.h
//
#include "std_typedef.h"

class formater_replace {
   string str;
   
public:
   explicit formater_replace (const string& s): str(s) {
   }
   
   static bool repeated_replace(string& s1, const string& s2, const string& s3) {
      bool bResult = false;
      index_string anf = s1.find(s2);
      while (string::npos!=anf) {
         // replace s2 with s3 in s1
         string r(s1.substr(anf+s2.size(), string::npos));
         string left(s1.substr(0, anf));
         s1 = left.append(s3).append(r);
         anf = s1.find(s2, anf + s3.size());
         bResult = true;
      }
      return bResult;
   }
   
   // The function call to process the next element
   void operator () (const pair_string& p1) {
      for (;repeated_replace(str, p1.first, p1.second););
      }
   
   // The function call to get the return value
   operator string () {
      return str;
   }
};

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
