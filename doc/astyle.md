## Templates
### GorgonMeducer code style

https://github.com/GorgonMeducer/

```bash
astyle --style=kr --indent=spaces=4 --pad-oper --pad-header --unpad-paren --suffix=none --align-pointer=name --indent-switches --lineend=windows --convert-tabs --verbose $1
```

### RT-Thread

```bash
#!/bin/sh

astyle --style=allman --indent=spaces=4 --pad-oper --pad-header --unpad-paren --suffix=none --align-pointer=name --lineend=linux --convert-tabs --verbose $1
```







## Usage

## `--style=kr`
```c
int Foo(bool isBar)
{
    if (isBar) {
        bar();
        return 1;
    } else
        return 0;
}

```
## `--pad-oper`



## Note

- trailing whitespaces always removed https://sourceforge.net/p/astyle/bugs/455/
- 

## Command

```bash
sh tool/as.sh --recursive "src/hal/user/*.c,*.h"
sh tool/as.sh --recursive "src/app/*.c,*.h"
sh tool/as.sh --recursive "src/hal/board/*.c,*.h"
```

## Generate standalone txt for review

```bash
sh ./tool/mergefiles.sh prj/nrf52840-m2/00-platform/prjfiles.txt  > _publish/platform-20201031-5.txt
```
