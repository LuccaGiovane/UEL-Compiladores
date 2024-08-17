#include <list>
#include <iostream>

#include "string_utils.h"


int contains(std::string str, std::string target) {
    size_t str_size = str.size();
    size_t target_size = target.size();

    // Checking if entry is valid
    if(!str_size || !target_size || str_size < target_size) {
        return -1;
    }

    for(size_t i {0}, j {0}; i < str_size; i++) {
        // If a char from str is in target
        if(str[i] == target[j]) {
            j++;
        }
        else {
            j = 0;
        }

        // If target is found in str
        if(j == target_size) {
            return i - j + 1;
        }
    }

    return -1;
}


std::vector<std::string> split(const std::string &str, const std::string &splitter) {
    std::vector<std::string> result;
    size_t start = 0, end;

    while ((end = str.find(splitter, start)) != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + splitter.size();
    }

    result.push_back(str.substr(start));
    return result;
}


bool is_in_interval(char letter, std::string interval) {
    std::vector<std::string> splt = split(interval, "-");
    char min {splt[0][0]};
    char max {splt[1][0]};

    bool is_in = (letter >= min && letter <= max);
    
    return is_in;
}
