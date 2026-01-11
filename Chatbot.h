// ==================================================
// Chatbot Header File
// ==================================================
// This file has function declarations for the chatbot system
// The chatbot helps users explore and choose home loan options

#ifndef CHATBOT_H
#define CHATBOT_H

#include "LoanTypes.h"
#include <string>
#include <vector>
using namespace std;

// These functions show the monthly installment plan
void printInstallmentPlan(const HomeLoanOption& option);
void printCarInstallmentPlan(const CarLoanOption& option);
void printScooterInstallmentPlan(const ScooterLoanOption& option);

// This is the main chatbot function
void runChatbot(const vector<string>& utteranceKeys,
    const vector<string>& utteranceValues,
    const vector<HomeLoanOption>& homeOptions,
    const vector<CarLoanOption>& carOptions,
    const vector<ScooterLoanOption>& scooterOptions);

#endif
// ==================================================
// End of Chatbot Header File
// ==================================================