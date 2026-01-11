#include "DataCollection.h"
#include "Validation.h"
#include "LoanTypes.h"
#include "FileOperations.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ============================================
// PERSONAL INFORMATION COLLECTION
// ============================================

bool collectPersonalInfo(LoanApplication& app, string& currentState, const string& userInput)
{
    string upperInput = userInput;
    for (char& c : upperInput)
        c = toupper(static_cast<unsigned char>(c));

    if (currentState == "CollectName")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Name cannot be empty. Please enter your full name.\n" << COLOR_RESET;
            return false;
        }
        app.applicantName = userInput;
        currentState = "CollectFatherName";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your father's name.\n";
        return false;
    }
    else if (currentState == "CollectFatherName")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Father's name cannot be empty.\n" << COLOR_RESET;
            return false;
        }
        app.fatherName = userInput;
        currentState = "CollectAddress";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your postal address.\n";
        return false;
    }
    else if (currentState == "CollectAddress")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Address cannot be empty.\n" << COLOR_RESET;
            return false;
        }
        app.postalAddress = userInput;
        currentState = "CollectPhone";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your contact number.\n";
        return false;
    }
    else if (currentState == "CollectPhone")
    {
        if (!isValidPhone(userInput))
        {
            cout << COLOR_RED << "Invalid phone number. Please try again.\n" << COLOR_RESET;
            return false;
        }
        app.contactNumber = userInput;
        currentState = "CollectEmail";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your email address.\n";
        return false;
    }
    else if (currentState == "CollectEmail")
    {
        if (!isValidEmail(userInput))
        {
            cout << COLOR_RED << "Invalid email address. Please try again.\n" << COLOR_RESET;
            return false;
        }
        app.email = userInput;
        currentState = "CollectCNIC";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your CNIC (13 digits, no dashes).\n";
        return false;
    }
    else if (currentState == "CollectCNIC")
    {
        if (!isValidCNIC(userInput))
        {
            cout << COLOR_RED << "Invalid CNIC. Please enter a 13-digit number without dashes.\n" << COLOR_RESET;
            return false;
        }
        app.cnic = userInput;
        currentState = "CollectCNICExpiry";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your CNIC expiry date (DD-MM-YYYY).\n";
        return false;
    }
    else if (currentState == "CollectCNICExpiry")
    {
        if (!isValidDate(userInput))
        {
            cout << COLOR_RED << "Invalid date format. Please use DD-MM-YYYY.\n" << COLOR_RESET;
            return false;
        }
        app.cnicExpiryDate = userInput;
        currentState = "CollectEmployment";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Employment status? (Self-employed/Salaried/Retired/Unemployed)\n";
        return false;
    }
    else if (currentState == "CollectEmployment")
    {
        if (upperInput != "SELF-EMPLOYED" && upperInput != "SALARIED" && upperInput != "RETIRED" && upperInput != "UNEMPLOYED")
        {
            cout << COLOR_RED << "Please enter: Self-employed, Salaried, Retired, or Unemployed.\n" << COLOR_RESET;
            return false;
        }
        app.employmentStatus = userInput;
        currentState = "CollectMarital";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Marital status? (Single/Married/Divorced/Widowed)\n";
        return false;
    }
    else if (currentState == "CollectMarital")
    {
        if (upperInput != "SINGLE" && upperInput != "MARRIED" && upperInput != "DIVORCED" && upperInput != "WIDOWED")
        {
            cout << COLOR_RED << "Please enter: Single, Married, Divorced, or Widowed.\n" << COLOR_RESET;
            return false;
        }
        app.maritalStatus = userInput;
        currentState = "CollectGender";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Gender? (Male/Female/Other)\n";
        return false;
    }
    else if (currentState == "CollectGender")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Gender cannot be empty.\n" << COLOR_RESET;
            return false;
        }
        app.gender = userInput;
        currentState = "CollectDependents";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Number of dependents? (Enter a number)\n";
        return false;
    }
    else if (currentState == "CollectDependents")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter a valid number.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.numDependents = stoi(userInput);
            currentState = "CollectAnnualIncome";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Annual income in PKR? (numeric value, no commas)\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }

    return false;
}

