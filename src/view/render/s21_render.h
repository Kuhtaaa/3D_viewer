#ifndef S21_RENDER_H
#define S21_RENDER_H

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QGuiApplication>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QPoint>
#include <QPointerEvent>
#include <QTime>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_render;
}
QT_END_NAMESPACE

class s21_render : public QOpenGLWidget {
    Q_OBJECT

public:
    s21_render(QWidget *parent = nullptr);
    ~s21_render();

    void getColor(std::array<double, 9> *color);
    void getVertices(std::vector<double> *vertices_vector_);
    void getIndicesVec(std::vector<int> *indices_vec_);
    void projectMod(bool *size);
    void getLine(std::array<int, 2> *apexSetting);
    void getApex(std::array<int, 2> *lineSetting);
    void getRotation(std::array<double, 3> *rotation);

private:
    s21_render *ui;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void drawLine();
    void setProject();
    void setLineMod();
    void setLineSize();
    void setApexMod();
    void setApexSize();

private:
    std::array<double, 9> *colorSetting = nullptr;  // ColorSetting Line(R.G.B)/Apex/Back
    std::vector<double> *vertices_vector_ = nullptr;
    std::vector<int> *indices_vec_ = nullptr;
    bool *projectSetting = nullptr;
    std::array<int, 2> *apexSetting = nullptr;         // {apexMod/apexSize}
    std::array<int, 2> *lineSetting = nullptr;         // {lineMod/lineSize}
    std::array<double, 3> *rotationSetting = nullptr;  // {x,y,z}

    unsigned *vertices_counter_;
    unsigned *indices_counter_;
};

#endif  // S21_RENDER_H
