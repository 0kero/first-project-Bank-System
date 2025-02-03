#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsDeleteUserScreen :protected clsScreen
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
	static void ShowDeleteUserScreen()
	{
		string UserName = "";
		_DrawScreenHeader("Delete User Screen");
		cout << "please enter User Name : ";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "User Name Doesn't exist, please enter a valid User Name : ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		cout << "\nAre you sure you want to delete this User y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User);

			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}
	}

};

