#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const int FRAME_WIDTH = 1100;
const int FRAME_HEIGHT = 700;

const int LEFT_ARROW = 16777234;
const int RIGHT_ARROW = 16777236;
const int UP_ARROW = 16777235;
//const int DOWN_ARROW = 16777237;

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    timer(new QTimer {this}),
    level(new Level {FRAME_WIDTH, FRAME_HEIGHT, Player {10, 0}})
{
    setFixedSize(FRAME_WIDTH, FRAME_HEIGHT);
    configureLevel("/config.json");
    configureTimer();

    ui->setupUi(this);
    configureTimer();
}

Dialog::~Dialog() {
    delete ui;
    delete timer;
    delete level;
}

void Dialog::configureLevel(const QString filename) {

    QDir path = (QDir::currentPath());
    path.cd("../ArcadeGame");

    QFile file { path.path().append(filename) };

    file.open(QIODevice::ReadOnly);
    QByteArray val { file.readAll() };
    file.close();

    QJsonObject object {QJsonDocument::fromJson(val).object()};
    QJsonArray obstacles = object["obstacles"].toArray();

    for (int i = 0; i < obstacles.size(); i++) {
        QString colour {obstacles.at(i).toObject()["colour"].toString()};
        double xpos {obstacles.at(i).toObject()["position"].toObject()["x"].toDouble()};
        double ypos {obstacles.at(i).toObject()["position"].toObject()["y"].toDouble()};
        double width {obstacles.at(i).toObject()["dimensions"].toObject()["x"].toDouble()};
        double height {obstacles.at(i).toObject()["dimensions"].toObject()["y"].toDouble()};
        level->addObstacle( Obstacle {Point {xpos, ypos}, Point {width, height}, colour} );
    }

}

void Dialog::nextFrame() {
    if (left_key)
        level->setXVelocity(-6);
    if (right_key)
        level->setXVelocity(6);
    if ((left_key and right_key) or (!left_key and !right_key))
        level->setXVelocity(0);
    update();
}

void Dialog::configureTimer() {
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(15);
}

void Dialog::paintEvent(QPaintEvent *painter) {
    QPainter paint {this};
    level->renderLevel(paint);
    painter->ignore();
}

void Dialog::keyReleaseEvent(QKeyEvent *e) {
    if (!e->isAutoRepeat()) {
        if (e->key() == LEFT_ARROW)
            left_key = false;
        if (e->key() == RIGHT_ARROW)
            right_key = false;
        if (e->key() == UP_ARROW)
            up_key = false;
    }
}

void Dialog::keyPressEvent(QKeyEvent *e) {
    if (e->key() == LEFT_ARROW)
        left_key = true;
    if (e->key() == RIGHT_ARROW)
        right_key = true;
    if (e->key() == UP_ARROW and !up_key) {
        up_key = true;
        level->setYVelocity(8);
    }
}
