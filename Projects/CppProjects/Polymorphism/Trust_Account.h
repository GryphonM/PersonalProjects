//------------------------------------------------------------------------------
//
// File Name:	Trust_Account.h
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	PRG 7.2.9 Practice - Account Class with Polymorphism
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#ifndef _TRUST_ACCOUNT_H_
#define _TRUST_ACCOUNT_H_

#include "Savings_Account.h"

class Trust_Account : public Savings_Account {
private:
    static constexpr const char *def_name = "Unnamed Trust Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;
    static constexpr double bonus_amount = 50.0;
    static constexpr double bonus_threshold = 5000.0;
    static constexpr int max_withdrawals = 3;
    static constexpr double max_withdraw_percent = 0.2;
protected:
    int num_withdrawals;
public:
    Trust_Account(std::string name = def_name,  double balance = def_balance, double int_rate = def_int_rate);
    virtual ~Trust_Account() = default;

    // Deposits given amount bonus if amount is above threshold
    // Params:
    //   amount = amount to deposit
    // Return:
    //   Deposit Success
    bool deposit(double amount);

    // Withdraws given amount, restricted to amount of times and max percent to be taken out
    // Params:
    //   amount = amount to withdraw
    // Return:
    //   Withdrawal Success   
    bool withdraw(double amount);

    // Prints trust account data
    // Params:
    //   os = stream to output to
    virtual void print(std::ostream& os) const override;
};

#endif // _TRUST_ACCOUNT_H_
