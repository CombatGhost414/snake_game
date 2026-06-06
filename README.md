# 贪吃蛇游戏 (Snake Game)

C++ 控制台贪吃蛇游戏，使用面向对象设计实现。

## 游戏特性

- 经典贪吃蛇玩法：控制蛇移动，吃掉食物增长身体
- 撞墙/撞自身判定游戏结束
- 实时分数显示

## 项目结构

```
snake_game/
├── 代码/
│   ├── main.cpp        # 程序入口
│   ├── Game.h/cpp      # 游戏主逻辑（初始化、主循环、渲染）
│   ├── Snake.h/cpp     # 蛇类（移动、增长、碰撞检测）
│   ├── Food.h/cpp      # 食物类（随机生成位置）
│   ├── Board.h/cpp     # 棋盘类（边界绘制）
│   ├── Point.h         # 坐标点结构体
│   └── GameEntity.h    # 游戏实体基类
├── snake_game.exe      # 编译好的可执行文件
├── 1030425212_张俊哲_贪吃蛇.pdf  # 项目文档
└── README.md
```

## 编译运行

### Windows (MinGW)
```bash
g++ -o snake_game.exe 代码/*.cpp -static
./snake_game.exe
```

### Windows (MSVC)
```bash
cl /EHsc /Fe:snake_game.exe 代码/*.cpp
snake_game.exe
```

## 操作方式

| 按键 | 功能 |
|------|------|
| `W` / `↑` | 向上移动 |
| `S` / `↓` | 向下移动 |
| `A` / `←` | 向左移动 |
| `D` / `→` | 向右移动 |
| `Q` | 退出游戏 |

## 作者

张俊哲
