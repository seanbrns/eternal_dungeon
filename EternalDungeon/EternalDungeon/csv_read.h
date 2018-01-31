#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class csv_read
{
public:
    csv_read();
    ~csv_read();
    std::vector<std::vector<std::string>> csv_read::read_table(const std::string &file_name);
};

