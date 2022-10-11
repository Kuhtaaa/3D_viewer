QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += GL_SILENCE_DEPRECATION

SOURCES += \
    controller/s21_controller.cc \
    main.cpp \
    model/affineTransform/s21_affine_transform.cc \
    model/parser/s21_parser.cc \
    model/s21_model.cc \
    view/gifimage/dgif_lib.c \
    view/gifimage/egif_lib.c \
    view/gifimage/gif_err.c \
    view/gifimage/gif_font.c \
    view/gifimage/gif_hash.c \
    view/gifimage/gifalloc.c \
    view/gifimage/qgifimage.cpp \
    view/gifimage/quantize.c \
    view/interface/s21_interface.cc \
    view/render/s21_render.cc \
    view/s21_view.cc

HEADERS += \
    controller/s21_controller.h \
    model/affineTransform/s21_affine_transform.h \
    model/parser/s21_parser.h \
    model/s21_model.h \
    view/gifimage/gif_hash.h \
    view/gifimage/gif_lib.h \
    view/gifimage/gif_lib_private.h \
    view/gifimage/qgifglobal.h \
    view/gifimage/qgifimage.h \
    view/gifimage/qgifimage_p.h \
    view/interface/s21_interface.h \
    view/render/s21_render.h \
    view/s21_view.h

FORMS += \
    view/interface/s21_interface.ui \
    view/s21_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#openglwidgets
