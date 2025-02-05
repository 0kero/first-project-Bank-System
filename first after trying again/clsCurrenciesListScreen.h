#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrenciesListScreen :protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency CurrencyData)
	{
		cout << setw(8) << left << "" << "| " << setw(28) << left << CurrencyData.Country();
		cout << "| " << setw(5) << left << CurrencyData.CurrencyCode();
		cout << "| " << setw(24) << left << CurrencyData.CurrencyName();
		cout << "| " << setw(10) << left << CurrencyData.Rate();
	
	}
public:static void ShowCurrenciesListScreen()
{

	vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
	string Title = "\t  Currencies List Screen";
	string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currencies(s).";
	_DrawScreenHeader(Title, SubTitle);
	cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
	cout << setw(8) << left << "" << "| " << left << setw(28) << "Country Name";
	cout << "| " << left << setw(5) << "Currency Code";
	cout << "| " << left << setw(24) << "CUrrency Name";
	cout << "| " << left << setw(10) << "Rate(1/$)";
	cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
	if (vCurrencies.size() == 0)
		cout << "\t\t\t\tNo Currencies Available In the System!";
	else

		for (clsCurrency Currency : vCurrencies)
		{
			_PrintCurrencyRecordLine(Currency);
			cout << endl;
		}

	cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
}


};

