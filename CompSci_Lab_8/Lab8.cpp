#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Reads one food item and its three prices from the menu file.
// Parameters: menuFile is the input file. The other variables store
// the food name and prices using references.
// Returns: true if the item was read successfully.
bool readMenuItem(ifstream& menuFile, string& foodName,
    double& small, double& medium, double& large)
{
    if (!getline(menuFile, foodName))
        return false;

    if (!(menuFile >> small >> medium >> large))
        return false;

    menuFile.ignore(1000, '\n');
    return true;
}

// Displays one food item and its prices.
// Parameters: number, food name, and three prices.
// Returns: nothing.
void displayMenuItem(int number, string foodName,
    double small, double medium, double large)
{
    cout << number << ". " << foodName
        << "  $" << small
        << "  $" << medium
        << "  $" << large << "\n";
}

// Displays the complete restaurant menu.
// Parameters: five food names and their prices.
// Returns: nothing.
void displayMenu(
    string food1, double s1, double m1, double l1,
    string food2, double s2, double m2, double l2,
    string food3, double s3, double m3, double l3,
    string food4, double s4, double m4, double l4,
    string food5, double s5, double m5, double l5)
{
    cout << fixed << setprecision(2);
    cout << "\n--- FOOD MENU ---\n";
    cout << "#  Food                  Small   Medium  Large\n";

    displayMenuItem(1, food1, s1, m1, l1);
    displayMenuItem(2, food2, s2, m2, l2);
    displayMenuItem(3, food3, s3, m3, l3);
    displayMenuItem(4, food4, s4, m4, l4);
    displayMenuItem(5, food5, s5, m5, l5);
}

// Gets a valid menu choice from the customer.
// Parameters: none.
// Returns: a number from 0 through 5.
int getChoice()
{
    int choice;

    cout << "Enter 1-5 to order, or 0 to checkout: ";
    cin >> choice;

    while (cin.fail() || choice < 0 || choice > 5)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Enter a number from 0 to 5: ";
        cin >> choice;
    }

    return choice;
}

// Gets a valid food size.
// Parameters: none.
// Returns: S, M, or L (uppercase or lowercase).
char getSize()
{
    char size;

    cout << "Choose size (S/M/L): ";
    cin >> size;

    while (size != 'S' && size != 's' &&
        size != 'M' && size != 'm' &&
        size != 'L' && size != 'l')
    {
        cout << "Enter S, M, or L: ";
        cin >> size;
    }

    return size;
}

// Gets a positive quantity.
// Parameters: none.
// Returns: a positive whole number.
int getQuantity()
{
    int quantity;

    cout << "Quantity: ";
    cin >> quantity;

    while (cin.fail() || quantity <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Enter a positive whole number: ";
        cin >> quantity;
    }

    return quantity;
}

// Determines the price for the selected size.
// Parameters: size and the three available prices.
// Returns: the selected price.
double getPrice(char size, double small,
    double medium, double large)
{
    if (size == 'S' || size == 's')
        return small;

    if (size == 'M' || size == 'm')
        return medium;

    return large;
}

// Selects the food item based on the customer's choice.
// Parameters: choice, all menu information, and reference
// variables that receive the selected food and its prices.
// Returns: nothing.
void selectFood(
    int choice,
    string food1, double s1, double m1, double l1,
    string food2, double s2, double m2, double l2,
    string food3, double s3, double m3, double l3,
    string food4, double s4, double m4, double l4,
    string food5, double s5, double m5, double l5,
    string& foodName, double& small,
    double& medium, double& large)
{
    if (choice == 1)
    {
        foodName = food1;
        small = s1;
        medium = m1;
        large = l1;
    }
    else if (choice == 2)
    {
        foodName = food2;
        small = s2;
        medium = m2;
        large = l2;
    }
    else if (choice == 3)
    {
        foodName = food3;
        small = s3;
        medium = m3;
        large = l3;
    }
    else if (choice == 4)
    {
        foodName = food4;
        small = s4;
        medium = m4;
        large = l4;
    }
    else
    {
        foodName = food5;
        small = s5;
        medium = m5;
        large = l5;
    }
}

// Finds how many of a selected food item have been sold.
// Parameters: choice and the five sold quantities.
// Returns: the quantity sold for that food.
int getSold(int choice, int sold1, int sold2,
    int sold3, int sold4, int sold5)
{
    if (choice == 1) return sold1;
    if (choice == 2) return sold2;
    if (choice == 3) return sold3;
    if (choice == 4) return sold4;

    return sold5;
}

