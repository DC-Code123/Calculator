#include "../include/Calculator.h"

int main() {
  vector<Calculation> history;  // Stores calculation history
  loadHistoryFromFile(history);  // Load previous history

  while (true) {  // Main program loop
    cout << "\n===== Calculator Menu =====\n";
    cout << "(B)asic, (A)dvanced, (H)istory, (E)xit\n";
    cout << "Choice: ";
    
    char choice;
    cin >> choice;  // Get user selection

    switch (tolower(choice)) {  // Handle case-insensitive input
      case 'b':
        Basic_ops(history);  // Basic math operations
        break;
      case 'a':
        AdditionalOps(history);  // Advanced operations
        break;
      case 'h':
        displayHistory(history);  // Show history
        break;
      case 'e':
        saveHistoryToFile(history);  // Save before exiting
        cout << "Goodbye!\n";
        return 0;  // Exit program
      default:
        cout << "Invalid choice. Try again.\n";
    }
  }
}