#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsFindUserScreen:protected clsScreen
{
private:
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
	static void ShowFindClientScreen()
	{
		_DrawScreenHeader("\tFind User Screen");
		string UserName = "";
		cout << "please enter User Name : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "please enter a valid User Name : ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

		_PrintUser(User);

	}

};

