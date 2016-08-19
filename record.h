#ifndef RECORD_H
#define RECORD_H

#include <string>

using namespace std;

class Record
{
	public:
		Record();
		Record(int accountNumber, string firstName, string lastName, double balance);
		void menu();
		void addRecord();
		void findRecord(string key);
		void editRecord(string key);
		void deleteRecord(string key);
		void deposit(string key);
		void withdraw(string key);
		void checkAccountNumber(int key);
		int getAccountNumber() const;
		string getFirstName() const;
		string getLastName() const;
		double getBalance() const;
		void readRecord() const;

	private:
		int accountNumber;
		string firstName;
		string lastName;
		double balance;
};

#endif