// ============================================
// FINANCIAL INFORMATION COLLECTION
// ============================================

bool collectFinancialInfo(LoanApplication& app, string& currentState, const string& userInput)
{
    if (currentState == "CollectAnnualIncome")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter numeric value only, no commas.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.annualIncome = stoll(userInput);
            currentState = "CollectAvgElecBill";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Monthly average electricity bill for last 12 months in PKR? (numeric only)\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }
    else if (currentState == "CollectAvgElecBill")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter numeric value only.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.avgElectricityBill = stoll(userInput);
            currentState = "CollectCurrentElecBill";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Current electricity bill amount in PKR? (numeric only)\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }
    else if (currentState == "CollectCurrentElecBill")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter numeric value only.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.currentElectricityBill = stoll(userInput);
            currentState = "AskExistingLoans";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Do you have any existing loans? (Yes/No)\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }

    return false;
}

// ============================================
// EXISTING LOANS COLLECTION
// ============================================

bool collectExistingLoans(LoanApplication& app, string& currentState, const string& userInput)
{
    string upperInput = userInput;
    for (char& c : upperInput)
        c = toupper(static_cast<unsigned char>(c));

    if (currentState == "AskExistingLoans")
    {
        if (upperInput == "YES" || upperInput == "Y")
        {
            if (app.existingLoans.size() >= MAX_EXISTING_LOANS)
            {
                cout << COLOR_RED << "Maximum " << MAX_EXISTING_LOANS << " loans allowed.\n" << COLOR_RESET;
                currentState = "CollectRef1Name";
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Now let's collect reference information.\n";
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter name of Referee 1.\n";
                return false;
            }
            currentState = "CollectLoanActive";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Is this loan currently active? (Yes/No)\n";
            return false;
        }
        else if (upperInput == "NO" || upperInput == "N")
        {
            currentState = "CollectRef1Name";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Now let's collect reference information.\n";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter name of Referee 1.\n";
            return false;
        }
        else
        {
            cout << COLOR_RED << "Please answer Yes or No.\n" << COLOR_RESET;
            return false;
        }
    }
    else if (currentState == "CollectLoanActive")
    {
        ExistingLoan loan;
        loan.isActive = userInput;
        app.existingLoans.push_back(loan);
        currentState = "CollectLoanTotal";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Total loan amount in PKR? (numeric only)\n";
        return false;
    }
    else if (currentState == "CollectLoanTotal")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter numeric value only.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.existingLoans.back().totalAmount = stoll(userInput);
            currentState = "CollectLoanReturned";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Amount already returned in PKR? (numeric only)\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }
    else if (currentState == "CollectLoanReturned")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter numeric value only.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.existingLoans.back().amountReturned = stoll(userInput);
            currentState = "CollectLoanDue";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Amount still due in PKR? (numeric only)\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }
    else if (currentState == "CollectLoanDue")
    {
        if (!isNumeric(userInput))
        {
            cout << COLOR_RED << "Please enter numeric value only.\n" << COLOR_RESET;
            return false;
        }
        try
        {
            app.existingLoans.back().amountDue = stoll(userInput);
            currentState = "CollectLoanBank";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Bank name?\n";
            return false;
        }
        catch (...)
        {
            cout << COLOR_RED << "Invalid number. Try again.\n" << COLOR_RESET;
            return false;
        }
    }
    else if (currentState == "CollectLoanBank")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Bank name cannot be empty.\n" << COLOR_RESET;
            return false;
        }
        app.existingLoans.back().bankName = userInput;
        currentState = "CollectLoanCategory";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Loan category? (Car/Home/Bike)\n";
        return false;
    }
    else if (currentState == "CollectLoanCategory")
    {
        if (upperInput != "CAR" && upperInput != "HOME" && upperInput != "BIKE")
        {
            cout << COLOR_RED << "Please enter: Car, Home, or Bike.\n" << COLOR_RESET;
            return false;
        }
        app.existingLoans.back().category = userInput;

        if (app.existingLoans.size() < MAX_EXISTING_LOANS)
        {
            currentState = "AskAnotherLoan";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Do you have another existing loan? (Yes/No)\n";
        }
        else
        {
            currentState = "CollectRef1Name";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Maximum loans recorded. Moving to references.\n";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter name of Referee 1.\n";
        }
        return false;
    }
    else if (currentState == "AskAnotherLoan")
    {
        if (upperInput == "YES" || upperInput == "Y")
        {
            currentState = "CollectLoanActive";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Is this loan currently active? (Yes/No)\n";
            return false;
        }
        else if (upperInput == "NO" || upperInput == "N")
        {
            currentState = "CollectRef1Name";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Now let's collect reference information.\n";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter name of Referee 1.\n";
            return false;
        }
        else
        {
            cout << COLOR_RED << "Please answer Yes or No.\n" << COLOR_RESET;
            return false;
        }
    }

    return false;
}

