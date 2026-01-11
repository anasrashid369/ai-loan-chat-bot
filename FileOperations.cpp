#include "FileOperations.h"
#include "LoanTypes.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <direct.h>
#include <algorithm>

using namespace std;

// ============================================
// FILE VALIDATION FUNCTIONS
// ============================================

bool fileExists(const string& path)
{
    ifstream file(path);
    return file.good();
}

bool isValidImageFile(const string& path)
{
    string ext = getFileExtension(path);

    // Convert to lowercase for comparison
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    return (ext == ".jpg" || ext == ".jpeg" || ext == ".png" ||
        ext == ".bmp" || ext == ".gif" || ext == ".tiff");
}

string getFileExtension(const string& path)
{
    size_t dotPos = path.find_last_of('.');
    if (dotPos == string::npos)
        return "";

    return path.substr(dotPos);
}

string getFileName(const string& path)
{
    size_t slashPos = path.find_last_of("/\\");
    if (slashPos == string::npos)
        return path;

    return path.substr(slashPos + 1);
}

// ============================================
// DIRECTORY OPERATIONS
// ============================================

bool createDirectory(const string& path)
{
    struct stat info;

    // Check if directory already exists
    if (stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
    {
        return true;
    }

    // Create directory
    int result = _mkdir(path.c_str());

    if (result == 0)
    {
        return true;
    }

    return false;
}

// ============================================
// FILE COPY OPERATION
// ============================================

bool copyFile(const string& source, const string& destination)
{
    // Open source file in binary mode
    ifstream src(source, ios::binary);
    if (!src.is_open())
    {
        cout << COLOR_RED << "Error: Could not open source file: " << source << COLOR_RESET << endl;
        return false;
    }

    // Open destination file in binary mode
    ofstream dst(destination, ios::binary);
    if (!dst.is_open())
    {
        cout << COLOR_RED << "Error: Could not create destination file: " << destination << COLOR_RESET << endl;
        src.close();
        return false;
    }

    // Copy file contents
    dst << src.rdbuf();

    // Check for errors
    bool success = src.good() && dst.good();

    src.close();
    dst.close();

    if (success)
    {
        cout << COLOR_GREEN << "File copied successfully!" << COLOR_RESET << endl;
    }
    else
    {
        cout << COLOR_RED << "Error occurred during file copy." << COLOR_RESET << endl;
    }

    return success;
}