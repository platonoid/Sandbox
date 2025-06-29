#include "intogif.h"
#include "gif.h"

BMPImage MakeFrame(Vector<Vector<uint64_t>>& mass, int32_t max_x, int32_t max_y) {
    BMPImage frame;
    frame.width = max_x;
    frame.height = max_y;
    frame.pixels.resize(max_x * max_y * 3);

    for (int32_t y = 0; y < max_y; y++) {
        for (int32_t x = 0; x < max_x; x++) {
            uint8_t color = static_cast<uint8_t>(mass[y][x] % 4);
            uint8_t red = 0, green = 0, blue = 0;
            switch (color) {
                case 0: red = 255; green = 255; blue = 255; break;
                case 1: red = 0; green = 255; blue = 0; break;    
                case 2: red = 255; green = 0; blue = 255; break;  
                case 3: red = 0; green = 255; blue = 255; break;   
                default: break;
            }

            size_t index = ((max_y - 1 - y) * max_x + x) * 3;  
            frame.pixels[index] = blue;
            frame.pixels[index + 1] = green;
            frame.pixels[index + 2] = red;
        }
    }

    return frame;
}

void SaveGIF(Vector<Picture>& pictures, const std::string& output_filename) {
    Vector<BMPImage> frames;
    uint64_t max_width = 0;
    uint64_t max_height = 0;
    for (auto& picture : pictures) {
        BMPImage img = MakeFrame(picture.mass_, picture.max_x_, picture.max_y_);
        frames.push_back(img);
        max_width = std::max(max_width, img.width);
        max_height = std::max(max_height, img.height);
    }

    GifWriter writer;
    if (!GifBegin(&writer, output_filename.c_str(), max_width, max_height, 0)) {
        throw std::runtime_error{"failed to create GIF"};
    }

    for (auto& frame : frames) {
        Vector<uint8_t> gif_frame(max_width * max_height * 4, 255);

        int32_t x_offset = (max_width - frame.width) / 2;
        int32_t y_offset = (max_height - frame.height) / 2;

        for (uint64_t y = 0; y < frame.height; y++) {
            for (uint64_t x = 0; x < frame.width; x++) {
                uint64_t srcIdx = (y * frame.width + x) * 3;
                uint64_t x_distance = x + x_offset;
                uint64_t y_distance = y + y_offset;

                if (x_distance >= max_width || y_distance >= max_height) continue;

                uint64_t index_distance = (y_distance * max_width + x_distance) * 4;
                gif_frame[index_distance] = frame.pixels[srcIdx + 2];  // R
                gif_frame[index_distance + 1] = frame.pixels[srcIdx + 1];  // G
                gif_frame[index_distance + 2] = frame.pixels[srcIdx];  // B
                gif_frame[index_distance + 3] = 0;
            }
        }

        GifWriteFrame(&writer, gif_frame.data(), max_width, max_height, 0);
    }

    GifEnd(&writer);
    std::cout << "GIF saved succesful\n";
}