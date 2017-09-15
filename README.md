# CheatInADraw
A less elegant program shows how to cheat in a draw by using serval dangerous tricks.

## What's this?

When I audited a class of **Cryptography**, Professor gave us a task as follows:

1. There are N people joined a draw and N will be the lucky dogs. You shall write a program to do this.
2. The result of draw should be random.
3. No one can be chosen twice.
4. After finished this, try to cheat others in your program to make someone owned a higher probability of win.
5. Try to hide your cheat in your code so that no one will find it.

## Prerequisites

* Ubuntu or other 64 bits Unix-like system
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


## How

I may write a blog about it when I got free...