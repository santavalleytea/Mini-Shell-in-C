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
- [x] Line parsing with tokenization
- [x] Memory-safe input handling using `getline()` and `strdup()`
- [x] Clean memory management (Valgrind clean)

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

myshell> exit
