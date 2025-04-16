#include "../include/Calculator.h"

// Gets current time in YYYY-MM-DD HH:MM:SS format
string getCurrentTimestamp() {
  time_t now = time(nullptr);  // Get current time
  char buffer[80];             // Buffer to hold formatted time
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
  return string(buffer);  // Convert to string and return
}

// Ensures 'data' directory exists for file storage
void ensureDataDirectoryExists() {
  try {
    if (!fs::exists("data")) {  // Check if directory exists
      fs::create_directory("data");  // Create if missing
    }
  } catch (const fs::filesystem_error& e) {
    cerr << "Directory creation error: " << e.what() << endl;
  }
}

// Basic math operations implementations
int add(int x, int y) { return x + y; }  // Simple addition
int sub(int x, int y) { return x - y; }  // Simple subtraction
int multi(int x, int y) { return x * y; }  // Simple multiplication

// Safe division with zero checking
int mydiv(int x, int y) {
  if (y == 0) throw runtime_error("Division by zero");  // Prevent crash
  return x / y;  // Return integer division result
}

// Formatted division output with remainder
string div_print(int x, int y) {
  if (y == 0) return "Error: Division by zero";  // Handle zero case
  int quotient = x / y;  // Get whole number result
  int remainder = x % y;  // Get remainder
  return to_string(x) + " / " + to_string(y) + " = " + 
         to_string(quotient) + " R " + to_string(remainder);
}

// Calculates nth root using Newton-Raphson method
double nthRoot(double value, int n, double tolerance, int maxIterations) {
  // Validate inputs
  if (value < 0 && n % 2 == 0) throw invalid_argument("Even root of negative");
  if (n <= 0) throw invalid_argument("Root index must be positive");

  double x = value / n;  // Initial guess
  // Iteratively improve guess
  for (int i = 0; i < maxIterations; ++i) {
    double prev = x;  // Store previous value
    x = ((n - 1) * x + value / pow(x, n - 1)) / n;  // Newton-Raphson formula
    if (abs(x - prev) < tolerance) break;  // Stop if sufficiently accurate
  }
  return x;  // Return final approximation
}

// Saves calculation history to file
void saveHistoryToFile(const vector<Calculation>& history, const fs::path& filename) {
  ensureDataDirectoryExists();  // Make sure directory exists
  ofstream outFile(filename);  // Open output file
  
  if (!outFile) {  // Check if file opened successfully
    cerr << "Failed to save history to " << filename << endl;
    return;
  }

  // Write each calculation as pipe-separated values
  for (const auto& calc : history) {
    outFile << calc.timestamp << "|"
            << calc.operation << "|"
            << calc.expression << "|"
            << calc.result << "\n";
  }
}

// Loads calculation history from file
void loadHistoryFromFile(vector<Calculation>& history, const fs::path& filename) {
  ifstream inFile(filename);  // Open input file
  if (!inFile) return;  // Silently fail if file doesn't exist

  history.clear();  // Clear current history
  string line;  // Buffer for each line
  
  // Parse each line into Calculation objects
  while (getline(inFile, line)) {
    Calculation calc;
    istringstream iss(line);  // Create string stream for parsing
    // Extract fields using pipe delimiter
    getline(iss, calc.timestamp, '|');
    getline(iss, calc.operation, '|');
    getline(iss, calc.expression, '|');
    getline(iss, calc.result);
    history.push_back(calc);  // Add to history vector
  }
}

// Displays calculation history
void displayHistory(const vector<Calculation>& history) {
  if (history.empty()) {  // Handle empty history
    cout << "No calculations in history.\n";
    return;
  }

  cout << "\n=== Calculation History ===\n";
  // Print each entry in formatted way
  for (const auto& calc : history) {
    cout << calc.timestamp << " | "
         << calc.operation << " | "
         << calc.expression << " = "
         << calc.result << "\n";
  }
}

// Handles basic operations menu
int Basic_ops(vector<Calculation>& history) {
  cout << "\n--- Basic Operations ---\n";
  cout << "(A)ddition, (S)ubtraction, (M)ultiplication, (D)ivision: ";
  char op;
  cin >> op;  // Get user choice

  int x, y;
  cout << "Enter first number: ";
  cin >> x;
  cout << "Enter second number: ";
  cin >> y;

  Calculation calc;  // Create new history entry
  calc.timestamp = getCurrentTimestamp();  // Set current time

  try {
    switch (tolower(op)) {  // Handle case-insensitive input
      case 'a':
        calc.operation = "Addition";
        calc.expression = to_string(x) + " + " + to_string(y);
        calc.result = to_string(add(x, y));
        break;
      case 's':
        calc.operation = "Subtraction";
        calc.expression = to_string(x) + " - " + to_string(y);
        calc.result = to_string(sub(x, y));
        break;
      case 'm':
        calc.operation = "Multiplication";
        calc.expression = to_string(x) + " * " + to_string(y);
        calc.result = to_string(multi(x, y));
        break;
      case 'd':
        calc.operation = "Division";
        calc.expression = to_string(x) + " / " + to_string(y);
        calc.result = div_print(x, y);
        break;
      default:
        cout << "Invalid operation.\n";
        return 0;
    }
    cout << "Result: " << calc.result << "\n";
    history.push_back(calc);  // Add to history
  } catch (const exception& e) {
    cout << "Error: " << e.what() << "\n";
  }
  return 0;
}

// Handles advanced operations menu
int AdditionalOps(vector<Calculation>& history) {
  cout << "\n--- Advanced Operations ---\n";
  cout << "(P)ower, (R)oot: ";
  char op;
  cin >> op;

  Calculation calc;
  calc.timestamp = getCurrentTimestamp();

  try {
    if (tolower(op) == 'p') {  // Power operation
      int base, exp;
      cout << "Enter base: ";
      cin >> base;
      cout << "Enter exponent: ";
      cin >> exp;
      calc.operation = "Power";
      calc.expression = to_string(base) + "^" + to_string(exp);
      calc.result = to_string(pow(base, exp));
      cout << "Result: " << calc.result << "\n";
    } else if (tolower(op) == 'r') {  // Root operation
      double num;
      int root;
      cout << "Enter number: ";
      cin >> num;
      cout << "Enter root index: ";
      cin >> root;
      calc.operation = "Root";
      calc.expression = to_string(root) + "√" + to_string(num);
      calc.result = to_string(nthRoot(num, root));
      cout << "Result: " << calc.result << "\n";
    } else {
      cout << "Invalid operation.\n";
      return 0;
    }
    history.push_back(calc);  // Add to history
  } catch (const exception& e) {
    cout << "Error: " << e.what() << "\n";
  }
  return 0;
}