#include "LoanTypes.h"
#include "Chatbot.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // Vectors to hold chatbot responses
    vector<string> utteranceKeys;
    vector<string> utteranceValues;

    // Load chatbot responses from file
    loadUtterances(utteranceKeys, utteranceValues, "utterances.txt");

    // Load all loan options from files
    vector<HomeLoanOption> homeOptions = loadHomeLoanData("Home.txt");
    vector<CarLoanOption> carOptions = loadCarLoanData("Car.txt");
    vector<ScooterLoanOption> scooterOptions = loadScooterLoanData("Scooter.txt");

    // Start the chatbot
    runChatbot(utteranceKeys, utteranceValues, homeOptions, carOptions, scooterOptions);

    return 0;
}