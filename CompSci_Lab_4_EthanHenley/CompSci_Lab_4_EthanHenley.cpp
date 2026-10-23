// CompSci_Lab_4_EthanHenley.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	string foodName;
	char itemCode;
	int quantity;
	double unitPrice;
	char memberInput;
	bool isMember = false;

	// 1. Get information from the User
	cout << "Enter food name: ";
	getline(cin, foodName);

	cout << "Enter item code (single character): ";
	cin >> itemCode;

	cout << "Enter quantity: ";
	cin >> quantity;

	cout << "Enter unit price: ";
	cin >> unitPrice;

	cout << "Are you a member? (y/n): ";
	cin >> memberInput;

	double subtotal = quantity * unitPrice;
	double discount = 0.0;

	if (memberInput == 'y' || memberInput == 'Y') {
		discount = subtotal * 0.10; // 10% discount for members
	}

	double total = subtotal - discount;

	// clear the input before using getline
	cin.ignore();

	string cashierNotes;
	cout << "Enter cashier notes: ";
	getline(cin, cashierNotes);

	// 2. Calculations

	// 3. Format the Receipt
	cout << "\n\n==================================\n";
	cout << "             STORE RECEIPT        \n";
	cout << "======================================\n";


	cout << "\n--- RECIEPT ---" << endl;

	// Force money format to 2 decimal places
	cout << fixed << setprecision(2);

	cout << left << setw(15) << "Item:" << right << setw(10) << foodName << endl;
	cout << left << setw(15) << "Quantity:" << right << setw(10) << quantity << endl;
	cout << left << setw(15) << "Unit Price:" << right << setw(10) << unitPrice << endl;
	cout << "----------------------------------------\n";
	cout << left << setw(15) << "Subtotal:" << right << setw(10) << subtotal << endl;

	if (discount > 0) {
		cout << left << setw(15) << "Member Discount (10%):" << right << setw(10) << discount << endl;
	}

	cout << left << setw(15) << "Final Total:" << right << setw(23) << total << endl;
	cout << "----------------------------------------\n";
	cout << left << setw(15) << "Notes: " << right << setw(23) << cashierNotes << endl;
	cout << "=========================================\n";

	// 4. Inventory Audit table (around the bottom-ish)
	cout << "\n----------------------------------------------\n";
	cout << "          INVENTORY AUDIT TABLE                \n";
	cout << "-----------------------------------------------\n";
	cout << left << setw(12) << "Code" << setw(18) << "Item Name" << right << setw(10) << "Stock" << endl;
	cout << "------------------------------------------------\n";
	cout << left << setw(12) << itemCode << setw(18) << foodName << right << setw(10) << quantity << endl;
	cout << "=================================================\n";

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
