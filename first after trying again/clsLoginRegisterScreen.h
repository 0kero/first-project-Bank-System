#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsLoginRegisterScreen :protected clsScreen
{
private:
	static void _PrintLoginRecordLine(clsUser::stLoginLog LogInfo)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << LogInfo.DateLoginLine;
		cout << "| " << setw(15) << left << LogInfo.UserName;
		cout << "| " << setw(20) << left << LogInfo.Password;
		cout << "| " << setw(12) << left << LogInfo.Permissions;
	}
public:
	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;// this will exit the function and it will not continue
		}

		vector <clsUser::stLoginLog> vLoginInfo = clsUser::LoadLoginRegister();
		string Title = "\t  Login Register List Screen";
		string SubTitle = "\t    (" + to_string(vLoginInfo.size()) + ") Record(s).";
		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/ Time";
		cout << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________\n" << endl;
		if (vLoginInfo.size() == 0)
			cout << "\t\t\t\tLog Register Is Empty!";
		else

			for (clsUser::stLoginLog LogInfoLine : vLoginInfo)
			{
				_PrintLoginRecordLine(LogInfoLine);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________\n" << endl;
	}


	
};

