#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace s21 {

class Parser {
private:
    vector<double> vertexes_;
    vector<int> facets_;
    static Parser* parser_;
    Parser() {}
    ~Parser() { delete parser_; }

    void parsing_vertexes(string line);
    void parsing_facets(string line);
    void transform_facets(vector<int> temp);

public:
    static Parser* get_parser() {
        if (!parser_) parser_ = new Parser();
        return parser_;
    }
    void parsing(string file_name);
    vector<double> get_vertexes();
    vector<int> get_facets();
    void clear();
};

}  // namespace s21
