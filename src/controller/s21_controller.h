#include <vector>

#include "../model/s21_model.h"

namespace s21 {

class Controller {
private:
    Model* model_;
    static Controller* controller_;
    Controller() { model_ = model_->get_model(); }
    ~Controller() { delete controller_; }

public:
    static Controller* getController() {
        if (!controller_) controller_ = new Controller();
        return controller_;
    }
    vector<double> get_vertexes_after_parsing(string file_name);
    vector<int> get_facets_after_parsing();
    vector<double> get_vertexes_after_transform(vector<double> settings);
};

}  // namespace s21
