# CheatInADraw
A less elegant program shows how to cheat in a draw by using serval dangerous tricks.

## What's this?

When I audited a class of **Cryptography**, Professor gave us a task as follows:

1. There are N people joined a draw and M of them will be the lucky dogs. You shall write a program to do this.
2. The result of draw should be random.
3. No one can be chosen twice.
4. After finished this, try to cheat others in your program to make someone owned a higher probability of winning.
5. Try to hide your cheat in your code so that no one will find it.

## Prerequisites

* Ubuntu or other 64 bits Unix-like operating system
* gcc 5.0 or higher
* `/dev/urandom`should be avaliable

## Run

1. Compile `draw.c`.

```sh
gcc -Wl,-z,norelro draw.c -o draw
```

2. Run `objdump` on  executable file `draw` and change `FINALIZER`'s value to `VMA`.

```sh
objdump -h -j .fini_array draw
```

3. Disassemble executable file `draw`.

```sh
objdump -d ./draw > draw.s
```

4. Find these parts in `draw.s` and change macros in `draw.c` correspondingly.


| MAcro        | Value                                    |
| ------------ | ---------------------------------------- |
| MAGIC_NUMBER | Address of `total`                       |
| ADDR         | Address of `last`                        |
| OFFSET       | Assembly offset between line `57` and line` 60` |

5. Recompile `draw.c`.

```sh
gcc -Wl,-z,norelro draw.c -o draw
```

## How

[函数堆栈、格式化字符串攻击及抽奖作弊](http://w-angler.com/2017/09/21/%E5%87%BD%E6%95%B0%E5%A0%86%E6%A0%88%E3%80%81%E6%A0%BC%E5%BC%8F%E5%8C%96%E5%AD%97%E7%AC%A6%E4%B8%B2%E6%94%BB%E5%87%BB%E4%BB%A5%E5%8F%8A%E6%8A%BD%E5%A5%96%E4%BD%9C%E5%BC%8A/)
