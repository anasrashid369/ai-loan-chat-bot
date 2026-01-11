#include "Validation.h"
#include <cctype>

// ============================================
// VALIDATION FUNCTIONS
// ============================================

bool isValidCNIC(const string& cnic)
{
    if (cnic.size() != 13)
        return false;

    for (char c : cnic)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

bool isValidDate(const string& date)
{
    if (date.size() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

bool isValidEmail(const string& email)
{
    bool hasAt = false;
    bool hasDot = false;
    
    for (size_t i = 0; i < email.size(); i++)
    {
        if (email[i] == '@') hasAt = true;
        if (hasAt && email[i] == '.') hasDot = true;
    }
    
    return hasAt && hasDot && email.size() > 5;
}

bool isValidPhone(const string& phone)
{
    if (phone.size() < 10 || phone.size() > 15) return false;
    
    for (char c : phone)
    {
        if (!isdigit(c) && c != '+' && c != '-' && c != ' ')
            return false;
    }
    return true;
}

bool isNumeric(const string& str)
{
    if (str.empty()) return false;
    
    for (char c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}