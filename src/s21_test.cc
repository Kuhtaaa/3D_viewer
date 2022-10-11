#include <gtest/gtest.h>

#include <iostream>

#include "model/s21_model.h"
using namespace s21;

class S213DViewer : public testing::Test {
protected:
    Model *model;
    void SetUp() {
        model = model->get_model();
        model->parser("objects/CUB.obj");
    }
    void TearDown() {}
};

TEST_F(S213DViewer, cub_parser) {
    vector<double> vertexes_cub = {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0};
    vector<int> facets_cub = {0, 1, 1, 2, 2, 3, 3, 0, 7, 6, 6, 5, 5, 4, 4, 7, 3, 2, 2, 6, 6, 7, 7, 3,
                              4, 0, 0, 3, 3, 7, 7, 4, 4, 5, 5, 1, 1, 0, 0, 4, 1, 5, 5, 6, 6, 2, 2, 1};
    vector<double> vertexes = model->get_vertexes();
    vector<int> facets = model->get_facets();

    for (size_t it = 0; it < vertexes.size(); ++it) EXPECT_EQ(vertexes[it], vertexes_cub[it]);

    for (size_t it = 0; it < facets.size(); ++it) EXPECT_EQ(facets[it], facets_cub[it]);
}

// TEST_F(S213DViewer, cooper) {
//
// }

// TEST_F(S213DViewer, pumpkin) {
//
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}