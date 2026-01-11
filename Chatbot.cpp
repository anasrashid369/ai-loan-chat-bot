#include "Chatbot.h"
#include "LoanTypes.h"
#include "Validation.h"
#include "Display.h"
#include "DataCollection.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// ==================================================
// Helper Function: Get Response
// ==================================================
string getResponse(const string& input, const vector<string>& keys, const vector<string>& values)
{
    string defaultResponse = "I didn't understand that. Try again or press A to apply for a loan.";
    string fallbackResponse = "";

    string upperInput = input;
    for (char& c : upperInput)
        c = toupper(static_cast<unsigned char>(c));

    for (size_t i = 0; i < keys.size(); i++)
    {
        string upperKey = keys[i];
        for (char& c : upperKey)
            c = toupper(static_cast<unsigned char>(c));

        if (upperInput == upperKey)
            return values[i];
    }

    if (input.size() == 1)
    {
        char upperChar = toupper(static_cast<unsigned char>(input[0]));
        string temp(1, upperChar);

        for (size_t i = 0; i < keys.size(); i++)
        {
            if (keys[i].size() == 1 && keys[i] == temp)
                return values[i];
        }
    }

    for (size_t i = 0; i < keys.size(); i++)
    {
        if (keys[i] == "*")
            fallbackResponse = values[i];
    }

    if (!fallbackResponse.empty())
        return fallbackResponse;

    return defaultResponse;
}

// ==================================================
// Helper: Handle Loan Selection
// ==================================================
void handleHomeLoanSelection(string& currentState, LoanApplication& newApp,
    const vector<HomeLoanOption>& homeOptions,
    vector<int>& matchingIndexes, const string& userInput)
{
    int areaCode = 0;
    try { areaCode = stoi(userInput); }
    catch (...) { areaCode = 0; }

    if (currentState == "AreaSelection" && areaCode >= 1 && areaCode <= MAX_AREA_CODE)
    {
        string areaName = "Area " + to_string(areaCode);
        matchingIndexes.clear();

        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Available options for " << COLOR_BOLD << areaName << COLOR_RESET << ":\n";

        int count = 0;
        for (size_t i = 0; i < homeOptions.size(); i++)
        {
            if (homeOptions[i].area == areaName)
            {
                count++;
                matchingIndexes.push_back(i);
                cout << "   [" << COLOR_CYAN << count << COLOR_RESET << "] Size: " << homeOptions[i].size
                    << " | Installments: " << homeOptions[i].installments
                    << " | Monthly: " << COLOR_YELLOW << "PKR " << homeOptions[i].monthlyInstallment << COLOR_RESET << "\n";
            }
        }

        if (count > 0)
        {
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Enter the number next to the plan you want (1 to " << count << ").\n";
            currentState = "HomePlanSelection";
        }
        else
        {
            cout << COLOR_RED << "No options found for that area. Try again.\n" << COLOR_RESET;
        }
    }
    else if (currentState == "HomePlanSelection")
    {
        int planNum = 0;
        try { planNum = stoi(userInput); }
        catch (...) { planNum = 0; }

        if (planNum >= 1 && planNum <= matchingIndexes.size())
        {
            const HomeLoanOption& chosen = homeOptions[matchingIndexes[planNum - 1]];
            printInstallmentPlan(chosen);
            newApp.homeOption = chosen;
            newApp.loanType = "Home Loan";
            currentState = "CollectName";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your full name.\n";
        }
        else
        {
            cout << COLOR_RED << "Invalid plan number. Try again.\n" << COLOR_RESET;
        }
    }
}

