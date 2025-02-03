#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"

class clsTotalBalancesScreen:protected clsScreen
{
private:
	static void _PrintClientRecordBalanceLine(clsBankClient ClientData)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << ClientData.AccountNumber();
		cout << "| " << setw(40) << left << ClientData.FullName();
		cout << "| " << setw(12) << left << ClientData.AccountBalance;

	}
public:
	static void ShowTotalBalances()
	{
		
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string SubTitle = "   Balances List of (" + to_string(vClients.size()) + ") Client(s).";
	    _DrawScreenHeader("\t Total Balances Screen",SubTitle);
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;
		double TotalBalances = 0;
		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
			TotalBalances = clsBankClient::GetTotalBalances();
		for (clsBankClient Client : vClients)
		{
			_PrintClientRecordBalanceLine(Client);
			cout << endl;
		}

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;
		cout << "\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t\t(" << clsUtil::NumtoText(TotalBalances) << ")" << endl;


	}



};

