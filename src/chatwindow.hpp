#pragma once

#include <QWidget>

namespace Ui {
    class Form;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit ChatWindow(QWidget *parent = 0);
        ~ChatWindow();

    private:
        Ui::ChatWindow *ui;
};
