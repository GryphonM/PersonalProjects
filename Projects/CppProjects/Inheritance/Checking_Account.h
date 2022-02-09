#pragma once
#include "Account.h"

// Checking Account is a type of Account
//   adds an withdrawal fee
// Withdraw - withdraws an additional fee every withdrawal
// Deposit - same as Account
//
class Checking_Account : public Account
{
    friend std::ostream& operator<<(std::ostream& os, const Checking_Account& out);
private:
    static constexpr const char* def_name = "Unnamed Checking Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_fee = 1.5;
protected:
    double fee;
public:
    Checking_Account(std::string name = def_name, double balance = def_balance, double fee = def_fee);
    bool withdraw(double amount);
    // deposit is inherited from account
};

