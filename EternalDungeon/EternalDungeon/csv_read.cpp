#include "stdafx.h"
#include <iostream>
#include "csv_read.h"
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include <stdlib.h>

std::ifstream m_ifs;

csv_read::csv_read()
{
}

csv_read::~csv_read()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::open
/////////////////////////////////////////////////////////////////////////////////////////////////////
static int openCsv(const std::string &file_name)
{
    m_ifs.open(file_name.c_str());
    if (!m_ifs.is_open())
    {
        return -1;
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::read_row
/////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<std::string>> csv_read::read_table(const std::string &file_name)
{
    bool quote_mode = false;
    std::vector<std::vector<std::string>> table;
    std::vector<std::string> row;
    std::string str;
    char c;

    if (openCsv(file_name) < 0)
    {
        std::cout << "Cannot open file " << file_name << std::endl;
        return table;
    }

    while (m_ifs.get(c))
    {
        switch (c)
        {
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            //separator ',' detected. 
            //in quote mode add character to column
            //push column if not in quote mode
            /////////////////////////////////////////////////////////////////////////////////////////////////////
        case ',':
            if (quote_mode == true)
            {
                str += c;
            }
            else
            {
                row.push_back(str);
                str.clear();
            }
            break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////
            //quote '"' detected. 
            //toggle quote mode
            /////////////////////////////////////////////////////////////////////////////////////////////////////
        case '"':
            quote_mode = !quote_mode;
            break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////
            //line end detected
            //in quote mode add character to column
            //return row if not in quote mode
            /////////////////////////////////////////////////////////////////////////////////////////////////////
        case '\n':
        case '\r':
            if (quote_mode == true)
            {
                str += c;
            }
            else
            {
                row.push_back(str);
                str.clear();

                // copy row into table then clear it
                table.push_back(row);
                row.clear();
            }
            break;

            /////////////////////////////////////////////////////////////////////////////////////////////////////
            //default, add character to column
            /////////////////////////////////////////////////////////////////////////////////////////////////////
        default:
            str += c;
            break;
        }
    }

    m_ifs.close();

    return table;
}