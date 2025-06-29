#include "lib/matrix/matrix.h"
#include "lib/write_bmp/write_bmp.h"
#include "lib/parser/parser.h"
#include "lib/vector/vector.h"
#include "lib/fileparser/fileparser.h"
#include "lib/saveintogif/intogif.h"
#include <queue>
#include <exception>

int main(int argc, char** argv) {
    std::string output_file = "";
    std::string input_file = "";

    bool isgif = false;
    try {
        Parser parser(argc, argv);
        output_file = parser.get_output_file();
        input_file = parser.get_input_file();
        isgif = parser.get_isgif();
    } catch (char const* error_message) {
        std::cerr << error_message << '\n';
    }

    FileParser fileparser(input_file);

    Vector<int64_t> x_coord {};
    Vector<int64_t> y_coord {};
    Vector<uint64_t> sand_in_coords {};
    try {
        fileparser.ParseCoords(x_coord, y_coord, sand_in_coords);
    } catch (char const* error_message) {
        std::cerr << error_message << '\n';
    }

    uint64_t max_x = 0, max_y = 0;
    for (size_t i = 0; i < x_coord.size(); ++i) {
        if (x_coord[i] > max_x) max_x = x_coord[i];
        if (y_coord[i] > max_y) max_y = y_coord[i];
    }
    max_x += 1; 
    max_y += 1;

    size_t count_of_sand = 0;

    Vector<Vector<uint64_t>> mass(max_y, Vector<uint64_t>(max_x, 0)); 
    for (size_t i = 0; i < sand_in_coords.size(); i++) {
        if (sand_in_coords[i] != 0) {
            count_of_sand += sand_in_coords[i];
            mass[y_coord[i]][x_coord[i]] = sand_in_coords[i];
        }
    }
    if (isgif) {
        Vector<Picture> pictures;
        uint64_t count = 0;
        while (MoreThanFour(mass, max_x, max_y)) {
            IterationOfPicture(mass, max_x, max_y);
            if (count % (count_of_sand / 100) == 0) {
                pictures.push_back({mass, max_x, max_y});
            }
            count++;
        }
        SaveGIF(pictures, output_file);
    } else {
        MakePicture(mass, max_x, max_y);
        WriteToBmp(mass, output_file, max_x, max_y);
    }
}
