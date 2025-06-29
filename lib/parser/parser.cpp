#include "parser.h"

Parser::Parser(int32_t argc, char* argv[]) {
    try {
        for (int32_t i = 1; i < argc; i++) {
            size_t size = strlen(argv[i]);
            if ((strncmp(argv[i], "--output", size) == 0) || (strncmp(argv[i], "-o", size) == 0)) {
                if (i == argc - 1) {
                    throw std::runtime_error{"Don't write commands without values"};
                }
                output_file_ = argv[i + 1];
            } else if ((strncmp(argv[i], "--isgif", size) == 0) || (strncmp(argv[i], "-s", size) == 0)) {
                isgif_ = true;
            } else if ((strncmp(argv[i], "--input", size) == 0) || (strncmp(argv[i], "-i", size) == 0)) {
                if (i == argc - 1) {
                    throw std::runtime_error{"Don't write commands without values"};
                }
                input_file_ = argv[i + 1];
            }
        }
    } catch (...) {
        throw;
    }
}

std::string Parser::get_output_file() const noexcept {
    return output_file_;
}

char* Parser::get_input_file() const noexcept {
    return input_file_;
}

bool Parser::get_isgif() const noexcept {
    return isgif_;
}