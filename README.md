<a id="top"></a>

# Simple_C_Compiler


> Quick Links | 快速跳转
> [🇺🇸 English Document Click Here](#english) |  [🇨🇳 中文文档点击这里](#chinese)





<h1 id="english">🇺🇸 English Document</h1>


---

## 📋 Project Overview

### Objective:
This project aims to implement a C++ compiler. While studying compiler theory, the goal is to compile C++ programs into efficient x86 assembly language programs.

### Implementation Details:

- **1. Syntax Analysis:**
  - a. Utilizes the **Hyperlinked C++ BNF Grammar** (https://github.com/alx71hub/hcb).
  - b. Implements operator precedence handling using bottom-up parsing characteristics.
  - c. Implements **constant folding**.
  - d. Analyzes the layout of parameters and local variables within the stack frame during the parsing process.
  <br>
- **2. Symbol Table Management:**
  - a. Manages variable declarations using a `nametab` table.
  - b. Manages function declarations using a `btab` table.
  - c. Implements local variable declarations using a linking mechanism.
  <br>
- **3. Language Features:**
  - a. Implements a non-nested procedural language allowing for function calls and recursion (Implementation method: stack management and activation records). Function parameters are passed by value.
  - b. Adopts the **x86-32 (cdecl)** stack frame standard.
  <br>
- **4. Code Generation:**
  - a. Uses a temporary file method to delay the insertion of the prologue into the head of the code segment.
  <br>
- **5. Current Status:**
  - The project has progressed to calculation stack processing. Due to personal constraints, further development is currently halted. The current operational capabilities are:
    - a. Displays `nametab` and `btab`.
    - b. Generates assembly code, which includes:
      1. Prologue
      2. Pushing arguments onto the stack
      3. `call` to the corresponding function
      4. Stack cleanup after the `call`
      5. `return` handling (value saved to `eax`)

---

## ⚙️ Dependencies

| Dependency | Version |
|------|------|
| flex | 2.6.4 | 
| bison | 3.8.2 |

---

## 📁 Project Structure

```bash
WC++/
├── CHANGE.md                           # Project development log
├── LICENSE                             # License
├── README.md                           # Project documentation
├── emitter_tmpfile.h                   # Helper for delayed prologue insertion via temp files
├── lexer.c                             # Lexical Analysis (Source)
├── lexer.l                             # Lexical Analysis (Flex)
├── output.asm                          # Example output of x86 assembly
├── parser                              # Parser executable
├── parser.c                            # Syntax Analysis (Source)
├── parser.h                            # Syntax Analysis Header
├── parser.y                            # Syntax Analysis (Bison)
```

---

## 📜 LICENSE
This project is licensed under the [MIT License](LICENSE) open-source license.

```
MIT License

Copyright (c) 2025 kong-LrYz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```






[⬆ Back To Top](#top)


<h1 id="chinese">🇨🇳 中文文档</h1> 


---


## 📋 项目简介

### 功能：
本项目意在复现Cpp编译器，在学习编译原理的同时，也尽可能将Cpp程序编译成了高效的X86汇编语言程序。


### 实现了什么:

- **1. 语法分析方面:**
  - a. 使用的文法是 **Hyperlinked C++ BNF Grammar** (https://github.com/alx71hub/hcb)。
  - b. 利用了自底向上的特性实现了运算符优先级顺序的处理。
  - c. 实现了 **常量折叠**。
  - d. 在语法分析过程中，分析出了参数、局部变量在栈帧中的布局。
  <br>
- **2. 符号表管理方面:**
  - a. 利用`nametab`表实现了对变量声明的管理。
  - b. 利用`btab`表实现了对函数声明的管理。
  - c. 利用link的方式实现了局部变量的声明。
  <br>
- **3. 语言特性方面：**
  - a. 实现了非嵌套过程语言，允许函数调用以及函数递归（实现方法：栈式管理与活动记录），函数参数的传递方式是传值。
  - b. 栈帧采用**x86-32（cdecl）**栈帧标准。
  <br>
- **4. 代码段生成方面：**
  - a. 利用临时文件的方法，将prologue延迟插入到代码段头部。
  <br>
- **5. 当前情况:**
  - 目前进行到计算栈的处理，由于本人能力有限，不打算继续编写，目前运行的效果：
    - a. 显示`nametab`和`btab`。
    - b. 生成了汇编代码,包括：
      1. Prologue
      2. 参数压栈
      3. `call` 对应的函数
      4. `call`之后，参数栈的清理
      5. return的处理 (保存到`eax`中)



---


## ⚙️ 依赖版本说明

| 依赖名称 | 版本号 |
|------|------|
| flex | 2.6.4 | 
| bison | 3.8.2 |


---

## 📁 项目结构

```bash
WC++/
├── CHANGE.md                           # 本项目的开发日志
├── LICENSE                             # 协议
├── README.md                           # 本项目说明
├── emitter_tmpfile.h                   # 利用临时文件的方法，将prologue延迟插入到代码段头部
├── lexer.c                             # 词法分析
├── lexer.l                             # 词法分析
├── output.asm                          # 输出的x86汇编程序样例
├── parser                              # 解析器
├── parser.c                            # 语法分析
├── parser.h                            # 语法分析头文件
├── parser.y                            # 语法分析

```

---

## 📜 开源协议

本项目采用 [MIT License](LICENSE) 开源协议。
```
MIT License

Copyright (c) 2025 kong-LrYz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```


[⬆ 回到顶部](#top)