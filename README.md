# 🛠️ Process-Hunter

A **Linux process information retriever** written in **C**.  
This program uses the Linux `/proc` filesystem to fetch detailed information about a running process by providing its Process ID (PID).

---

## ✨ Features
- **Process Name** – Fetches the name of the process.
- **Command-line Arguments** – Retrieves the arguments used to launch the process.
- **Process State** – Displays current state (Running, Sleeping, etc.).
- **Parent PID (PPID)** – Shows the parent process ID.
- **Memory Usage** – Displays the virtual memory size (`VmSize`).
- **Number of Threads** – Fetches number of threads used by the process.
- **UID & GID** – Displays user and group IDs of the process owner.
- **Executable Path** – Retrieves full path to the executable file.
- **Robust Error Handling** – Handles invalid PID input and missing files gracefully.

---

## 📂 Project Structure
```plaintext
Process-Hunter/
├── process_hunter.c   # Main C program
└── README.md          # Documentation

--- ## 🖥️ Example Output
Enter Process ID (PID): 1234

Fetching information for PID: 1234
---------------------------------------
Process Name      : bash
Command-line     : /bin/bash -c sleep 100
=== Status Info ===
State: S (sleeping)
PPid: 1000
Uid: 1000  1000  1000  1000
Gid: 1000  1000  1000  1000
Threads: 1
VmSize: 12456 kB
Executable Path  : /usr/bin/bash
---------------------------------------
Process information retrieved successfully.


git clone https://github.com/Dadipavan/Process-Hunter.git
cd Process-Hunter

