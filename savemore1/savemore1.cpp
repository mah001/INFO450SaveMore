

#include "stdafx.h"
#include <string>
#include <iostream>

#include <stdio.h>
#include <iostream>

using namespace std;

struct date { int d, m, y; };
class bankAccount
{

protected:

	double balance = 0;
	const char *acctNum = new char[12];
	const char *acctName = new char[30];

public:
	void display_acctinfo();
	float interest = 0;
	virtual int withdraw(double w);
	virtual int deposit_funds(double d);

};



int bankAccount::deposit_funds(double d)
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
}

int bankAccount::withdraw(double w)
{



	if (w < 0)
	{
		cout << " Sorry, at this time you are 'Broke' not enough money in your account" << endl;
		return(-1);
	}
	else if (w > balance)
	{
		cout << "Sorry, you can't withdraw more than what's in your balance" << endl;
		return(-1);
	}
	else
	{

		balance -= w;
		return(0);
	}
}

void bankAccount::display_acctinfo()
{
	cout << "Bank account name: " << acctName << endl;
	cout << "Bank account number: " << acctNum << endl;
	cout << "Your Interest rate: " << interest << "" << endl;
	cout << "Your balance is: " << balance << "\n" << endl;
}

class checkingAccount : public bankAccount
{
public:
	checkingAccount()
	{
		acctName = "Checking account";
	}
	void chkbal()
	{
		if (balance < 500)
		{
			balance = balance - 5;
			cout << "Your balance is under $500 and you have been charged a $5 fee." << endl;
		}
	}
	void order_check()
	{
		balance -= 15;
	}

	int deposit_funds(double d)
	{
		bankAccount::deposit_funds(d);
		chkbal();
		return 0;
	}

	int withdraw(double w)
	{
		bankAccount::withdraw(w);
		chkbal();
		return 0;
	}
};
class saving_acct : public bankAccount
{
public:
	saving_acct()
	{
		acctName = "Saving Account";
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
		balance /= 12;
		chkbal();
	}

	int deposit_funds(double d)
	{
		bankAccount::deposit_funds(d);
		chkbal();
		return 0;
	}
	int withdraw(double w)
	{
		bankAccount::withdraw(w);
		chkbal();
		return 0;
	}
};

class cd : public bankAccount
{
public:
	int yearTerm;

	void checkterm(int term)
	{

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
		acctName = "Certificate of Deposit";
		checkterm(term);
		yearTerm = term;
	}
	void interest_calc()
	{
		balance = balance + (balance * (interest / 100) / 12);
	}
	void penalty(int p)
	{
		if (p == 1)
		{
			balance = balance - (balance *0.10);
		}
	}
	int withdraw(double w)
	{
		bankAccount::withdraw(w);
		checkterm(yearTerm);
		return 0;
	}
	int deposit_funds(double d)
	{
		bankAccount::deposit_funds(d);
		checkterm(yearTerm);
		return 0;
	}
};
int i;
int main()
{


	saving_acct new_svacct;
	new_svacct.deposit_funds(10000);
	checkingAccount newCheck;
	newCheck.deposit_funds(6000);
	cd CD_e(3);
	CD_e.deposit_funds(10000);

	new_svacct.display_acctinfo();
	newCheck.display_acctinfo();
	CD_e.display_acctinfo();


	new_svacct.interest_calc();
	CD_e.interest_calc();

	new_svacct.display_acctinfo();
	CD_e.display_acctinfo();
	newCheck.display_acctinfo();

	newCheck.order_check();
	newCheck.withdraw(200);
	new_svacct.withdraw(1000);
	CD_e.withdraw(2000);

	new_svacct.display_acctinfo();
	newCheck.display_acctinfo();
	CD_e.display_acctinfo();

	while (i != 'y')
	{

		cout << "press y to exit" << endl;
		cin >> i;
		break;
	}

	return 0;
}