//
// Created by ivan on 15/09/2019.
//

#include <string>
#include <vector>

class DailyReturnsCsvReader {

public:
    explicit DailyReturnsCsvReader(const std::string& file_path) : file_path(file_path) {}
    std::vector<double> read();
private:
    double parse(const std::string& line);
    std::string file_path;
    bool has_been_read = false;
};
