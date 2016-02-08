//
// file: yaca.cpp
//
#include "formater.h"
#include "formater_test.h"

int main(int argc, char* argv[])
{
   //	parse command line
   if (2==argc && 0==string("-t").compare(argv[1]))
      formater_test t;
   else if ((3==argc) && (0==string("-h").compare(argv[1]))) {
      formater f;
      f.run(argv[2]);       
   }
   else {
      cout << "yaca.exe [Flag] [FilePath]" << endl;
      cout << "   " << g_sVersion << endl;
      cout << "   -h (create html file with line numbers)" << endl;
      cout << "   -t (test)" << endl;
   }
   return 0;
}

/* Copyright (c) 2016 by Markus Sprunck. ALL RIGHTS RESERVED. */
