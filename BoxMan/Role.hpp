#pragma once
#include <QObject>
#include <QPoint>
#include <QPainter>

#define MYGAMEBEGIN namespace MyGame {
#define MYGAMEEND }

MYGAMEBEGIN

class Role :
    public QObject {
public:
    explicit Role(QObject* parent = nullptr);
    void move(const QPoint& point);
    void paintRole
    (QPainter& painter, const QPoint& displace) const;
    inline uint getRow() const { return mRow; }
    inline uint getCol() const { return mCol; }
    inline QPoint& getPos() { return mDrawPos; }

private:
    uint mRow;
    uint mCol;
    QImage mImg;
    QPoint mDrawPos;

};

MYGAMEEND