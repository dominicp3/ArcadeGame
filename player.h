#ifndef PLAYER_H
#define PLAYER_H

#include "obstacle.h"

class Player {
public:
    Player(int xpos, int ypos);
    void move(std::vector<Obstacle> &obstacles, int renderWidth, int renderHeight);
    void collisionDetection(Obstacle &ob);

    void render(QPainter &painter, int frameHeight);

    bool collisionLeft(Obstacle &ob);
    bool collisionRight(Obstacle &ob);
    bool collisionUp(Obstacle &ob);
    bool collisionDown(Obstacle &ob);

    // x coordinates for vertical edges
    double getLeftEdge() {return m_xpos;}
    double getRightEdge() {return m_xpos + m_width;}

    // y coordinates for horizontal edges
    double getTopEdge() {return m_ypos + m_height;}
    double getBottomEdge() {return m_ypos;}

    double getXVelocity() {return m_xvel;}

    void setXVelocity(double x) {m_xvel = x;}
    void setYVelocity(double y) {m_yvel = y;}
    void setIcon(QString &path) {m_playerIcon = QImage(path);}

private:
    double m_xpos;
    double m_ypos;

    double m_xvel;
    double m_yvel;

    int m_width;
    int m_height;

    QImage m_playerIcon;
    double m_gravity = 0.5;
};

#endif // PLAYER_H
