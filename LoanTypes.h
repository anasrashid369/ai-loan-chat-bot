// ============================================
// LOAN TYPES HEADER FILE
// ============================================
// Contains data structures and function declarations
// for the home loan chatbot system

#ifndef LOANTYPES_H
#define LOANTYPES_H

#include <string>
#include <vector>

using namespace std;

// ============================================
// COLOR CODES FOR CONSOLE OUTPUT
// ============================================
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_RED "\033[31m"
#define COLOR_BOLD "\033[1m"
#define COLOR_RESET "\033[0m"

// ============================================
// CONSTANTS
// ============================================
const int MAX_AREA_CODE = 4;
const int MAX_EXISTING_LOANS = 3;

// ============================================
// STRUCT: HomeLoanOption
// ============================================
struct HomeLoanOption
{
    string area;
    string size;
    int installments = 0;
    long long price = 0;
    long long downPayment = 0;
    long long monthlyInstallment = 0;
};

// ============================================
// STRUCT: CarLoanOption
// ============================================
struct CarLoanOption
{
    string make;
    string model;
    string engine;
    string used;
    string manufacturingYear;
    int installments = 0;
    long long price = 0;
    long long downPayment = 0;
    long long monthlyInstallment = 0;
};

// ============================================
// STRUCT: ScooterLoanOption
// ============================================
struct ScooterLoanOption
{
    string make;
    string model;
    string distancePerCharge;
    string chargingTime;
    string maxSpeed;
    int installments = 0;
    long long price = 0;
    long long downPayment = 0;
    long long monthlyInstallment = 0;
};

// ============================================
// STRUCT: ExistingLoan
// ============================================
struct ExistingLoan
{
    string isActive;
    long long totalAmount = 0;
    long long amountReturned = 0;
    long long amountDue = 0;
    string bankName;
    string category;
};

// ============================================
// STRUCT: Reference
// ============================================
struct Reference
{
    string name;
    string cnic;
    string cnicIssueDate;
    string phoneNumber;
    string email;
};

// ============================================
// STRUCT: LoanApplication
// ============================================
struct LoanApplication
{
    string applicationId = "0000";
    string loanType = "Home Loan";
    string applicantName = "N/A";
    string fatherName = "N/A";
    string postalAddress = "N/A";
    string contactNumber = "N/A";
    string email = "N/A";
    string cnic = "N/A";
    string cnicExpiryDate = "N/A";
    string employmentStatus = "N/A";
    string maritalStatus = "N/A";
    string gender = "N/A";
    int numDependents = 0;
    long long annualIncome = 0;
    long long avgElectricityBill = 0;
    long long currentElectricityBill = 0;

    vector<ExistingLoan> existingLoans;

    Reference referee1;
    Reference referee2;

    string cnicFrontPath;
    string cnicBackPath;
    string electricityBillPath;
    string salarySlipPath;

    HomeLoanOption homeOption;
    CarLoanOption carOption;
    ScooterLoanOption scooterOption;

    string status = "Submitted";
    string submissionDate = "N/A";
};

// ============================================
// FUNCTION DECLARATIONS
// ============================================

long long calculateMonthlyInstallment(long long price, long long downPayment, int installments);

void loadUtterances(vector<string>& keys, vector<string>& values, const string& filename);

vector<HomeLoanOption> loadHomeLoanData(const string& filename);
vector<CarLoanOption> loadCarLoanData(const string& filename);
vector<ScooterLoanOption> loadScooterLoanData(const string& filename);

void storeApplication(const LoanApplication& application, const string& filename);
string generateApplicationId(const string& filename);
vector<LoanApplication> loadAllApplications(const string& filename);
void updateApplicationStatus(const string& applicationId, const string& newStatus, const string& filename);
int countApplicationsByCNIC(const string& cnic, const string& status, const string& filename);

// New function for copying application documents
bool copyApplicationDocuments(LoanApplication& app);

#endif // LOANTYPES_H