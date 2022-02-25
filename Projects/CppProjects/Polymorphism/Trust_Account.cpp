//------------------------------------------------------------------------------
//
// File Name:	Trust_Account.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Trust_Account.h"

Trust_Account::Trust_Account(std::string name, double balance, double int_rate)
    : Savings_Account {name, balance, int_rate}, num_withdrawals {0}  {
        
}

// Deposits given amount bonus if amount is above threshold
// Params:
//   amount = amount to deposit
// Return:
//   Deposit Success
bool Trust_Account::deposit(double amount) {
    if (amount >= bonus_threshold)
        amount += bonus_amount;
    return Savings_Account::deposit(amount);
}

// Withdraws given amount, restricted to amount of times and max percent to be taken out
// Params:
//   amount = amount to withdraw
// Return:
//   Withdrawal Success    
bool Trust_Account::withdraw(double amount) {
    if (num_withdrawals >= max_withdrawals || (amount > balance * max_withdraw_percent))
        return false;
    else {
        ++num_withdrawals;
        return Savings_Account::withdraw(amount);
    }
}

// Prints trust account data
// Params:
//   os = stream to output to
void Trust_Account::print(std::ostream &os) const {
    os << "[Trust Account: " << name << ": " << balance << ", " << int_rate 
        << "%, withdrawals: " << num_withdrawals <<  "]";
}
