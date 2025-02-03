#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"

#include "clsLoginScreen.h"

#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUserScreen.h"
#include "clsLoginRegisterScreen.h"
using namespace std;

class clsMainScreen: protected clsScreen
{
private:
  
    enum enMainMenuOptions{
     
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
        eManageUsers = 7,eLoginRegisterList = 8, eExit = 9
    };
    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 9, "\t\t\t\t     Number is not within range, Enter number between [1,9]? ");
        return choice;

    }
    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";

        system("pause>0");
        ShowMainMenu();
    
    }
    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClinetScreen();

    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();

    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();

    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsScreen();

    }

    static void _ShowManageUsersMenu()
    {
        clsManageUserScreen::ShowManageUsersMenu();
    }
    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static void _Logout()
    {
       CurrentUser = clsUser::Find("", "");
    }
   static void _PerformMainMenuOptions(enMainMenuOptions MainMenuOption)
    {
       switch (MainMenuOption)
       {
       case clsMainScreen::eListClients:
           system("cls");
           _ShowAllClientsScreen();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eAddNewClient:
           system("cls");
           _ShowAddNewClientsScreen();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eDeleteClient:
           system("cls");
           _ShowDeleteClientScreen();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eUpdateClient:
           system("cls");
           _ShowUpdateClientScreen();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eFindClient:
           system("cls");
           _ShowFindClientScreen();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eShowTransactionsMenu:
           system("cls");
           _ShowTransactionsMenu();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eManageUsers:
           system("cls");
           _ShowManageUsersMenu();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eLoginRegisterList:
           system("cls");
           _ShowLoginRegisterScreen();
           _GoBackToMainMenu();
           break;
       case clsMainScreen::eExit:
           system("cls");
           _Logout();
           break;
       default:
           break;
       }
    }

public:
	static void ShowMainMenu()
	{
        system("cls");

		_DrawScreenHeader("\t\tMain Screen");
      
        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register List.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "=============================================\n";

        _PerformMainMenuOptions(enMainMenuOptions(_ReadMainMenuOption()));
	}
};

