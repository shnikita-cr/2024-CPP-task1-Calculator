#include "tech.h"
#include <iostream>

double err(std::string_view s) {
    std::cerr << "error: " << s << std::endl;
    return 1;
}