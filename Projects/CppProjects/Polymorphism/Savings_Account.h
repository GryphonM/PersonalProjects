//------------------------------------------------------------------------------
//
// File Name:	Savings_Account.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#ifndef _SAVINGS_ACCOUNT_H_
#define _SAVINGS_ACCOUNT_H_
#include "Account.h"

class Savings_Account: public Account {
private:
    static constexpr const char *def_name = "Unnamed Savings Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;
protected:
    double int_rate;
public:
    Savings_Account(std::string name = def_name, double balance =def_balance, double int_rate = def_int_rate);
    virtual ~Savings_Account() = default;

    // Deposits given amount plus int rate
    // Params:
    //   amount = amount to deposit
    // Return:
    //   Deposit Success
    virtual bool deposit(double) override;
    // Withdraw is inherited from Account

    // Prints checking account data
    // Params:
    //   os = stream to output to
    virtual void print(std::ostream& os) const override;
};

#endif // _SAVINGS_ACCOUNT_H_
