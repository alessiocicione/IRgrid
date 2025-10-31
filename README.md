# C++ Firmware and Hardware Prototyping for Low-Power IR Sensing (Smart City)

This repository provides the design for a micro-controller-based system:
1.  **C++ Firmware** (Source Code) for data acquisition.
2.  **Hardware Schematics** for the Infrared (IR) sensing circuit.

The project's primary goal is power consumption minimization and scalable integration into existing Smart City sensing networks.

---

## I. Hardware & I/O Expansion

The hardware design features the use of **Parallel-In, Serial-Out (PISO) Shift Registers** (e.g., CD4021B). This allows for reading the state of multiple digital inputs (e.g., from an IR sensor array) using only three micro-controller pins, optimizing I/O usage.

### Key Circuit Files

The `hardware/` directory contains the schematics of both sender and receiver.

### I/O Interface

Communication relies on standard synchronous serial protocol via three pins:

| Arduino Pin | Role |
| :--- | :--- |
| `latchPin` (Pin 8) | **Parallel Load:** Samples input data into the register. |
| `clockPin` (Pin 7) | **Clock (CLK):** Synchronizes the serial data shift. |
| `dataPin` (Pin 9) | **Serial Data Input:** The single line for reading data. |

---

## II. Firmware Overview (`.ino`)

The C++ firmware implements the synchronous serial communication protocol to retrieve data from the cascaded shift registers.

| Function | Purpose |
| :--- | :--- |
| **`setup()`** | Initializes serial port (9600 baud) and configures the I/O pins. |
| **`loop()`** | Executes the data acquisition cycle: latches parallel data, then calls `shiftIn()` to read the 8-bit registers. |
| **`shiftIn()`** | Custom logic for synchronous serial reading, acquiring data **MSB first**. |

---
