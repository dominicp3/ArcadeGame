#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include <QDir>

class Level {
public:
    Level(int width, int height, Player player);

    void renderLevel(QPainter &paint);
    void addObstacle(Obstacle obj);

    void setXVelocity(double xV) {m_player.setXVelocity(xV);}
    void setYVelocity(double yV) {m_player.setYVelocity(yV);}

private:
    const int m_frameWidth;
    const int m_frameHeight;

    Player m_player;
    std::vector<Obstacle> m_obstacles;

    QImage m_background;

    int m_screenOffset = 0;
};

#endif // LEVEL_H
