# ft_ls

My own implementation of a ~~infamous~~ famous ```ls``` UNIX utility, which lists files and their respective directories.

---

## Installation

To get the executable `ft_ls`, simply run ```make```

---

## Usage

```
usage: ./ft_ls [-AGRadefgilprstu1@] [file ...]
```

Program's behaviour is almost identical to `md5`, only lacking some of the flags.
And, I gotta say, original ```ls``` does have some juicy fucntionality hidden up its sleeve, so

```
man ls
```

---

## Features

In order to get an optimal time while recursively sorting directories and files in them  
I implemented `quicksort`, which was a bit of a tricky part given different parameters  
of sorting are possible.

Besides, I've done a locale switch when printing time in `-l` mode  
by reading environment variable. Very simple, but fancy😏

Yep, there's also pretty neat moment of printing `block` & `char` devices  
For instance, when you launch ```./ft_ls -laG /dev```, you get interesting stuff going on  
with some of the files marked with `c` or `b`. To learn more about it, I recommend googling  

```
char and block devices unix
```

---

## So, guys, I hope you will find this project useful and, in case any questions occur, feel free to connect with me by any of the emails listed below

- [Artemkupriyanets@yahoo.com](https://www.yahoo.com)  
- [mr.tyomka.97@gmail.com](https://www.gmail.com)  

## Thanks for attention:kissing_heart:
