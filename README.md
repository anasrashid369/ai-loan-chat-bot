# ai-loan-chat-bot
A chatbot-based loan processing system with lender approval, multi-session applications, and AI conversation support developed for the ISE course
📌 Project Overview

This project was developed in three increments as part of the ISE course.
It simulates a real-world loan processing system where:

Borrowers interact with a chatbot

Lenders use a separate management program

All data is stored in text files

Applications can be saved, resumed, approved, or rejected

🧩 System Architecture
Borrower  →  Chatbot Program  →  applications.txt  →  Lender Program
                               data/xxxx/ (images)


Chatbot Interface → Used by loan applicants

Lender Interface → Used by bank staff

File-based database → applications.txt, Utterances.txt, etc

🗂 Folder Structure
📁 Project
 ├── chatbot.py
 ├── lender.py
 ├── applications.txt
 ├── Utterances.txt
 ├── Home.txt
 ├── Car.txt
 ├── Scooter.txt
 ├── Personal.txt
 ├── human_chat_corpus.txt
 └── 📁 data
       └── 📁 1234
            ├── cnic_front.jpg
            ├── cnic_back.jpg
            ├── bill.jpg
            └── salary.jpg

🚀 Increment 1 — Loan Inquiry & Installment Calculation 

ISE Project - Increment 1

Features

Rule-based chatbot using Utterances.txt

Loan categories:

Home

Car

Electric Bike

Reads data from:

Home.txt

Car.txt

Scooter.txt

Calculates monthly installment using:

Monthly Installment = (Price - Down Payment) / Number of Installments


Generates full installment plans

🧾 Increment 2 — Loan Application System 

ISE Project - Increment 2

Applicant Data Collection

The chatbot collects:

Personal Information

Name, Father’s Name

Address, Phone, Email

CNIC & Expiry

Gender, Marital Status, Dependents

Employment Status

Financial Information

Annual Income

Electricity Bills

Existing Loans

References (2)

Names, CNICs, Phones, Emails

Documents

CNIC Front

CNIC Back

Electricity Bill

Salary Slip / Bank Statement

Storage

Each application gets a unique 4-digit ID

Images stored in:

./data/xxxx/


Data saved in:

applications.txt

Additional Features

User confirms submission

Users can check:

Submitted

Approved

Rejected applications (by CNIC)

Approved users get month-wise payment plan

Separate Lender Program:

View applications

Approve / Reject

🧠 Increment 3 — Resume Applications + AI Chatbot 

ISE Project - Increment 3

Multi-Session Application Support

Applications are divided into 4 checkpoints:

Personal Information

Financial Information

References

Documents

Status saved in applications.txt:

C1, C2, C3

Submitted

Users can:

Leave mid-way

Resume using:

Application ID + CNIC


Completed applications cannot be edited.

🧠 AI Conversation Mode

The chatbot now supports general conversation using:

human_chat_corpus.txt


It uses Intersection over Union (IoU) to match responses:

IoU = |Common Tokens| / |Total Unique Tokens|


The response of the highest IoU match is selected.

👨‍💼 Lender Program (Parallel System)

The lender can:

View all applications

Open specific applications

Approve or reject applications

Change status inside applications.txt

This is a menu-based program, not a chatbot.

🧪 Validation

The system validates:

CNIC format

Dates (DD-MM-YYYY)

Numeric values

Missing inputs

Invalid choices

Image paths

🗃 Data Files Used
File	Purpose
Utterances.txt	Chatbot Q&A
Home.txt	Home loan data
Car.txt	Car loan data
Scooter.txt	Electric bike loans
Personal.txt	Personal loan data
human_chat_corpus.txt	AI conversation
applications.txt	All applications
📅 Sprint Schedule
Increment	Sprint End	Demo
Increment 1	Nov 12, 2025	Nov 13
Increment 2	Nov 19, 2025	Nov 20
Increment 3	Nov 26, 2025	Nov 27
📊 Effort Tracking

Each team member recorded:

Estimated hours

Actual hours
in a Google Sheet for every task.

These values are used for planning and grading.

📌 Submission Checklist

✔ Code uploaded on GitHub
✔ Jira updated
✔ Google Sheet completed
✔ Demo ready

🏁 Final Note

This project demonstrates:

Chatbot engineering

File-based databases

State management

Validation

AI similarity matching

Real-world loan workflow
