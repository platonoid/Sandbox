#include "write_bmp.h"

void WriteToBmp(Vector<Vector<uint64_t>>& mass, std::string output, int32_t max_x, int32_t max_y) {
    const int32_t size_bmp_header = 14;
    uint8_t BMP_header[size_bmp_header] = {
        'B', 'M',
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    const int32_t size_dib_header = 40;
    uint8_t DIB_header[size_dib_header] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        5, 0, 0, 0,
        5, 0, 0, 0
    };
    const int32_t count_of_colors = 4;
    const int32_t colors_bits = pow(2, count_of_colors);
    DIB_header[0] = size_dib_header;
    DIB_header[14] = count_of_colors;

    DIB_header[4] = (max_x) & 255;
    DIB_header[5] = (max_x >> 8) & 255;
    DIB_header[6] = (max_x >> 16) & 255;
    DIB_header[7] = (max_x >> 24) & 255;

    DIB_header[8] = (max_y) & 255;
    DIB_header[9] = (max_y >> 8) & 255;
    DIB_header[10] = (max_y >> 16) & 255;
    DIB_header[11] = (max_y >> 24) & 255;

    const int32_t size_color_pallete = 20;
    uint8_t palette[size_color_pallete] = {
        255, 255, 255, 0, //white
        0, 255, 0, 0, //green
        255, 0, 255, 0, //purple
        0, 255, 255, 0, //yellow
        0, 0, 0, 0, //black
    };

    int32_t row_size = (max_x + 1) / 2;
    int32_t padding_size = (4 - (row_size % 4)) % 4;
    int32_t size_of_bmp =  size_bmp_header + size_dib_header + size_color_pallete + max_y * (max_x + padding_size);
    const int32_t skip = size_bmp_header + size_dib_header + size_color_pallete;

    BMP_header[2] = size_of_bmp & 255;
    BMP_header[3] = (size_of_bmp >> 8) & 255;
    BMP_header[4] = (size_of_bmp >> 16) & 255;
    BMP_header[5] = (size_of_bmp >> 24) & 255;

    DIB_header[24] = size_of_bmp & 255;
    DIB_header[25] = (size_of_bmp >> 8) & 255;
    DIB_header[26] = (size_of_bmp >> 16) & 255;
    DIB_header[27] = (size_of_bmp >> 24) & 255;

    BMP_header[10] = skip;

    std::ofstream bmp_file(output, std::ios::binary);
    if (!bmp_file.is_open()) {
        std::cout << "Error!! The directory way is incorrect!!!" << std::endl;
        return;
    }

    bmp_file.write(reinterpret_cast<char*>(BMP_header), size_bmp_header);
    bmp_file.write(reinterpret_cast<char*>(DIB_header), size_dib_header);
    bmp_file.write(reinterpret_cast<char*>(palette), size_color_pallete);

    for (int32_t y = max_y - 1; y >= 0; --y) {
        for (int32_t x = 0; x < max_x; x += 2) {
            uint8_t prev_color = mass[y][x];
            uint8_t next_color = 0;
            if (x + 1 != max_x) {
                next_color = mass[y][x + 1];
            }
            if (prev_color > 3) {
                prev_color = 4;
            }
            if (next_color > 3) {
                next_color = 4;
            }
            uint8_t byte_of_color = (prev_color << 4) | next_color;
            bmp_file.write(reinterpret_cast<char*>(&byte_of_color), 1);
        }
        uint8_t padding_byte = 0; 
        for (int32_t i = 0; i < padding_size; ++i) {
            bmp_file.write(reinterpret_cast<char*>(&padding_byte), 1);
        }
    }
    bmp_file.close();
    std::cout << "BMP saved succesful\n";;
}
