#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalcScreen.h"
class clsCurrencyExchangeScreen:protected clsScreen
{
private:
    enum enCurrencyExhangeMenuOptions { eListCurrencies = 1, eFindCurrency, eUpdateRate, eCurrencyCalc, eMainMenu };
    static short _ReadCurrencyExchangeMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 5, "\t\t\t\t     Number is not within range, Enter number between [1,5]? ");
        return choice;

    }

    static void _GoBackToCurrencyExhangeScreen()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menu...\n";
        system("pause>0");
        ShowCurrencyexchangeScreen();

    }
    static void _ShowCurrenciesListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }
    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _ShowCurrencyCalcScreen()
    {
        clsCurrencyCalcScreen::ShowCurrencyCalcScreen();
    }

    static void _PerformCurrencyExchangeMenuOptions(enCurrencyExhangeMenuOptions Option)
    {
        switch (Option)
        {
        case clsCurrencyExchangeScreen::eListCurrencies:
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrencyExhangeScreen();
            break;
        case clsCurrencyExchangeScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExhangeScreen();
            break;
        case clsCurrencyExchangeScreen::eUpdateRate:
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrencyExhangeScreen();
            break;
        case clsCurrencyExchangeScreen::eCurrencyCalc:
            system("cls");
            _ShowCurrencyCalcScreen();
            _GoBackToCurrencyExhangeScreen();
            break;
        case clsCurrencyExchangeScreen::eMainMenu:
            break;
        default:
            break;
        }
    }

public:
	static void ShowCurrencyexchangeScreen()
	{
        system("cls");

        _DrawScreenHeader("\tCurrency Exchange Main Screen");

        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t\t   Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "=============================================\n";
        cout << setw(37) << left << "" << "\t[1] Currencies List.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "=============================================\n";

        _PerformCurrencyExchangeMenuOptions(enCurrencyExhangeMenuOptions(_ReadCurrencyExchangeMenuOption()));
    }

};

