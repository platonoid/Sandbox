#include <iostream>
#include <string>
#include <limits>

class Parser {
    std::string output_file_;
    char* input_file_;

    bool isgif_ = 0;
public:
    Parser(int32_t argc, char* argv[]);

    std::string get_output_file() const noexcept;
    char* get_input_file() const noexcept;

    bool get_isgif() const noexcept;
};