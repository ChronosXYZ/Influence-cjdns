#pragma once

#include "network.hpp"
#include <QJsonObject>

class Handler : public QObject
{
    Q_OBJECT

    public:
        Handler();
    signals:
        createSessionSuccess();
    private:
        Network *network;
    private slots:
        void handle(QJsonObject jsonReceived);
};
