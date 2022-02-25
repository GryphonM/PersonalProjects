//------------------------------------------------------------------------------
//
// File Name:	Checking_Account.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance)
    : Account {name, balance} {
}

// Withdraws given amount plus a fee
// Params:
//   amount = amount to withdraw
// Return:
//   Withdrawal Success
bool Checking_Account::withdraw(double amount) {
    amount += per_check_fee;
    return Account::withdraw(amount);
}

// Prints checking account data
// Params:
//   os = stream to output to
void Checking_Account::print(std::ostream &os) const {
    os << "[Checking_Account: " << name << ": " << balance  << "]";
}

