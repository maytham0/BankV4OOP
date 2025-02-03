#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include "clsPerson.h"
#include "clsString.h"

using namespace  std;
class clsBankClient :public clsPerson
{
private : 
	enum enMode  { EmptyMode = 0,UpdateMode = 1, AddNewMode=2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.Pincode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}
	static vector<clsBankClient>_LoadClientDataFromFile()
	{
		vector<clsBankClient>vClient;
		fstream Myfile;
		Myfile.open("Clients.txt", ios::in);
		if (Myfile.is_open())
		{
			string Line;
			while (getline(Myfile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClient.push_back(Client);
			}
			Myfile.close();
		}
		return vClient;

	}
	static void _SaveClientsDataToFile(vector<clsBankClient>vClients)
	{
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out);
		string DataLine;
		if (Myfile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				
					if (C.MarkedForDelete == false)
					{
						DataLine = _ConverClientObjectToLine(C);
						Myfile << DataLine << endl;
					}
				
			}
			Myfile.close();
		}

	}
	void _Update()
	{
		vector<clsBankClient>_vClient;
		_vClient = _LoadClientDataFromFile();

		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClient);
		
	}
	void _AddNew()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
public :
	clsBankClient(enMode Mode,string firstname, string lastname, string email, string phone, string AccNumber, string pincode, float Balance)
		:clsPerson(firstname,lastname,email,phone)
	{
		_Mode = Mode;
		_AccountNumber = AccNumber;
		_PinCode = pincode;
		_AccountBalance = Balance;

	}
	bool IsEmpty()
	{
		return (_Mode==enMode::EmptyMode);
	}
	//Read Onlay  *_*
	string AccountNumber()
	{
		return _AccountNumber;
	}
	void SetPinCode(string pincode)
	{
		_PinCode = pincode;
	}
	string GetPincode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPincode, put = SetPinCode))string Pincode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	void setMarkForDelete(bool Mark)
	{
		_MarkForDelete = Mark;
	}
	bool getMarkForDelete()
	{
		return _MarkForDelete;
	}
	__declspec(property(get = getMarkForDelete, put = setMarkForDelete)) bool MarkedForDelete;

	//No UI In back code plz
	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}*/

	static clsBankClient Find(string AccountNumber)
	{
		fstream Myfile;

		Myfile.open("Clients.txt", ios::in);

		if (Myfile.is_open())
		{
			string Line;
			while (getline(Myfile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					Myfile.close();
					return Client;
				}
			}

Myfile.close();
		}
		return _GetEmptyClientObject();
		
	}

	static clsBankClient Find(string AccountNumber,string PinCode)
	{
		fstream Myfile;

		Myfile.open("Clients.txt", ios::in);

		if (Myfile.is_open())
		{
			string Line;
			while (getline(Myfile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber&&Client.Pincode==PinCode)
				{
					Myfile.close();
					return Client;
				}
			}

			Myfile.close();
		}
		return _GetEmptyClientObject();

	}

	static bool IsClientExist(string AccountNumber)
	{

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists=2};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		
		case enMode::EmptyMode:{
			return enSaveResults::svFaildEmptyObject;
			break;
			}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode :
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;

			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}

		}
	}
	static clsBankClient GetAddNewClientObject(string AccountNum)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNum, "", 0);
	}
	bool Delete()
	{
		vector<clsBankClient>_vClient;
		_vClient = _LoadClientDataFromFile();
		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(_vClient);
		*this = _GetEmptyClientObject();
		return true;
	}
	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientDataFromFile();
	}
	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient & Client : vClients)
		{

			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;

	}
	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}
};

