// Assignment1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//constants
const int NUM_ITEMS = 5;

//Declaration of Inventory structure

struct Inventory
{
int productID;
string productDescription;
double productPrice;
char productTax;

};

struct CustomerOrder
{
	int orderID;
	int orderAmount;
};

//function prototypes
vector<CustomerOrder> customerOrders();
vector<CustomerOrder> checkDuplicate(vector<CustomerOrder> testOrder);
void processCustomerOrder(Inventory[]);


int main() {
	// create array to hold inventory items
	Inventory currentInventory[NUM_ITEMS];
	//file that holds the inventory
	ifstream inFile;

	//open the input file
	inFile.open("Invent.txt");

	//Add each inventory item to the inventory array
	for (int i = 0; i < NUM_ITEMS; i++) {
		inFile >> currentInventory[i].productID;
		inFile >> currentInventory[i].productDescription;
		inFile >> currentInventory[i].productPrice;
		inFile >> currentInventory[i].productTax;
	}


	//Process and print the customer order
	processCustomerOrder(currentInventory);



	//close the infile
	inFile.close();

	//pause the window to stay open
	cin.get();

	return 0;
}

//Function to process customer orders
vector<CustomerOrder> customerOrders() {

	//create vector to hold customer order ID
	vector<CustomerOrder> customerOrder;

	//hold index for acessing vector
	int i = 0;

	//create a customer order instance
	CustomerOrder newCustomerOrder;
	newCustomerOrder.orderID = 1;


	//loop to get customer order
	while (newCustomerOrder.orderID != 0) {
		//Ask for customer order
		cout << "Enter the order ID and amount to be order or 0 to end" << endl;

		//save their order in the vector
		cin >> newCustomerOrder.orderID;
		if (newCustomerOrder.orderID == 0) {
			break;
		}
		cin >> newCustomerOrder.orderAmount;
		while (newCustomerOrder.orderAmount < 1 || newCustomerOrder.orderAmount > 100) {
			//Ask for customer order
			cout << "Enter the order ID and amount to be ordered(1 to 100) or 0 to end" << endl;

			//save their order in the vector
			cin >> newCustomerOrder.orderID;
			if (newCustomerOrder.orderID == 0) {
				break;
			}
			cin >> newCustomerOrder.orderAmount;
		}
		customerOrder.push_back(newCustomerOrder);

		//increment i to save in next slot of vector
		i++;
	}

	return customerOrder;
}

//function to check duplicates in the customer order
vector<CustomerOrder> checkDuplicate(vector<CustomerOrder> testOrder) {
	//loop through the order vector and find if any duplicates
	//only if order size is > 1
	if (testOrder.size() > 1) {
		for (int i = 0; i < (testOrder.size() - 1); i++) {
			for (int j = i+1; j < testOrder.size(); j++) {
				if (testOrder[i].orderID == testOrder[j].orderID) {
					//if duplicate found erase it
					testOrder.erase(testOrder.begin() + j);
					j--;
				}
			}
		}
	}

	return testOrder;

}

//function to process the customers order and print it to the receipt
void processCustomerOrder(Inventory currentInventory[NUM_ITEMS]) {

	//file for printing receipts
	ofstream outputFile;

	//open a file name receipts
	outputFile.open("Receipts.txt");

	//keep track of customer number
	int customerNumber = 1;

	//Ask to add additional customers
	char answer;

	do {
		//Take a customers order
		
		vector<CustomerOrder> newCustomer = customerOrders();

		//Make sure there aren't any duplicate orders
		vector<CustomerOrder> validOrder = checkDuplicate(newCustomer);

		//print to the reciepts file for the order
		outputFile << "\n\nCustomer " << customerNumber << endl;

		//keep track of item totals and add tax if necessary
		double itemTotal = 0.0;
		double subTotal = 0.0;
		double tax = 0.0;
		double total = 0.0;
		//boolean to say item was found
		bool itemFound = false;

		//Go through the customer order, if it matches inventory order then calculate the order
		for (int i = 0; i < validOrder.size(); i++) {
			for (int j = 0; j < NUM_ITEMS; j++) {
				if (validOrder[i].orderID == currentInventory[j].productID) {
					itemTotal = currentInventory[j].productPrice * validOrder[i].orderAmount;
					subTotal += itemTotal;
					if (currentInventory[j].productTax == 'T') {
						tax += itemTotal * .075;
					}
					outputFile << currentInventory[j].productDescription << " " << validOrder[i].orderAmount << " @ " << currentInventory[j].productPrice << " " << itemTotal << " " << currentInventory[j].productTax << endl;
					itemFound = true;
				}

			}


			if (itemFound == false) {
				outputFile << "*** item " << validOrder[i].orderID << " not in inventory ***" << endl;
			}

			itemFound = false;
			
			
		}

		//print subtotal
		outputFile << "\n\t\tSubtotal: " << subTotal << endl;
		//print tax
		outputFile << "\t\tTax: " << tax << endl;

		//calculate total
		total = subTotal + tax;

		//print total
		outputFile << "\n\tTotal: " << total << endl << endl;

		customerNumber++;

		cout << "Would you like to add another customer? (Y or N)" << endl;
		cin >> answer;
		answer = toupper(answer);
	} while (answer != 'N');

	//close the outfile
	outputFile.close();

}
