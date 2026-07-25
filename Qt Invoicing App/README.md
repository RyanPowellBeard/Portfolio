# OSI Invoicing Application

A modern, cross-platform  desktop application built with **Qt 6** and **C++** designed for managing client invoicing, records, database connections,
And business accounting workflows.

--- 

## 📸 Overview 

The OSI Invoicing App provides a clean graphical user interface (GUI) and robust database connectivity to manage invoicing pipelines efficiently. 
Built on CMake and leveraging modern Qt Qt Widgets / Core frameworks, it supports macOS, Linux, and Windows seamlessly.

 ---

## 🛠️ Built With 
* [Qt Framework](https://www.qt.io/) - Cross-platform GUI and Database modules (Used under LGPLv3). 
* [SQLite](https://www.sqlite.org/) - Server-less, zero-configuration database engine.

 ---

## 🛠️ Features 
* **Client & Customer Management:** Easily add, view, and store customer records. 
* **Database Integration:** Managed via custom `DatabaseManager` interfaces for secure and performant local/remote data storage. 
* **Custom Resource Management:** Uses Qt's Resource System (`.qrc`) for consolidated icon sets, asset management, and unified styling. 
* **Cross-Platform Support:** Fully dynamic CMake build configuration supporting cross-compilation across major platforms. 

---

## 🗂 Project Structure

**OSI-Invocing/
|—CMakeLists.txt		# Primary CMake build specifications
|—DatabaseManager.cpp	# SQLite/Database handling logic
|—DatabaseManager.h	# Header for DatabaseManager
|—contact_customer.cpp	# Customer/Client logic implementation 
|—contact_customer.h	# Header for contact_customer
|—resources.qrc		# Qt Resource file (icons, images, styles)
|___main.cpp			# Application entry point

--- 

## 📋 Prerequisites & Requirements 

Before building the project, ensure you have the following installed on your machine: 
 1. **C++ Compiler:** Supporting **C++17** or higher (Clang/GCC/MSVC). 
 2. **CMake:** Version **3.16** or higher. 
 3. **Qt Framework:** Version **Qt 6.x** (with `Qt6Widgets`, `Qt6Core`, and `Qt6Sql` installed). 

--- 

## 🚀 Building & Running 
### Using Qt Creator (Recommended) 
 1. Open **Qt Creator**. 
 2. Select **Open File or Project** and open `OSI-Invoicing/CMakeLists.txt`. 
 3. Choose your configured Qt 6 Kit (e.g., *Qt 6.11.1 for macOS*). 
 4. Click **Build** (`Cmd + B` / `Ctrl + B`) or **Run** (`Cmd + R` / `Ctrl + R`).

 --- 

### Using Command Line (CMake) 

1. Clone or navigate into the project directory: 
	```bash 
	cd "Qt Invoicing App/OSI-Invoicing"