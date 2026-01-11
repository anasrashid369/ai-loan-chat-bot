// ============================================
// FILE OPERATIONS HEADER FILE
// ============================================
// Contains functions for file validation and copying

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <string>
using namespace std;

// Check if file exists at given path
bool fileExists(const string& path);

// Check if file has valid image extension
bool isValidImageFile(const string& path);

// Create directory if it doesn't exist
bool createDirectory(const string& path);

// Copy file from source to destination
bool copyFile(const string& source, const string& destination);

// Get file extension from path
string getFileExtension(const string& path);

// Get filename from full path
string getFileName(const string& path);

#endif // FILEOPERATIONS_H