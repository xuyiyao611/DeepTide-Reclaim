#include "gamewindow.h"

#include "gamescene.h"

#include <QIcon>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent),
      m_gameScene(new GameScene(this))
{
    setWindowTitle(QStringLiteral("深潮回收站 - P8 海域推进与解锁"));
    resize(1280, 720);
    setMinimumSize(960, 540);
    setCentralWidget(m_gameScene);
}
