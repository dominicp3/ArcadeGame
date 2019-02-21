#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QColor>
#include <QPainter>

class Obstacle {
public:
    Obstacle(int xpos, int ypos, int width, int height, QColor colour);
    void render(QPainter &paint, int frameHeight);

    int getRightEdge() {return m_xpos + m_width;}
    int getBottomEdge() {return m_ypos;}
    int getLeftEdge() {return m_xpos;}
    int getTopEdge() {return m_ypos + m_height;}
    int getWidth() {return m_width;}
    int getHeight() {return m_height;}

    void moveLeft(int x);

private:
    int m_xpos;
    int m_ypos;

    int m_width;
    int m_height;

    QColor m_colour;
};

#endif // OBSTACLE_H
