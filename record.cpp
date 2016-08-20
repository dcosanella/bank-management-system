#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "record.h"

using namespace std;

Record::Record() {
	accountNumber = 0;
	balance = 0;
}

Record::Record(int accountNumber, string firstName, string lastName, double balance) {
	this->accountNumber = accountNumber;
	this->firstName = firstName;
	this->lastName = lastName;
	this->balance = balance;
}

void Record::addRecord() {
	int accountNumber;
	string firstName;
	string lastName;
	double balance;
	cout << "Create an account number: ";
	cin >> accountNumber;
	checkAccountNumber(accountNumber);

	string space;
	getline(cin, space);
	cout << "Enter your first name: ";
	getline(cin, firstName);
	cout << "Enter your last name: ";
	getline(cin, lastName);
	cout << "Enter your current balance (dollars & cents): ";
	cin >> balance;

	ofstream data;
	data.open("data.txt", ios::app);

	data << "Account Number: " << accountNumber << "\n";
	data << "First Name: " << firstName << "\n";
	data << "Last Name: " << lastName << "\n";
	data.precision(2);
	data << "Balance: $" << fixed << balance << "\n";
	data << "\n";

	data.close();
	system("clear");
	cout << "Bank account " << accountNumber << " has been created." << endl;
	menu();
}

void Record::menu() {
	cout << "\n***** Bank Management System *****" << endl;
	cout << "Select an option below: (1-6)" << endl;
	cout << "	1. Add a bank account" << endl;
	cout << "	2. Show an existing bank account" << endl;
	cout << "	3. Edit a bank account" << endl;
	cout << "	4. Delete a bank account" << endl;
	cout << "	5. Make transactions" << endl;
	cout << "	6. Exit" << endl;

	int i;
	cin >> i;

	switch(i) {
		case 1:
		{
			Record record;
			record.addRecord();
			break;
		}
		case 2:
		case 3:
		case 4:
		case 5:
		{
			string number;
			cout << "Enter an account number: ";
			cin >> number;
			Record record;
			if(i == 2) {
				record.findRecord(number);
			}
			else if(i == 3) {
				record.editRecord(number);
			}
			else if(i == 4) {
				record.deleteRecord(number);
			}
			else if(i == 5) {
				if(!(checkAccount(number))) {
					menu();
				}
				cout << "Choose a type of transaction" << endl;
				cout << "	1. Deposit" << endl;
				cout << "	2. Withdraw" << endl;

				int j;
				cin >> j;

				switch(j) {
					case 1:
					{
						record.deposit(number);
					}
					case 2:
					{
						record.withdraw(number);
					}
				}
			}
				
			break;
		}
		case 6:
		{
			system("clear");
			exit(0);
		}
		default:
			system("clear");
			cout << i << " is not a valid command. Please try again" << endl;
			i = 0;
			menu();
	}
}

void Record::findRecord(string key) {
	string line;
	int i = 0;
	ifstream file;
	file.open("data.txt");
	while(getline(file, line)) {
		if(line == "Account Number: " + key) {
			i++;
			system("clear");
			cout << line << endl;
			string record;
			while(getline(file, record) && record != "") {
				cout << record << endl;
			}
			break;
		}
	}
	if(i == 0) {
		system("clear");
		cout << "Account Number " << key << " not found." << endl;
	}
	file.close();
	menu();
}

void Record::editRecord(string key) {
	if(!(checkAccount(key))) {
		menu();
	}

	system("clear");
	cout << "Which part of account number " << key << " would you like to edit?" << endl;
	cout << "	1. First Name" << endl;
	cout << "	2. Last Name" << endl;
	cout << "	3. Exit" << endl;

	int i;
	cin >> i;

	switch(i) {
		case 1:
		{
			string line;
			ifstream file;
			ofstream data;
			file.open("data.txt");
			data.open("temp.txt");
			while(getline(file, line)) {
				data << line << "\n";
				if(line == "Account Number: " + key) {
					cout << "I am here!!!!!" << endl;
					string record;
					while(getline(file, record) && record != "") {
						cout << "Enter your first name: ";
						string name;
						cin >> name;

						if(record.find("First") != string::npos) {
							data << "First Name: " << name << "\n";
							while(getline(file, line)) {
								data << line << "\n";
							}
						}
					}
				}
			}
			file.close();
			remove("data.txt");
			data.close();
			rename("temp.txt", "data.txt");
			menu();
			break;
		}
		case 2:
		{
			string line;
			ifstream file;
			ofstream data;
			file.open("data.txt");
			data.open("temp.txt");
			while(getline(file, line)) {
				data << line << "\n";
				if(line == "Account Number: " + key) {
					cout << "I am here!!!!!" << endl;
					string record;
					while(getline(file, record) && record != "") {
						if(record.find("First") != string::npos) {
							data << record << "\n";
						}

						if(record.find("Last") != string::npos) {
							cout << "Enter your last name: ";
							string name;
							cin >> name;
							data << "Last Name: " << name << "\n";
							while(getline(file, line)) {
								data << line << "\n";
							}
						}
					}
				}
			}
			file.close();
			remove("data.txt");
			data.close();
			rename("temp.txt", "data.txt");
			menu();
			break;
		}
		case 3:
		{
			menu();
		}
	}
}

