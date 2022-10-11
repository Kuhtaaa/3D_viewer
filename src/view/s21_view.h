#ifndef S21_VIEW_H
#define S21_VIEW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>
#include <ctime>

#include "../controller/s21_controller.h"
#include "QtWidgets/qlcdnumber.h"
#include "QtWidgets/qlineedit.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qslider.h"
#include "gifimage/qgifimage.h"  // либа для gif

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE

class view : public QMainWindow {
    Q_OBJECT

public:
    view(QWidget *parent = nullptr);
    ~view();

private:
    Ui::view *ui;
    void connectSetting();
    bool openFile();
    void defaultSetting();

private:
    s21::Controller *controller = nullptr;
    std::array<double, 9> colorSetting_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};  // ColorSetting Line(R.G.B)/Apex/Back
    std::array<double, 3> rotationSetting_ = {0, 0, 0};                 // ColorSetting Line(R.G.B)/Apex/Back
    std::array<int, 2> apexSetting_ = {0, 1};                           // {apexMod/apexSize}
    std::array<int, 2> lineSetting_ = {0, 1};                           // {lineMod/lineSize}
    std::vector<double> settingModel_ = {
        0, 0, 0, 0, 0, 0, 0};  // settings[7] = {move_x, move_y, move_z, rot_x, rot_y, rot_z, scale}
    std::string file_;
    bool projectMod_ = 0;
    std::vector<int> indices_vec_ = {0, 1, 1, 2, 2, 0};
    std::vector<double> vertices_vector_ = {0.5, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.5};
    QTimer *timer;
    QGifImage gif;

public slots:
    void stop_timer();
    void make_gif();
    void setColor();
    void setPosition();
    void setRotation();
    void setZoom();
    void setLineSize();
    void setLineMode();
    void setApexSize();
    void setApexMode();
    void setProjectSet();
    void setGif();
    void setScreenShot();
    void setOpenFile();
};
#endif  // S21_VIEW_H
