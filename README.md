# 🏥 Hospital Management System

A console-based Hospital Management System written in **C**. It helps manage patient records, appointments, and billing, with data saved to files so nothing is lost when the program closes.

## Features

- **Patient Records** – add, view, search, update, and delete patient information
- **Appointment Booking** – schedule and view appointments
- **Billing** – generate and view patient bills
- **File Handling** – all data is stored in files for persistent storage

## Tech Stack

- Language: C
- Interface: Console / Terminal
- Storage: File handling (`fopen`, `fread`, `fwrite`, etc.)

## Getting Started

### Prerequisites

- A C compiler such as [GCC](https://gcc.gnu.org/) (MinGW on Windows)

### Clone the repository

```bash
git clone https://github.com/azmain-abrar/Hospital-Management-System.git
cd Hospital-Management-System
```

### Compile

```bash
gcc 1.c -o hospital
```

### Run

```bash
# Linux / macOS
./hospital

# Windows
hospital.exe
```

## Project Structure

```
Hospital-Management-System/
├── 1.c          # Main source code
└── README.md    # Project documentation
```

## Usage

1. Run the program.
2. Choose an option from the main menu.
3. Follow the on-screen prompts to manage patients, appointments, and bills.

## Future Improvements

- Doctor and staff management
- Login / authentication system
- Better input validation
- Splitting the code into multiple files and functions

## Author

**Mohammod Azmain Abrar**
B.Sc. in CSE, International Islamic University Chittagong (IIUC)

- Email: azmainaabrar@gmail.com
- LinkedIn: [azmain-abrar](https://www.linkedin.com/in/azmain-abrar-90a21a32a/)
- Portfolio: [azmainabrar1410.netlify.app](https://azmainabrar1410.netlify.app/)
