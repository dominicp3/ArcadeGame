#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include "level.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;
    void configureTimer();
    void paintEvent(QPaintEvent *painter) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void configureLevel(const QString filename);

public slots:
    void nextFrame();

private:
    Ui::Dialog *ui;
    QTimer *timer;
    Level *level;
    bool up_key = false;
    bool left_key = false;
    bool right_key = false;
};

#endif // DIALOG_H
