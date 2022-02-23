//------------------------------------------------------------------------------
//
// File Name:	Trust_Account.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.9 Practice - Account Class with Inheritance
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Trust_Account.h"

Trust_Account::Trust_Account(std::string name, double balance, double int_rate, double bonus_req, double bonus, double limit, int max)
	: Savings_Account{ name, balance, int_rate }, bonus_req{ bonus_req }, bonus{ bonus }, withdrawal_limit{ limit }, withdrawals{0}, max_withdrawals{ max }{
}

// Deposit with bonus if requirement is met
// Params:
//   amount = amount to withdraw
// Return:
//   return success
bool Trust_Account::deposit(double amount)
{
	if (amount >= bonus_req)
		amount += bonus;
	return Savings_Account::deposit(amount);
}

// Withdrawal with counter and limit
// Params:
//   amount = amount to withdraw
// Return:
//   return success
bool Trust_Account::withdraw(double amount)
{
	if (amount < withdrawal_limit * balance && withdrawals < max_withdrawals)
	{
		withdrawals++;
		return Savings_Account::withdraw(amount);
	}
	else
		return false;
}

// Overrides the output operator
// Params:
//   os = The stream to output to
//   out = The object to output
// Return:
//   Reference to the stream the object was output to
std::ostream& operator<<(std::ostream& os, const Trust_Account& out) {
	os << "[Trust_Account: " << out.name << ": " << out.balance << ", " << out.int_rate << "%, withdrawals: " << out.withdrawals << "]";
	return os;
}