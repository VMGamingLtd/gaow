#include <string>
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

std::string generate_uuid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < 8; ++i) {
        ss << std::setw(1) << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 4; ++i) {
        ss << std::setw(1) << dis(gen);
    }
    ss << "-4"; // 4 indicates UUID version 4
    for (int i = 0; i < 3; ++i) {
        ss << std::setw(1) << dis(gen);
    }
    ss << "-";
    ss << std::setw(1) << (8 + dis(gen) % 4); // The variant (bits 6-7 of the clock_seq_hi_and_reserved field)
    for (int i = 0; i < 3; ++i) {
        ss << std::setw(1) << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 12; ++i) {
        ss << std::setw(1) << dis(gen);
    }

    return ss.str();
}

