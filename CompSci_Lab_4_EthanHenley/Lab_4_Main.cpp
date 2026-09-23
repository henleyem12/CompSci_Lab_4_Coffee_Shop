#include <iostream>
#include <string>



using namespace std;

int main() {
	string foodName;
	int quantity;
	double price;

	cout << "Enter food name: ";
	getline(cin, foodName);

	cout << "Enter quantity: ";
	cin >> quantity;

	cout << "Enter price per item: ";
	cin >> price;

	double total = quantity * price;

	cout << "/n--- RECIEPT ---" << endl;
	cout << "Item: " << foodName << endl;
	cout << "Quantity: " << quantity << endl;
	cout << "Total Price: $" << total << endl;

	return 0;
}

// test sync by the queen