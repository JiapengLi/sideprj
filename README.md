

## File Structure

| Path                   | Description                                    |
| ---------------------- | ---------------------------------------------- |
| `prj/`                 | All projects file                              |
| `prj/$BOARD/$APP/`     | Project path                                   |
| `src/`                 | All source code files                          |
| `src/app/$BOARD/$APP/` | Application layer source code                  |
| `src/app/common/`      | Common application driver                      |
| `src/lib/`             | Middle layer driver                            |
| `src/hal/mcu`          | CMSIS and manufacture library                  |
| `src/hal/user/$CHIP`   | User defined low level driver for a group MCUs |
| `src/hal/board/$BOARD` | Board specific driver, `lib` low level driver  |
|                        |                                                |
|                        |                                                |

## Design Rules

1. Manipulate MCU registers directly, use minimum official redundancy library. 
2. Split source code into layers

## Projects

| Subject     | Path                                           | Percent |
| ----------- | ---------------------------------------------- | ------- |
| 00-platform | `prj\nrf52840-m2\00-platform\platform.uvprojx` | 100%    |
|             |                                                |         |
|             |                                                |         |

## TODO

- [x] ~~astyle  auto format code~~
- [x] ~~change variable name~~

