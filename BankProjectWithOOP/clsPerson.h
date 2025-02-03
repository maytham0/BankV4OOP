#pragma once
#include<iostream>

using namespace std; 
class clsPerson
{
private : 
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;


public :
	clsPerson(string firstname, string lastname, string email, string phone)
	{
		_FirstName = firstname;
		_LastName = lastname;
		_Email = email;
		_Phone = phone;
	}
	void setFirstName(string firstname)
	{
		_FirstName = firstname;
	}
	string GetFirstName()
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = setFirstName))string FirstName;

	void SetLastName(string lastname)
	{
		_LastName = lastname;
	}
	string GetLastName()
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName))string LastName;

	void SetEmail(string email)
	{
		_Email = email;
	}
	string GetEmail()
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail))string Email;

	void SetPhone(string phone)
	{
		_Phone = phone;

	}
	string GetPhone()
	{
		return _Phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone))string Phone; \

		string FullName()
	{
		return _FirstName + " " + _LastName;
	}


};

