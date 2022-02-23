//------------------------------------------------------------------------------
//
// File Name:	Checking_Account.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.9 Practice - Account Class with Inheritance
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Account.h"

// Checking Account is a type of Account
//   adds an withdrawal fee
// Withdraw - withdraws an additional fee every withdrawal
// Deposit - same as Account
//
class Checking_Account : public Account
{
    // Overrides the output operator
    // Params:
    //   os = The stream to output to
    //   out = The object to output
    // Return:
    //   Reference to the stream the object was output to
    friend std::ostream& operator<<(std::ostream& os, const Checking_Account& out);
private:
    static constexpr const char* def_name = "Unnamed Checking Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_fee = 1.5;
protected:
    double fee;
public:
    Checking_Account(std::string name = def_name, double balance = def_balance, double fee = def_fee);
    
    // Withdrawal with fee
    // Params:
    //   amount = amount to withdraw
    // Return:
    //   return success
    bool withdraw(double amount);
    // deposit is inherited from account
};

