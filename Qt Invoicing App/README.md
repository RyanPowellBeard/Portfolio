# OSI Invoicing Application

OSI Invoicing is a cross-platform desktop application for small-business invoicing and business management, developed using **C++ and Qt 6**.

The project began as a Java prototype used to explore application requirements and business workflows. It was subsequently rebuilt in C++ using Qt to create a native desktop application with local SQLite database management and a structured, maintainable architecture.

The application is designed to bring customer management, invoicing, payments, products and services, and business reporting together in one desktop environment.

## Project Overview

OSI Invoicing combines a graphical user interface with a local relational database to support everyday business accounting workflows.

The application uses a layered architecture that separates the user interface, database management, and data-access operations.

Development focuses on cross-platform compatibility, maintainable code, and practical business functionality.

## Built With

- **C++** — Primary application programming language.
- **Qt 6** — Cross-platform graphical user interface and application framework.
- **Qt Widgets** — Desktop interface components.
- **Qt SQL** — Database integration.
- **SQLite** — Local relational database.
- **CMake** — Cross-platform build configuration.
- **Qt Resource System** — Embedded application resources, icons, and assets.

## Key Capabilities

- Customer and contact management.
- Invoice creation and management.
- Product and service catalog.
- Payment tracking.
- Tax configuration.
- Company profile management.
- Dashboard and business reporting.
- CSV data preparation and import workflows.

## Cross-Platform Development

The current application version has been built and tested on:

- Windows 11
- macOS Sequoia
- Linux — Pop!_OS

The project uses Qt 6 and CMake to maintain a common codebase across supported desktop platforms.

## Project Structure

```text
Qt Invoicing App/
├── README.md
├── OSI-Invoicing/
│   ├── README.md
│   ├── CMakeLists.txt
│   └── Application source files
└── OSI-Screen-shots/
    ├── Windows 11/
    ├── macOS Sequoia/
    └── Linux - Pop! OS/
```

The application source code, technical documentation, and platform screenshots are organized separately to make the project easier to navigate.

## Building the Application

The project requires:

- A compatible C++ compiler.
- Qt 6.5 or newer, including Core, Widgets, and SQL.
- CMake 3.19 or newer.
- Qt SQLite database driver (`QSQLITE`).

For detailed setup and build instructions, see the [OSI-Invoicing README](OSI-Invoicing/README.md).

## Development Status

OSI Invoicing remains under active development. Component integration, feature refinement, and manual testing are ongoing.

Planned improvements include database encryption, automated testing, and evaluation of additional database options.

## Detailed Documentation

For application features, architecture, database design, screenshots, and build instructions, see:

**[OSI-Invoicing — Application Documentation](OSI-Invoicing/README.md)**

## License

Released under the **GNU Affero General Public License v3.0 (AGPL-3.0)**.

See the [LICENSE](OSI-Invoicing/LICENSE) file for complete license terms.