void handleCarLoanSelection(string& currentState, LoanApplication& newApp,
    const vector<CarLoanOption>& carOptions,
    vector<int>& matchingIndexes, const string& userInput)
{
    if (currentState == "CarMakeSelection")
    {
        int makeNum = 0;
        try { makeNum = stoi(userInput); }
        catch (...) { makeNum = 0; }

        vector<string> makes;
        for (const auto& car : carOptions)
        {
            bool found = false;
            for (const auto& m : makes)
            {
                if (m == car.make)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                makes.push_back(car.make);
        }

        if (makeNum >= 1 && makeNum <= makes.size())
        {
            string selectedMake = makes[makeNum - 1];
            matchingIndexes.clear();

            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Available models for " << COLOR_BOLD << selectedMake << COLOR_RESET << ":\n";

            int count = 0;
            for (size_t i = 0; i < carOptions.size(); i++)
            {
                if (carOptions[i].make == selectedMake)
                {
                    count++;
                    matchingIndexes.push_back(i);
                    cout << "   [" << COLOR_CYAN << count << COLOR_RESET << "] Model: " << carOptions[i].model
                        << " | Engine: " << carOptions[i].engine << "cc"
                        << " | Used: " << carOptions[i].used
                        << " | Year: " << carOptions[i].manufacturingYear
                        << " | Monthly: " << COLOR_YELLOW << "PKR " << carOptions[i].monthlyInstallment << COLOR_RESET << "\n";
                }
            }

            if (count > 0)
            {
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Enter the number next to the car you want (1 to " << count << ").\n";
                currentState = "CarModelSelection";
            }
        }
        else
        {
            cout << COLOR_RED << "Invalid selection. Try again.\n" << COLOR_RESET;
        }
    }
    else if (currentState == "CarModelSelection")
    {
        int carNum = 0;
        try { carNum = stoi(userInput); }
        catch (...) { carNum = 0; }

        if (carNum >= 1 && carNum <= matchingIndexes.size())
        {
            const CarLoanOption& chosen = carOptions[matchingIndexes[carNum - 1]];
            printCarInstallmentPlan(chosen);
            newApp.carOption = chosen;
            newApp.loanType = "Car Loan";
            currentState = "CollectName";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your full name.\n";
        }
        else
        {
            cout << COLOR_RED << "Invalid selection. Try again.\n" << COLOR_RESET;
        }
    }
}

void handleScooterLoanSelection(string& currentState, LoanApplication& newApp,
    const vector<ScooterLoanOption>& scooterOptions,
    const string& userInput)
{
    int scooterNum = 0;
    try { scooterNum = stoi(userInput); }
    catch (...) { scooterNum = 0; }

    if (scooterNum >= 1 && scooterNum <= scooterOptions.size())
    {
        const ScooterLoanOption& chosen = scooterOptions[scooterNum - 1];
        printScooterInstallmentPlan(chosen);
        newApp.scooterOption = chosen;
        newApp.loanType = "Scooter Loan";
        currentState = "CollectName";
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your full name.\n";
    }
    else
    {
        cout << COLOR_RED << "Invalid selection. Try again.\n" << COLOR_RESET;
    }
}

// ==================================================
// Main Chatbot Function
// ==================================================
void runChatbot(const vector<string>& utteranceKeys,
    const vector<string>& utteranceValues,
    const vector<HomeLoanOption>& homeOptions,
    const vector<CarLoanOption>& carOptions,
    const vector<ScooterLoanOption>& scooterOptions)
{
    string userInput;
    string currentState = "Initial";
    vector<int> matchingIndexes;
    LoanApplication newApp;

    cout << COLOR_BOLD << COLOR_CYAN << "\n--- LOAN CHATBOT ---" << COLOR_RESET << "\n";
    cout << COLOR_YELLOW << "Program: " << COLOR_RESET << getResponse("*", utteranceKeys, utteranceValues) << "\n";

    while (true)
    {
        cout << COLOR_BOLD << "User: " << COLOR_RESET;
        getline(cin, userInput);

        string upperInput = userInput;
        for (char& c : upperInput)
            c = toupper(static_cast<unsigned char>(c));

        if (upperInput == "X")
        {
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Thank you for using the chatbot. Goodbye!\n";
            break;
        }

        // Query application counts
        if (currentState == "Initial" && upperInput == "Q")
        {
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Please enter your CNIC (13 digits) to check applications.\n";
            currentState = "QueryCNIC";
            continue;
        }

        if (currentState == "QueryCNIC")
        {
            if (isValidCNIC(userInput))
            {
                int submitted = countApplicationsByCNIC(userInput, "Submitted", "applications.txt");
                int approved = countApplicationsByCNIC(userInput, "Approved", "applications.txt");
                int rejected = countApplicationsByCNIC(userInput, "Rejected", "applications.txt");

                cout << COLOR_CYAN << "\n--- Application Summary for CNIC: " << userInput << " ---\n" << COLOR_RESET;
                cout << "  Submitted: " << COLOR_YELLOW << submitted << COLOR_RESET << "\n";
                cout << "  Approved:  " << COLOR_GREEN << approved << COLOR_RESET << "\n";
                cout << "  Rejected:  " << COLOR_RED << rejected << COLOR_RESET << "\n\n";

                currentState = "Initial";
                continue;
            }
            else
            {
                cout << COLOR_RED << "Invalid CNIC. Please enter a 13-digit number.\n" << COLOR_RESET;
                continue;
            }
        }

        // Loan selection states
        if (currentState == "AreaSelection" || currentState == "HomePlanSelection")
        {
            handleHomeLoanSelection(currentState, newApp, homeOptions, matchingIndexes, userInput);
            continue;
        }

        if (currentState == "CarMakeSelection" || currentState == "CarModelSelection")
        {
            handleCarLoanSelection(currentState, newApp, carOptions, matchingIndexes, userInput);
            continue;
        }

        if (currentState == "ScooterSelection")
        {
            handleScooterLoanSelection(currentState, newApp, scooterOptions, userInput);
            continue;
        }

        // Data collection using modular functions
        if (currentState == "CollectName" || currentState == "CollectFatherName" ||
            currentState == "CollectAddress" || currentState == "CollectPhone" ||
            currentState == "CollectEmail" || currentState == "CollectCNIC" ||
            currentState == "CollectCNICExpiry" || currentState == "CollectEmployment" ||
            currentState == "CollectMarital" || currentState == "CollectGender" ||
            currentState == "CollectDependents")
        {
            collectPersonalInfo(newApp, currentState, userInput);
            continue;
        }

        if (currentState == "CollectAnnualIncome" || currentState == "CollectAvgElecBill" ||
            currentState == "CollectCurrentElecBill")
        {
            collectFinancialInfo(newApp, currentState, userInput);
            continue;
        }

        if (currentState == "AskExistingLoans" || currentState == "CollectLoanActive" ||
            currentState == "CollectLoanTotal" || currentState == "CollectLoanReturned" ||
            currentState == "CollectLoanDue" || currentState == "CollectLoanBank" ||
            currentState == "CollectLoanCategory" || currentState == "AskAnotherLoan")
        {
            collectExistingLoans(newApp, currentState, userInput);
            continue;
        }

        if (currentState.find("CollectRef") == 0)
        {
            collectReferences(newApp, currentState, userInput);
            continue;
        }

        if (currentState == "CollectCNICFront" || currentState == "CollectCNICBack" ||
            currentState == "CollectElecBillPath" || currentState == "CollectSalarySlipPath")
        {
            bool allCollected = collectDocuments(newApp, currentState, userInput);
            if (allCollected)
            {
                // Generate Application ID and timestamp
                newApp.applicationId = generateApplicationId("applications.txt");

                time_t now = time(0);
                tm localTime;
                localtime_s(&localTime, &now);
                stringstream ss;
                ss << (1900 + localTime.tm_year) << "-"
                    << setfill('0') << setw(2) << (1 + localTime.tm_mon) << "-"
                    << setfill('0') << setw(2) << localTime.tm_mday << " "
                    << setfill('0') << setw(2) << localTime.tm_hour << ":"
                    << setfill('0') << setw(2) << localTime.tm_min << ":"
                    << setfill('0') << setw(2) << localTime.tm_sec;
                newApp.submissionDate = ss.str();

                // Copy application documents to unique folder
                cout << COLOR_CYAN << "\n[System] Processing your documents...\n" << COLOR_RESET;
                if (!copyApplicationDocuments(newApp))
                {
                    cout << COLOR_RED << "\n[System] Error: Failed to copy documents. Application not submitted.\n" << COLOR_RESET;
                    cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Press A for new application or X to exit.\n";
                    newApp = LoanApplication();
                    currentState = "Initial";
                    continue;
                }

                displayApplicationSummary(newApp);

                currentState = "ConfirmSubmission";
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Do you want to submit this application? (Yes/No)\n";
            }
            continue;
        }

        if (currentState == "ConfirmSubmission")
        {
            if (upperInput == "YES" || upperInput == "Y")
            {
                storeApplication(newApp, "applications.txt");

                cout << COLOR_GREEN << "\n[System] Application submitted successfully!\n" << COLOR_RESET;
                cout << COLOR_CYAN << "[System] Your Application ID: " << newApp.applicationId << "\n" << COLOR_RESET;
                cout << COLOR_CYAN << "[System] Documents saved in: ./data/" << newApp.applicationId << "/\n" << COLOR_RESET;
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Press A for new application, Q to query applications, or X to exit.\n";

                newApp = LoanApplication();
                currentState = "Initial";
                continue;
            }
            else if (upperInput == "NO" || upperInput == "N")
            {
                cout << COLOR_RED << "Application discarded.\n" << COLOR_RESET;
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Press A for new application or X to exit.\n";
                newApp = LoanApplication();
                currentState = "Initial";
                continue;
            }
            else
            {
                cout << COLOR_RED << "Please answer Yes or No.\n" << COLOR_RESET;
                continue;
            }
        }

        // Initial commands
        if (currentState == "Initial" && upperInput == "A")
        {
            currentState = "LoanCategory";
            cout << COLOR_YELLOW << "Program: " << COLOR_RESET << getResponse("A", utteranceKeys, utteranceValues) << "\n";
            continue;
        }

        if (currentState == "LoanCategory")
        {
            if (upperInput == "H")
            {
                newApp.loanType = "Home Loan";
                currentState = "AreaSelection";
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << getResponse("H", utteranceKeys, utteranceValues) << "\n";
                continue;
            }
            else if (upperInput == "C")
            {
                vector<string> makes;
                for (const auto& car : carOptions)
                {
                    bool found = false;
                    for (const auto& m : makes)
                    {
                        if (m == car.make)
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        makes.push_back(car.make);
                }

                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Available car makes:\n";
                for (size_t i = 0; i < makes.size(); i++)
                {
                    cout << "   [" << COLOR_CYAN << (i + 1) << COLOR_RESET << "] " << makes[i] << "\n";
                }
                cout << "Enter the number of the car make you're interested in.\n";
                currentState = "CarMakeSelection";
                continue;
            }
            else if (upperInput == "S")
            {
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "Available scooters:\n";
                for (size_t i = 0; i < scooterOptions.size(); i++)
                {
                    cout << "   [" << COLOR_CYAN << (i + 1) << COLOR_RESET << "] "
                        << scooterOptions[i].make << " " << scooterOptions[i].model
                        << " | Range: " << scooterOptions[i].distancePerCharge << "km"
                        << " | Monthly: " << COLOR_YELLOW << "PKR " << scooterOptions[i].monthlyInstallment << COLOR_RESET << "\n";
                }
                cout << "Enter the number of the scooter you want (1 to " << scooterOptions.size() << ").\n";
                currentState = "ScooterSelection";
                continue;
            }
            else if (upperInput == "P")
            {
                cout << COLOR_YELLOW << "Program: " << COLOR_RESET << "That loan type is not supported yet. Please select H, C, S or X to exit.\n";
                continue;
            }
        }

        if (currentState == "Initial" && (upperInput == "H" || upperInput == "C" || upperInput == "S" || upperInput == "P"))
        {
            cout << COLOR_RED << "Invalid command. Press A first to start an application.\n" << COLOR_RESET;
            continue;
        }

        // Default case
        string reply = getResponse(userInput, utteranceKeys, utteranceValues);
        cout << COLOR_YELLOW << "Program: " << COLOR_RESET << reply << "\n";
        currentState = "Initial";
    }
}