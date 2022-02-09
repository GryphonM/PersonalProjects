#pragma once
#include "Savings_Account.h"

class Trust_Account : public Savings_Account
{
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
        double bonus_req = def_bonus_req, double bonus = def_bonus, int max = def_max, double limit = def_limit);
    bool deposit(double amount);
    bool withdraw(double amount);
};

