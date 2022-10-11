#include "s21_render.h"

s21_render::s21_render(QWidget *parent) : QOpenGLWidget(parent) {
    setWindowTitle("3D_Viewer_v2.0");
    setGeometry(1000, 1000, 900, 700);
}

s21_render::~s21_render() {
    //    delete ui;  // Do you see the Sig11? It is here.
}

void s21_render::initializeGL() {
    if (vertices_vector_ != nullptr) glEnable(GL_DEPTH_TEST);
}

void s21_render::resizeGL(int w, int h) {
    if (vertices_vector_ != nullptr) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        setProject();  // проверить работоспособность
    }
}

void s21_render::paintGL() {
    glClearColor(((*colorSetting)[6]), ((*colorSetting)[7]), ((*colorSetting)[8]), 0);
    glColor3d(((*colorSetting)[0]), ((*colorSetting)[1]), ((*colorSetting)[2]));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (vertices_vector_ != nullptr) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -4);

        setLineMod();
        setLineSize();
        drawLine();

        glEnableClientState(GL_VERTEX_ARRAY);
        setApexMod();
    }
    update();
}

void s21_render::drawLine() {
    glVertexPointer(3, GL_DOUBLE, 0, &(*vertices_vector_)[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, (*(indices_vec_)).size(), GL_UNSIGNED_INT, &(*indices_vec_)[0]);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void s21_render::setLineMod() {
    glLineStipple(1, 35939);
    ((*lineSetting)[0] == 1) ? glEnable(GL_LINE_STIPPLE) : glDisable(GL_LINE_STIPPLE);
}

void s21_render::setLineSize() {  // заменить на поинтер
    glLineWidth((*lineSetting)[1]);
}

void s21_render::setApexMod() {
    if ((*apexSetting)[0] == 1) {
        glEnable(GL_POINT_SMOOTH);
        glPointSize((*apexSetting)[1]);
        glColor3d(((*colorSetting)[3]), ((*colorSetting)[4]), ((*colorSetting)[5]));
        glDrawArrays(GL_POINTS, 0, (*(vertices_vector_)).size() / 3);
        glDisable(GL_POINT_SMOOTH);
    } else if ((*apexSetting)[0] == 0) {
        glPointSize((*apexSetting)[1]);
        glColor3d(((*colorSetting)[3]), ((*colorSetting)[4]), ((*colorSetting)[5]));
        glDrawArrays(GL_POINTS, 0, (*(vertices_vector_)).size() / 3);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void s21_render::setApexSize() {}

void s21_render::setProject() {  // проверить функционал
    (*projectSetting) ? glFrustum(-1, 1, -1, 1, 1, 1000) : glOrtho(-1, 1, -1, 1, 1, 1000);
}

void s21_render::getColor(std::array<double, 9> *color) { colorSetting = color; }

void s21_render::getRotation(std::array<double, 3> *rotation) { rotationSetting = rotation; }

void s21_render::getLine(std::array<int, 2> *apexSetting) { lineSetting = apexSetting; }

void s21_render::getApex(std::array<int, 2> *lineSetting) { apexSetting = lineSetting; }

void s21_render::getVertices(std::vector<double> *verticesVector) { vertices_vector_ = verticesVector; }

void s21_render::getIndicesVec(std::vector<int> *indicesVec) { indices_vec_ = indicesVec; }

void s21_render::projectMod(bool *size) { projectSetting = size; }
