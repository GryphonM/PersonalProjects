//------------------------------------------------------------------------------
//
// File Name:	Account.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <iostream>
#include <string>
#include "I_Printable.h"

class Account : public I_Printable {
private:   
    static constexpr const char *def_name = "Unnamed Account";
    static constexpr double def_balance = 0.0;
protected:
    std::string name;
    double balance;
public:
    Account(std::string name = def_name, double balance = def_balance);
    virtual ~Account() = default;

    // Deposits given amount into account
    // Params:
    //   amount = amount to deposit
    // Return:
    //   Deposit Result
    virtual bool deposit(double amount);

    // Withdraws given amount from account
    // Params:
    //   amount = amount to withdraw
    // Return:
    //   Withdraw Result
    virtual bool withdraw(double amount);

    // Prints Account info
    // Params:
    //   os = stream to output to
    virtual void print(std::ostream& os) const override;
};
#endif