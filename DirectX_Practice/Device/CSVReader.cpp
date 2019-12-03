#include "CSVReader.h"
#include "../System/Game.h"
#include <cassert>
#include <fstream>
#include <sstream>

CSVReader::CSVReader() = default;

CSVReader::~CSVReader() = default;

const std::vector<char>& CSVReader::read(const char* fileName) {
    //���g���Z�b�g
    mCSV.clear();

    setDataDirectory();

    //�ǂݍ��݊J�n
    std::ifstream ifs(fileName, std::ios::in);
    assert(ifs);

    std::string line;
    bool first = true;
    while (!ifs.eof()) {
        std::getline(ifs, line);

        const char delimiter = ',';
        for (const auto& s : line) {
            if (s != delimiter) {
                mCSV.emplace_back(s);
            }
        }

        if (first) {
            first = false;
            mWidthCount = mCSV.size();
        }
    }
    mHeightCount = mCSV.size() / mWidthCount;

    return mCSV;
}

int CSVReader::getWidth() {
    return mWidthCount;
}

int CSVReader::getHeight() {
    return mHeightCount;
}

std::vector<char> CSVReader::mCSV;
int CSVReader::mWidthCount = 0;
int CSVReader::mHeightCount = 0;
