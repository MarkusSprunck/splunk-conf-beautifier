#pragma once
//
// file: formater_counter.h
//
// useage: for_each(command.begin(), command.end(), formater_counter(&line_status, line));
//

#include "std_typedef.h"
#include "line_status.h"

using namespace std;

class layer_counter {
    line_status* m_line_status;
    const string* m_line;

public:

    layer_counter(line_status* line_status, const string& line) : m_line_status(line_status), m_line(&line) {
    }

    // The function call to process the next element

    void operator()(const pair_command& p1) {
        if (string::npos != m_line->find(p1.first)) {
            if (INCREMENT == (INCREMENT & p1.second)) {
                if ((*m_line_status).GetLayerCount() == 0) {
                    (*m_line_status).IncrementMacro();
                }
            }
        }
    }
};


