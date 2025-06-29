#include "fileparser.h"

std::ifstream OpenFile(std::string path) {
    std::ifstream sand_coords(path);
    if (!sand_coords.is_open()) {
       throw std::runtime_error{"Cannor open the file"};
    }
    return sand_coords;
}

int64_t FileParser::ParseNumber(const char* str, int32_t& max_val) {
    int64_t num = 0;
    bool negative = false;
    while (*str == ' ') str++;

    if (*str == '-') {
        negative = true;
        str++;
    }

    while (isdigit(*str)) {
        num = num * 10 + (*str - '0');
        str++;
    }

    if (num > max_val) {
        max_val = num;
    }

    return negative ? -num : num;
}

void FileParser::ParseLine(const char* line, Vector<int64_t>& x_coord, Vector<int64_t>& y_coord, 
        Vector<uint64_t>& sand_in_coords, int32_t index, int32_t& max_x, int32_t& max_y) {
    int32_t x = ParseNumber(line, max_x);
    x_coord[index] = x;

    const char* y_start = line;
    y_start++;
    while (*y_start && *y_start == ' ') y_start++;
    if (!y_start) throw std::runtime_error("missing y coordinate");
    int32_t y = ParseNumber(y_start, max_y);
    y_coord[index] = y;

    const char* sand_start = strchr(y_start + 1, ' ');
    if (!sand_start) throw std::runtime_error("missing sand count");
    int32_t zero = 0;
    sand_in_coords[index] = ParseNumber(sand_start, zero);
    if (sand_in_coords[index] < 0) throw std::runtime_error("bad num for sand");
}

void FileParser::NormalizeCoordinates(Vector<int64_t>& x_coord, Vector<int64_t>& y_coord, 
        int32_t count, int32_t& max_x, int32_t& max_y, int32_t& min_x, int32_t& min_y) {
    for (int32_t i = 0; i < count; ++i) {
        if (x_coord[i] < min_x) min_x = x_coord[i];
        if (x_coord[i] > max_x) max_x = x_coord[i];
        if (y_coord[i] < min_y) min_y = y_coord[i];
        if (y_coord[i] > max_y) max_y = y_coord[i];
    }

    for (int32_t i = 0; i < count; ++i) {
        x_coord[i] -= min_x;
        y_coord[i] -= min_y;
    }
}

void FileParser::ParseCoords(Vector<int64_t>& x_coord, Vector<int64_t>& y_coord, Vector<uint64_t>& sand_in_coords) {
    std::ifstream sand_coords = OpenFile(path_);  
    char str_coords[100] {};       
    int32_t count = 0;
    int32_t max_x = 0, max_y = 0;
    int32_t min_x = INT_MAX, min_y = INT_MAX;
    std::string line;

    while (std::getline(sand_coords, line)) {
        if (count >= x_coord.size()) {
            x_coord.resize(count + 1);
            y_coord.resize(count + 1);
            sand_in_coords.resize(count + 1);
        }
        
        ParseLine(line.c_str(), x_coord, y_coord, sand_in_coords, count, max_x, max_y);
        count++;
    }
    sand_coords.close();

    NormalizeCoordinates(x_coord, y_coord, count, max_x, max_y, min_x, min_y);
}