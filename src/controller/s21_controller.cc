#include "s21_controller.h"

using namespace s21;

Controller* Controller::controller_ = 0;

vector<double> Controller::get_vertexes_after_parsing(string file_name) {
    model_->parser(file_name);
    return model_->get_vertexes();
}

vector<int> Controller::get_facets_after_parsing() { return model_->get_facets(); }

// settings[7] = {move_x, move_y, move_z, rot_x, rot_y, rot_z, scale}
vector<double> Controller::get_vertexes_after_transform(vector<double> settings) {
    return model_->affine_transfom(settings);
}