#pragma once
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


#include "base64.h"

class formater_mark_html {
   static const string sFontCode;
   static const string sFontKeyword;
   static const string sFontMarked;
   string line;
   
public:
   formater_mark_html(const string& s): line(s) {
   }
   
   // The function call to process the next element
   void operator () (const pair_command& p1) {
      string value = p1.first;
      long command = p1.second;
      index_string anf = line.find(value);
      while (string::npos!=anf) {
         size_t length = 0;
         string start = "";
         if (0<anf){
            start = line.substr(anf-1, 1);
         }
         
         string temp(" }{*+-,:<>\t&");
         if (string::npos==start.find_first_not_of(temp)) {
            string right = line.substr(anf+value.size(), string::npos);
            line = line.substr(0, anf);
            if (KEYWORD==(command & KEYWORD)) {
               length = sFontKeyword.length() + sFontCode.length();
               line.append(sFontKeyword).append(value).append(sFontCode);
            }
            else if (MARK==(command & MARK)) {
               length = sFontMarked.length() + sFontCode.length();
               line.append(sFontMarked).append(value).append(sFontCode);
            }
            else {
               line.append(value);
            }
            line.append(right);
         }
         anf = line.find(value, anf + value.length() +length);
      }
   }
   
   // The function call to get the return value
   operator string () {
      return line;
   }
};

const string formater_mark_html::sFontCode = "</FONT>\n<FONT face=\'courier new\' color=\'black\'>";
const string formater_mark_html::sFontKeyword = "</FONT>\n<FONT face=\'ourier new\' color=\'blue\'>";
const string formater_mark_html::sFontMarked = "</FONT>\n<FONT face=\'courier new\' color=\'grey\'>";
