#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T15:44:11
#
#-------------------------------------------------

QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    kernel/network.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
        mainwindow.h \
    kernel/network.hpp \
    lib/json/detail/conversions/from_json.hpp \
    lib/json/detail/conversions/to_chars.hpp \
    lib/json/detail/conversions/to_json.hpp \
    lib/json/detail/input/binary_reader.hpp \
    lib/json/detail/input/input_adapters.hpp \
    lib/json/detail/input/lexer.hpp \
    lib/json/detail/input/parser.hpp \
    lib/json/detail/iterators/internal_iterator.hpp \
    lib/json/detail/iterators/iter_impl.hpp \
    lib/json/detail/iterators/iteration_proxy.hpp \
    lib/json/detail/iterators/json_reverse_iterator.hpp \
    lib/json/detail/iterators/primitive_iterator.hpp \
    lib/json/detail/output/binary_writer.hpp \
    lib/json/detail/output/output_adapters.hpp \
    lib/json/detail/output/serializer.hpp \
    lib/json/detail/exceptions.hpp \
    lib/json/detail/json_pointer.hpp \
    lib/json/detail/json_ref.hpp \
    lib/json/detail/macro_scope.hpp \
    lib/json/detail/macro_unscope.hpp \
    lib/json/detail/meta.hpp \
    lib/json/detail/value_t.hpp \
    lib/json/adl_serializer.hpp \
    lib/json/json.hpp \
    lib/json/json_fwd.hpp \
    mainwindow.h

FORMS += \
        mainwindow.ui
