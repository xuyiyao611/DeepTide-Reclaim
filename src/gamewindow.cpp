#include "gamewindow.h"

#include "gamescene.h"

#include <QIcon>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent),
      m_gameScene(new GameScene(this))
{
    setWindowTitle(QStringLiteral("深潮回收站 - P2 碰撞与边界"));
    resize(1280, 720);
    setMinimumSize(960, 540);
    setCentralWidget(m_gameScene);
}
