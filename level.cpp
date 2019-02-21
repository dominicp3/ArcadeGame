#include "level.h"

Level::Level(int width, int height, Player player) :
    m_frameWidth(width),
    m_frameHeight(height),
    m_player(player)
{
    QDir path = QDir::currentPath();
    path.cd("../ArcadeGame/images");
    m_background = QImage {path.path().append("/background.png")};
}

Level::Level(Point dimensions, Player player) :
    m_frameWidth(static_cast<int>(dimensions.x)),
    m_frameHeight(static_cast<int>(dimensions.y)),
    m_player(player)
{
    QDir path = QDir::currentPath();
    path.cd("../ArcadeGame/images");
    m_background = QImage {path.path().append("/background.png")};
}

void Level::renderLevel(QPainter &paint) {

    if (m_screenOffset <= -2*m_frameWidth) m_screenOffset = 0;
    paint.drawImage(m_screenOffset, 0, m_background, 0, 0, 3600, m_frameHeight);

    bool playerAtMiddle = m_player.getRightEdge() + m_player.getXVelocity() >= m_frameWidth/2;

    if (playerAtMiddle) {
        m_player.setXVelocity(0);
        m_screenOffset -= 6;
    }

    for (auto &o : m_obstacles) {
        if (playerAtMiddle) o.moveLeft(6);
        o.render(paint, m_frameHeight);
    }

    m_player.move(m_obstacles, m_frameWidth, m_frameHeight);
    m_player.render(paint, m_frameHeight);
}

void Level::addObstacle(Obstacle obj) {
    m_obstacles.push_back(obj);
}
