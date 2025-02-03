#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsClientListScreen :protected clsScreen
{
private:

	static void _PrintClientRecordLine(clsBankClient ClientData)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << ClientData.AccountNumber();
		cout << "| " << setw(25) << left << ClientData.FullName();
		cout << "| " << setw(12) << left << ClientData.Phone;
		cout << "| " << setw(25) << left << ClientData.Email;
		cout << "| " << setw(10) << left << ClientData.PinCode;
		cout << "| " << setw(12) << left << ClientData.AccountBalance;
	}

public:
	static void ShowClientsList()
	{

		if (!CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;// this will exit the function and it will not continue
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t  Client List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";
		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(25) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordLine(Client);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________\n" << endl;
	}

};

