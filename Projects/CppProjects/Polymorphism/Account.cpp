//------------------------------------------------------------------------------
//
// File Name:	Account.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Account.h"

Account::Account(std::string name, double balance) 
    : name{name}, balance{balance} {
}

// Deposits given amount into account
// Params:
//   amount = amount to deposit
// Return:
//   Deposit Result
bool Account::deposit(double amount) {
    if (amount < 0) 
        return false;
    else {
        balance += amount;
        return true;
    }
}

// Withdraws given amount from account
// Params:
//   amount = amount to withdraw
// Return:
//   Withdraw Result
bool Account::withdraw(double amount) {
    if (balance-amount >=0) {
        balance-=amount;
        return true;
    } else
        return false;
}

// Prints Account info
// Params:
//   os = stream to output to
void Account::print(std::ostream &os) const {
    os << "[Account: " << name << ": " << balance << "]";
}
