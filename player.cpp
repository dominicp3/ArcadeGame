#include <QDir>
#include "player.h"

Player::Player(int xpos, int ypos) :
    m_xpos(xpos),
    m_ypos(ypos)
{
    QDir iconPath = QDir::currentPath();
    iconPath.cd("../ArcadeGame/images");
    setIcon(iconPath.path().append("/mario.png"));
    m_width  = m_playerIcon.width();
    m_height = m_playerIcon.height();
}

void Player::render(QPainter &painter, int frameHeight) {
    painter.drawImage(static_cast<int>(m_xpos), static_cast<int>(frameHeight - m_height - m_ypos), m_playerIcon);
}

void Player::move(std::vector<Obstacle> &obstacles, int renderWidth, int renderHeight) {

    for (auto &ob : obstacles)
        collisionDetection(ob);

    if (getBottomEdge() + m_yvel <= 54) {
        m_ypos = 54;
        m_yvel = 0;
    }

    if (getLeftEdge() + m_xvel >= 0 and getRightEdge() + m_xvel < renderWidth)
        m_xpos += m_xvel;

    if (getBottomEdge() + m_yvel >= 54 and getTopEdge() + m_yvel <= renderHeight)
        m_ypos += m_yvel;

    m_yvel -= m_gravity;
}

void Player::collisionDetection(Obstacle &ob) {
    m_xpos += m_xvel;
    m_ypos += m_yvel;

    if (collisionLeft(ob)) {
        m_xvel = 0;
        m_xpos = ob.getRightEdge() + 1;
    }

    if (collisionRight(ob)) {
        m_xvel = 0;
        m_xpos = ob.getLeftEdge() - m_width;
    }

    if (collisionDown(ob)) {
        m_yvel = 0;
        m_ypos = ob.getTopEdge();
    }

    if (collisionUp(ob)) {
        m_yvel = -1;
        m_ypos = ob.getBottomEdge() - m_height;
    }

    m_xpos -= m_xvel;
    m_ypos -= m_yvel;
}

bool Player::collisionLeft(Obstacle &ob) {
    if (getLeftEdge() >= ob.getRightEdge() - 8 and getLeftEdge() <= ob.getRightEdge()) {
        if (getBottomEdge() > ob.getBottomEdge() and getBottomEdge() < ob.getTopEdge() - 1)
            return true;
        if (getTopEdge() > ob.getBottomEdge() and getTopEdge() < ob.getTopEdge())
            return true;
        if (getTopEdge() > ob.getTopEdge() and getBottomEdge() < ob.getBottomEdge())
            return true;
    }
    return false;
}

bool Player::collisionRight(Obstacle &ob) {
    if (getRightEdge() >= ob.getLeftEdge() and getRightEdge() <= ob.getLeftEdge() + 7) {
        if (getBottomEdge() >= ob.getBottomEdge() and getBottomEdge() <= ob.getTopEdge() - 1)
            return true;
        if (getTopEdge() > ob.getBottomEdge() and getTopEdge() < ob.getTopEdge())
            return true;
        if (getTopEdge() > ob.getTopEdge() and getBottomEdge() < ob.getBottomEdge())
            return true;
    }

    return false;
}

bool Player::collisionUp(Obstacle &ob) {
    if (getTopEdge() >= ob.getBottomEdge() and getTopEdge() <= ob.getBottomEdge() + 8) {
        if (getLeftEdge() > ob.getLeftEdge() and getLeftEdge() < ob.getRightEdge())
            return true;
        if (getRightEdge() > ob.getLeftEdge() and getRightEdge() < ob.getRightEdge())
            return true;
        if (getLeftEdge() <= ob.getLeftEdge() and getRightEdge() >= ob.getRightEdge())
            return true;
    }
    return false;
}

bool Player::collisionDown(Obstacle &ob) {
    if (getBottomEdge() >= ob.getTopEdge() - 20 and getBottomEdge() <= ob.getTopEdge()) {
        if (getLeftEdge() > ob.getLeftEdge() and getLeftEdge() < ob.getRightEdge())
            return true;
        if (getRightEdge() > ob.getLeftEdge() and getRightEdge() < ob.getRightEdge())
            return true;
        if (getLeftEdge() <= ob.getLeftEdge() and getRightEdge() >= ob.getRightEdge())
            return true;
    }
    return false;
}
