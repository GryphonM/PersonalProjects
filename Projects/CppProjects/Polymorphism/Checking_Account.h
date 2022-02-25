//------------------------------------------------------------------------------
//
// File Name:	Checking_Account.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#ifndef _CHECKING_ACCOUNT_H_
#define _CHECKING_ACCOUNT_H_
#include <iostream>
#include <string>
#include "Account.h"

class Checking_Account: public Account {
private:
    static constexpr const char *def_name = "Unnamed Checking Account";
    static constexpr double def_balance = 0.0;
    static constexpr double per_check_fee = 1.5;
public:
    Checking_Account(std::string name = def_name, double balance = def_balance);
    virtual ~Checking_Account() = default;

    // Withdraws given amount plus a fee
    // Params:
    //   amount = amount to withdraw
    // Return:
    //   Withdrawal Success
    virtual bool withdraw(double) override;
    // Deposit is inherited from account

    // Prints checking account data
    // Params:
    //   os = stream to output to
    virtual void print(std::ostream& os) const override;
};

#endif // _CHECKING_ACCOUNT_H_
