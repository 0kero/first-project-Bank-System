#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalcScreen :protected clsScreen
{
private:

    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }

    static clsCurrency _GetCurrency(string Message)
    {

        string CurrencyCode;
        cout << Message << endl;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }

    static void _PrintCalculationsResults(clsCurrency Currency1,clsCurrency Currency2,float Ammount)
    {
        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmmountInUSD = Currency1.ConvertToUSD(Ammount);
        cout << Ammount << " " << Currency1.CurrencyCode() << " = " << AmmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }
        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Ammount,Currency2);

        cout << Ammount << " " << Currency1.CurrencyCode()
            << " = " << AmmountInCurrrency2 << " " << Currency2.CurrencyCode();

    }

public:

    static void ShowCurrencyCalcScreen()
    {
        char Continue = 'y';
       while(tolower(Continue)=='y')
       {
           system("cls");
           _DrawScreenHeader("\tCurrency Calculator Screen");

            clsCurrency Currency1 =_GetCurrency("Please enter currency 1 code? ");

            clsCurrency Currency2 = _GetCurrency("Please enter currency 2 code? ");
            
            float Ammount = _ReadAmount();

            _PrintCalculationsResults(Currency1, Currency2,Ammount);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;


        }


    }
};

