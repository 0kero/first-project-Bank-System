#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}
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
public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen");
		double TransferAmmount = 0;
		char choice = 'n';
		cout << "\n\nPlease an Account Number to transfer From: ";
		clsBankClient ClientToTransferFrom = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(ClientToTransferFrom);
		
		cout << "\n\nPlease enter a differrent account number to transfer To: ";
		clsBankClient ClientToTransferTo = clsBankClient::Find(_ReadAccountNumber());

		while (ClientToTransferTo.AccountNumber() == ClientToTransferFrom.AccountNumber())
		{
			cout << "\n\nYou Chose the same Account Number enter a differrent account number to transfer To: ";
		    ClientToTransferTo = clsBankClient::Find(_ReadAccountNumber());


		}
		_PrintClient(ClientToTransferTo);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
		

		cout << "\n\nPlease the Ammount you want to transfer: ";
		TransferAmmount = clsInputValidate::ReadDblNumberBetween(0, 99999999999999);
		cout << "\n\nDo you Really Want To Do This Transaction: ";
		choice = clsInputValidate::ReadChar();
		if (tolower(choice)=='y')
		{
			while (!ClientToTransferFrom.TransferMoneyTo(ClientToTransferTo,TransferAmmount))
			{
				cout << "Amount Exceeds the available Balance, Enter another Amount ? ";
				TransferAmmount = clsInputValidate::ReadDblNumberBetween(0, 99999999999999);
				cout << "\n\nDo you Really Want To Do This Transaction: ";
				choice = clsInputValidate::ReadChar();
				if (tolower(choice) != 'y')
				{
					break;
				}

			}
			if (tolower(choice) != 'y')
			{
				cout << "\nTransaction IS Cancelled\n";
				return;
			}
			cout << "\nTrasfer Done Successfully\n";
			_PrintClient(ClientToTransferFrom);
			_PrintClient(ClientToTransferTo);

		}
		else
		{
			cout << "\nTransaction IS Cancelled\n";
		}

	}
};

