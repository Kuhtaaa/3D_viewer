#include "s21_interface.h"

#include "ui_s21_interface.h"

s21_interface::s21_interface(QWidget *parent) : QWidget(parent), ui(new Ui::s21_interface) {
    ui->setupUi(this);
    connetColorSlider_ = {
        {ui->Slider_11, ui->lcd_R1}, {ui->Slider_12, ui->lcd_G1}, {ui->Slider_13, ui->lcd_B1},
        {ui->Slider_21, ui->lcd_R2}, {ui->Slider_22, ui->lcd_G2}, {ui->Slider_23, ui->lcd_B2},
        {ui->Slider_31, ui->lcd_R3}, {ui->Slider_32, ui->lcd_G3}, {ui->Slider_33, ui->lcd_B3}};

    connectButtonPosition_ = {
        {ui->pushButton_moveX_max, ui->lineEdit_moveX}, {ui->pushButton_moveX_min, ui->lineEdit_moveX},
        {ui->pushButton_moveY_max, ui->lineEdit_moveY}, {ui->pushButton_moveY_min, ui->lineEdit_moveY},
        {ui->pushButton_moveZ_max, ui->lineEdit_moveZ}, {ui->pushButton_moveZ_min, ui->lineEdit_moveZ}};

    connetRotationSlider_ = {{ui->Slider_RotationX, ui->lcd_RotationX},
                             {ui->Slider_RotationY, ui->lcd_RotationY},
                             {ui->Slider_RotationZ, ui->lcd_RotationZ}};
    buttonGroup_ = {ui->pushButton_openFile, ui->pushButton_ScreenShot, ui->pushButton_Gif};

    connectSetting();

    settings_ = new QSettings(QCoreApplication::applicationDirPath() + "/setting.ini", QSettings::IniFormat);

    loadSettings();
}

s21_interface::~s21_interface() {
    saveSetting();
    delete ui;
}

void s21_interface::changeColor() {
    QSlider *slider = (QSlider *)sender();
    connetColorSlider_.find(slider)->second->display(slider->value());
    emit updateColor();
}

void s21_interface::changeZoom() {
    QSlider *slider = (QSlider *)sender();
    ui->lcd_Zoom->display(slider->value());
    emit updateZoom();
}

void s21_interface::changeLineSize() {
    QSlider *slider = (QSlider *)sender();
    ui->lcd_LineS->display(slider->value());
    emit updateLineSize();
}

void s21_interface::changeApexSize() {
    QSlider *slider = (QSlider *)sender();
    ui->lcd_ApexS->display(slider->value());
    emit updateApexSize();
}

void s21_interface::changeApexMod() { emit updateApexMode(); }

void s21_interface::changeLineMod() { emit updateLineMode(); }

void s21_interface::changeProjectionMod() { emit updateProjectSet(); }

void s21_interface::changeRotation() {
    QSlider *slider = (QSlider *)sender();
    connetRotationSlider_.find(slider)->second->display(slider->value());
    emit updateRotation();
}

void s21_interface::changePosition() {
    QPushButton *button = (QPushButton *)sender();
    int size = connectButtonPosition_.find(button)->second->text().toInt();
    QString tmpValue = button->text();
    (tmpValue[2] == '+') ? size++ : size--;
    connectButtonPosition_.find(button)->second->setText(QString::number(size));
    emit updatePosition();
}

void s21_interface::otherButtonClicked() {
    QPushButton *button = (QPushButton *)sender();
    if (button == buttonGroup_[0]) emit openFile();
    if (button == buttonGroup_[1]) emit screenShot();
    if (button == buttonGroup_[2]) emit gif();
}

std::array<double, 9> s21_interface::setColor() {
    std::array<double, 9> colorSetting;
    colorSetting[0] = ui->lcd_R1->value() / 100;
    colorSetting[1] = ui->lcd_G1->value() / 100;
    colorSetting[2] = ui->lcd_B1->value() / 100;
    colorSetting[3] = ui->lcd_R2->value() / 100;
    colorSetting[4] = ui->lcd_G2->value() / 100;
    colorSetting[5] = ui->lcd_B2->value() / 100;
    colorSetting[6] = ui->lcd_R3->value() / 100;
    colorSetting[7] = ui->lcd_G3->value() / 100;
    colorSetting[8] = ui->lcd_B3->value() / 100;
    return colorSetting;
}

