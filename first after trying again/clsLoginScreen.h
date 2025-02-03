#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "Global.h"
class clsLoginScreen:protected clsScreen
{
private:
	static bool _Login()
	{

		bool LoginFailed = false;
		short Tries = 3;
		string UserName, Password;
		do
		{

			if (LoginFailed)
			{
				cout << "\nInvlaid Username/Password!\n";
				Tries--;
				cout << "You have " << Tries << " trials to login\n\n";
			}
			if(Tries==0)
			{
				system("cls");
				cout << "\n\n\t\t\tYou ran out of tries you have been blocked from the system\n";
				return false;
			}
			cout << "Enter Username? ";
			UserName=clsInputValidate::ReadString();

			cout << "Enter Password? ";
			Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();
		
		} while (LoginFailed);

		CurrentUser.SaveLogLine();
		clsMainScreen::ShowMainMenu();
		return true;
			
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}
};

