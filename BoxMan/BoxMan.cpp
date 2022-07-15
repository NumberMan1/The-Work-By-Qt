#include "BoxMan.h"
#include "BoxMap.hpp"
#include <QKeyEvent>
#include <QMessageBox>
#include <stdexcept>

BoxMan::BoxMan(QWidget *parent)
    : QMainWindow(parent), mTimer(nullptr),
    mPMap(nullptr), mPainter(nullptr), mPRole(nullptr),
    mWinFlag(false) {
    ui.setupUi(this);
    mPainter = new QPainter(this);
    try {
        mPMap = new MyGame::BoxMap(this);
        mPRole = new MyGame::Role(this);
    } catch (std::runtime_error err) {
        auto message = new QErrorMessage(this);
        message->showMessage(err.what());
        message->exec();
        return;
    }
    setFixedSize(1280, 720);
    // 定时刷新屏幕
    mTimer = new QTimer(this);
    mTimer->start(100);
    connect(mTimer, &QTimer::timeout, [this]() {
        this->update();
        if (this->checkWin() && !this->mWinFlag) {
            this->mWinFlag = true;
            auto message = new QMessageBox(this);
            message->resize(300, 300);
            message->setText("Game Win!");
            message->setIcon(QMessageBox::Icon::Information);
            message->exec();
        }
        });
}

BoxMan::~BoxMan()
{}

void BoxMan::paintEvent(QPaintEvent* event) {
    mPainter->begin(this);
    // 画地图
    QImage img(":/Pictures/Image/ground.png");
    mPainter->drawImage(QRect(0, 0, 1280, 720), img);
    mPMap->drawMap(0, 300, img, mPainter);
    // 画人物
    mPRole->paintRole(*mPainter, QPoint(0, 300));

    mPainter->end();
}

void BoxMan::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_W:
    case Qt::Key::Key_Up: {
        collision(0, -1);
        mPRole->paintRole(*mPainter, QPoint(0, 300));
        break;
    }
    case Qt::Key::Key_S:
    case Qt::Key::Key_Down: {
        collision(0, 1);
        mPRole->paintRole(*mPainter, QPoint(0, 300));
        break;
    }
    case Qt::Key::Key_A:
    case Qt::Key::Key_Left: {
        collision(-1, 0);
        mPRole->paintRole(*mPainter, QPoint(0, 300));
        break;
    }
    case Qt::Key::Key_D:
    case Qt::Key::Key_Right: {
        collision(1, 0);
        mPRole->paintRole(*mPainter, QPoint(0, 300));
        break;
    }
    default:
        break;
    }
}

void BoxMan::collision(const int col, const int row) {
    using MyGame::mapElement;
    auto& tMap = mPMap->getMap();
    auto width = mPRole->getCol(), heighth = mPRole->getRow();
    switch (tMap[row + heighth][col + width]) { // 人物前面一格
    case mapElement::Wall: return;
    case mapElement::Case: {
        switch (tMap[row * 2 + heighth][col * 2 + width]) { // 箱子后面一格
        case mapElement::Wall: return;
        case mapElement::Case: return;
        case mapElement::Win: return;
        case mapElement::End: {
            mPRole->move(QPoint(col, row));
            tMap[row * 2 + heighth][col * 2 + width] = mapElement::Win;
            tMap[row + heighth][col + width] = 0;
            return;
        }
        default: {
            mPRole->move(QPoint(col, row));
            tMap[row * 2 + heighth][col * 2 + width] =
                tMap[row + heighth][col + width];
            tMap[row + heighth][col + width] = 0;
            return;
        }
        }
    }
    case mapElement::End: return;
    case mapElement::Win: {
        switch (tMap[row * 2 + heighth][col * 2 + width]) { // 箱子后面一格
        case mapElement::Wall: return;
        case mapElement::Case: return;
        case mapElement::Win: return;
        case mapElement::End: {
            mPRole->move(QPoint(col, row));
            tMap[row * 2 + heighth][col * 2 + width] = mapElement::Win;
            tMap[row + heighth][col + width] = mapElement::End;
            return;
        }
        default: { // 出洞
            mPRole->move(QPoint(col, row));
            tMap[row * 2 + heighth][col * 2 + width] = mapElement::Case;
            tMap[row + heighth][col + width] = mapElement::End;
            return;
        }
        }
    }
    default: { // 正常移动
        mPRole->move(QPoint(col, row));
        return;
    }
    }
}

bool BoxMan::checkWin() const noexcept {
    for (auto& l : mPMap->getMap()) {
        for (auto value : l) {
            if (value == MyGame::mapElement::End) {
                return false;
            }
        }
    }
    return true;
}