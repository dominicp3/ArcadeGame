#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const int FRAME_WIDTH = 1700;
const int FRAME_HEIGHT = 700;

const int LEFT_ARROW = 16777234;
const int RIGHT_ARROW = 16777236;
const int UP_ARROW = 16777235;
//const int DOWN_ARROW = 16777237;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    timer(new QTimer {this}),
    level(new Level {FRAME_WIDTH, FRAME_HEIGHT, Player {10, 0}})
{
    setFixedSize(FRAME_WIDTH, FRAME_HEIGHT);
    configureLevel("/config.json");
    ui->setupUi(this);
    configureTimer();
}

Dialog::~Dialog() {
    delete ui;
    delete timer;
    delete level;
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

void Dialog::configureLevel(const QString filename) {

    QDir filepath {QDir::currentPath()};
    filepath.cd("../ArcadeGame");

    QFile file {filepath.path().append(filename)};

    file.open(QIODevice::ReadOnly);
    QJsonObject object {QJsonDocument::fromJson(file.readAll()).object()};
    file.close();

    QJsonArray obstacles = object["obstacles"].toArray();

    for (auto o : obstacles) {
        QString colour {o.toObject()["colour"].toString()};
        double xpos {o.toObject()["position"].toObject()["x"].toDouble()};
        double ypos {o.toObject()["position"].toObject()["y"].toDouble()};
        double width {o.toObject()["dimensions"].toObject()["x"].toDouble()};
        double height {o.toObject()["dimensions"].toObject()["y"].toDouble()};
        level->addObstacle( Obstacle {Point {xpos, ypos}, Point {width, height}, colour} );
    }
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
