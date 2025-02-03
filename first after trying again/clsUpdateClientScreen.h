#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen:protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "please enter first name: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "please enter last name: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "please enter email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "please enter phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "please enter pin code: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "please enter balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();

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
	static void ShowUpdateClientScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
		{
			return;// this will exit the function and it will not continue
		}

		string AccountNumber = "";
		_DrawScreenHeader("\tUpdate Client Screen");
		cout << "please enter account number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "please enter a valid account number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		cout << "\n\nUpdate Client Info:";
		cout << "\n____________________\n";

		char choice;
		cout << "do you really want to update this client: y/n ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			_ReadClientInfo(Client);
			clsBankClient::enSaveResult SaveResult;
			SaveResult = Client.Save();
			switch (SaveResult)
			{
			case clsBankClient::svFailedEmptyObject:
				cout << "\nError account was not saved because it's Empty";
				break;
			case clsBankClient::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(Client);
				break;
			default:
				break;
			}

		}
		else
		{
			cout << "client has NOT been updated\n";;
		}

	}

};

