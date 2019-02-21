#include "obstacle.h"

Obstacle::Obstacle(int xpos, int ypos, int width, int height, QColor colour) :
    m_xpos(xpos),
    m_ypos(ypos),
    m_width(width),
    m_height(height),
    m_colour(colour) {}

void Obstacle::render(QPainter &paint, int frameHeight) {
    QBrush brush {m_colour};
    paint.setBrush(brush);
    paint.drawRect(m_xpos, frameHeight - m_ypos - m_height, m_width, m_height);
}

void Obstacle::moveLeft(int x) {
    m_xpos -= x;
}