// ============================================
// REFERENCES COLLECTION
// ============================================

bool collectReferences(LoanApplication& app, string& currentState, const string& userInput)
{
    // REFEREE 1
    if (currentState == "CollectRef1Name")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Name cannot be empty.\n" << COLOR_RESET;
            return false;
        }
        app.referee1.name = userInput;
        currentState = "CollectRef1CNIC";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "CNIC of Referee 1? (13 digits)\n";
        return false;
    }
    else if (currentState == "CollectRef1CNIC")
    {
        if (!isValidCNIC(userInput))
        {
            cout << COLOR_RED << "Invalid CNIC. Please enter 13 digits.\n" << COLOR_RESET;
            return false;
        }
        app.referee1.cnic = userInput;
        currentState = "CollectRef1IssueDate";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "CNIC issue date of Referee 1? (DD-MM-YYYY)\n";
        return false;
    }
    else if (currentState == "CollectRef1IssueDate")
    {
        if (!isValidDate(userInput))
        {
            cout << COLOR_RED << "Invalid date format. Please use DD-MM-YYYY.\n" << COLOR_RESET;
            return false;
        }
        app.referee1.cnicIssueDate = userInput;
        currentState = "CollectRef1Phone";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Phone number of Referee 1?\n";
        return false;
    }
    else if (currentState == "CollectRef1Phone")
    {
        if (!isValidPhone(userInput))
        {
            cout << COLOR_RED << "Invalid phone number.\n" << COLOR_RESET;
            return false;
        }
        app.referee1.phoneNumber = userInput;
        currentState = "CollectRef1Email";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Email of Referee 1?\n";
        return false;
    }
    else if (currentState == "CollectRef1Email")
    {
        if (!isValidEmail(userInput))
        {
            cout << COLOR_RED << "Invalid email address.\n" << COLOR_RESET;
            return false;
        }
        app.referee1.email = userInput;
        currentState = "CollectRef2Name";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter name of Referee 2.\n";
        return false;
    }
    // REFEREE 2
    else if (currentState == "CollectRef2Name")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Name cannot be empty.\n" << COLOR_RESET;
            return false;
        }
        app.referee2.name = userInput;
        currentState = "CollectRef2CNIC";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "CNIC of Referee 2? (13 digits)\n";
        return false;
    }
    else if (currentState == "CollectRef2CNIC")
    {
        if (!isValidCNIC(userInput))
        {
            cout << COLOR_RED << "Invalid CNIC. Please enter 13 digits.\n" << COLOR_RESET;
            return false;
        }
        app.referee2.cnic = userInput;
        currentState = "CollectRef2IssueDate";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "CNIC issue date of Referee 2? (DD-MM-YYYY)\n";
        return false;
    }
    else if (currentState == "CollectRef2IssueDate")
    {
        if (!isValidDate(userInput))
        {
            cout << COLOR_RED << "Invalid date format. Please use DD-MM-YYYY.\n" << COLOR_RESET;
            return false;
        }
        app.referee2.cnicIssueDate = userInput;
        currentState = "CollectRef2Phone";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Phone number of Referee 2?\n";
        return false;
    }
    else if (currentState == "CollectRef2Phone")
    {
        if (!isValidPhone(userInput))
        {
            cout << COLOR_RED << "Invalid phone number.\n" << COLOR_RESET;
            return false;
        }
        app.referee2.phoneNumber = userInput;
        currentState = "CollectRef2Email";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Email of Referee 2?\n";
        return false;
    }
    else if (currentState == "CollectRef2Email")
    {
        if (!isValidEmail(userInput))
        {
            cout << COLOR_RED << "Invalid email address.\n" << COLOR_RESET;
            return false;
        }
        app.referee2.email = userInput;
        currentState = "CollectCNICFront";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Now provide document file paths.\n";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Enter the full path to your CNIC front image file:\n";
        cout << COLOR_CYAN << "(Example: C:\\Users\\YourName\\Documents\\cnic_front.jpg)\n" << COLOR_RESET;
        return false;
    }

    return false;
}

