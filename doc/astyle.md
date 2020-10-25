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




