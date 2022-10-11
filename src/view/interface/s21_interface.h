#ifndef S21_INTERFACE_H
#define S21_INTERFACE_H

#include <QSettings>
#include <QWidget>
#include <functional>

#include "QtWidgets/qlcdnumber.h"
#include "QtWidgets/qlineedit.h"
#include "QtWidgets/qpushbutton.h"
#include "QtWidgets/qradiobutton.h"
#include "QtWidgets/qslider.h"

typedef void (*func)();

namespace Ui {
class s21_interface;
}

class s21_interface : public QWidget {
    Q_OBJECT

public:
    explicit s21_interface(QWidget *parent = nullptr);
    ~s21_interface();

    std::array<double, 9> setColor();
    std::array<double, 3> setPosition();
    std::array<double, 3> setRotation();
    int setZoom();
    int setLineSize();
    int setApexSize();
    int setLineMode();
    int setApexMode();
    int setProjectSet();
    void loadSettings();
    void saveSetting();
    void changeSlidetY();

private:
    Ui::s21_interface *ui;
    std::map<QSlider *, QLCDNumber *> connetColorSlider_;
    std::map<QSlider *, QLCDNumber *> connetRotationSlider_;
    std::map<QPushButton *, QLineEdit *> connectButtonPosition_;
    std::vector<QPushButton *> buttonGroup_;
    QSettings *settings_;
    void connectSetting();
    void sendLineMode(bool mode);
    void sendApexMode(int mode);
    void sendProjectMode(bool mode);

private slots:
    void changeColor();
    void changePosition();
    void otherButtonClicked();
    void changeLineMod();
    void changeApexMod();
    void changeProjectionMod();
    void changeRotation();
    void changeZoom();
    void changeLineSize();
    void changeApexSize();

signals:
    void updateColor();
    void updatePosition();
    void updateRotation();
    void updateLineSize();
    void updateLineMode();
    void updateApexSize();
    void updateApexMode();
    void updateProjectSet();
    void gif();
    void screenShot();
    void openFile();
    void updateZoom();
};

#endif  // S21_INTERFACE_H
