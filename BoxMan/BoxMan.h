#ifndef _BOXMAN_H_
#define _BOXMAN_H_

#include <QtWidgets/QMainWindow>
#include "ui_BoxMan.h"
#include "BoxMap.hpp"
#include <QPainter>
#include "Role.hpp"
#include <QTimer>

class BoxMan : public QMainWindow
{
    Q_OBJECT

public:
    BoxMan(QWidget *parent = nullptr);
    ~BoxMan();
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void collision(const int row, const int col);
    bool checkWin() const noexcept;

private:
    Ui::BoxManClass ui;
    QTimer* mTimer;
    MyGame::BoxMap* mPMap;
    QPainter* mPainter;
    MyGame::Role* mPRole;
    bool mWinFlag;
};

#endif // !_BOXMAN_H_