#pragma once

#include <QMainWindow>

class GameScene;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

private:
    GameScene *m_gameScene = nullptr;
};