// ============================================
// DOCUMENTS COLLECTION WITH FILE COPYING
// ============================================

bool collectDocuments(LoanApplication& app, string& currentState, const string& userInput)
{
    if (currentState == "CollectCNICFront")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Path cannot be empty.\n" << COLOR_RESET;
            return false;
        }

        // Validate file exists
        if (!fileExists(userInput))
        {
            cout << COLOR_RED << "File does not exist at the specified path. Please check and try again.\n" << COLOR_RESET;
            return false;
        }

        // Validate file type
        if (!isValidImageFile(userInput))
        {
            cout << COLOR_RED << "Invalid file type. Please provide an image file (.jpg, .jpeg, .png, .bmp, .gif, .tiff)\n" << COLOR_RESET;
            return false;
        }

        app.cnicFrontPath = userInput;
        currentState = "CollectCNICBack";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Enter the full path to your CNIC back image file:\n";
        cout << COLOR_CYAN << "(Example: C:\\Users\\YourName\\Documents\\cnic_back.jpg)\n" << COLOR_RESET;
        return false;
    }
    else if (currentState == "CollectCNICBack")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Path cannot be empty.\n" << COLOR_RESET;
            return false;
        }

        if (!fileExists(userInput))
        {
            cout << COLOR_RED << "File does not exist at the specified path. Please check and try again.\n" << COLOR_RESET;
            return false;
        }

        if (!isValidImageFile(userInput))
        {
            cout << COLOR_RED << "Invalid file type. Please provide an image file (.jpg, .jpeg, .png, .bmp, .gif, .tiff)\n" << COLOR_RESET;
            return false;
        }

        app.cnicBackPath = userInput;
        currentState = "CollectElecBillPath";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Enter the full path to your electricity bill image file:\n";
        cout << COLOR_CYAN << "(Example: C:\\Users\\YourName\\Documents\\elec_bill.jpg)\n" << COLOR_RESET;
        return false;
    }
    else if (currentState == "CollectElecBillPath")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Path cannot be empty.\n" << COLOR_RESET;
            return false;
        }

        if (!fileExists(userInput))
        {
            cout << COLOR_RED << "File does not exist at the specified path. Please check and try again.\n" << COLOR_RESET;
            return false;
        }

        if (!isValidImageFile(userInput))
        {
            cout << COLOR_RED << "Invalid file type. Please provide an image file (.jpg, .jpeg, .png, .bmp, .gif, .tiff)\n" << COLOR_RESET;
            return false;
        }

        app.electricityBillPath = userInput;
        currentState = "CollectSalarySlipPath";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Enter the full path to your salary slip/bank statement image file:\n";
        cout << COLOR_CYAN << "(Example: C:\\Users\\YourName\\Documents\\salary_slip.jpg)\n" << COLOR_RESET;
        return false;
    }
    else if (currentState == "CollectSalarySlipPath")
    {
        if (userInput.empty())
        {
            cout << COLOR_RED << "Path cannot be empty.\n" << COLOR_RESET;
            return false;
        }

        if (!fileExists(userInput))
        {
            cout << COLOR_RED << "File does not exist at the specified path. Please check and try again.\n" << COLOR_RESET;
            return false;
        }

        if (!isValidImageFile(userInput))
        {
            cout << COLOR_RED << "Invalid file type. Please provide an image file (.jpg, .jpeg, .png, .bmp, .gif, .tiff)\n" << COLOR_RESET;
            return false;
        }

        app.salarySlipPath = userInput;
        return true; // All data collected
    }

    return false;
}