#include "stdafx.h"
#include <stdio.h>
#include <iostream>

using namespace std;

class bankAccount
{
protected:
	int choose_account;
	float balance = 0;
	int acctNum;
	const char *acctName = new char[30];

public:
	int yearTerm;
	void display_acctinfo();
	float interest = 0;
	virtual int withdraw(float w);
	virtual int deposit_funds(float d);
};

int bankAccount::deposit_funds(float d)
{
	if (d < 0)
	{
		cout << "Can't take negative amount" << endl;
		return(-1);
	}
	else
	{
		balance += d;
	}
	return 0;
}

int bankAccount::withdraw(float w)
{
	if (w < 0)
	{
		cout << " Sorry not enough money in your account" << "\n" << endl;
		return(-1);
	}
	else if (w > balance)
	{
		cout << "Sorry, you can't withdraw more than what's in your balance" << "\n" << endl;
		return(-1);
	}
	else
	{
		balance -= w;
		cout << "successful withdrawl. Your new balance is: $" << balance << "\n" << endl;
		return(0);
	}
}

void bankAccount::display_acctinfo()
{
	if (choose_account == 1) {
		acctName = "Saving Account";
	}
	else if (choose_account == 2)
	{
		acctName = "Checking account ";
	}
	else if (choose_account == 3)
	{
		acctName = "Certificate of Deposit";
	}
	else
	{
		cout << "Does not exist" << endl;
	}
	cout << "Bank account name: " << acctName << endl;
	cout << "Bank account number: " << acctNum << endl;
	cout << "Your Interest rate: " << interest << "%" << endl;
	cout << "Your balance is: $" << balance << "\n" << endl;
}

class saving_acct : public bankAccount
{
public:
	saving_acct()
	{
		choose_account = 1;
	}
	void chkbal()
	{
		if (balance >= 10000)
		{
			interest = 2;
		}
		else
		{
			interest = 1;
		}
	}
	void interest_calc()
	{
		balance += (balance * (interest / 100));

		chkbal();
	}

	int deposit_funds(float d)
	{
		char acctNum;
		cout << "Enter the account number for savings account: " << flush;
		cin >> acctNum;
		cout << "Enter amount to deposit to savings: $" << flush;
		cin >> d;

		cin.clear();
		cin.ignore();

		bankAccount::deposit_funds(d);
		chkbal();
		return 0;
	}
	int withdraw(float w)
	{
		cout << "Please enter amount to withdraw from saving: $" << flush;
		cin >> w;

		cin.clear();
		cin.ignore();

		bankAccount::withdraw(w);
		chkbal();
		return 0;
	}

};

class checking_account : public bankAccount
{
public:
	checking_account()
	{
		choose_account = 2;
	};
	void chkbal()
	{
		if (balance < 500)
		{
			balance = balance - 5;
			cout << "Your balance is under $500 and you have been charged a $5 fee." << "\n" << endl;
		}
	}
	char input;
	void order_check()
	{
		cout << "Would you like to order checks?" << endl;
		cout << "Press Y for yes or Press N for no to continue" << flush;
		cin >> input;

		cin.clear();
		cin.ignore();

		if (input != 'n')
		{
			balance -= 15;
			cout << "Your balance is: " << balance << "\n" << endl;
		}
		else
		{
			cout << "Continue" << endl;
		}
	}

	int deposit_funds(float d)
	{
		char acctNum;
		cout << "Enter the account number for checking account: " << flush;
		cin >> acctNum;
		cout << "Enter amount to deposit to checking: $" << flush;
		cin >> d;

		cin.clear();
		cin.ignore();

		bankAccount::deposit_funds(d);
		chkbal();
		return 0;
	}

	int withdraw(float w)
	{
		cout << "Please enter amount to withdraw checking: $" << flush;
		cin >> w;

		cin.clear();
		cin.ignore();

		bankAccount::withdraw(w);
		chkbal();
		return 0;
	}

};


class cd : public bankAccount
{
public:
	cd()
	{
		choose_account = 3;
	}
	void checkterm(int term)
	{
		yearTerm = term;
		cout << "Enter number of terms for CD: " << flush;
		cin >> term;

		cin.clear();
		cin.ignore();

		if (term >= 5)
		{
			interest = 10;
		}
		else
		{
			interest = 5;
		}
	}
	cd(int term)
	{

		checkterm(term);
	}
	void interest_calc()
	{
		balance = balance + (balance * (interest / 100) / 12);
	}

	int withdraw(float w)
	{
		int penalty = 0.10;
		cout << "Please enter amount to withdraw CD: $" << flush;
		cin >> w;

		cin.clear();
		cin.ignore();

		balance = balance - (balance *penalty);
		bankAccount::withdraw(w);
		checkterm(yearTerm);
		return 0;
	}
	int deposit_funds(float d)
	{
		char acctNum;
		cout << "Enter the account number for certificate of deposit: $" << flush;
		cin >> acctNum;
		cout << "Enter amount to deposit to certificate of deposit: $" << flush;
		cin >> balance;

		cin.clear();
		cin.ignore();

		bankAccount::deposit_funds(d);
		checkterm(yearTerm);
		return 0;
	}

};
int i;
int main()
{
	cout << "Saving (1)  " << "Checking (2)  " << "COD (3)" << endl;
	saving_acct new_svacct;
	checking_account newCheck;
	cd cod;

	new_svacct.deposit_funds(0);


	newCheck.deposit_funds(0);


	cod.deposit_funds(0);

	new_svacct.display_acctinfo();
	newCheck.display_acctinfo();
	cod.display_acctinfo();


	new_svacct.interest_calc();
	cod.interest_calc();

	newCheck.order_check();

	newCheck.withdraw(0);
	new_svacct.withdraw(0);
	cod.withdraw(0);

	new_svacct.display_acctinfo();
	newCheck.display_acctinfo();
	cod.display_acctinfo();


	
	while (i != 'y')
	{

		cout << "press y to exit" << endl;
		cin >> i;
		break;
	}

	return 0;
}