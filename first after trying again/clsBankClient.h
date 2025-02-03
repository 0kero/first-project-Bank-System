#pragma once


#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>
#include "Global.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode ,AddNewMode};
	
	enMode _Mode;
	struct stTransferLog;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static stTransferLog _ConvertTransferRegisterLineToStruct(string Line)
	{
		stTransferLog TransferLog;
		vector <string> data = clsString::Split(Line, "#//#");
		TransferLog.DateTransferLine = data[0];
		TransferLog.SourceAccount = data[1];
		TransferLog.DestinationAccount = data[2];
		TransferLog.TransferAmmount = stoi(data[3]);
		TransferLog.SourceAccountAfterTransfer = stoi(data[4]);
		TransferLog.DestinationAccountAfterTransfer = stoi(data[5]);
		TransferLog.UserName = data[6];


		return TransferLog;
	}

	static string _GetTransferRegisterLine(clsBankClient SourceAccount,clsBankClient DestinationAccount,double TransferAmmount, string Seperator = "#//#")
	{
		string TransferLine = "";
		clsDate TransferDate;
		TransferLine += TransferDate.GetDateLogLine() + Seperator; 
		TransferLine += SourceAccount.AccountNumber() + Seperator;
		TransferLine += DestinationAccount.AccountNumber() + Seperator;
		TransferLine += to_string(TransferAmmount) + Seperator;
		TransferLine += to_string(SourceAccount.AccountBalance) + Seperator;
		TransferLine += to_string(DestinationAccount.AccountBalance) + Seperator;
		TransferLine += CurrentUser.UserName ;
		return TransferLine;


	}
	void _SaveTransferRegisterLine(clsBankClient ClientToTransferTo, double TransferAmmount)
	{
		fstream MyFile;
		MyFile.open("Transfer Register.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			string TransferLine;
			TransferLine = _GetTransferRegisterLine(*this, ClientToTransferTo, TransferAmmount);
			MyFile << TransferLine << endl;
			MyFile.close();
		}
	}
	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4],
			vClientData[5], stod(vClientData[6]));
	}
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		vector <string> vClientData;
		vClientData.push_back(Client.FirstName);
		vClientData.push_back(Client.LastName);
		vClientData.push_back(Client.Email);
		vClientData.push_back(Client.Phone);
		vClientData.push_back(Client.AccountNumber());
		vClientData.push_back(Client.PinCode);
		vClientData.push_back(to_string(Client.AccountBalance));
		return clsString::JoinString(vClientData, Seperator);
	}
	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> _vClients;
		fstream MyFile;
		MyFile.open("clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				_vClients.push_back(_ConvertLinetoClientObject(Line));
			}
			MyFile.close();
		}
		return _vClients;
		
	}
	static void _SaveClientDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		string ClientRecord;
		MyFile.open("clients.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient& c : vClients)
			{
				if (c._MarkedForDelete==false)
				{
					ClientRecord = _ConvertClientObjectToLine(c);
					MyFile << ClientRecord << endl;
				}
			}
		}
		MyFile.close();
	}
	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();
		for (clsBankClient &c:_vClients)
		{
			if (c.AccountNumber()==AccountNumber())
			{
				c = *this;
				break;
			}

		}
		_SaveClientDataToFile(_vClients);
	}
	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;

		MyFile.open("clients.txt", ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			
		}
		MyFile.close();
	}

public:

	struct stTransferLog {
		string DateTransferLine = "";
		string SourceAccount = "";
		string DestinationAccount = "";
		double TransferAmmount = 0;
		double SourceAccountAfterTransfer = 0;
		double DestinationAccountAfterTransfer = 0;
		string UserName ="";
	};
	//these ara the constructors used to initialize values
	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	
	//get and set properties for object 
	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}
	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}
	//only get prperty for gettin account number
	string AccountNumber()
	{
		return _AccountNumber;
	}
	//set and get properties for pin code
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	//set and get properties for account balance;
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	//find client
	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("clients.txt", ios::in);
		if(MyFile.is_open())
		{
			string Line;
			while (getline(MyFile,Line))
			{
				clsBankClient client = _ConvertLinetoClientObject(Line);
				if (client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient client = _ConvertLinetoClientObject(Line);
				if (client.AccountNumber() == AccountNumber && client.PinCode == PinCode)
				{
					MyFile.close();
					return client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();

	}
    void Deposit(double DepositAmmount)
	{
		
		_AccountBalance += DepositAmmount;
		Save();

	}
	bool Withdraw(double WithdrawAmmount)
	{
		if (WithdrawAmmount > this->AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= WithdrawAmmount;
			Save();
			return true;
		}
	}
	//delete client
	bool Delete()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();
		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == AccountNumber())
			{
				c._MarkedForDelete = true;
				break;
			}

		}
		_SaveClientDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;

	}

	//does the client exist
	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient client = Find(AccountNumber);
		return (!client.IsEmpty());
	}

	//function that save the operation you just did and returns the result
	enum enSaveResult { svFailedEmptyObject, svSucceeded ,svFailedAccountNumberExists};
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResult::svFailedEmptyObject;
			}
			break;
		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
			break;
		case clsBankClient::AddNewMode:
			if (IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFailedAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}

			break;
		default:
			break;
		}
	}
	
	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}
	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;
		for (clsBankClient Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}

	bool TransferMoneyTo(clsBankClient &ClientToTransferTo, double TransferAmmount)
	{
		
		if (!Withdraw(TransferAmmount))
		{
			return false;
		}
		ClientToTransferTo.Deposit(TransferAmmount);
		_SaveTransferRegisterLine(ClientToTransferTo,TransferAmmount);
		return true;


	}
	
	static vector <stTransferLog> LoadTransferRegister()
	{

		fstream MyFile;
		vector <stTransferLog> vTransferInfo;
		string Line;
		MyFile.open("Transfer Register.txt", ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vTransferInfo.push_back(_ConvertTransferRegisterLineToStruct(Line));
			}
			MyFile.close();
		}
		return vTransferInfo;
	}
};

