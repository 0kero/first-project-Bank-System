#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsWithdrawScreen:protected clsScreen
{
private:
	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "please enter account number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number Doesn't exist, please enter a valid account number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}
public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");

		clsBankClient Client1 = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(Client1);
		char choice = 'N';
		cout << "\ndo you really want to deposit to this account? ";
		choice = clsInputValidate::ReadChar();
		if (toupper(choice) == 'Y')
		{
			double WithdrawAmmount = 0;
			cout << "\nPlease enter the Ammount you want to withdraw from your account? ";
			WithdrawAmmount = clsInputValidate::ReadDblNumberBetween(0, 99999999, "invalid Please enter positive value");
			cout << "\nAre you sure you want to do this transaction? ";
			choice = clsInputValidate::ReadChar();
			if (toupper(choice) == 'Y')
			{
				if (Client1.Withdraw(WithdrawAmmount))
				{
					cout << "\nwithdraw is Done Successfully\n";
					cout << "\t\t your new balance is " << Client1.AccountBalance << endl;
				}
				else
				{
					cout << "your balance is not enough\n";
				}
								
			}
			else
			{
				cout << "\n\n\tThanks The Process Has Been Cancelled\n";
			}
		}
		else
		{
			cout << "\n\n\tThanks The Process Has Been Cancelled\n";
		}
	}

};