void Record::deleteRecord(string key) {
	if(!(checkAccount(key))) {
		menu();
	}

	cout << "Delete record with account number " << key << "? (y/n)" << endl;
	string choice;
	cin >> choice;
	if(choice == "y") {
		string line;
		ifstream file;
		ofstream data;
		file.open("data.txt");
		data.open("temp.txt");
		while(getline(file, line)) {
			if(line != "Account Number: " + key) {
				data << line << "\n";
			}
			else {
				string record;
				while(getline(file, record)) {
					if(record.find("Account") != string::npos) {
						data << record << "\n";
						while(getline(file, line)) {
							data << line << "\n";
						}
					}
				}
			}
		}
		ifstream numbers;
		numbers.open("numbers.txt");
		ofstream tempNumbers;
		tempNumbers.open("tempNumbers.txt");
		string number;
		while(getline(numbers, number)) {
			if(number != key) {
				tempNumbers << number << endl;
			}
		}
		file.close();
		remove("data.txt");
		data.close();
		rename("temp.txt", "data.txt");
		numbers.close();
		remove("numbers.txt");
		tempNumbers.close();
		rename("tempNumbers.txt", "numbers.txt");
		cout << "Bank account number " << key << " has been deleted.\n\n";
		menu();
	}
	else if(choice == "n") {
		menu();
	}
}

void Record::deposit(string key) {
	cout << "How much would you like to deposit in bank account " << key << "?" << endl;
	double amount;
	cin >> amount;

	ifstream file;
	ofstream data;
	file.open("data.txt");
	data.open("temp.txt");
	string line;
	double balance;
	while(getline(file, line)) {
		data << line << "\n";
		if(line == "Account Number: " + key) {
			string record;
			while(getline(file, record) && record != "") {
				if(!(record.find("Balance") != string::npos)) {
					data << record << "\n";
				}
				else if(record.find("Balance") != string::npos) {
					record.erase(0, 9);
					cout << "r: " << record << endl;
					balance = atof(record.c_str());
					balance += amount;
					data.precision(2);
					data << "Balance: $" << fixed << balance << "\n\n";
				}
			}
		}
	}
	file.close();
	remove("data.txt");
	data.close();
	rename("temp.txt", "data.txt");
	menu();
}

void Record::withdraw(string key) {
	cout << "How much would you like to withdraw from bank account " << key << "?" << endl;
	double amount;
	cin >> amount;

	ifstream file;
	ofstream data;
	file.open("data.txt");
	data.open("temp.txt");
	string line;
	double balance;
	while(getline(file, line)) {
		data << line << "\n";
		if(line == "Account Number: " + key) {
			string record;
			while(getline(file, record) && record != "") {
				if(!(record.find("Balance") != string::npos)) {
					data << record << "\n";
				}
				else if(record.find("Balance") != string::npos) {
					record.erase(0, 10);
					balance = atof(record.c_str());
					if(amount > balance) {
						cout << "Cannot withdraw " << amount << ". Insufficient funds.";
						menu();
					}
					else {
						balance -= amount;
						data.precision(2);
						data << "Balance: $" << fixed << balance << "\n";
						while(getline(file, line)) {
							data << line << "\n";
						}
					}
				}
			}
		}
	}
	file.close();
	remove("data.txt");
	data.close();
	rename("temp.txt", "data.txt");
	menu();
}

void Record::checkAccountNumber(int key) {
	ifstream file;
	ofstream numbers;
	file.open("numbers.txt");
	numbers.open("numbers.txt", ios::app);
	string line;
	while(getline(file, line) && line != "") {
		int number;
		number = atof(line.c_str());
		if(number == key) {
			cout << "Account number " << key << " already exists. Please try again." << endl;
			addRecord();
		}
	}
	numbers << key << "\n";
	file.close();
	numbers.close();
}

bool Record::checkAccount(string key) {
	bool account = true;
	system("clear");
	ifstream numbers;
	numbers.open("numbers.txt");
	string n;
	int i = 0, j = 0;
	while(getline(numbers, n)) {
		if(n != key) {
			i++;
			j++;
		}
		else {
			j--;
		}
	}
	if(i == j) {
		account = false;
		cout << "Bank account " << key << " does not exist. Returning to main menu." << endl;
		numbers.close();
 	}
 	return account;
}

int Record::getAccountNumber() const {
	return accountNumber;
}

string Record::getFirstName() const {
	return firstName;
}

string Record::getLastName() const {
	return lastName;
}

double Record::getBalance() const {
	return balance;
}

void Record::readRecord() const {
	cout << "Account Number: " << getAccountNumber() << endl;
	cout << "First Name: " << getFirstName() << endl;
	cout << "Last Name: " << getLastName() << endl;
	cout << "Balance: " << getBalance() << endl;
	cout << endl;
}

int main() {
	system("clear");
	Record record;
	record.menu();
}
	