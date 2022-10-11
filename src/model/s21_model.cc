#include "s21_model.h"

using namespace s21;

Model* Model::model_ = 0;

void Model::parser(string file_name) {
    parser_->clear();
    parser_->parsing(file_name);
}

vector<double> Model::get_vertexes() { return parser_->get_vertexes(); }

vector<int> Model::get_facets() { return parser_->get_facets(); }

vector<double> Model::affine_transfom(vector<double> settings) {
    transform_->set_vertexes(parser_->get_vertexes());
    transform_->move_x(settings[0]);
    transform_->move_y(settings[1]);
    transform_->move_z(settings[2]);
    transform_->rotation_x(settings[3]);
    transform_->rotation_y(settings[4]);
    transform_->rotation_z(settings[5]);
    transform_->scaling(settings[6]);
    return transform_->get_vertexes();
}