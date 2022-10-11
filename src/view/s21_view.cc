#include "s21_view.h"

#include "ui_s21_view.h"

view::view(QWidget *parent) : QMainWindow(parent), ui(new Ui::view) {
    ui->setupUi(this);

    controller = controller->getController();
    defaultSetting();
    connectSetting();
}

view::~view() {
    ui->widget_2->saveSetting();
    delete ui;
}

bool view::openFile() {
    QString fileTmp = QFileDialog::getOpenFileName(this, tr("Open Model"),
                                                   QCoreApplication::applicationDirPath(), tr("*.obj"));
    file_ = fileTmp.toStdString();
    return (fileTmp != nullptr);
}

void view::setOpenFile() {
    if (openFile()) {
        vertices_vector_ = controller->get_vertexes_after_parsing(file_);
        indices_vec_ = controller->get_facets_after_parsing();
        setRotation();
        setZoom();
        setPosition();
    }
}

void view::setColor() {
    colorSetting_ = ui->widget_2->setColor();
    ui->widget->getColor(&colorSetting_);
}

void view::setPosition() {
    if (!file_.empty()) {
        for (int i = 0, j = 0; i < 3; i++, j++) settingModel_[j] = ui->widget_2->setPosition()[i];
        vertices_vector_ = controller->get_vertexes_after_transform(settingModel_);
    }
}

void view::setRotation() {
    if (!file_.empty()) {
        for (int i = 0, j = 3; i < 3; i++, j++) settingModel_[j] = ui->widget_2->setRotation()[i];
        vertices_vector_ = controller->get_vertexes_after_transform(settingModel_);
    }
}

void view::setZoom() {
    if (!file_.empty()) {
        settingModel_[6] = ui->widget_2->setZoom();
        vertices_vector_ = controller->get_vertexes_after_transform(settingModel_);
    }
}

void view::setLineSize() {
    lineSetting_[1] = ui->widget_2->setLineSize();
    ui->widget->getLine(&lineSetting_);
}

void view::setLineMode() {
    lineSetting_[0] = ui->widget_2->setLineMode();
    ui->widget->getLine(&lineSetting_);
}

void view::setApexSize() {
    apexSetting_[1] = ui->widget_2->setApexSize();
    ui->widget->getApex(&apexSetting_);
}

void view::setApexMode() {
    apexSetting_[0] = ui->widget_2->setApexMode();
    ui->widget->getApex(&apexSetting_);
}

void view::setProjectSet() {
    projectMod_ = ui->widget_2->setProjectSet();
    ui->widget->projectMod(&projectMod_);
}

void view::setGif() {
    gif.setDefaultDelay(100);
    timer = new QTimer(this);
    timer->setInterval(200);  // ?
    connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
    timer->start();
    QTimer::singleShot(20000, this, SLOT(stop_timer()));
}

void view::setScreenShot() {
    QFileDialog image(this);
    QString file_name = image.getSaveFileName(this, tr("Save a screenshot"), "", tr("image (*.jpeg *.bmp)"));
    QImage img = ui->widget->grabFramebuffer();
    img.save(file_name);
}

void view::stop_timer() {
    timer->stop();
    QFileDialog call(this);
    QString file_name = call.getSaveFileName(this, tr("Save a gif"), "", tr("gif (*.gif)"));
    gif.save(file_name);
    delete timer;
}

void view::make_gif() {
    QImage img = ui->widget->grabFramebuffer();
    gif.addFrame(img);
    ui->widget_2->changeSlidetY();
}

void view::defaultSetting() {
    ui->widget->getVertices(&vertices_vector_);
    ui->widget->getIndicesVec(&indices_vec_);
    setColor();
    setLineSize();
    setLineMode();
    setApexSize();
    setApexMode();
    setProjectSet();
}

void view::connectSetting() {
    connect(ui->widget_2, SIGNAL(updateColor()), this, SLOT(setColor()));
    connect(ui->widget_2, SIGNAL(updatePosition()), this, SLOT(setPosition()));
    connect(ui->widget_2, SIGNAL(updateRotation()), this, SLOT(setRotation()));
    connect(ui->widget_2, SIGNAL(updateLineSize()), this, SLOT(setLineSize()));
    connect(ui->widget_2, SIGNAL(updateLineMode()), this, SLOT(setLineMode()));
    connect(ui->widget_2, SIGNAL(updateApexSize()), this, SLOT(setApexSize()));
    connect(ui->widget_2, SIGNAL(updateApexMode()), this, SLOT(setApexMode()));
    connect(ui->widget_2, SIGNAL(updateProjectSet()), this, SLOT(setProjectSet()));
    connect(ui->widget_2, SIGNAL(gif()), this, SLOT(setGif()));
    connect(ui->widget_2, SIGNAL(screenShot()), this, SLOT(setScreenShot()));
    connect(ui->widget_2, SIGNAL(openFile()), this, SLOT(setOpenFile()));
    connect(ui->widget_2, SIGNAL(updateZoom()), this, SLOT(setZoom()));
}
