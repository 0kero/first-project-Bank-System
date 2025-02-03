#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsAddNewUserScreen :protected clsScreen
{
private:
	static int _ReadPermissions()
	{
		int Permissions = 0;
		char choice = 'n';
		cout << "Do you want to give Permission to Everything? ";
		cin >> choice;
		if (tolower(choice)=='y')
		{
			return -1;
		}
		cout << "\n\nDo you want to give access to :\n";
		cout << "\nshow client list : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions+=clsUser::enPermissions::pListClients;
		}
		cout << "\nAdd New client : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}
		cout << "\nDelete client : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}
		cout << "\nUpdate client : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pUpdateClient;
		}
		cout << "\nFind client : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}
		cout << "\nTransactions : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pShowTransactionsMenu;
		}
		cout << "\nManage Users : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}
		cout << "\nLogin Register : ";
		cin >> choice;
		if (tolower(choice) == 'y')
		{
			Permissions += clsUser::enPermissions::pLoginRegister;
		}
		return Permissions;
	}
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "please enter first name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "please enter last name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "please enter email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "please enter phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "please enter password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "please enter Permissions: ";
		User.Permissions = _ReadPermissions();

	}
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	} 

public:
	static void ShowAddNewUserScreen()
	{
		string UserName = "";
		_DrawScreenHeader("\tAdd New User Screen");

		cout << "please enter User Name : ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name Is Already In Use, Choose another one: ";

			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(NewUser);
		clsUser::enSaveResult SaveResult;
		SaveResult = NewUser.Save();
		switch (SaveResult)
		{
		case clsUser::svFailedEmptyObject:
			cout << "\nError User was not saved because it's Empty";
			break;
		case clsUser::svSucceeded:
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		case clsUser::svFailedUserNameExists:
			cout << "\nError User was not saved because User Name is used!\n";
			break;
		default:
			break;
		}
	}
};

