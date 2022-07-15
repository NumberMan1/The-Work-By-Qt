#include "BoxMap.hpp"
#include <QFile>
#include <QByteArray>
#include <QList>
#include <QFileDialog>

MyGame::BoxMap::BoxMap(QObject* parent)
    :QObject(parent), mRow(0), mCol(0), mMap() {
    if (!initByFile(QString(":/Maps/Map/Map.txt")))
        throw std::runtime_error("地图初始化失败");
    
}

bool MyGame::BoxMap::initByFile(const QString& fileName) {
    QFile file(fileName);
    std::string s;
    if (!file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
        return false;
    }
    QByteArray bitArr = file.readAll(); // 得所有字符
    bitArr.replace("\r\n", "\n");
    using Line = QList<QByteArray>;
    Line rowList = bitArr.split('\n'), colList; // 得每行字符
    colList = rowList[0].split(','); // 得首行每个数字
    mRow = rowList.length(), mCol = colList.length();
    std::vector<int> temp;
    for (int i = 0; i < mCol; ++i) {
        temp.push_back(colList[i].toInt());
    }
    mMap.push_back(temp);
    for (int i = 1; i != mRow; ++i) { // 得其它行每个数字
        temp.clear();
        colList = rowList[i].split(',');
        for (int j = 0; j != mCol; ++j) {
            temp.push_back(colList[j].toInt());
        }
        mMap.push_back(temp);
    }
    return true;
}

void MyGame::BoxMap::drawMap
(const uint x, const uint y, QImage& img, QPainter* painter) const noexcept {
    uint row = 0;
    for (auto& a : mMap) {
        uint col = 0;
        for (auto& value : a) {
            switch (value) {
            case MyGame::mapElement::Wall: {
                img.load(":/Pictures/Image/wall.png");
                painter->drawImage(QRect(x + col * MyGame::PICTURE_WIDTH,
                    y + row * MyGame::PICTURE_WIDTH,
                    MyGame::PICTURE_WIDTH, MyGame::PICTURE_WIDTH),
                    img);
                break;
            }
            case MyGame::mapElement::Case: {
                img.load(":/Pictures/Image/case.png");
                painter->drawImage(QRect(x + col * MyGame::PICTURE_WIDTH,
                    y + row * MyGame::PICTURE_WIDTH,
                    MyGame::PICTURE_WIDTH, MyGame::PICTURE_WIDTH),
                    img);
                break;
            }
            case MyGame::mapElement::End: {
                img.load(":/Pictures/Image/end.png");
                painter->drawImage(QRect(x + col * MyGame::PICTURE_WIDTH,
                    y + row * MyGame::PICTURE_WIDTH,
                    MyGame::PICTURE_WIDTH, MyGame::PICTURE_WIDTH),
                    img);
                break;
            }
            case MyGame::mapElement::Win: {
                img.load(":/Pictures/Image/win.png");
                painter->drawImage(QRect(x + col * MyGame::PICTURE_WIDTH,
                    y + row * MyGame::PICTURE_WIDTH,
                    MyGame::PICTURE_WIDTH, MyGame::PICTURE_WIDTH),
                    img);
                break;
            }
            default: break;
            }
            ++col;
        }
        ++row;
    }
}