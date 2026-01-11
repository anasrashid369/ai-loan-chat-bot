#pragma once
#pragma once
// ============================================
// VALIDATION HEADER FILE
// ============================================
// Contains validation functions for user inputs

#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
using namespace std;

// Validates CNIC (13 digits)
bool isValidCNIC(const string& cnic);

// Validates date format (DD-MM-YYYY)
bool isValidDate(const string& date);

// Validates email format
bool isValidEmail(const string& email);

// Validates phone number
bool isValidPhone(const string& phone);

// Checks if string contains only digits
bool isNumeric(const string& str);

#endif 