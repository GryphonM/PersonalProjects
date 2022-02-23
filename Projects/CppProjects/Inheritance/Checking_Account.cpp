//------------------------------------------------------------------------------
//
// File Name:	Checking_Account.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.9 Practice - Account Class with Inheritance
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance, double fee) 
	: Account{ name, balance }, fee{ fee } {
}

// Withdrawal with fee
// Params:
//   amount = amount to withdraw
// Return:
//   return success
bool Checking_Account::withdraw(double amount) 
{
	return Account::withdraw(amount + fee);
}

// Overrides the output operator
// Params:
//   os = The stream to output to
//   out = The object to output
// Return:
//   Reference to the stream the object was output to
std::ostream& operator<<(std::ostream& os, const Checking_Account& out)
{
	os << "[Checking_Account: " << out.name << ": " << out.balance << "]";
	return os;
}