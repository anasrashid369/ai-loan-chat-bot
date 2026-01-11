#include "LoanTypes.h"
#include "FileOperations.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <ctime>

using namespace std;

// ============================================
// Basic Calculation
// ============================================
long long calculateMonthlyInstallment(long long price, long long downPayment, int installments)
{
    if (installments <= 0)
        return 0;
    return (price - downPayment) / installments;
}

// ============================================
// String Helper
// ============================================
string removeCommas(const string& str)
{
    string result;
    for (char c : str)
    {
        if (c != ',')
            result += c;
    }
    return result;
}

string trim(const string& str)
{
    size_t start = 0;
    size_t end = str.length();

    while (start < end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r'))
        start++;

    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\n' || str[end - 1] == '\r'))
        end--;

    return str.substr(start, end - start);
}

// ============================================
// Load Chatbot Data
// ============================================
void loadUtterances(vector<string>& keys, vector<string>& values, const string& filename)
{
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << COLOR_RED << "Error: Could not open " << filename << COLOR_RESET << endl;
        return;
    }

    while (getline(file, line))
    {
        size_t pos = line.find('#');
        if (pos != string::npos)
        {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);
            keys.push_back(key);
            values.push_back(value);
        }
    }

    file.close();
}

// ============================================
// Load Home Loan Data
// ============================================
vector<HomeLoanOption> loadHomeLoanData(const string& filename)
{
    vector<HomeLoanOption> options;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << COLOR_RED << "Error: Could not open " << filename << COLOR_RESET << "\n";
        return options;
    }

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string part;
        vector<string> fields;

        while (getline(ss, part, '#'))
            fields.push_back(part);

        if (fields.size() == 5)
        {
            HomeLoanOption opt;
            opt.area = fields[0];
            opt.size = fields[1];

            try
            {
                opt.installments = stoi(fields[2]);
                opt.price = stoll(removeCommas(fields[3]));
                opt.downPayment = stoll(removeCommas(fields[4]));
                opt.monthlyInstallment = calculateMonthlyInstallment(opt.price, opt.downPayment, opt.installments);
                options.push_back(opt);
            }
            catch (const exception& e)
            {
                cout << COLOR_RED << "Error converting data in file: " << e.what() << COLOR_RESET << "\n";
            }
        }
    }

    file.close();
    return options;
}

// ============================================
// Load Car Loan Data
// ============================================
vector<CarLoanOption> loadCarLoanData(const string& filename)
{
    vector<CarLoanOption> options;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << COLOR_RED << "Error: Could not open " << filename << COLOR_RESET << "\n";
        return options;
    }

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string part;
        vector<string> fields;

        while (getline(ss, part, '#'))
            fields.push_back(part);

        if (fields.size() == 8)
        {
            CarLoanOption opt;
            opt.make = fields[0];
            opt.model = fields[1];
            opt.engine = fields[2];
            opt.used = fields[3];
            opt.manufacturingYear = fields[4];

            try
            {
                opt.installments = stoi(fields[5]);
                opt.price = stoll(removeCommas(fields[6]));
                opt.downPayment = stoll(removeCommas(fields[7]));
                opt.monthlyInstallment = calculateMonthlyInstallment(opt.price, opt.downPayment, opt.installments);
                options.push_back(opt);
            }
            catch (const exception& e)
            {
                cout << COLOR_RED << "Error converting car data: " << e.what() << COLOR_RESET << "\n";
            }
        }
    }

    file.close();
    return options;
}

// ============================================
// Load Scooter Loan Data
// ============================================
vector<ScooterLoanOption> loadScooterLoanData(const string& filename)
{
    vector<ScooterLoanOption> options;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cout << COLOR_RED << "Error: Could not open " << filename << COLOR_RESET << "\n";
        return options;
    }

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string part;
        vector<string> fields;

        while (getline(ss, part, '#'))
            fields.push_back(part);

        if (fields.size() == 8)
        {
            ScooterLoanOption opt;
            opt.make = fields[0];
            opt.model = fields[1];
            opt.distancePerCharge = fields[2];
            opt.chargingTime = fields[3];
            opt.maxSpeed = fields[4];

            try
            {
                opt.installments = stoi(fields[5]);
                opt.price = stoll(removeCommas(fields[6]));
                opt.downPayment = stoll(removeCommas(fields[7]));
                opt.monthlyInstallment = calculateMonthlyInstallment(opt.price, opt.downPayment, opt.installments);
                options.push_back(opt);
            }
            catch (const exception& e)
            {
                cout << COLOR_RED << "Error converting scooter data: " << e.what() << COLOR_RESET << "\n";
            }
        }
    }

    file.close();
    return options;
}