int s21_interface::setZoom() { return ui->lcd_Zoom->intValue(); }

std::array<double, 3> s21_interface::setPosition() {
    std::array<double, 3> positionSetting;
    positionSetting[0] = ui->lineEdit_moveX->text().toDouble();
    positionSetting[1] = ui->lineEdit_moveY->text().toDouble();
    positionSetting[2] = ui->lineEdit_moveZ->text().toDouble();
    return positionSetting;
}

std::array<double, 3> s21_interface::setRotation() {
    std::array<double, 3> rotationSetting;
    rotationSetting[0] = ui->lcd_RotationX->value() / 60;
    rotationSetting[1] = ui->lcd_RotationY->value() / 60;
    rotationSetting[2] = ui->lcd_RotationZ->value() / 60;
    return rotationSetting;
}

int s21_interface::setLineSize() { return ui->lcd_LineS->intValue(); }

int s21_interface::setApexSize() { return ui->lcd_ApexS->intValue(); }

int s21_interface::setLineMode() { return (ui->radioDotted->isChecked()); }

int s21_interface::setApexMode() {
    if (!(ui->radioCube->isChecked()) && !(ui->radioLayer->isChecked())) return 2;
    if (!(ui->radioCube->isChecked()) && !(ui->radioVoid->isChecked())) return 1;
    return 0;
}

int s21_interface::setProjectSet() { return (ui->radioButtonParallel->isChecked()); }

void s21_interface::connectSetting() {  // union pair object lcd+slider or button+lineEdit
    for (auto it = connetColorSlider_.begin(); it != connetColorSlider_.end(); it++)
        connect(it->first, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));
    for (auto it = connetRotationSlider_.begin(); it != connetRotationSlider_.end(); it++)
        connect(it->first, SIGNAL(valueChanged(int)), this, SLOT(changeRotation()));
    for (auto it = connectButtonPosition_.begin(); it != connectButtonPosition_.end(); it++)
        connect(it->first, SIGNAL(clicked()), this, SLOT(changePosition()));
    for (auto it = buttonGroup_.begin(); it != buttonGroup_.end(); it++)
        connect(*it, SIGNAL(clicked()), this, SLOT(otherButtonClicked()));

    connect(ui->Slider_Zoom, SIGNAL(valueChanged(int)), this, SLOT(changeZoom()));
    connect(ui->Slider_LineS, SIGNAL(valueChanged(int)), this, SLOT(changeLineSize()));
    connect(ui->Slider_ApexS, SIGNAL(valueChanged(int)), this, SLOT(changeApexSize()));

    connect(ui->radioCube, SIGNAL(clicked()), this, SLOT(changeApexMod()));
    connect(ui->radioVoid, SIGNAL(clicked()), this, SLOT(changeApexMod()));
    connect(ui->radioLayer, SIGNAL(clicked()), this, SLOT(changeApexMod()));

    connect(ui->radioSolid, SIGNAL(clicked()), this, SLOT(changeLineMod()));
    connect(ui->radioDotted, SIGNAL(clicked()), this, SLOT(changeLineMod()));

    connect(ui->radioButtonCentral, SIGNAL(clicked()), this, SLOT(changeProjectionMod()));
    connect(ui->radioButtonParallel, SIGNAL(clicked()), this, SLOT(changeProjectionMod()));
}