// Updates the sold quantity for the selected food.
// Parameters: choice, quantity, and five sold counters by reference.
// Returns: nothing.
void updateInventory(int choice, int quantity,
    int& sold1, int& sold2, int& sold3,
    int& sold4, int& sold5)
{
    if (choice == 1) sold1 += quantity;
    else if (choice == 2) sold2 += quantity;
    else if (choice == 3) sold3 += quantity;
    else if (choice == 4) sold4 += quantity;
    else sold5 += quantity;
}

// Creates one line describing an ordered item.
// Parameters: food name, size, quantity, and unit price.
// Returns: a formatted string for the receipt.
string createOrderLine(string foodName, char size,
    int quantity, double unitPrice)
{
    double itemTotal = quantity * unitPrice;

    ostringstream line;
    line << fixed << setprecision(2);

    line << foodName << " (" << size << ") x"
        << quantity << " @ $" << unitPrice
        << " = $" << itemTotal << "\n";

    return line.str();
}

// Takes one customer's complete order.
// Parameters: menu information, sold counters by reference,
// and orderText by reference to store the ordered items.
// Returns: the customer's subtotal.
double takeOrder(
    string food1, double s1, double m1, double l1,
    string food2, double s2, double m2, double l2,
    string food3, double s3, double m3, double l3,
    string food4, double s4, double m4, double l4,
    string food5, double s5, double m5, double l5,
    int& sold1, int& sold2, int& sold3,
    int& sold4, int& sold5, string& orderText)
{
    double subtotal = 0.0;
    bool ordering = true;

    while (ordering)
    {
        displayMenu(
            food1, s1, m1, l1,
            food2, s2, m2, l2,
            food3, s3, m3, l3,
            food4, s4, m4, l4,
            food5, s5, m5, l5);

        int choice = getChoice();

        if (choice == 0)
        {
            ordering = false;
            continue;
        }

        string foodName;
        double small = 0.0;
        double medium = 0.0;
        double large = 0.0;

        selectFood(
            choice,
            food1, s1, m1, l1,
            food2, s2, m2, l2,
            food3, s3, m3, l3,
            food4, s4, m4, l4,
            food5, s5, m5, l5,
            foodName, small, medium, large);

        char size = getSize();
        int quantity = getQuantity();

        double unitPrice = getPrice(
            size, small, medium, large);

        int sold = getSold(
            choice, sold1, sold2, sold3,
            sold4, sold5);

        int remaining = 50 - sold;

        // Do not allow orders larger than the available inventory.
        if (quantity > remaining)
        {
            cout << "Only " << remaining
                << " left. Item not added.\n";
            continue;
        }

        updateInventory(
            choice, quantity,
            sold1, sold2, sold3, sold4, sold5);

        subtotal += unitPrice * quantity;

        orderText += createOrderLine(
            foodName, size, quantity, unitPrice);

        cout << "Added " << foodName << "!\n";
    }

    return subtotal;
}

// Calculates the discount for a member.
// Parameters: subtotal and member answer.
// Returns: 10% of the subtotal for members, otherwise zero.
double calculateDiscount(double subtotal, char member)
{
    if (member == 'y' || member == 'Y')
        return subtotal * 0.10;

    return 0.0;
}

// Calculates loyalty points based on the final total.
// Parameters: finalTotal is the amount paid.
// Returns: one point for every three dollars.
int calculatePoints(double finalTotal)
{
    return static_cast<int>(finalTotal / 3.0);
}

// Creates the complete customer receipt.
// Parameters: customer information, order, totals, and notes.
// Returns: the receipt as a string.
string calculateReceipt(string customerName,
    string orderText, double subtotal,
    double discount, string cashierNotes)
{
    double finalTotal = subtotal - discount;
    int points = calculatePoints(finalTotal);

    string stars(points, '*');

    ostringstream receipt;
    receipt << fixed << setprecision(2);

    receipt << "\n========== STORE RECEIPT ==========\n";
    receipt << "Customer: " << customerName << "\n";

    if (orderText.empty())
        receipt << "No items purchased.\n";
    else
        receipt << orderText;

    receipt << "Subtotal: $" << subtotal << "\n";

    if (discount > 0)
        receipt << "Member discount (10%): -$"
        << discount << "\n";

    receipt << "Final total: $" << finalTotal << "\n";
    receipt << "Notes: " << cashierNotes << "\n";
    receipt << "Loyalty Points Earned: " << points << "\n";
    receipt << "Points Display: " << stars << "\n";
    receipt << "===================================\n";

    return receipt.str();
}

// Writes text to a file.
// Parameters: fileName is the output file, text is the content,
// and append decides whether existing content is preserved.
// Returns: true if the file was opened and written successfully.
bool printToFile(string fileName, string text, bool append)
{
    ofstream outputFile;

    if (append)
        outputFile.open(fileName, ios::app);
    else
        outputFile.open(fileName);

    if (!outputFile)
    {
        cout << "Could not open " << fileName << ".\n";
        return false;
    }

    outputFile << text;

    bool success = outputFile.good();
    outputFile.close();

    return success;
}

