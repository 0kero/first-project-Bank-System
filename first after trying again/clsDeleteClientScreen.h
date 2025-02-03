#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen:protected clsScreen
{
private:
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

	static void ShowDeleteClinetScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;// this will exit the function and it will not continue
		}

		string AccountNumber = "";
		_DrawScreenHeader("Delete Client Screen");
		cout << "please enter account number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number Doesn't exist, please enter a valid account number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\nAre you sure you want to delete this client y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client1);
							
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}

};

