#include "s21_affine_transform.h"

using namespace s21;

AffineTransform* AffineTransform::transform_ = 0;

void AffineTransform::set_vertexes(vector<double> vertexes) { this->vertexes_ = vertexes; }

vector<double> AffineTransform::get_vertexes() { return this->vertexes_; }

void AffineTransform::move_x(double step) {
    for (size_t i = 0; i < this->vertexes_.size() - 2; i += 3) this->vertexes_[i] += step;
}

void AffineTransform::move_y(double step) {
    for (size_t i = 1; i < this->vertexes_.size() - 1; i += 3) this->vertexes_[i] += step;
}

void AffineTransform::move_z(double step) {
    for (size_t i = 2; i < this->vertexes_.size(); i += 3) this->vertexes_[i] += step;
}

void AffineTransform::rotation_x(double angle) {
    for (size_t i = 0; i < this->vertexes_.size() - 2; i += 3) {
        size_t index_y = i + 1, index_z = i + 2;
        double temp_y = this->vertexes_[index_y];
        double temp_z = this->vertexes_[index_z];
        this->vertexes_[index_y] = cos(angle) * temp_y - sin(angle) * temp_z;
        this->vertexes_[index_z] = sin(angle) * temp_y + cos(angle) * temp_z;
    }
}

void AffineTransform::rotation_y(double angle) {
    for (size_t i = 1; i < this->vertexes_.size() - 1; i += 3) {
        size_t index_x = i - 1, index_z = i + 1;
        double temp_x = this->vertexes_[index_x];
        double temp_z = this->vertexes_[index_z];
        this->vertexes_[index_x] = cos(angle) * temp_x + sin(angle) * temp_z;
        this->vertexes_[index_z] = cos(angle) * temp_z - sin(angle) * temp_x;
    }
}

void AffineTransform::rotation_z(double angle) {
    for (size_t i = 2; i < this->vertexes_.size(); i += 3) {
        size_t index_x = i - 2, index_y = i - 1;
        double temp_y = this->vertexes_[index_y];
        double temp_x = this->vertexes_[index_x];
        this->vertexes_[index_x] = cos(angle) * temp_x - sin(angle) * temp_y;
        this->vertexes_[index_y] = cos(angle) * temp_y + sin(angle) * temp_x;
    }
}

void AffineTransform::scaling(double scale) {
    scale /= 100.;
    for (size_t i = 0; i < this->vertexes_.size(); i++) this->vertexes_[i] *= scale;
}
