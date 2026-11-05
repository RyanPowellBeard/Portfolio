# Ryan Powell — Software & Systems Portfolio

Software developer with a long electronics, systems, and field-infrastructure background. I work in C/C++, Python, Java, and SQL, and I like projects where software meets hardware or a real business workflow.

- **Location:** Worland, WY — open to remote work and relocation to Colorado
- **Security clearance:** reinstatable (Secret / Confidential)
- **Education:** B.S. in Computer Science, Colorado State University — currently enrolled (between classes), four courses remaining. B.S. in Electronic Engineering, DeVry University — three courses remaining, on hold until the CSU degree is complete. Neither degree has been awarded yet.
- **Contact:** RPowellB@protonmail.com · [LinkedIn](https://www.linkedin.com/in/ryan-powell-beard-aba7bb2a3/)

---

## Projects in this repository

### OSI — Invoicing & Business Management (C++ / Qt 6)
[`Qt Invoicing App/OSI-Invoicing`](Qt%20Invoicing%20App/OSI-Invoicing)

A cross-platform desktop application for customers, invoices, items and services, payments, tax settings, and reporting. Screenshots from Windows 11, macOS Sequoia, and Pop!_OS are in [`OSI-Screen-shots`](Qt%20Invoicing%20App/OSI-Screen-shots).

- Qt 6, CMake, Qt SQL, SQLite
- A `DatabaseManager` owns database setup, the schema, foreign-key enforcement, and connections
- Data Access Objects (DAOs), each constructed with a reference to the `DatabaseManager`, contain the SQL; the UI windows go through the DAOs
- Dashboard, A/R summary, sales reports, and CSV import with column matching
- **Status:** component integration and manual testing are in progress. Encryption, automated tests, and additional database options are planned and are **not** complete.
- Licensed AGPL-3.0

### OSI — Java prototype (being added)
The original Java version of OSI, built to explore requirements and workflows before the C++/Qt rebuild.

### x86 Assembly Bootloaders
[`ASM`](ASM)

NASM bootloaders for BIOS real mode: boot-sector text output (INT 0x10), a two-stage loader that reads the second stage from disk (INT 0x13) with error handling, and an interactive input example. Tested in QEMU.

### OpenGL Sphere
[`OpenGL with C-C++/Sphere`](OpenGL%20with%20C-C%2B%2B/Sphere)

A C++ / GLFW / GLEW program that builds a sphere from triangles and rotates it in real time with depth testing and viewport resizing. It uses the legacy fixed-function (`glBegin`) pipeline.

### Academic Projects
[`School Projects`](School%20Projects)

Coursework in C++ and Java: data structures and sorting, multithreading with mutexes, and Java concurrency. See the [Academic README](School%20Projects/Academic%20README.md).

---

## Work not shown here

- **Wireless animal-tracking R&D (Zigbee, Embedded Python, C):** I was one of two people on this project. It is covered by an NDA, so no code or details are published.
- **Electronics and systems work** at Signs of Sutherland (board-level troubleshooting, digital signage, CNC, IT) and earlier infrastructure and test-range roles. These are described on my resume rather than in code.

---

## Skills

| Area | Tools and languages |
| :--- | :--- |
| Languages | C/C++, Python (incl. 2.7 / 3.5 and embedded), Java, SQL; exposure to C#, VHDL, HTML, Assembly |
| Application development | Qt 6, Java Swing, CMake, desktop application architecture |
| Databases | SQLite, MySQL, Data Access Object pattern, prepared queries |
| Tools | Git/GitHub (branching and merge-conflict workflow), Linux/Unix shell |
| Hardware | Multimeters, oscilloscopes, soldering, device programmers, PCB/PCA diagnostics, FPGA interfacing, microcontrollers |
