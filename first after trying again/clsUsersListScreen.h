#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsUsersListScreen :protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser UserData)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << UserData.UserName;
		cout << "| " << setw(25) << left << UserData.FullName();
		cout << "| " << setw(12) << left << UserData.Phone;
		cout << "| " << setw(25) << left << UserData.Email;
		cout << "| " << setw(10) << left << UserData.Password;
		cout << "| " << setw(12) << left << UserData.Permissions;
	}
public:
	static void ShowUsersListScreen()
	{

		vector <clsUser> vUsers = clsUser::GetUsersList();
		string Title = "\t  Users List Screen";
		string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";
		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!";
		else

			for (clsUser user : vUsers)
			{
				_PrintUserRecordLine(user);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
	}
	
};

