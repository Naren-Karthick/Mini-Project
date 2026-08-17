# Hospital Patient Management System

A lightweight, console-based **Hospital Patient Management System** implemented in standard C. This project demonstrates core computer science fundamentals, including user-defined data types (`struct`), string manipulation, modular programming with functions, and persistent data storage using file I/O operations.

---

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Concepts Applied](#concepts-applied)
- [System Flowchart](#system-flowchart)
- [File Structure](#file-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation & Execution](#compilation--execution)
- [Data Storage Format](#data-storage-format)
- [Future Enhancements](#future-enhancements)
- [License](#license)

---

## Overview

The Hospital Patient Management System provides an automated solution for healthcare desks to manage in-patient records. It replaces manual ledger record-keeping by allowing staff to register patients, view all active admissions, search for individual records, update medical information, and automatically calculate discharge bills.

---

## Key Features

1. **Add Patient Record:** Captures patient ID, name, age, disease/condition, room number, admission duration, daily room rate, and medicine costs.
2. **Display All Patients:** Prints a formatted table listing all admitted patients.
3. **Search Patient:** Quickly fetches a complete patient summary using their unique Patient ID.
4. **Update Patient Info:** Modifies details for existing records while preserving the overall dataset using safe temporary file replacement.
5. **Automated Billing:** Calculates total payable fees based on room stay duration and added medicine/treatment charges.
6. **Data Persistence:** Automatically appends and updates records inside a persistent text file (`patients.txt`).

---

## Concepts Applied

- **Structures (`struct`):** Encapsulates multi-attribute patient records into a single custom type.
- **File Handling:** Implements file pointers (`FILE*`), stream modes (`"a"`, `"r"`, `"w"`), structured reads (`fscanf`), writes (`fprintf`), and file operations (`remove`, `rename`).
- **Control Structures & Loops:** Driven by a menu loop (`while (1)`) and conditional branch evaluation (`switch-case`).
- **Formatted I/O:** Utilizes format specifiers (e.g., `%-15s`, `%.2f`) for clean console reporting and structured file writing.

---

## File Structure

```text
├── main.c              # Core source code containing all functions and driver menu
├── patients.txt        # Auto-generated text file for persistent storage
└── README.md           # Project documentation