// Creates one line of the daily inventory report.
// Parameters: food name and quantity sold.
// Returns: a formatted inventory line.
string inventoryLine(string foodName, int sold)
{
    ostringstream line;

    line << left << setw(25) << foodName
        << setw(10) << 50
        << setw(10) << -sold
        << 50 - sold << "\n";

    return line.str();
}

// Creates the complete daily inventory report.
// Parameters: five food names and their sold quantities.
// Returns: the inventory report as a string.
string createInventoryReport(
    string food1, int sold1,
    string food2, int sold2,
    string food3, int sold3,
    string food4, int sold4,
    string food5, int sold5)
{
    ostringstream report;

    report << "DAILY INVENTORY\n";
    report << left << setw(25) << "Item"
        << setw(10) << "Start"
        << setw(10) << "Change"
        << "End\n";

    report << inventoryLine(food1, sold1);
    report << inventoryLine(food2, sold2);
    report << inventoryLine(food3, sold3);
    report << inventoryLine(food4, sold4);
    report << inventoryLine(food5, sold5);

    return report.str();
}

// Main function: reads the menu, serves customers,
// saves receipts, and writes the daily inventory report.
int main()
{
    string food1, food2, food3, food4, food5;

    double s1, m1, l1;
    double s2, m2, l2;
    double s3, m3, l3;
    double s4, m4, l4;
    double s5, m5, l5;

    int sold1 = 0;
    int sold2 = 0;
    int sold3 = 0;
    int sold4 = 0;
    int sold5 = 0;

    // Open and read the menu file.
    ifstream menuFile("menu.txt");

    if (!menuFile)
    {
        cout << "Could not open menu.txt.\n";
        return 1;
    }

    bool menuLoaded = true;

    if (!readMenuItem(menuFile, food1, s1, m1, l1))
        menuLoaded = false;

    if (menuLoaded &&
        !readMenuItem(menuFile, food2, s2, m2, l2))
        menuLoaded = false;

    if (menuLoaded &&
        !readMenuItem(menuFile, food3, s3, m3, l3))
        menuLoaded = false;

    if (menuLoaded &&
        !readMenuItem(menuFile, food4, s4, m4, l4))
        menuLoaded = false;

    if (menuLoaded &&
        !readMenuItem(menuFile, food5, s5, m5, l5))
        menuLoaded = false;

    menuFile.close();

    if (!menuLoaded)
    {
        cout << "The menu file has missing or invalid data.\n";
        return 1;
    }

    // Clear the receipt file at the start of the day.
    if (!printToFile("receipts.txt", "", false))
        return 1;

    double grandTotalSales = 0.0;
    int totalCustomers = 0;
    char nextCustomerChoice;

    // Continue serving customers until the cashier finishes.
    do
    {
        string customerName;
        char memberInput;

        cout << "\nNEW CUSTOMER ORDER\n";
        cout << "Enter customer name: ";
        getline(cin, customerName);

        cout << "Is the customer a member? (y/n): ";
        cin >> memberInput;

        string orderText = "";

        double subtotal = takeOrder(
            food1, s1, m1, l1,
            food2, s2, m2, l2,
            food3, s3, m3, l3,
            food4, s4, m4, l4,
            food5, s5, m5, l5,
            sold1, sold2, sold3,
            sold4, sold5, orderText);

        cin.ignore(1000, '\n');

        string cashierNotes;

        cout << "Enter cashier notes: ";
        getline(cin, cashierNotes);

        double discount = calculateDiscount(
            subtotal, memberInput);

        double finalTotal = subtotal - discount;

        string receipt = calculateReceipt(
            customerName, orderText,
            subtotal, discount, cashierNotes);

        cout << receipt;

        if (!printToFile("receipts.txt", receipt, true))
            return 1;

        grandTotalSales += finalTotal;
        totalCustomers++;

        cout << "Another customer? (y/n): ";
        cin >> nextCustomerChoice;
        cin.ignore(1000, '\n');

    } while (nextCustomerChoice == 'y' ||
        nextCustomerChoice == 'Y');

    // Display the end-of-day summary.
    cout << fixed << setprecision(2);
    cout << "\nEND OF DAY SUMMARY\n";
    cout << "Customers served: " << totalCustomers << "\n";
    cout << "Grand total sales: $" << grandTotalSales << "\n";

    // Create and save the inventory report.
    string inventoryReport = createInventoryReport(
        food1, sold1,
        food2, sold2,
        food3, sold3,
        food4, sold4,
        food5, sold5);

    if (!printToFile("inventory_log.txt", inventoryReport, false))
        return 1;

    cout << "Saved receipts.txt and inventory_log.txt.\n";

    return 0;
}