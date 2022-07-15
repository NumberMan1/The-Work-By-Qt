#include "Role.hpp"
#include "BoxMap.hpp"

using MyGame::mapElement;

MyGame::Role::Role(QObject* parent)
    : mRow(1), mCol(1), mImg(":/Pictures/Image/people.png"),
    mDrawPos(mRow * PICTURE_WIDTH, mCol * PICTURE_WIDTH) {
    
}

void MyGame::Role::move(const QPoint& point) {
    mRow += point.y(), mCol += point.x();
    mDrawPos += point * static_cast<int>(PICTURE_WIDTH);
}

void MyGame::Role::paintRole
(QPainter& painter, const QPoint& displace) const {
    painter.drawImage(mDrawPos + displace, mImg);
}
