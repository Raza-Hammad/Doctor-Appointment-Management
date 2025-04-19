# 🏥 Hospital Management System (C++ Project)

This is a simple console-based Hospital Management System implemented in C++. The system is divided into three major modules:

1. **Appointment Management**
2. **Emergency Care**
3. **Surgery Scheduling**

Each module offers different functionalities to manage appointments, handle emergency patients using triage levels, and schedule surgeries in operating rooms.

---

## 🔧 Features

### 📅 Appointment Management
- Book an appointment with a doctor at a specific time slot.
- Update the status of an appointment (Pending / Completed).
- Cancel an existing appointment.
- View all appointments for a particular doctor.

### 🚨 Emergency Care
- Admit patients based on triage level (1 to 5).
- Automatically prioritize and treat the patient with the highest urgency (lowest triage number).
- Display all patients in order of triage.

### 🏥 Surgery Scheduling
- Schedule a surgery with a surgeon for a specified time and operating room.
- Prevent double-booking of operating rooms.
- View all scheduled surgeries for a particular operating room.

---

## 🗃️ Data Structures Used
- **Queue**: Used for managing doctor appointments.
- **Linked List**: Used for maintaining surgery schedules.
- **Binary Search Tree (BST)**: Used for prioritizing emergency patients based on triage level.

---

## 👨‍⚕️ Doctors and Surgeons
**Doctors:**
- Dr. Huzaifa
- Dr. Umer
- Dr. Fiza
- Dr. Ali

**Surgeons and Their Expertise:**
- Dr. Fiza – Cardiology
- Dr. Imran – Neurology
- Dr. Ali – Orthopedics
- Dr. Biggie – General Surgery

---

## ⏰ Time Slots
- 09:00 AM to 06:00 PM (1-hour intervals)

---

## 🛠️ How to Run

1. Compile the program using a C++ compiler:
   ```bash
   g++ -o hospital_system hospital_system.cpp
