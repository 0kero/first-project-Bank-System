#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
class clsTransferRegisterScreen :protected clsScreen
{
private:


	static void _PrintTransferRecordLine(clsBankClient::stTransferLog TransferLog)
	{
		cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLog.DateTransferLine;
		cout << "| " << setw(8) << left << TransferLog.SourceAccount;
		cout << "| " << setw(8) << left << TransferLog.DestinationAccount;
		cout << "| " << setw(8) << left << TransferLog.TransferAmmount;
		cout << "| " << setw(10) << left << TransferLog.SourceAccountAfterTransfer;
		cout << "| " << setw(10) << left << TransferLog.DestinationAccountAfterTransfer;
		cout << "| " << setw(8) << left << TransferLog.UserName;
	}
public:
	static void ShowTransferRegisterScreen()
	{


		vector <clsBankClient::stTransferLog> vTransferInfo = clsBankClient::LoadTransferRegister();
		string Title = "\t  Transfer Register List Screen";
		string SubTitle = "\t    (" + to_string(vTransferInfo.size()) + ") Record(s).";
		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/ Time";
		cout << "| " << left << setw(8) << "S.Acc";
		cout << "| " << left << setw(8) << "D.Acc";
		cout << "| " << left << setw(8) << "Ammount";
		cout << "| " << left << setw(10) << "S.balance";
		cout << "| " << left << setw(10) << "D.balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________\n" << endl;
		if (vTransferInfo.size() == 0)
			cout << "\t\t\t\tLog Register Is Empty!";
		else

			for (clsBankClient::stTransferLog TransferLine : vTransferInfo)
			{
				_PrintTransferRecordLine(TransferLine);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________\n" << endl;
	}



};
