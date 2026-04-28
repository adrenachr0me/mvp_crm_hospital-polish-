# Przychodnia - Clinic CRM System

## Overview
A console-based Customer Relationship Management (CRM) system for a medical clinic, written in C. This project was developed as a university coursework to demonstrate practical skills in procedural programming, manual memory management, and implementing dynamic data structures from scratch.

## Key Features
- **Doctor & Patient Management:** Complete CRUD (Create, Read, Update, Delete) operations for medical staff and patients.
- **Appointments System:** Scheduling, rescheduling, canceling, and advanced filtering of appointments (by date, status, specific doctor, or patient).
- **Advanced Sorting:** Multi-level, bidirectional sorting of records (by ID, Name, Surname, PESEL, Specialization, etc.) using custom comparators and the standard `qsort` function.
- **Data Persistence:** Automatic loading and saving of the clinic's database state using local text files.
- **Modular Architecture:** The codebase is strictly divided into isolated logical modules (doctors, patients, appointments, file management) to ensure code readability and maintainability.

## Technical Details
- **Language:** C (C11 Standard)
- **Core Data Structures:** Custom Singly Linked Lists
- **Build System:** CMake / GCC

## Compilation and Execution
To compile the project using GCC from the command line, run:

```bash
gcc main.c lekarz.c pacjent.c wizyta.c file_man.c -o przychodnia

To start the application:
./przychodnia
```
## Note: Ensure that the initial data files (lekarze.txt, pacjenci.txt, wizyty.txt) are located in the same working directory as the compiled executable before running the program.