// ============================================
// Generate Application ID
// ============================================
string generateApplicationId(const string& filename)
{
    ifstream file(filename);
    int maxId = 0;
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.empty()) continue;

            size_t pos = line.find('#');
            if (pos != string::npos)
            {
                string idStr = line.substr(0, pos);
                try
                {
                    int id = stoi(idStr);
                    if (id > maxId)
                        maxId = id;
                }
                catch (...) {}
            }
        }
        file.close();
    }

    maxId++;
    stringstream ss;
    ss << setfill('0') << setw(4) << maxId;
    return ss.str();
}

// ============================================
// Copy Application Documents
// ============================================
bool copyApplicationDocuments(LoanApplication& app)
{
    // Create application directory path
    string dataDir = "./data/" + app.applicationId;

    cout << COLOR_CYAN << "\n[System] Creating application directory: " << dataDir << COLOR_RESET << endl;

    // Create ./data directory if it doesn't exist
    if (!createDirectory("./data"))
    {
        cout << COLOR_RED << "[System] Failed to create ./data directory\n" << COLOR_RESET;
        return false;
    }

    // Create application-specific directory
    if (!createDirectory(dataDir))
    {
        cout << COLOR_RED << "[System] Failed to create application directory: " << dataDir << "\n" << COLOR_RESET;
        return false;
    }

    cout << COLOR_GREEN << "[System] Directory created successfully!\n" << COLOR_RESET;

    // Copy CNIC Front
    cout << COLOR_CYAN << "[System] Copying CNIC front image...\n" << COLOR_RESET;
    string cnicFrontDest = dataDir + "/cnic_front" + getFileExtension(app.cnicFrontPath);
    if (!copyFile(app.cnicFrontPath, cnicFrontDest))
    {
        cout << COLOR_RED << "[System] Failed to copy CNIC front image\n" << COLOR_RESET;
        return false;
    }
    app.cnicFrontPath = cnicFrontDest;

    // Copy CNIC Back
    cout << COLOR_CYAN << "[System] Copying CNIC back image...\n" << COLOR_RESET;
    string cnicBackDest = dataDir + "/cnic_back" + getFileExtension(app.cnicBackPath);
    if (!copyFile(app.cnicBackPath, cnicBackDest))
    {
        cout << COLOR_RED << "[System] Failed to copy CNIC back image\n" << COLOR_RESET;
        return false;
    }
    app.cnicBackPath = cnicBackDest;

    // Copy Electricity Bill
    cout << COLOR_CYAN << "[System] Copying electricity bill image...\n" << COLOR_RESET;
    string elecBillDest = dataDir + "/electricity_bill" + getFileExtension(app.electricityBillPath);
    if (!copyFile(app.electricityBillPath, elecBillDest))
    {
        cout << COLOR_RED << "[System] Failed to copy electricity bill image\n" << COLOR_RESET;
        return false;
    }
    app.electricityBillPath = elecBillDest;

    // Copy Salary Slip
    cout << COLOR_CYAN << "[System] Copying salary slip image...\n" << COLOR_RESET;
    string salarySlipDest = dataDir + "/salary_slip" + getFileExtension(app.salarySlipPath);
    if (!copyFile(app.salarySlipPath, salarySlipDest))
    {
        cout << COLOR_RED << "[System] Failed to copy salary slip image\n" << COLOR_RESET;
        return false;
    }
    app.salarySlipPath = salarySlipDest;

    cout << COLOR_GREEN << "\n[System] All documents copied successfully!\n" << COLOR_RESET;
    return true;
}

