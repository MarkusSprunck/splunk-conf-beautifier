#pragma once
//
// file: formater_mark_html.h
//
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

const string formater_mark_html::sFontCode = "</FONT><FONT face=\"courier new\" color=\"black\" size=\"-1\">";
const string formater_mark_html::sFontKeyword = "</FONT><FONT face=\"courier new\" color=\"mediumslateblue\" size=\"-1\">";
const string formater_mark_html::sFontMarked = "</FONT><FONT face=\"courier new\" color=\"darkred\" size=\"-1\">";

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
