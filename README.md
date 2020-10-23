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

