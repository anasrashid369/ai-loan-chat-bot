// ============================================
// DATA COLLECTION HEADER FILE
// ============================================
// Functions for collecting application data from users

#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include "LoanTypes.h"
#include <string>

using namespace std;

// Collect personal information
bool collectPersonalInfo(LoanApplication& app, string& currentState, const string& userInput);

// Collect financial information
bool collectFinancialInfo(LoanApplication& app, string& currentState, const string& userInput);

// Collect existing loans information
bool collectExistingLoans(LoanApplication& app, string& currentState, const string& userInput);

// Collect reference information
bool collectReferences(LoanApplication& app, string& currentState, const string& userInput);

// Collect document paths
bool collectDocuments(LoanApplication& app, string& currentState, const string& userInput);

#endif // DATACOLLECTION_H#pragma once
