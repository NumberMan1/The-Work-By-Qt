#ifndef _BOXMAP_HPP_
#define _BOXMAP_HPP_

#include <QObject>
#include <QPainter>
#include <QErrorMessage>

#define MYGAMEBEGIN namespace MyGame {
#define MYGAMEEND }

MYGAMEBEGIN

enum mapElement : uint {
    // 地图元素
    Wall = 1,
    Case = 2,
    End = 3,
    Win = 4,
    Human = 5, 
    PICTURE_WIDTH = 40, // 地图图片宽度

};

class BoxMap
    : public QObject {
public:
    explicit BoxMap(QObject* parent = nullptr);
    void drawMap
    (const uint x, const uint y, QImage& img, QPainter* painter) const noexcept;
    inline std::vector<std::vector<int>>& getMap() { return mMap; }
    inline uint getRow() const { return mRow; }
    inline uint getCol() const { return mCol; }

private:
    uint mRow;
    uint mCol;
    std::vector<std::vector<int>> mMap;
    bool initByFile(const QString& fileName);
};

MYGAMEEND
#endif // !_BOXMAP_HPP_