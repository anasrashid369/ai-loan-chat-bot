#include "Display.h"
#include "LoanTypes.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ============================================
// DISPLAY FUNCTIONS
// ============================================

void printInstallmentPlan(const HomeLoanOption& option)
{
    cout << fixed << setprecision(0);

    cout << "\n" << COLOR_BOLD << COLOR_CYAN;
    cout << "========================================================\n";
    cout << "               HOME LOAN DETAILS AND PAYMENT INFO       \n";
    cout << "========================================================" << COLOR_RESET << "\n";

    cout << COLOR_GREEN << "   Loan Type: " << COLOR_RESET << "Home Loan ("
        << option.area << ", " << option.size << ")\n";
    cout << COLOR_GREEN << "   Status:    " << COLOR_RESET << "Pending Initial Approval\n";
    cout << "--------------------------------------------------------\n";

    cout << COLOR_YELLOW << "   Price (PKR):        " << COLOR_RESET << setw(15) << option.price << "\n";
    cout << COLOR_YELLOW << "   Down Payment (PKR): " << COLOR_RESET << setw(15) << option.downPayment << "\n";
    cout << COLOR_CYAN << "   Loan Amount (PKR):  " << COLOR_RESET << setw(15) << (option.price - option.downPayment) << "\n";
    cout << "--------------------------------------------------------\n";

    cout << COLOR_GREEN << "   Installments:       " << COLOR_RESET << setw(15) << option.installments << " months\n";
    cout << COLOR_BOLD << COLOR_GREEN << "   MONTHLY INSTALLMENT: PKR " << COLOR_RESET << setw(15) << option.monthlyInstallment << "\n";

    cout << COLOR_BOLD << COLOR_CYAN << "========================================================\n" << COLOR_RESET << "\n";

    cout << defaultfloat;
}

void printCarInstallmentPlan(const CarLoanOption& option)
{
    cout << fixed << setprecision(0);

    cout << "\n" << COLOR_BOLD << COLOR_CYAN;
    cout << "========================================================\n";
    cout << "               CAR LOAN DETAILS AND PAYMENT INFO        \n";
    cout << "========================================================" << COLOR_RESET << "\n";

    cout << COLOR_GREEN << "   Loan Type: " << COLOR_RESET << "Car Loan ("
        << option.make << " " << option.model << ")\n";
    cout << COLOR_GREEN << "   Engine:    " << COLOR_RESET << option.engine << "cc\n";
    cout << COLOR_GREEN << "   Condition:" << COLOR_RESET << option.used << "\n";
    cout << COLOR_GREEN << "   Year:      " << COLOR_RESET << option.manufacturingYear << "\n";
    cout << COLOR_GREEN << "   Status:    " << COLOR_RESET << "Pending Initial Approval\n";
    cout << "--------------------------------------------------------\n";

    cout << COLOR_YELLOW << "   Price (PKR):        " << COLOR_RESET << setw(15) << option.price << "\n";
    cout << COLOR_YELLOW << "   Down Payment (PKR): " << COLOR_RESET << setw(15) << option.downPayment << "\n";
    cout << COLOR_CYAN << "   Loan Amount (PKR):  " << COLOR_RESET << setw(15) << (option.price - option.downPayment) << "\n";
    cout << "--------------------------------------------------------\n";

    cout << COLOR_GREEN << "   Installments:       " << COLOR_RESET << setw(15) << option.installments << " months\n";
    cout << COLOR_BOLD << COLOR_GREEN << "   MONTHLY INSTALLMENT: PKR " << COLOR_RESET << setw(15) << option.monthlyInstallment << "\n";

    cout << COLOR_BOLD << COLOR_CYAN << "========================================================\n" << COLOR_RESET << "\n";

    cout << defaultfloat;
}

void printScooterInstallmentPlan(const ScooterLoanOption& option)
{
    cout << fixed << setprecision(0);

    cout << "\n" << COLOR_BOLD << COLOR_CYAN;
    cout << "========================================================\n";
    cout << "             SCOOTER LOAN DETAILS AND PAYMENT INFO      \n";
    cout << "========================================================" << COLOR_RESET << "\n";

    cout << COLOR_GREEN << "   Loan Type: " << COLOR_RESET << "Scooter Loan ("
        << option.make << " " << option.model << ")\n";
    cout << COLOR_GREEN << "   Range:     " << COLOR_RESET << option.distancePerCharge << " km per charge\n";
    cout << COLOR_GREEN << "   Charge Time:" << COLOR_RESET << option.chargingTime << " hours\n";
    cout << COLOR_GREEN << "   Max Speed: " << COLOR_RESET << option.maxSpeed << " km/h\n";
    cout << COLOR_GREEN << "   Status:    " << COLOR_RESET << "Pending Initial Approval\n";
    cout << "--------------------------------------------------------\n";

    cout << COLOR_YELLOW << "   Price (PKR):        " << COLOR_RESET << setw(15) << option.price << "\n";
    cout << COLOR_YELLOW << "   Down Payment (PKR): " << COLOR_RESET << setw(15) << option.downPayment << "\n";
    cout << COLOR_CYAN << "   Loan Amount (PKR):  " << COLOR_RESET << setw(15) << (option.price - option.downPayment) << "\n";
    cout << "--------------------------------------------------------\n";

    cout << COLOR_GREEN << "   Installments:       " << COLOR_RESET << setw(15) << option.installments << " months\n";
    cout << COLOR_BOLD << COLOR_GREEN << "   MONTHLY INSTALLMENT: PKR " << COLOR_RESET << setw(15) << option.monthlyInstallment << "\n";

    cout << COLOR_BOLD << COLOR_CYAN << "========================================================\n" << COLOR_RESET << "\n";

    cout << defaultfloat;
}

