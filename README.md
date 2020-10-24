## File Structure

| Path                   | Description                                    |
| ---------------------- | ---------------------------------------------- |
| `prj/`                 | All projects file                              |
| `prj/$BOARD/$APP/`     | Project path                                   |
| `src/`                 | All source code files                          |
| `src/app/$BOARD/$APP/` | Application layer source code                  |
| `src/app/common/`      | Common application driver                      |
| `src/lib/`             | Middle layer driver                            |
| `src/hal/mcu`          | CMSIS and verdor library                       |
| `src/hal/user/$CHIP`   | User defined low level driver for a group MCUs |
| `src/hal/board/$BOARD` | Board specific driver, `lib` low level driver  |
|                        |                                                |
|                        |                                                |



## 设计原则

1. 使用直接调用寄存器的方式实现外设操作的简单接口，最小化依赖官方仓库
2. 