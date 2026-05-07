# P0 启动排障说明

本文档只记录 `P0 工程基础确认` 阶段最常见的启动问题。

## 1. 程序能编译但窗口不显示

- 先确认是否通过 `QApplication` 进入事件循环。
- 先确认 `GameWindow::show()` 已执行。
- 先确认主窗口没有在构造函数中被异常关闭。

## 2. 能显示窗口但场景不刷新

- 先确认 `QTimer` 已连接到刷新槽函数。
- 先确认定时器已 `start()`。
- 先确认 `tick()` 中最终调用了 `update()`。

## 3. 按键无效

- 先点击一次游戏窗口，让焦点回到主场景。
- 确认场景控件 `setFocusPolicy(Qt::StrongFocus)` 已设置。
- 确认没有别的控件抢走键盘焦点。

## 4. 资源路径识别异常

- 当前工程会从程序目录向上查找项目根目录。
- 根目录判定依赖 `assets/`、`src/` 和 `深潮回收站文档说明/` 同时存在。
- 如果目录结构被改动，需要同步修改 `src/projectpaths.cpp`。

## 5. MinGW + Qt AutoGen 在中文路径下失败

- 当前仓库位于 `D:\大作业`，直接构建时，Qt 自动生成阶段可能把中文路径读坏。
- 如果出现 `AutogenInfo.json is not readable` 这类错误，优先不要怀疑业务代码。
- 当前稳定方案是通过 ASCII 入口 `D:\deep_tide_workspace` 构建。
- 已提供 `build-qt.cmd` 统一完成这件事。

## 6. 如何验证 P0 已通过

- 程序可稳定启动。
- 主场景能持续刷新。
- 控制台能看到启动日志和输入日志。
- `assets/images/`、`assets/sounds/`、`assets/maps/` 检查通过。
