//#include "LoanTypes.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <sstream>
//
//using namespace std;
//
//// Forward declarations
//void displayMenu();
//void viewAllApplications(const vector<LoanApplication>& apps);
//void viewApplicationDetails(const vector<LoanApplication>& apps);
//void approveRejectApplication(vector<LoanApplication>& apps);
//void generateMonthlyPlan();
//
//string getMonthName(int month)
//{
//    string months[] = { "January", "February", "March", "April", "May", "June",
//                      "July", "August", "September", "October", "November", "December" };
//    if (month >= 1 && month <= 12)
//        return months[month - 1];
//    return "Invalid";
//}
//
//// ===================== SAFE INPUT HELPERS =====================
//
//// Safe integer input (no additional libraries)
//int getSafeInt(const string& prompt, int minVal, int maxVal)
//{
//    string input;
//    int value;
//
//    while (true)
//    {
//        cout << prompt;
//        getline(cin, input);
//
//        bool valid = true;
//        if (input.empty()) valid = false;
//
//        // Check every character
//        for (char c : input)
//        {
//            if (c < '0' || c > '9')
//            {
//                valid = false;
//                break;
//            }
//        }
//
//        if (valid)
//        {
//            value = stoi(input);
//            if (value >= minVal && value <= maxVal)
//                return value;
//        }
//
//        cout << COLOR_RED << "Invalid input. Try again.\n" << COLOR_RESET;
//    }
//}
//
//// Safe non-empty string input
//string getSafeString(const string& prompt)
//{
//    string s;
//    while (true)
//    {
//        cout << prompt;
//        getline(cin, s);
//
//        if (!s.empty())
//            return s;
//
//        cout << COLOR_RED << "Input cannot be empty.\n" << COLOR_RESET;
//    }
//}
//
//
//// ===================== MAIN PROGRAM =====================
//
//int main()
//{
//    cout << COLOR_BOLD << COLOR_CYAN;
//    cout << "========================================================\n";
//    cout << "           LOAN APPLICATION LENDER INTERFACE            \n";
//    cout << "========================================================\n" << COLOR_RESET;
//
//    while (true)
//    {
//        displayMenu();
//
//        int choice = getSafeInt("\nEnter your choice: ", 1, 5);
//
//        if (choice == 1)
//        {
//            vector<LoanApplication> apps = loadAllApplications("applications.txt");
//            viewAllApplications(apps);
//        }
//        else if (choice == 2)
//        {
//            vector<LoanApplication> apps = loadAllApplications("applications.txt");
//            viewApplicationDetails(apps);
//        }
//        else if (choice == 3)
//        {
//            vector<LoanApplication> apps = loadAllApplications("applications.txt");
//            approveRejectApplication(apps);
//        }
//        else if (choice == 4)
//        {
//            generateMonthlyPlan();
//        }
//        else if (choice == 5)
//        {
//            cout << COLOR_YELLOW << "\nThank you for using the Lender Interface. Goodbye!\n" << COLOR_RESET;
//            break;
//        }
//    }
//
//    return 0;
//}
//
//
//// ===================== MENU =====================
//
//void displayMenu()
//{
//    cout << "\n" << COLOR_CYAN << "========== LENDER MENU ==========" << COLOR_RESET << "\n";
//    cout << "1. View All Applications\n";
//    cout << "2. View Application Details\n";
//    cout << "3. Approve/Reject Application\n";
//    cout << "4. Generate Monthly Payment Plan\n";
//    cout << "5. Exit\n";
//}
//
//
//// ===================== VIEW ALL =====================
//
//void viewAllApplications(const vector<LoanApplication>& apps)
//{
//    if (apps.empty())
//    {
//        cout << COLOR_YELLOW << "\nNo applications found.\n" << COLOR_RESET;
//        return;
//    }
//
//    cout << "\n" << COLOR_BOLD << COLOR_CYAN << "========== ALL APPLICATIONS ==========" << COLOR_RESET << "\n\n";
//    cout << left << setw(8) << "App ID"
//        << setw(20) << "Applicant Name"
//        << setw(15) << "CNIC"
//        << setw(15) << "Loan Type"
//        << setw(12) << "Status"
//        << "Date\n";
//    cout << string(90, '-') << "\n";
//
//    for (const auto& app : apps)
//    {
//        string statusColor = COLOR_YELLOW;
//        if (app.status == "Approved")
//            statusColor = COLOR_GREEN;
//        else if (app.status == "Rejected")
//            statusColor = COLOR_RED;
//
//        cout << left << setw(8) << app.applicationId
//            << setw(20) << app.applicantName
//            << setw(15) << app.cnic
//            << setw(15) << app.loanType
//            << statusColor << setw(12) << app.status << COLOR_RESET
//            << app.submissionDate << "\n";
//    }
//    cout << "\n";
//}
//
//
//// ===================== VIEW DETAILS =====================
//
//void viewApplicationDetails(const vector<LoanApplication>& apps)
//{
//    if (apps.empty())
//    {
//        cout << COLOR_YELLOW << "\nNo applications found.\n" << COLOR_RESET;
//        return;
//    }
//
//    string appId = getSafeString("\nEnter Application ID to view: ");
//
//    bool found = false;
//    for (const auto& app : apps)
//    {
//        if (app.applicationId == appId)
//        {
//            found = true;
//
//            cout << "\n" << COLOR_BOLD << COLOR_CYAN;
//            cout << "========================================================\n";
//            cout << "              APPLICATION DETAILS - ID: " << app.applicationId << "\n";
//            cout << "========================================================" << COLOR_RESET << "\n\n";
//
//            cout << COLOR_YELLOW << "PERSONAL INFORMATION:" << COLOR_RESET << "\n";
//            cout << "  Full Name:        " << app.applicantName << "\n";
//            cout << "  Father's Name:    " << app.fatherName << "\n";
//            cout << "  CNIC:             " << app.cnic << "\n";
//            cout << "  CNIC Expiry:      " << app.cnicExpiryDate << "\n";
//            cout << "  Gender:           " << app.gender << "\n";
//            cout << "  Marital Status:   " << app.maritalStatus << "\n";
//            cout << "  Dependents:       " << app.numDependents << "\n\n";
//
//            cout << COLOR_YELLOW << "CONTACT INFORMATION:" << COLOR_RESET << "\n";
//            cout << "  Address:          " << app.postalAddress << "\n";
//            cout << "  Phone:            " << app.contactNumber << "\n";
//            cout << "  Email:            " << app.email << "\n\n";
//
//            cout << COLOR_YELLOW << "FINANCIAL INFORMATION:" << COLOR_RESET << "\n";
//            cout << "  Employment:       " << app.employmentStatus << "\n";
//            cout << "  Annual Income:    PKR " << app.annualIncome << "\n";
//            cout << "  Avg Elec. Bill:   PKR " << app.avgElectricityBill << "\n";
//            cout << "  Current Bill:     PKR " << app.currentElectricityBill << "\n\n";
//
//            if (!app.existingLoans.empty())
//            {
//                cout << COLOR_YELLOW << "EXISTING LOANS (" << app.existingLoans.size() << "):" << COLOR_RESET << "\n";
//                for (size_t j = 0; j < app.existingLoans.size(); j++)
//                {
//                    cout << "  Loan " << (j + 1) << " - " << app.existingLoans[j].category
//                        << " (" << app.existingLoans[j].bankName << ")\n";
//                    cout << "    Active: " << app.existingLoans[j].isActive
//                        << " | Total: PKR " << app.existingLoans[j].totalAmount
//                        << " | Due: PKR " << app.existingLoans[j].amountDue << "\n";
//                }
//                cout << "\n";
//            }
//
//            cout << COLOR_YELLOW << "REFERENCES:" << COLOR_RESET << "\n";
//            cout << "  Referee 1: " << app.referee1.name << "\n";
//            cout << "    CNIC: " << app.referee1.cnic << " | Issue Date: " << app.referee1.cnicIssueDate << "\n";
//            cout << "    Phone: " << app.referee1.phoneNumber << " | Email: " << app.referee1.email << "\n";
//            cout << "  Referee 2: " << app.referee2.name << "\n";
//            cout << "    CNIC: " << app.referee2.cnic << " | Issue Date: " << app.referee2.cnicIssueDate << "\n";
//            cout << "    Phone: " << app.referee2.phoneNumber << " | Email: " << app.referee2.email << "\n\n";
//
//            cout << COLOR_YELLOW << "DOCUMENTS:" << COLOR_RESET << "\n";
//            cout << "  CNIC Front:       " << app.cnicFrontPath << "\n";
//            cout << "  CNIC Back:        " << app.cnicBackPath << "\n";
//            cout << "  Electricity Bill: " << app.electricityBillPath << "\n";
//            cout << "  Salary Slip:      " << app.salarySlipPath << "\n\n";
//
//            cout << COLOR_YELLOW << "LOAN DETAILS:" << COLOR_RESET << "\n";
//
//            if (app.loanType == "Home Loan")
//            {
//                cout << "  Type:             Home Loan\n";
//                cout << "  Area:             " << app.homeOption.area << "\n";
//                cout << "  Size:             " << app.homeOption.size << "\n";
//                cout << "  Price:            PKR " << app.homeOption.price << "\n";
//                cout << "  Down Payment:     PKR " << app.homeOption.downPayment << "\n";
//                cout << "  Installments:     " << app.homeOption.installments << " months\n";
//                cout << "  Monthly Payment:  PKR " << app.homeOption.monthlyInstallment << "\n";
//            }
//            else if (app.loanType == "Car Loan")
//            {
//                cout << "  Type:             Car Loan\n";
//                cout << "  Car:              " << app.carOption.make << " " << app.carOption.model << "\n";
//                cout << "  Engine:           " << app.carOption.engine << "cc\n";
//                cout << "  Condition:        " << app.carOption.used << "\n";
//                cout << "  Year:             " << app.carOption.manufacturingYear << "\n";
//                cout << "  Price:            PKR " << app.carOption.price << "\n";
//                cout << "  Down Payment:     PKR " << app.carOption.downPayment << "\n";
//                cout << "  Installments:     " << app.carOption.installments << " months\n";
//                cout << "  Monthly Payment:  PKR " << app.carOption.monthlyInstallment << "\n";
//            }
//            else if (app.loanType == "Scooter Loan")
//            {
//                cout << "  Type:             Scooter Loan\n";
//                cout << "  Scooter:          " << app.scooterOption.make << " " << app.scooterOption.model << "\n";
//                cout << "  Range:            " << app.scooterOption.distancePerCharge << " km\n";
//                cout << "  Charging Time:    " << app.scooterOption.chargingTime << " hours\n";
//                cout << "  Max Speed:        " << app.scooterOption.maxSpeed << " km/h\n";
//                cout << "  Price:            PKR " << app.scooterOption.price << "\n";
//                cout << "  Down Payment:     PKR " << app.scooterOption.downPayment << "\n";
//                cout << "  Installments:     " << app.scooterOption.installments << " months\n";
//                cout << "  Monthly Payment:  PKR " << app.scooterOption.monthlyInstallment << "\n";
//            }
//
//            string statusColor = COLOR_YELLOW;
//            if (app.status == "Approved")
//                statusColor = COLOR_GREEN;
//            else if (app.status == "Rejected")
//                statusColor = COLOR_RED;
//
//            cout << "\n  " << COLOR_BOLD << "Status:           "
//                << statusColor << app.status << COLOR_RESET << "\n";
//            cout << "  Submission Date:  " << app.submissionDate << "\n";
//
//            cout << "\n" << COLOR_BOLD << COLOR_CYAN;
//            cout << "========================================================\n" << COLOR_RESET;
//            break;
//        }
//    }
//
//    if (!found)
//    {
//        cout << COLOR_RED << "\nApplication ID not found.\n" << COLOR_RESET;
//    }
//}
//
//
//// ===================== APPROVE / REJECT =====================
//
//void approveRejectApplication(vector<LoanApplication>& apps)
//{
//    if (apps.empty())
//    {
//        cout << COLOR_YELLOW << "\nNo applications found.\n" << COLOR_RESET;
//        return;
//    }
//
//    string appId = getSafeString("\nEnter Application ID to approve/reject: ");
//
//    bool found = false;
//
//    for (size_t i = 0; i < apps.size(); i++)
//    {
//        if (apps[i].applicationId == appId)
//        {
//            found = true;
//
//            cout << "\nApplication: " << apps[i].applicantName << " - " << apps[i].loanType << "\n";
//            cout << "Current Status: " << apps[i].status << "\n\n";
//
//            cout << "1. Approve\n";
//            cout << "2. Reject\n";
//            cout << "3. Cancel\n";
//
//            int choice = getSafeInt("Enter choice: ", 1, 3);
//
//            if (choice == 1 || choice == 2)
//            {
//                ofstream file("applications.txt");
//                if (!file.is_open())
//                {
//                    cout << COLOR_RED << "Error: Could not update application.\n" << COLOR_RESET;
//                    return;
//                }
//                file.close();
//
//                for (size_t j = 0; j < apps.size(); j++)
//                {
//                    if (j == i)
//                        apps[j].status = (choice == 1 ? "Approved" : "Rejected");
//
//                    storeApplication(apps[j], "applications.txt");
//                }
//
//                if (choice == 1)
//                    cout << COLOR_GREEN << "\nApplication " << appId << " has been APPROVED.\n" << COLOR_RESET;
//                else
//                    cout << COLOR_RED << "\nApplication " << appId << " has been REJECTED.\n" << COLOR_RESET;
//            }
//            else
//            {
//                cout << COLOR_YELLOW << "\nOperation cancelled.\n" << COLOR_RESET;
//            }
//
//            break;
//        }
//    }
//
//    if (!found)
//    {
//        cout << COLOR_RED << "\nApplication ID not found.\n" << COLOR_RESET;
//    }
//}
//
//
//// ===================== MONTHLY PLAN =====================
//
//void generateMonthlyPlan()
//{
//    vector<LoanApplication> apps = loadAllApplications("applications.txt");
//
//    if (apps.empty())
//    {
//        cout << COLOR_YELLOW << "\nNo applications found.\n" << COLOR_RESET;
//        return;
//    }
//
//    string appId = getSafeString("\nEnter Application ID for monthly plan: ");
//
//    bool found = false;
//
//    for (const auto& app : apps)
//    {
//        if (app.applicationId == appId)
//        {
//            found = true;
//
//            if (app.status != "Approved")
//            {
//                cout << COLOR_RED << "\nThis application is not approved yet. Cannot generate plan.\n" << COLOR_RESET;
//                return;
//            }
//
//            int startMonth = getSafeInt("Enter starting month (1-12): ", 1, 12);
//
//            long long monthlyPayment = 0, totalAmount = 0;
//            int numInstallments = 0;
//
//            if (app.loanType == "Home Loan")
//            {
//                monthlyPayment = app.homeOption.monthlyInstallment;
//                totalAmount = app.homeOption.price - app.homeOption.downPayment;
//                numInstallments = app.homeOption.installments;
//            }
//            else if (app.loanType == "Car Loan")
//            {
//                monthlyPayment = app.carOption.monthlyInstallment;
//                totalAmount = app.carOption.price - app.carOption.downPayment;
//                numInstallments = app.carOption.installments;
//            }
//            else if (app.loanType == "Scooter Loan")
//            {
//                monthlyPayment = app.scooterOption.monthlyInstallment;
//                totalAmount = app.scooterOption.price - app.scooterOption.downPayment;
//                numInstallments = app.scooterOption.installments;
//            }
//
//            cout << "\n" << COLOR_BOLD << COLOR_CYAN;
//            cout << "========================================================\n";
//            cout << "         MONTHLY PAYMENT PLAN - APP ID: " << appId << "\n";
//            cout << "========================================================" << COLOR_RESET << "\n";
//
//            cout << "Applicant: " << app.applicantName << "\n";
//            cout << "Loan Type: " << app.loanType << "\n";
//            cout << "Total Loan: PKR " << totalAmount << "\n";
//            cout << "Monthly Payment: PKR " << monthlyPayment << "\n\n";
//
//            cout << left << setw(15) << "Month"
//                << right << setw(20) << "Payment Due"
//                << setw(20) << "Total Paid"
//                << setw(20) << "Remaining" << "\n";
//            cout << string(75, '-') << "\n";
//
//            long long totalPaid = 0;
//            int currentMonth = startMonth;
//
//            for (int j = 1; j <= numInstallments; j++)
//            {
//                long long payment = (j == numInstallments)
//                                    ? totalAmount - totalPaid
//                                    : monthlyPayment;
//
//                totalPaid += payment;
//                long long remaining = totalAmount - totalPaid;
//
//                cout << left << setw(15) << getMonthName(currentMonth)
//                    << right << setw(20) << payment
//                    << setw(20) << totalPaid
//                    << setw(20) << remaining << "\n";
//
//                currentMonth++;
//                if (currentMonth > 12)
//                    currentMonth = 1;
//            }
//
//            cout << "\n" << COLOR_BOLD << COLOR_CYAN;
//            cout << "========================================================\n" << COLOR_RESET;
//            break;
//        }
//    }
//
//    if (!found)
//    {
//        cout << COLOR_RED << "\nApplication ID not found.\n" << COLOR_RESET;
//    }
//}
