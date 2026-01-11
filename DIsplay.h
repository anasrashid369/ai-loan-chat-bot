// ============================================
// DISPLAY HEADER FILE
// ============================================
// Contains display functions for loan details

#ifndef DISPLAY_H
#define DISPLAY_H

#include "LoanTypes.h"

// Display home loan installment plan
void printInstallmentPlan(const HomeLoanOption& option);

// Display car loan installment plan
void printCarInstallmentPlan(const CarLoanOption& option);

// Display scooter loan installment plan
void printScooterInstallmentPlan(const ScooterLoanOption& option);

// Display complete application summary
void displayApplicationSummary(const LoanApplication& app);

#endif // DISPLAY_H#pragma once