void displayApplicationSummary(const LoanApplication& app)
{
    cout << "\n" << COLOR_BOLD << COLOR_CYAN;
    cout << "========================================================\n";
    cout << "            APPLICATION SUMMARY - REVIEW DETAILS        \n";
    cout << "========================================================" << COLOR_RESET << "\n\n";

    cout << COLOR_YELLOW << "PERSONAL INFORMATION:" << COLOR_RESET << "\n";
    cout << "  Full Name:        " << app.applicantName << "\n";
    cout << "  Father's Name:    " << app.fatherName << "\n";
    cout << "  CNIC:             " << app.cnic << "\n";
    cout << "  CNIC Expiry:      " << app.cnicExpiryDate << "\n";
    cout << "  Gender:           " << app.gender << "\n";
    cout << "  Marital Status:   " << app.maritalStatus << "\n";
    cout << "  Dependents:       " << app.numDependents << "\n\n";

    cout << COLOR_YELLOW << "CONTACT INFORMATION:" << COLOR_RESET << "\n";
    cout << "  Address:          " << app.postalAddress << "\n";
    cout << "  Phone:            " << app.contactNumber << "\n";
    cout << "  Email:            " << app.email << "\n\n";

    cout << COLOR_YELLOW << "FINANCIAL INFORMATION:" << COLOR_RESET << "\n";
    cout << "  Employment:       " << app.employmentStatus << "\n";
    cout << "  Annual Income:    PKR " << app.annualIncome << "\n";
    cout << "  Avg Elec. Bill:   PKR " << app.avgElectricityBill << "\n";
    cout << "  Current Bill:     PKR " << app.currentElectricityBill << "\n\n";

    if (app.existingLoans.size() > 0)
    {
        cout << COLOR_YELLOW << "EXISTING LOANS (" << app.existingLoans.size() << "):" << COLOR_RESET << "\n";
        for (size_t i = 0; i < app.existingLoans.size(); i++)
        {
            cout << "  Loan " << (i + 1) << " - " << app.existingLoans[i].category << " ("
                << app.existingLoans[i].bankName << ")\n";
            cout << "    Active: " << app.existingLoans[i].isActive
                << " | Total: PKR " << app.existingLoans[i].totalAmount
                << " | Due: PKR " << app.existingLoans[i].amountDue << "\n";
        }
        cout << "\n";
    }

    cout << COLOR_YELLOW << "REFERENCES:" << COLOR_RESET << "\n";
    cout << "  Referee 1: " << app.referee1.name << " (CNIC: " << app.referee1.cnic << ")\n";
    cout << "  Referee 2: " << app.referee2.name << " (CNIC: " << app.referee2.cnic << ")\n\n";

    cout << COLOR_YELLOW << "DOCUMENTS:" << COLOR_RESET << "\n";
    cout << "  CNIC Front:       " << app.cnicFrontPath << "\n";
    cout << "  CNIC Back:        " << app.cnicBackPath << "\n";
    cout << "  Electricity Bill: " << app.electricityBillPath << "\n";
    cout << "  Salary Slip:      " << app.salarySlipPath << "\n\n";

    cout << COLOR_YELLOW << "LOAN DETAILS:" << COLOR_RESET << "\n";
    if (app.loanType == "Home Loan")
    {
        cout << "  Type: Home Loan\n";
        cout << "  Area: " << app.homeOption.area << "\n";
        cout << "  Size: " << app.homeOption.size << "\n";
        cout << "  Installments: " << app.homeOption.installments << " months\n";
        cout << "  Monthly Payment: PKR " << app.homeOption.monthlyInstallment << "\n";
    }
    else if (app.loanType == "Car Loan")
    {
        cout << "  Type: Car Loan\n";
        cout << "  Car: " << app.carOption.make << " " << app.carOption.model << "\n";
        cout << "  Installments: " << app.carOption.installments << " months\n";
        cout << "  Monthly Payment: PKR " << app.carOption.monthlyInstallment << "\n";
    }
    else if (app.loanType == "Scooter Loan")
    {
        cout << "  Type: Scooter Loan\n";
        cout << "  Scooter: " << app.scooterOption.make << " " << app.scooterOption.model << "\n";
        cout << "  Installments: " << app.scooterOption.installments << " months\n";
        cout << "  Monthly Payment: PKR " << app.scooterOption.monthlyInstallment << "\n";
    }

    cout << "\n" << COLOR_BOLD << COLOR_CYAN;
    cout << "========================================================\n" << COLOR_RESET;
}