// ============================================
// Load All Applications
// ============================================
vector<LoanApplication> loadAllApplications(const string& filename)
{
    vector<LoanApplication> applications;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        return applications;
    }

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string part;
        vector<string> fields;

        while (getline(ss, part, '#'))
            fields.push_back(part);

        if (fields.size() < 25) continue;

        LoanApplication app;
        int idx = 0;

        app.applicationId = fields[idx++];
        app.loanType = fields[idx++];
        app.applicantName = fields[idx++];
        app.fatherName = fields[idx++];
        app.postalAddress = fields[idx++];
        app.contactNumber = fields[idx++];
        app.email = fields[idx++];
        app.cnic = fields[idx++];
        app.cnicExpiryDate = fields[idx++];
        app.employmentStatus = fields[idx++];
        app.maritalStatus = fields[idx++];
        app.gender = fields[idx++];

        try
        {
            app.numDependents = stoi(fields[idx++]);
            app.annualIncome = stoll(fields[idx++]);
            app.avgElectricityBill = stoll(fields[idx++]);
            app.currentElectricityBill = stoll(fields[idx++]);

            int numLoans = stoi(fields[idx++]);
            for (int i = 0; i < numLoans && idx + 5 < fields.size(); i++)
            {
                ExistingLoan loan;
                loan.isActive = fields[idx++];
                loan.totalAmount = stoll(fields[idx++]);
                loan.amountReturned = stoll(fields[idx++]);
                loan.amountDue = stoll(fields[idx++]);
                loan.bankName = fields[idx++];
                loan.category = fields[idx++];
                app.existingLoans.push_back(loan);
            }

            app.referee1.name = fields[idx++];
            app.referee1.cnic = fields[idx++];
            app.referee1.cnicIssueDate = fields[idx++];
            app.referee1.phoneNumber = fields[idx++];
            app.referee1.email = fields[idx++];

            app.referee2.name = fields[idx++];
            app.referee2.cnic = fields[idx++];
            app.referee2.cnicIssueDate = fields[idx++];
            app.referee2.phoneNumber = fields[idx++];
            app.referee2.email = fields[idx++];

            app.cnicFrontPath = fields[idx++];
            app.cnicBackPath = fields[idx++];
            app.electricityBillPath = fields[idx++];
            app.salarySlipPath = fields[idx++];

            if (app.loanType == "Home Loan" && idx + 5 < fields.size())
            {
                app.homeOption.area = fields[idx++];
                app.homeOption.size = fields[idx++];
                app.homeOption.installments = stoi(fields[idx++]);
                app.homeOption.price = stoll(fields[idx++]);
                app.homeOption.downPayment = stoll(fields[idx++]);
                app.homeOption.monthlyInstallment = stoll(fields[idx++]);
            }
            else if (app.loanType == "Car Loan" && idx + 7 < fields.size())
            {
                app.carOption.make = fields[idx++];
                app.carOption.model = fields[idx++];
                app.carOption.engine = fields[idx++];
                app.carOption.used = fields[idx++];
                app.carOption.manufacturingYear = fields[idx++];
                app.carOption.installments = stoi(fields[idx++]);
                app.carOption.price = stoll(fields[idx++]);
                app.carOption.downPayment = stoll(fields[idx++]);
                app.carOption.monthlyInstallment = stoll(fields[idx++]);
            }
            else if (app.loanType == "Scooter Loan" && idx + 7 < fields.size())
            {
                app.scooterOption.make = fields[idx++];
                app.scooterOption.model = fields[idx++];
                app.scooterOption.distancePerCharge = fields[idx++];
                app.scooterOption.chargingTime = fields[idx++];
                app.scooterOption.maxSpeed = fields[idx++];
                app.scooterOption.installments = stoi(fields[idx++]);
                app.scooterOption.price = stoll(fields[idx++]);
                app.scooterOption.downPayment = stoll(fields[idx++]);
                app.scooterOption.monthlyInstallment = stoll(fields[idx++]);
            }

            app.status = fields[idx++];
            app.submissionDate = fields[idx++];

            applications.push_back(app);
        }
        catch (...) {}
    }

    file.close();
    return applications;
}

// ============================================
// Count Applications by CNIC
// ============================================
int countApplicationsByCNIC(const string& cnic, const string& status, const string& filename)
{
    vector<LoanApplication> apps = loadAllApplications(filename);
    int count = 0;

    for (size_t i = 0; i < apps.size(); i++)
    {
        if (apps[i].cnic == cnic && apps[i].status == status)
            count++;
    }

    return count;
}

