# OSI — Invoicing & Business Management

OSI Invoicing is a cross-platform desktop application for small-business invoicing and business management, developed using C++ and Qt 6.

The project began as a Java prototype used to explore application requirements and business workflows. It was subsequently rebuilt in C++ using Qt to create a native desktop application with structured architecture, local database management, and cross-platform support.

The application provides tools for managing customers, invoices, products and services, payments, tax settings, company information, and business reporting.

## Screenshots

Screenshots of the application running on Windows 11, macOS Sequoia, and Linux (Pop!_OS) are maintained in the repository's `OSI-Screen-shots` directory.

### Application Dashboard — Linux (Pop!_OS)

The dashboard provides an overview of business activity, including billing and collections, recent transactions, open invoices, overdue balances, and recent payments.

![OSI Invoicing Dashboard](../OSI-Screen-shots/Linux%20-%20Pop!%20OS/Dashboard.png)

### CSV Preparation Utility

The companion CSV preparation utility helps organize and prepare accounting data for import. Its interface includes column matching, suggested field completion, invoice matching, configurable delimiters, and CSV export.

![CSV Preparation Utility](../OSI-Screen-shots/Linux%20-%20Pop!%20OS/csv-prep.png)

## Features

- **Customer Management** — Add, edit, search, and browse customer records.
- **Invoice Management** — Create and manage invoices with line items, per-line tax, discounts, due dates, purchase order information, and notes.
- **Products and Services** — Maintain a reusable catalog of products and services for invoicing.
- **Payment Management** — Record payments against invoices and track outstanding balances.
- **Tax Settings** — Configure user-defined tax rates and activate or deactivate tax settings.
- **Company Profile** — Maintain business information and application preferences.
- **Dashboard** — Review billing, collections, outstanding balances, recent transactions, open invoices, and past-due invoices.
- **Business Reports** — Review accounts receivable, sales by item, sales by customer, and sales-tax information.
- **CSV Import Support** — Read and prepare CSV data using delimiter detection, encoding handling, column matching, and import-mapping components.

## Development Background

OSI Invoicing evolved from an initial Java prototype into a C++/Qt desktop application.

The original prototype helped establish requirements and explore the workflows needed for a small-business invoicing system. The subsequent rebuild focused on developing a native desktop application with a more organized database architecture and a maintainable separation between the interface and persistence layers.

This progression provided an opportunity to translate an initial application concept into a more comprehensive software project.

## Architecture

The application uses a layered architecture that separates the user interface, database access, and data persistence.

### Database Management

`DatabaseManager` handles SQLite initialization, schema creation, and database connections.

Key responsibilities include:

- Creating the database in the platform-specific application data directory.
- Initializing the database schema.
- Enabling SQLite foreign-key enforcement.
- Enabling Write-Ahead Logging (WAL).
- Managing database connections, including separate connections for worker threads.

### Data Access Layer

Data Access Objects (`DAO_*`) organize database operations by functional area.

These components handle operations for customers, invoices, items, payments, tax settings, company information, dashboard data, and reports.

Prepared SQL statements and bound parameters are used for database operations.

### User Interface

The application uses Qt Widgets, windows, and dialogs to provide its desktop interface.

Database operations are handled through the DAO layer rather than placing SQL directly in interface components.

This separation provides a more maintainable structure and a foundation for extending application functionality.

## Technology Stack

| Component | Technology |
|---|---|
| Programming Language | C++ |
| User Interface | Qt 6 Widgets |
| Database | SQLite |
| Database Integration | Qt SQL |
| Build System | CMake |
| Qt Requirement | Qt 6.5 or newer |
| CMake Requirement | CMake 3.19 or newer |

## Requirements

To build the application, you will need:

- A compatible C++ compiler.
- Qt 6.5 or newer.
- Qt Core, Widgets, and SQL modules.
- Qt SQLite database driver (`QSQLITE`).
- CMake 3.19 or newer.
- A compatible build tool, such as Ninja or Make.

## Building

Clone the repository and navigate to the application directory:

```bash
cd "Qt Invoicing App/OSI-Invoicing"
```

Configure the project with CMake:

```bash
cmake -S . -B build
```

Build the application:

```bash
cmake --build build
```

If CMake cannot locate your Qt installation, provide the Qt installation prefix:

```bash
cmake -S . -B build \
  -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x.x/gcc_64"

cmake --build build
```

Replace the example path with the location of your installed Qt kit.

Alternatively, open `CMakeLists.txt` in Qt Creator and configure and build the project using an installed Qt kit.

The application executable target is:

```text
OSI-NewMainWindow
```

The exact executable location depends on the selected platform and build configuration.

## Database and Data Storage

OSI Invoicing uses SQLite for local data persistence.

The database file is named:

```text
OSIinvoices.db
```

It is created automatically when the application initializes its database for the first time.

The database is stored in Qt's platform-specific application data directory rather than the source-code or build directory.

## Platforms

The current application version has been built and tested on:

- Windows 11
- macOS Sequoia
- Linux — Pop!_OS

The use of C++, Qt 6, and CMake provides a cross-platform foundation for development and deployment.

## Development Status and Roadmap

OSI Invoicing remains under active development. Component integration, feature refinement, and manual testing are ongoing.

Planned or under evaluation:

- Database encryption.
- Automated testing.
- Additional database options.
- Continued refinement of data import and validation workflows.

These items are planned improvements and are not represented as completed features.

## License

Released under the **GNU Affero General Public License v3.0 (AGPL-3.0)**.

See the [LICENSE](LICENSE) file for complete license terms.
