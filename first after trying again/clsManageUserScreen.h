#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


class clsManageUserScreen :protected clsScreen
{
private:

    enum enManageUsersMenuOptions { eListUsers = 1, eAddNewUser, eDeleteUser, eUpdateUser, eFindUser, eMainMenu };
    static short _ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 6, "\t\t\t\t     Number is not within range, Enter number between [1,6]? ");
        return choice;
    }
    static void _GoBackToManageUsersScreen()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menu...\n";
        system("pause>0");
        ShowManageUsersMenu();

    }

    static void _ShowUserListScreen()
    {
        clsUsersListScreen::ShowUsersListScreen();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindClientScreen();
    }

    static void _PerformManageUsersMenuOptions(enManageUsersMenuOptions Option)
    {
        switch (Option)
        {
        case clsManageUserScreen::eListUsers:
            system("cls");
            _ShowUserListScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUserScreen::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUserScreen::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUserScreen::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUserScreen::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersScreen();
            break;
        case clsManageUserScreen::eMainMenu:
            break;
        default:
            break;
        }
    }
public:
    static void ShowManageUsersMenu()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");

        _DrawScreenHeader("\t    Manage Users Screen");

        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t\t    Manage Users Menu\n";
        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t[1] Users List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "=============================================\n";

        _PerformManageUsersMenuOptions(enManageUsersMenuOptions(_ReadManageUsersMenuOption()));
    }
};

