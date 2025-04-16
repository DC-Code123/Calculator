#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <cmath>
#include <stdexcept>

using namespace std;  // Standard namespace for common C++ functions
namespace fs = filesystem;  // Alias for filesystem namespace

// Structure to store calculation history entries
struct Calculation {
  string operation;    // Type of operation (e.g., "Addition")
  string expression;   // Math expression (e.g., "5 + 3")
  string result;       // Result of calculation (e.g., "8")
  string timestamp;    // When calculation was performed
};

// Basic arithmetic operations
int add(int x, int y);       // Addition
int sub(int x, int y);       // Subtraction
int multi(int x, int y);     // Multiplication
int mydiv(int x, int y);     // Division with error checking
string div_print(int x, int y);  // Formatted division output

// Advanced math operations
double nthRoot(double value, int n, double tolerance = 1e-10, int maxIterations = 1000);

// History management functions
void ensureDataDirectoryExists();  // Creates 'data' directory if needed
void saveHistoryToFile(const vector<Calculation>& history, const fs::path& filename = "data/calc_history.txt");
void loadHistoryFromFile(vector<Calculation>& history, const fs::path& filename = "data/calc_history.txt");
void displayHistory(const vector<Calculation>& history);  // Shows calculation log

// Utility functions
string getCurrentTimestamp();  // Generates current time string

// Menu operation handlers
int Basic_ops(vector<Calculation>& history);  // Basic math menu
int AdditionalOps(vector<Calculation>& history);  // Advanced math menu

#endif