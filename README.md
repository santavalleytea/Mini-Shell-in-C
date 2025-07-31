# 🐚 myshell — A Minimal UNIX Shell in C

This is a custom mini-shell written in C, built as a systems programming project to explore core UNIX concepts like process control, input parsing, memory management, and command execution.

---

## 🚀 Features

- [x] Interactive shell prompt (`myshell>`)
- [x] Executes external commands (e.g. `ls`, `cat`, `gcc`)
- [x] Built-in commands:
  - `cd` — change directory
  - `pwd` — print current directory
  - `exit` — exit the shell
  - `history` — show previously entered commands
- [x] Line parsing with tokenization
- [x] Memory-safe input handling using `getline()` and `strdup()`
- [x] Clean memory management (Valgrind clean)
- [x] Output redirection: `command > file.txt`, `command >> file.txt`
- [x] Input redirection: `command < file.txt`
- [x] Piping: `command1 | command2` (e.g. `ls | grep .c`)

---

## 🧪 Sample Commands

```bash
myshell> pwd
/home/jason/projects/myshell

myshell> cd src
myshell> ls
main.c  parser.c  executor.c ...

myshell> echo Hello World
Hello World

myshell> echo first > out.txt
myshell> echo second >> out.txt
myshell> cat < out.txt
first
second

myshell> ls | grep .c
executor.c
main.c
parser.c

myshell> history
1 pwd
2 cd src
3 echo Hello World
...

myshell> exit
