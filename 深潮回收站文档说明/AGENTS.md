# AGENTS.md

> 本文件只记录稳定、长期有效的项目约定。  
> 不记录一次性任务、当前阶段 TODO、会频繁变化的数值试验结果，也不记录第三方文档的复制内容。

## 1. 项目技术栈

- 语言：`C++17`
- 图形框架：`Qt Widgets`
- 渲染方式：`QPainter`
- 定时更新：`QTimer`
- 图片资源：`QPixmap`
- 音效：`QSoundEffect` 或后续等价轻量方案
- 构建工具：`CMake` 或 Qt Creator 默认构建链
- 目标平台：`Windows`

## 2. 项目正式目标

本项目长期固定目标为：

1. 实现一个图形化 2D 海底采集游戏。
2. 形成“下潜 - 采集 - 返航 - 结算 - 升级”的完整闭环。
3. 使用原创资源命名、原创场景命名和原创 UI 表达。
4. 保持工程结构清晰，适合课程报告讲解和后续维护。

## 3. 推荐工程结构

推荐按以下方式组织：

- `src/`
  存放源码

- `assets/images/`
  存放图片资源

- `assets/sounds/`
  存放音效资源

- `assets/maps/`
  存放地图配置

- `docs/`
  存放开发文档和报告素材

## 4. 统一代码组织原则

优先遵守：

1. 场景层负责流程，不负责堆积全部业务细节。
2. 玩家、资源、敌人、背包、升级、存档分别建类。
3. 配置优先数据驱动，不把所有数值散落在多个源文件里。
4. 输入、更新、碰撞、结算、渲染尽量分函数。
5. 临时调试代码必须容易清理，不要长期污染主逻辑。

## 5. 推荐类与职责边界

- `GameWindow`
  只负责主窗口和场景承载

- `SceneManager`
  负责场景切换和状态交接

- `GameScene`
  负责主循环、输入分发和场景内对象协调

- `Player`
  负责玩家状态、移动、氧气和交互

- `ResourceItem`
  负责采集物定义

- `Enemy`
  负责危险生物行为

- `Inventory`
  负责背包统计和容量控制

- `UpgradeManager`
  负责升级规则和效果应用

- `LevelManager`
  负责海域地图和解锁状态

- `SaveData`
  负责存档与读取

## 6. 代码风格约定

- 类名：使用 `PascalCase`
- 函数名：使用 `camelCase`
- 成员变量：使用 `m_` 前缀
- 静态文件内辅助变量：使用 `s_` 前缀
- 常量：使用 `k` 前缀或全大写常量名，项目内保持统一
- 枚举：使用明确的枚举类 `enum class`
- 布尔变量：优先使用 `is`、`has`、`can` 前缀

### 示例

```cpp
class Player {
public:
    void update(float dt);
    bool canCollect() const;

private:
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_oxygen = 100.0f;
    bool m_isCollecting = false;
};
```

## 7. 函数拆分约定

避免把一个大函数写成全部逻辑入口。

在 `GameScene` 中优先拆成：

```cpp
void processInput();
void updateGame(float dt);
void updatePlayer(float dt);
void updateWorld(float dt);
void handleCollisions();
void handleInteractions();
void renderHud(QPainter& painter);
void checkGameState();
```

## 8. 注释约定

- 注释只写“为什么这么做”或“这里有什么坑”。
- 不要写和代码表面意思重复的废话注释。
- 临时代码、绕过逻辑、平台兼容处理必须加简短注释。

## 9. 资源命名约定

- 图片：`snake_case`
- 地图：`level_xx.txt` 或 `zone_xx.json`
- 音效：`action_name_variant.wav`
- 存档：`save_slot_01.json`

### 示例

- `player_idle.png`
- `glow_cluster.png`
- `zone_01_shallow.json`

## 10. 已知陷阱

1. Qt 键盘输入如果焦点不在主场景控件上，会出现“按键无效”。
2. `QTimer` 驱动下如果逻辑写得过重，会导致实际帧率抖动。
3. 在 `paintEvent` 内修改游戏状态容易引入渲染和逻辑耦合错误。
4. 场景切换时如果直接销毁对象，容易丢失需要结算的数据。
5. 背包、升级和结算如果共用一份临时数据结构，后续极容易出现重复结算。
6. 地图碰撞盒和精灵尺寸不一致时，手感会很差。
7. 氧气消耗如果直接绑定帧数而不是时间步长，机器快慢不同会导致体验不一致。
8. 存档结构如果过早写死且没有版本字段，后期改字段容易读档崩溃。
9. 在 `MinGW + CMake + Qt AutoGen` 组合下，如果项目路径包含中文，可能出现 `AutogenInfo.json` 读取失败；优先通过 ASCII 路径入口构建。

## 11. 关键指令

以下命令用于项目的长期日常开发。

### 如果使用 Qt Creator

- 打开项目文件并直接构建运行

### 如果使用 CMake

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

### 运行程序

```powershell
.\build\Debug\DeepTideStation.exe
```

### 清理后重新构建

```powershell
Remove-Item -Recurse -Force .\build
cmake -S . -B build
cmake --build build --config Debug
```

### 当前仓库的稳定构建方式

如果直接在 `D:\大作业` 下用 `MinGW + CMake` 构建，可能因为中文路径触发 Qt 自动生成问题。  
当前推荐优先使用：

```powershell
powershell -ExecutionPolicy Bypass -File .\build-qt.ps1
```

## 12. 必跑命令

每次较大代码修改后，至少执行：

```powershell
cmake --build build --config Debug
```

如果项目已接入自动化测试，再执行：

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

如果没有自动化测试，至少人工跑一遍核心闭环：

1. 启动程序
2. 进入游戏
3. 移动
4. 采集
5. 返航
6. 结算

## 13. 提交约定

- 每完成一个独立阶段再提交，不要把大量不相关改动混在一个提交里。
- 提交信息优先使用：
  - `init:`
  - `feat:`
  - `fix:`
  - `refactor:`
  - `docs:`
- 不提交编译产物、临时缓存和大型无关资源。

## 14. 文档优先级

项目推进时优先参考：

1. `项目工作流程.md`
2. `执行计划与测试.md`
3. `架构概览.md`

视频录制时优先参考：

1. `视频讲解提纲.md`
2. `视频逐段脚本.md`
3. `视频演示流程与检查清单.md`

## 15. 本文件明确不记录的内容

以下内容不应写进本文件：

1. 某一轮临时任务分配
2. 当前阶段未完成事项
3. 今天的测试结果
4. 一次性需求
5. 频繁变动的临时数值
6. 第三方文档全文复制

## 16. 最后结论

本文件的作用是保证项目在多轮开发中保持稳定的工程约定，而不是充当任务清单。

只要有内容明显属于“短期状态”而不是“长期规范”，就不应该写进这里。
