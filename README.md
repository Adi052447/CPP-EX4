# CPP-EX4

# 🧮 MyContainer Project

## 📌 Overview
This project implements a generic templated container class in C++ called `MyContainer`, which supports insertion, deletion, and multiple custom iteration strategies. It is built for academic purposes to demonstrate the use of iterators, operator overloading, and memory-safe design in modern C++.

## 🧰 Features

- ✅ **Generic container** with support for any data type (`int`, `string`, etc.)
- ➕ Add and remove elements
- 🔁 **Custom iterators**:
  - `AscendingOrder`: from smallest to largest
  - `DescendingOrder`: from largest to smallest
  - `SideCrossOrder`: zigzag pattern from edges inward
  - `MiddleOutOrder`: starts from the middle and expands outward
  - `ReverseOrder`: simple reverse of insertion order
- 📜 Clean and safe code (Rule of 3)
- 🧪 Unit testing with `doctest`
- 🧠 Written in modern C++17 with focus on clarity and modularity

## 📂 File Structure

```
.
├── MyContainer.hpp       # The main templated container class and iterators
├── main.cpp              # Demo of the container usage
├── tests.cpp             # Doctest unit tests for all iterators and methods
├── Makefile              # Build and test automation
└── README.md             # This documentation file
```

## 🧪 How to Run

### 🛠️ Build
To compile the main file:

```bash
make
```

To compile and run tests:

```bash
make test
```

### 🧹 Clean Build Files

```bash
make clean
```

### 🧼 Run Valgrind (memory leak checker)

```bash
make valgrind
```


```

