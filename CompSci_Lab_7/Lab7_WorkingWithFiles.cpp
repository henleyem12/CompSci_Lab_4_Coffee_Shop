// Lab 7: Working with Files
// Reads restaurant menu prices from menu.txt, saves receipts, and logs inventory.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cctype>
using namespace std;

int main() {
    const int ITEM_COUNT = 5;
    const int STARTING_INVENTORY = 50;
    string foodNames[ITEM_COUNT];
    double smallPrices[ITEM_COUNT], mediumPrices[ITEM_COUNT], largePrices[ITEM_COUNT];
    int itemsSold[ITEM_COUNT] = {0};

    // Read each item name and its three prices from the text file.
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Error: Could not open menu.txt.\n";
        return 1;
    }
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (!getline(menuFile, foodNames[i]) ||
            !(menuFile >> smallPrices[i] >> mediumPrices[i] >> largePrices[i])) {
            cout << "Error: menu.txt is missing or contains invalid data.\n";
            return 1;
        }
        menuFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    menuFile.close();

    // Keep receipts from all customers in one file.
    ofstream receiptFile("receipts.txt");
    if (!receiptFile) {
        cout << "Error: Could not create receipts.txt.\n";
        return 1;
    }

    double grandTotalSales = 0.0;
    int totalCustomers = 0;
    char nextCustomerChoice;

    // OUTER LOOP: One transaction per customer.
    do {
        string customerName;
        char memberInput;
        cout << "\n==================================================\n";
        cout << "                 NEW CUSTOMER ORDER\n";
        cout << "==================================================\n";
        cout << "Enter customer name: ";
        getline(cin, customerName);
        cout << "Is the customer a member? (y/n): ";
        cin >> memberInput;

        double totalSubtotal = 0.0;
        string orderAccumulator = "";
        bool ordering = true;

        // INNER LOOP: Customer can add multiple menu items.
        while (ordering) {
            cout << "\n--- MENU OPTIONS ---\n";
            for (int i = 0; i < ITEM_COUNT; i++) {
                cout << i + 1 << ". " << foodNames[i] << " (S $"
                     << fixed << setprecision(2) << smallPrices[i]
                     << ", M $" << mediumPrices[i]
                     << ", L $" << largePrices[i] << ")\n";
            }
            cout << "0. Checkout\n";
            cout << "Enter choice (0-" << ITEM_COUNT << "): ";
            int selection;
            cin >> selection;
            while (cin.fail() || selection < 0 || selection > ITEM_COUNT) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Enter 0-" << ITEM_COUNT << ": ";
                cin >> selection;
            }
            if (selection == 0) {
                ordering = false;
            } else {
                int itemIndex = selection - 1;
                if (itemsSold[itemIndex] == STARTING_INVENTORY) {
                    cout << "Sorry, that item is sold out.\n";
                    continue;
                }
                char size;
                int quantity;
                double unitPrice;
                cout << "Enter size (S/M/L): ";
                cin >> size;
                while (size != 'S' && size != 's' && size != 'M' &&
                       size != 'm' && size != 'L' && size != 'l') {
                    cout << "Invalid size. Enter S, M, or L: ";
                    cin >> size;
                }
                if (size == 'S' || size == 's') unitPrice = smallPrices[itemIndex];
                else if (size == 'M' || size == 'm') unitPrice = mediumPrices[itemIndex];
                else unitPrice = largePrices[itemIndex];

                cout << "Enter quantity: ";
                cin >> quantity;
                while (cin.fail() || quantity <= 0 ||
                       quantity > STARTING_INVENTORY - itemsSold[itemIndex]) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid quantity or not enough inventory ("
                         << STARTING_INVENTORY - itemsSold[itemIndex]
                         << " left). Enter quantity: ";
                    cin >> quantity;
                }
                double subtotal = quantity * unitPrice;
                totalSubtotal += subtotal;
                itemsSold[itemIndex] += quantity;

                ostringstream itemStream;
                itemStream << left << setw(22) << foodNames[itemIndex]
                           << "(" << static_cast<char>(toupper(size)) << ") "
                           << "x" << quantity << " @ $" << fixed << setprecision(2)
                           << unitPrice << " = $" << subtotal << "\n";
                orderAccumulator += itemStream.str();
                cout << "--> " << foodNames[itemIndex] << " added to order!\n";
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string cashierNotes;
        cout << "Enter cashier notes: ";
        getline(cin, cashierNotes);
        double discount = 0.0;
        if (memberInput == 'y' || memberInput == 'Y') {
            discount = totalSubtotal * 0.10;
        }
        double finalTotal = totalSubtotal - discount;
        int loyaltyPoints = static_cast<int>(finalTotal / 3.0);
        string stars(loyaltyPoints, '*');

        // Build the receipt once, then print identical text to both destinations.
        ostringstream receipt;
        receipt << "\n========================================\n";
        receipt << "             STORE RECEIPT\n";
        receipt << "========================================\n";
        receipt << "Customer: " << customerName << "\n";
        receipt << "----------------------------------------\n";
        if (orderAccumulator.empty()) receipt << "No items purchased.\n";
        else receipt << orderAccumulator;
        receipt << "----------------------------------------\n";
        receipt << fixed << setprecision(2);
        receipt << "Subtotal: $" << totalSubtotal << "\n";
        if (discount > 0.0) receipt << "Member Discount (10%): -$" << discount << "\n";
        receipt << "Final Total: $" << finalTotal << "\n";
        receipt << "Notes: " << cashierNotes << "\n";
        receipt << "Loyalty Points Earned: " << loyaltyPoints << "\n";
        receipt << "Points Display: " << stars << "\n";
        receipt << "========================================\n";
        cout << receipt.str();
        receiptFile << receipt.str();

        grandTotalSales += finalTotal;
        totalCustomers++;
        cout << "\nIs there another customer? (y/n): ";
        cin >> nextCustomerChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (nextCustomerChoice == 'y' || nextCustomerChoice == 'Y');
    receiptFile.close();

    cout << "\n========================================\n";
    cout << "          END OF DAY SUMMARY\n";
    cout << "========================================\n";
    cout << "Total Customers Served: " << totalCustomers << "\n";
    cout << fixed << setprecision(2);
    cout << "Grand Total Sales: $" << grandTotalSales << "\n";

    // Write starting inventory, negative changes, and ending inventory.
    ofstream logFile("inventory_log.txt");
    if (!logFile) {
        cout << "Error: Could not create inventory_log.txt.\n";
        return 1;
    }
    logFile << "Daily Inventory\n";
    logFile << left << setw(24) << "Item" << right << setw(8) << "Start"
            << setw(9) << "Change" << setw(8) << "End" << "\n";
    for (int i = 0; i < ITEM_COUNT; i++) {
        logFile << left << setw(24) << foodNames[i] << right
                << setw(8) << STARTING_INVENTORY
                << setw(9) << -itemsSold[i]
                << setw(8) << STARTING_INVENTORY - itemsSold[i] << "\n";
    }
    logFile << "\nTotal Customers: " << totalCustomers << "\n";
    logFile << fixed << setprecision(2) << "Grand Total Sales: $" << grandTotalSales << "\n";
    logFile.close();
    cout << "Receipts saved to receipts.txt and inventory saved to inventory_log.txt.\n";
    return 0;
}
