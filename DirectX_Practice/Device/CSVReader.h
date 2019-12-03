#pragma once

#include <string>
#include <vector>

class CSVReader {
public:
    CSVReader();
    ~CSVReader();
    static const std::vector<char>& read(const char* fileName);
    static int getWidth();
    static int getHeight();

private:
    static std::vector<char> mCSV;
    static int mWidthCount;
    static int mHeightCount;
};
