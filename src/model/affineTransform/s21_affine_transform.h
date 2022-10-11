#include <cmath>
#include <vector>

using std::vector;

namespace s21 {

class AffineTransform {
private:
    vector<double> vertexes_;
    static AffineTransform* transform_;
    AffineTransform() {}
    ~AffineTransform() { delete transform_; }

public:
    static AffineTransform* get_transform() {
        if (!transform_) transform_ = new AffineTransform();
        return transform_;
    }
    void set_vertexes(vector<double> vertexes);
    vector<double> get_vertexes();
    void move_x(double step);
    void move_y(double step);
    void move_z(double step);
    void rotation_x(double angle);
    void rotation_y(double angle);
    void rotation_z(double angle);
    void scaling(double scale);
};

}  // namespace s21
