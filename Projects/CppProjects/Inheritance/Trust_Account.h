//------------------------------------------------------------------------------
//
// File Name:	Trust_Account.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.1.9 Practice - Account Class with Inheritance
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Savings_Account.h"

class Trust_Account : public Savings_Account
{
    // Overrides the output operator
    // Params:
    //   os = The stream to output to
    //   out = The object to output
    // Return:
    //   Reference to the stream the object was output to
    friend std::ostream& operator<<(std::ostream& os, const Trust_Account& account);
private:
    static constexpr const char* def_name = "Unnamed Trust Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;
    static constexpr double def_bonus_req = 5000;
    static constexpr double def_bonus = 50;
    static constexpr double def_limit = 0.2;
    static constexpr int def_max = 3;
protected:
    double bonus_req;
    double bonus;
    double withdrawal_limit;
    int withdrawals;
    int max_withdrawals;
public:
    Trust_Account(std::string name = def_name, double balance = def_balance, double int_rate = def_int_rate, 
        double bonus_req = def_bonus_req, double bonus = def_bonus, double limit = def_limit, int max = def_max);
    
    // Deposit with bonus if requirement is met
    // Params:
    //   amount = amount to withdraw
    // Return:
    //   return success
    bool deposit(double amount);

    // Withdrawal with counter and limit
    // Params:
    //   amount = amount to withdraw
    // Return:
    //   return success
    bool withdraw(double amount);
};

