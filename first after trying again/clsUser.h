#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>
using namespace std;

class clsUser :public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode, AddNewMode };

	struct stLoginLog;
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;
	static clsUser _ConvertLineToUserObject(string DataLine,string Seperator ="#//#")
	{
		vector <string> vClientData;
		
		vClientData = clsString::Split(DataLine, Seperator);
		return clsUser(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], clsUtil::DecryptText(vClientData[5]), stoi(vClientData[6]));
	}
	static string _ConvertUserObjectToLine(clsUser User,string Seperator = "#//#")
	{
		string DataLine = "";
		DataLine += User.FirstName + Seperator;
		DataLine += User.LastName + Seperator;
		DataLine += User.Email + Seperator;
		DataLine += User.Phone + Seperator;
		DataLine += User.UserName + Seperator;
		DataLine += clsUtil::EncryptText(User.Password) + Seperator;
		DataLine += to_string(User.Permissions);
		return DataLine;
	}

	static string _GetLoginRegisterLine(clsUser User,string Seperator="#//#")
	{
		string LogLine = "";
		clsDate LogDate;
		LogLine += LogDate.GetDateLogLine() + Seperator;
		LogLine += User.UserName + Seperator;
		LogLine += clsUtil::EncryptText(User.Password) + Seperator;
		LogLine += to_string(User.Permissions);
		return LogLine;


	}

	static stLoginLog _ConvertLoginRegisterLineToStruct(string Line)
	{
		stLoginLog LoginInfo;
		vector <string> data = clsString::Split(Line, "#//#");
		LoginInfo.DateLoginLine = data[0];
		LoginInfo.UserName = data[1];
		LoginInfo.Password = data[2];
		LoginInfo.Permissions = stoi(data[3]);
		return LoginInfo;
	}
	static vector <stLoginLog> _LoadLoginRegisterDataFromFile()
	{

		fstream MyFile;
		vector <stLoginLog> vLoginInfo;
		string Line;
		MyFile.open("Login Register.txt", ios::in);
		if (MyFile.is_open())
		{
			while (getline(MyFile,Line))
			{
				vLoginInfo.push_back(_ConvertLoginRegisterLineToStruct(Line));
			}
			MyFile.close();
		}
		return vLoginInfo;
	}
	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> _vUsers;
		fstream MyFile;
		MyFile.open("users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				_vUsers.push_back(_ConvertLineToUserObject(Line));
			}
			MyFile.close();
			return _vUsers;
		}
	}
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static void _SaveUsersDataToFile(vector <clsUser> vUsers )
	{
		fstream MyFile;
		string ClientRecord;
		MyFile.open("users.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsUser& c : vUsers)
			{
				if (c._MarkedForDelete == false)
				{
					ClientRecord = _ConvertUserObjectToLine(c);
					MyFile << ClientRecord << endl;
				}
			}
		}
		MyFile.close();
	}
	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();
		for ( clsUser &c:_vUsers)
		{
			if (c.UserName== UserName)
			{
				c = *this;
				break;
			}

		}
		_SaveUsersDataToFile(_vUsers);
	}
	void _AddNew()
	{
		_AddDatatLineToFile(_ConvertUserObjectToLine(*this));
	}
	static void _AddDatatLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("users.txt", ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
public:

	struct stLoginLog {
		string DateLoginLine = "";
		string UserName = "";
		string Password = "";
		int Permissions = 0;
	};
	enum enPermissions {
		eAll = -1,
		pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pShowTransactionsMenu = 32,
		pManageUsers = 64, pLoginRegister = 128
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	bool IsMarkedForDelete()
	{
		return (_MarkedForDelete);
	}


	void SetUserName(string username)
	{
		_UserName = username;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (UserName==User.UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
			return _GetEmptyUserObject();
		}
	}
	static clsUser Find(string UserName,string Password)
	{
		fstream MyFile;
		MyFile.open("users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (UserName == User.UserName&&Password== User.Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
			return _GetEmptyUserObject();
		}
	}

	bool Delete()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();
		for (clsUser& c : vUsers)
		{
			if (c.UserName == UserName)
			{
				c._MarkedForDelete = true;
				break;
			}

		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}
	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);
		return (!User.IsEmpty());

	}

	enum enSaveResult { svFailedEmptyObject, svSucceeded, svFailedUserNameExists };
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResult::svFailedEmptyObject;
			}
			break;
		case clsUser::UpdateMode:
			_Update();
			return enSaveResult::svSucceeded;
			break;
		case clsUser::AddNewMode:
			if (IsUserExist(_UserName))
			{
				return enSaveResult::svFailedUserNameExists;
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
	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;

	}
    void SaveLogLine()
	{
		fstream MyFile;
		MyFile.open("Login Register.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			string LogLine;
			LogLine = _GetLoginRegisterLine(*this);
			MyFile << LogLine << endl;
			MyFile.close();
		}
	}
	static vector <stLoginLog> LoadLoginRegister()
	{
		return _LoadLoginRegisterDataFromFile();
	}
};

