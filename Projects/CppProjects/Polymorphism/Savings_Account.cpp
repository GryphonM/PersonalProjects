//------------------------------------------------------------------------------
//
// File Name:	Savings_Account.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Savings_Account.h"

Savings_Account::Savings_Account(std::string name, double balance, double int_rate)
    : Account {name, balance}, int_rate{int_rate} {
}

// Deposits given amount plus int rate
// Params:
//   amount = amount to deposit
// Return:
//   Deposit Success
bool Savings_Account::deposit(double amount) {
    amount += amount * (int_rate/100);
    return Account::deposit(amount);
}

// Prints checking account data
// Params:
//   os = stream to output to
void Savings_Account::print(std::ostream &os) const {
    os << "[Savings_Account: " << name << ": " << balance << ", " << int_rate << "%]";
}

