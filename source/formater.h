#pragma once
//
// file: formater.h
//
#include "std_typedef.h"

static const string g_sVersion = "spl2html v0.1";

class line_status;
class formater {
public:
   explicit formater();
   
   void run(const string& inputFile);

protected:
   
   // file input & output
   void importLines(const string& file, list<string>& m_Lines);
   void exportLines(const string& file);
   
   // each line
   void formatAll();
   void removeEmptyAll();
   void wrapLines();
   void appendLineNumbersToHtmlAll();
   
   // single line
   bool parseLine(string &line, line_status& ls);
   void replaceSubstrings(const index_string& begin, index_string& end, string &s);
   static void createIndenting(string &line, line_status& ls);
   
   // support for string manipulation
   static void trimRight(string &s);
   static void trimLeft(string &s);
   
   // succsses information
   string m_sResult;
   
   // create a html file
   bool m_bCreateHtml;
   
   // file content
   list<string> m_Lines;
   
   // commands for each 'string pattern'
   map<string, long> m_commands;
   
   // string replace map
   map<string, string> m_replacePatterns, m_replacePatternsHtml;
};

/* Copyright (c) 2003-2004 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
