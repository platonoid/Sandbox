#include <fstream>
#include <iostream>
#include <exception>
#include <string>
#include "../vector/vector.h"
#pragma once

std::ifstream OpenFile(std::string path);

class FileParser {
    std::string path_;
public:
    int64_t ParseNumber(const char* str, int32_t& max_val);

    void ParseLine(const char* line, Vector<int64_t>& x_coord, Vector<int64_t>& y_coord, 
        Vector<uint64_t>& sand_in_coords, int32_t index, int32_t& max_x, int32_t& max_y);

    void NormalizeCoordinates(Vector<int64_t>& x_coord, Vector<int64_t>& y_coord, 
        int32_t count, int32_t& max_x, int32_t& max_y, int32_t& min_x, int32_t& min_y);

    FileParser(std::string path) : path_(path)  {}

    void ParseCoords(Vector<int64_t>& x_coord, Vector<int64_t>& y_coord, Vector<uint64_t>& sand_in_coords);
};
