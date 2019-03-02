#include "dialog.h"
#include "ui_dialog.h"
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>

const int FRAME_WIDTH = 1700;
const int FRAME_HEIGHT = 700;

Dialog::Dialog(QWidget *parent):
        QDialog(parent),
        ui(new Ui::Dialog),
        timer(new QTimer {this})
{
        setFixedSize(FRAME_WIDTH, FRAME_HEIGHT);
        configureLevel("/config.json");
        configureTimer();
        ui->setupUi(this);
}

Dialog::~Dialog()
{
        delete ui;
        delete timer;
        delete level;
}

void Dialog::nextFrame()
{
        if (left_key)
                level->setXVelocity(-6);
        if (right_key)
                level->setXVelocity(6);
        if ((left_key and right_key) or (!left_key and !right_key))
                level->setXVelocity(0);
        update();
}

void Dialog::configureLevel(const QString filename)
{
        QDir filepath {QDir::currentPath()};
        filepath.cd("../ArcadeGame");

        QFile file {filepath.path().append(filename)};

        if (!file.exists())
                throw "file does not exist!";

        file.open(QIODevice::ReadOnly);
        QJsonObject object {QJsonDocument::fromJson(file.readAll()).object()};
        file.close();

        auto sizeObject {object["size"]};
        auto positionObject {object["position"]};
        auto obstaclesObject {object["obstacles"]};

        if (sizeObject.isNull())
                throw "invalid size object in config file, name should be \"size\"";
        if (positionObject.isNull())
                throw "invalid position object in config file, name should be \"position\"";
        if (obstaclesObject.isNull())
                throw "invalid obstacles object in config file, name should be \"obstacles\"";

        auto size {sizeObject.toString()};

        if (size != "tiny" and size != "normal" and size != "large" and size != "giant")
                throw "invalid size value, options are \"tiny\", \"normal\", \"large\", \"giant\"";

        auto xPosition {positionObject.toObject()["x"].toInt()};
        auto yPosition {obstaclesObject.toObject()["y"].toInt()};

        if (xPosition < 0 or xPosition > FRAME_WIDTH / 2)
                throw "invalid x position, should be between 0 and FRAME_WIDTH/2";
        if (yPosition < 0 or yPosition > FRAME_HEIGHT)
                throw "invalid y position, should be between 0 and FRAME_HEIGHT";

        level = new Level {FRAME_WIDTH, FRAME_HEIGHT, Player {xPosition, yPosition, size.prepend("/")}};

        QJsonArray obstacles = object["obstacles"].toArray();

        for (auto o : obstacles) {
                auto colour {o.toObject()["colour"].toString()};
                auto xpos {o.toObject()["position"].toObject()["x"].toInt()};
                auto ypos {o.toObject()["position"].toObject()["y"].toInt()};
                auto width {o.toObject()["dimensions"].toObject()["x"].toInt()};
                auto height {o.toObject()["dimensions"].toObject()["y"].toInt()};
                level->addObstacle(Obstacle {xpos, ypos, width, height, colour});
        }
}

void Dialog::configureTimer()
{
        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        timer->start(15);
}

void Dialog::paintEvent(QPaintEvent *painter)
{
        if (level != nullptr) {
                QPainter paint {this};
                level->renderLevel(paint);
                painter->ignore();
        }
}

void Dialog::keyReleaseEvent(QKeyEvent *e)
{
        if (!e->isAutoRepeat()) {
                if (e->key() == Qt::Key_Left) left_key = false;
                if (e->key() == Qt::Key_Right) right_key = false;
                if (e->key() == Qt::Key_Up) up_key = false;
        }
}

void Dialog::keyPressEvent(QKeyEvent *e)
{
        if (e->key() == Qt::Key_Left) left_key = true;
        if (e->key() == Qt::Key_Right) right_key = true;
        if (e->key() == Qt::Key_Up and !up_key) {
                up_key = true;
                level->setYVelocity(8);
        }
}