// ============================================
// Update Application Status
// ============================================
void updateApplicationStatus(const string& applicationId, const string& newStatus, const string& filename)
{
    vector<LoanApplication> apps = loadAllApplications(filename);

    ofstream file(filename);
    if (!file.is_open())
    {
        cout << COLOR_RED << "Error: Could not open file for writing." << COLOR_RESET << endl;
        return;
    }

    for (size_t i = 0; i < apps.size(); i++)
    {
        if (apps[i].applicationId == applicationId)
            apps[i].status = newStatus;

        storeApplication(apps[i], filename);
    }

    file.close();
}

// ============================================
// Save Application
// ============================================
void storeApplication(const LoanApplication& app, const string& filename)
{
    ofstream file(filename, ios::app);

    if (!file.is_open())
    {
        cout << COLOR_RED << "\n[System] Error: Could not save application to " << filename << COLOR_RESET << endl;
        return;
    }

    // Application ID
    file << app.applicationId << "#";

    // Basic Info
    file << app.loanType << "#";
    file << app.applicantName << "#";
    file << app.fatherName << "#";
    file << app.postalAddress << "#";
    file << app.contactNumber << "#";
    file << app.email << "#";
    file << app.cnic << "#";
    file << app.cnicExpiryDate << "#";
    file << app.employmentStatus << "#";
    file << app.maritalStatus << "#";
    file << app.gender << "#";
    file << app.numDependents << "#";
    file << app.annualIncome << "#";
    file << app.avgElectricityBill << "#";
    file << app.currentElectricityBill << "#";

    // Existing Loans
    file << app.existingLoans.size() << "#";
    for (size_t i = 0; i < app.existingLoans.size(); i++)
    {
        file << app.existingLoans[i].isActive << "#";
        file << app.existingLoans[i].totalAmount << "#";
        file << app.existingLoans[i].amountReturned << "#";
        file << app.existingLoans[i].amountDue << "#";
        file << app.existingLoans[i].bankName << "#";
        file << app.existingLoans[i].category << "#";
    }

    // References
    file << app.referee1.name << "#";
    file << app.referee1.cnic << "#";
    file << app.referee1.cnicIssueDate << "#";
    file << app.referee1.phoneNumber << "#";
    file << app.referee1.email << "#";

    file << app.referee2.name << "#";
    file << app.referee2.cnic << "#";
    file << app.referee2.cnicIssueDate << "#";
    file << app.referee2.phoneNumber << "#";
    file << app.referee2.email << "#";

    // Image Paths
    file << app.cnicFrontPath << "#";
    file << app.cnicBackPath << "#";
    file << app.electricityBillPath << "#";
    file << app.salarySlipPath << "#";

    // Loan Specific Details
    if (app.loanType == "Home Loan")
    {
        file << app.homeOption.area << "#";
        file << app.homeOption.size << "#";
        file << app.homeOption.installments << "#";
        file << app.homeOption.price << "#";
        file << app.homeOption.downPayment << "#";
        file << app.homeOption.monthlyInstallment << "#";
    }
    else if (app.loanType == "Car Loan")
    {
        file << app.carOption.make << "#";
        file << app.carOption.model << "#";
        file << app.carOption.engine << "#";
        file << app.carOption.used << "#";
        file << app.carOption.manufacturingYear << "#";
        file << app.carOption.installments << "#";
        file << app.carOption.price << "#";
        file << app.carOption.downPayment << "#";
        file << app.carOption.monthlyInstallment << "#";
    }
    else if (app.loanType == "Scooter Loan")
    {
        file << app.scooterOption.make << "#";
        file << app.scooterOption.model << "#";
        file << app.scooterOption.distancePerCharge << "#";
        file << app.scooterOption.chargingTime << "#";
        file << app.scooterOption.maxSpeed << "#";
        file << app.scooterOption.installments << "#";
        file << app.scooterOption.price << "#";
        file << app.scooterOption.downPayment << "#";
        file << app.scooterOption.monthlyInstallment << "#";
    }

    // Status and Date
    file << app.status << "#";
    file << app.submissionDate << "\n";

    file.close();
}