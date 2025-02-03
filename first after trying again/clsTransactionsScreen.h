#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h";
#include "clsTransferRegisterScreen.h"
class clsTransactionsScreen:protected clsScreen
{
private:
    enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw,eTotalBalances,eTransfer,eTransferRegister,eMainMenu };
    static short _ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 6, "\t\t\t\t     Number is not within range, Enter number between [1,6]? ");
        return choice;

    }
    static void _GoBackToTransactionsScreen()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menu...\n";
        system("pause>0");
        ShowTransactionsScreen();

    }
    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferRegisterScreen()
    {
        clsTransferRegisterScreen::ShowTransferRegisterScreen();
    }
    static void _PerformTransactionsMenuOptions(enTransactionsMenuOptions TransactionMenuOption)
    {
        switch (TransactionMenuOption)
        {
        case clsTransactionsScreen::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsScreen();
            break;
        case clsTransactionsScreen::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsScreen();
            break;
        case clsTransactionsScreen::eTotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsScreen();
            break;
        case clsTransactionsScreen::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsScreen();
            break;
        case clsTransactionsScreen::eTransferRegister:
            system("cls");
            _ShowTransferRegisterScreen();
            _GoBackToTransactionsScreen();
            break;
        case clsTransactionsScreen::eMainMenu:
            break;
        default:
            break;
        }

    }
public:
	static void ShowTransactionsScreen()
	{

        if (!CheckAccessRights(clsUser::enPermissions::pShowTransactionsMenu))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");

        _DrawScreenHeader("\tTrancationcs Screen");

        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t\t    Transactions Menu\n";
        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Register.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "=============================================\n";

        _PerformTransactionsMenuOptions(enTransactionsMenuOptions(_ReadTransactionsMenuOption()));
    }

	
};