void s21_interface::saveSetting() {
    settings_->sync();

    settings_->setValue("colorLineR", ui->lcd_R1->value());
    settings_->setValue("colorLineG", ui->lcd_G1->value());
    settings_->setValue("colorLineB", ui->lcd_B1->value());
    settings_->setValue("colorApexR", ui->lcd_R2->value());
    settings_->setValue("colorApexG", ui->lcd_G2->value());
    settings_->setValue("colorApexB", ui->lcd_B2->value());
    settings_->setValue("colorBackR", ui->lcd_R3->value());
    settings_->setValue("colorBackG", ui->lcd_G3->value());
    settings_->setValue("colorBackB", ui->lcd_B3->value());

    settings_->setValue("ZoomSize", ui->lcd_Zoom->intValue());

    settings_->setValue("positionSettinX", ui->lineEdit_moveX->text().toDouble());
    settings_->setValue("positionSettinY", ui->lineEdit_moveY->text().toDouble());
    settings_->setValue("positionSettinZ", ui->lineEdit_moveZ->text().toDouble());

    settings_->setValue("rotationSettingX", ui->lcd_RotationX->value());
    settings_->setValue("rotationSettingY", ui->lcd_RotationY->value());
    settings_->setValue("rotationSettingZ", ui->lcd_RotationZ->value());

    settings_->setValue("LineSize", ui->lcd_LineS->intValue());
    settings_->setValue("ApexSize", ui->lcd_ApexS->intValue());

    settings_->setValue("LineMode", ui->radioDotted->isChecked());
    settings_->setValue("ApexMode", setApexMode());

    settings_->setValue("ProjectSet", ui->radioButtonParallel->isChecked());
}

void s21_interface::loadSettings() {
    ui->Slider_11->setValue(settings_->value("colorLineR", 0).value<int>());
    ui->Slider_12->setValue(settings_->value("colorLineG", 0).value<int>());
    ui->Slider_13->setValue(settings_->value("colorLineB", 0).value<int>());
    ui->Slider_21->setValue(settings_->value("colorApexR", 0).value<int>());
    ui->Slider_22->setValue(settings_->value("colorApexG", 0).value<int>());
    ui->Slider_23->setValue(settings_->value("colorApexB", 0).value<int>());
    ui->Slider_31->setValue(settings_->value("colorBackR", 0).value<int>());
    ui->Slider_32->setValue(settings_->value("colorBackG", 0).value<int>());
    ui->Slider_33->setValue(settings_->value("colorBackB", 0).value<int>());

    ui->Slider_RotationX->setValue(settings_->value("rotationSettingX", 0).value<int>());
    ui->Slider_RotationY->setValue(settings_->value("rotationSettingY", 0).value<int>());
    ui->Slider_RotationZ->setValue(settings_->value("rotationSettingZ", 0).value<int>());

    ui->lineEdit_moveX->setText(QString::number(settings_->value("positionSettinX", 0).value<double>()));
    ui->lineEdit_moveY->setText(QString::number(settings_->value("positionSettinY", 0).value<double>()));
    ui->lineEdit_moveZ->setText(QString::number(settings_->value("positionSettinZ", 0).value<double>()));

    ui->Slider_LineS->setValue(settings_->value("LineSize", 1).value<int>());
    ui->Slider_ApexS->setValue(settings_->value("ApexSize", 1).value<int>());

    ui->Slider_Zoom->setValue(settings_->value("ZoomSize", 10).value<int>());

    sendLineMode(settings_->value("LineMode", false).value<bool>());
    sendApexMode(settings_->value("ApexMode", 0).value<int>());
    sendProjectMode(settings_->value("ProjectSet", false).value<bool>());
}

void s21_interface::sendLineMode(bool mode) {
    (mode == 0) ? ui->radioSolid->click() : ui->radioDotted->click();
}

void s21_interface::sendApexMode(int mode) {
    ui->radioCube->click();
    if (mode == 1) ui->radioLayer->click();
    if (mode == 2) ui->radioVoid->click();
}

void s21_interface::sendProjectMode(bool mode) {
    (mode == 0) ? ui->radioButtonCentral->click() : ui->radioButtonParallel->click();
}

void s21_interface::changeSlidetY() {
    ui->Slider_RotationY->setValue(ui->Slider_RotationY->value() + 1);
    ;
}
