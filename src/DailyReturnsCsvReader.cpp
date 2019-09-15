//
// Created by ivan on 15/09/2019.
//

#include "DailyReturnsCsvReader.h"
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

std::vector<double> DailyReturnsCsvReader::read() {
    if (has_been_read) throw "File has already been read";
    std::vector<double> buffer;
    std::string line;
    std::ifstream file_stream(file_path);
    while (file_stream >> line) {
        double amount = parse(line);
        buffer.emplace_back(amount);
    }
    has_been_read = true;
    return buffer;
}

double DailyReturnsCsvReader::parse(const std::string& line) {
    std::stringstream line_stream(line);
    std::string date;
    double amount;
    //first token is a date, second token is the daily return
    std::getline(line_stream, date, ',');
    line_stream >> amount;
    return amount;
}