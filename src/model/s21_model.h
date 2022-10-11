#include <vector>

#include "affineTransform/s21_affine_transform.h"
#include "parser/s21_parser.h"

using std::vector;

namespace s21 {

class Model {
private:
    Parser* parser_;
    AffineTransform* transform_;
    static Model* model_;
    Model() {
        parser_ = parser_->get_parser();
        transform_ = transform_->get_transform();
    }
    ~Model() { delete model_; }

public:
    static Model* get_model() {
        if (!model_) model_ = new Model();
        return model_;
    }
    void parser(string file_name);
    vector<double> get_vertexes();
    vector<int> get_facets();
    vector<double> affine_transfom(vector<double> settings);
};

}  // namespace s21
