#include "s21_parser.h"

using namespace s21;

Parser* Parser::parser_ = 0;

void Parser::parsing(string file_name) {
    string line;
    std::ifstream file(file_name);
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == 'v') {
                parsing_vertexes(line);
            } else if (line[0] == 'f') {
                parsing_facets(line);
            }
        }
    }
    file.close();
}

void Parser::parsing_vertexes(string line) {
    for (size_t i = 1; i < line.size(); i++) {
        size_t temp = (i == line.size() - 1) ? i : i + 1;
        if (line[i] == ' ' && (isdigit(line[temp]) || line[temp] == '-')) {
            string temp = line.substr(i);
            this->vertexes_.push_back(stod(temp));
        }
    }
}

void Parser::parsing_facets(string line) {
    vector<int> one_line_facets;
    for (size_t i = 1; i < line.size(); i++) {
        size_t temp = (i == line.size() - 1) ? i : i + 1;
        if (line[i] == ' ' && isdigit(line[temp])) {
            string temp = line.substr(i);
            one_line_facets.push_back(stoi(temp));
        }
    }
    transform_facets(one_line_facets);
}

void Parser::transform_facets(vector<int> temp) {
    size_t max = temp.size();
    for (size_t i = 0; i < max; i++) {
        this->facets_.push_back(temp[i] - 1);
        this->facets_.push_back((i == max - 1) ? temp[0] - 1 : temp[i + 1] - 1);
    }
}

void Parser::clear() {
    this->facets_.clear();
    this->vertexes_.clear();
}

vector<double> Parser::get_vertexes() { return this->vertexes_; }

vector<int> Parser::get_facets() { return this->facets_; }
