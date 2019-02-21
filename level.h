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

        void scroll(bool s);

private:
        int m_renderWidth;
        const int m_renderHeight;
        Player m_player;
        std::vector<Obstacle> m_obstacles;
        QImage m_background;
        int m_screenOffset = 0;
        bool m_scroll = true;
};

#endif // LEVEL_H
