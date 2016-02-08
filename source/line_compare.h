#pragma once
//
// file: line_compare.h
//

class line_compare {
    long count;

public:

    line_compare() : count(0) {
    }

    // The function call to process the next element

    bool operator()(const string& s1, const string& s2) {
        count++;        
        if (0 != s1.compare(s2)) {
            cout << endl << "line(" << count << "):";
            cout << endl << "\t[" << s1.size() << "]" << '\"' << s1.c_str() << '\"';
            cout << endl << "\t[" << s2.size() << "]" << '\"' << s2.c_str() << '\"';
            return false;
        }
        return true;
    }
};

/* Copyright (c) 2008-2011 by Markus W. Sprunck. ALL RIGHTS RESERVED. */
