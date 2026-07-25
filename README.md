# Delveloper Portfolio & Technical Sanbox

Welcome to my personal project portfolio! This repository serves as a showcase of my work spanning low-level systems programming, full-stack
desktop application development, and interactive graphics programming.

---

## 🛠 Tech Stack Overview

* **Languages:** C, C++, Assembly (x86 / NASM)
* **Frameworks & Graphics:** Qt Framework, OpenGL, CMake
* **Databases:** SQLite / Custom Application Database Layer
* **Tools & Build Systems:** Make, CMake, QMake, Xcode / Clang, QEMU

---
## 📂 Featured Projects

### 1. 🖥️ Low-Level x86 Assembly Bootloader
> **Directory:** [`/ASM`](./ASM)

A bare-metal low-level programming exploration focused on system boot sequences and x86 Assembly.

* **Highlights:**
  * Custom 16-bit real mode bootloader written in x86 Assembly (`NASM`).
  * Demonstrates a multi-stage loading architecture (`first_stage.asm`, `second_stage.asm`).
  * Features a classic "Hello World" kernel environment runnable via emulator (e.g., QEMU or VirtualBox) as raw binary blobs (`.bin`).

---

### 2. 🧾 Qt Invoicing Desktop Application
> **Directory:** [`/Qt Invoicing App`](./Qt%20Invoicing%20App)

A full-featured, cross-platform desktop management application built with Modern C++ and the Qt Framework. Currently in active development, utilizing Git and GitHub workflows—including feature branching, pull requests, and commit discipline—to demonstrate professional version control practices.

* **Highlights:**
  * Built using **Qt 6** and compiled via **CMake** for modern macOS / cross-platform compatibility.
  * Managed via Git & GitHub using structured version control, feature branching, and organized release management
  * Robust database architecture managed through a dedicated `DatabaseManager` C++ class.
  * Designed to manage client contacts, customer profiles, and streamline business invoice generation.

---

### 3. 🌐 OpenGL C++ 3D Sphere Renderer
> **Directory:** [`/OpenGL with C-C++`](./OpenGL%20with%20C-C%2B%2B)

An interactive computer graphics project demonstrating modern 3D rendering pipeline principles in C++.

* **Highlights:**
  * Procedural 3D geometry generation (calculating sphere vertices, normals, and texture coordinates).
  * OpenGL shader pipeline integration for real-time lighting and rendering.
  * Native C++ implementation targeting optimized graphics rendering performance.

---

## 🚀 Getting Started & Building

### Prerequisites
* **Assembly:** `nasm` assembler and `qemu-system-x86_64` (for running assembly bootloaders).
* **Qt App:** `Qt 6.x` SDK, `CMake 3.20+`, and a C++17 compatible compiler (`clang++` or `g++`).
* **OpenGL Project:** OpenGL development libraries, `GLFW` / `GLUT` (depending on platform headers), and `make` / `g++`.

### Example: Running the Assembly Bootloader
```bash
cd ASM
nasm -f bin bootloader-hello.asm -o bootloader-hello.bin
qemu-system-x86_64 -drive format=raw,file=bootloader-hello.bin
