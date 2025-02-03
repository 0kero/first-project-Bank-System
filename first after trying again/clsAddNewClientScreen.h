#pragma once
#include <iostream>
#include "clsScreen.h"

#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen:protected clsScreen
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
		cout << "\nLastName    : " <<Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " <<Client.Email;
		cout << "\nPhone       : " <<Client.Phone;
		cout << "\nAcc. Number : " <<Client.AccountNumber();
		cout << "\nPassword    : " <<Client.PinCode;
		cout << "\nBalance     : " <<Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:
	static void ShowAddNewClientScreen()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;// this will exit the function and it will not continue
		}

		string AccountNumber = "";
		_DrawScreenHeader("\tAdd New Client Screen");

		cout << "please enter account number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Already In Use, Choose another one: ";

			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
		_ReadClientInfo(NewClient);
		clsBankClient::enSaveResult SaveResult;
		SaveResult = NewClient.Save();
		switch (SaveResult)
		{
		case clsBankClient::svFailedEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		case clsBankClient::svFailedAccountNumberExists:
			cout << "\nError account was not saved because account number is used!\n";
			break;
		default:
			break;
		}

	}


};

