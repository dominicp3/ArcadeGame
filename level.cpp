#include "level.h"

Level::Level(int width, int height, Player player) :
        m_renderWidth(width),
        m_renderHeight(height),
        m_player(player)
{
        QDir path = QDir::currentPath();
        path.cd("../ArcadeGame/images");
        m_background = QImage {path.path().append("/background.png")};
}

void Level::renderLevel(QPainter &paint)
{
        bool playerAtMiddle = m_player.getRightEdge() + m_player.getXVelocity() >= m_renderWidth;

        if (m_screenOffset <= -2200) m_screenOffset = 0;
        if (m_scroll and playerAtMiddle) m_screenOffset -= 6;

        paint.drawImage(m_screenOffset, 0, m_background, 0, 0, 4400, m_renderHeight);

        for (auto &o : m_obstacles) {
                if (m_scroll and playerAtMiddle) o.moveLeft(6);
                o.render(paint, m_renderHeight);
        }

        m_player.move(m_obstacles, m_renderWidth, m_renderHeight);
        m_player.render(paint, m_renderHeight);
}

void Level::addObstacle(Obstacle obj)
{
        m_obstacles.push_back(obj);
}

void Level::scroll(bool s)
{
        m_scroll = s;
        if (s) m_renderWidth /= 2;
}
