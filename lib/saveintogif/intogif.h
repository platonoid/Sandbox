#include "../vector/vector.h"
#include "../write_bmp/write_bmp.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#pragma once

struct Picture {
    Vector<Vector<uint64_t>> mass_;
    uint64_t max_x_;
    uint64_t max_y_;

    Picture(Vector<Vector<uint64_t>>& mass, uint64_t max_x, uint64_t max_y) : mass_(mass), max_x_(max_x), max_y_(max_y) {}
};


struct BMPImage {
    uint64_t width;
    uint64_t height;
    Vector<uint8_t> pixels;  
};

BMPImage MakeFrame(Vector<Vector<uint64_t>>& mass, int32_t max_x, int32_t max_y);

void SaveGIF(Vector<Picture>& pictures, const std::string& output_filename);