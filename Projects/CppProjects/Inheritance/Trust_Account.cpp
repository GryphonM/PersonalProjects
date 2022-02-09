#include "Trust_Account.h"

Trust_Account::Trust_Account(std::string name, double balance, double int_rate, double bonus_req, double bonus, int max, double limit)
	: Savings_Account{ name, balance, int_rate }, bonus_req{ bonus_req }, bonus{ bonus }, max_withdrawals{ max }, withdrawal_limit{ limit }, withdrawals{0}{
}

// Deposit with bonus if requirement is met
// Params:
//   amount = amount to withdraw
// Return:
//   return success
bool Trust_Account::deposit(double amount)
{
	if (amount >= bonus_req)
		amount += bonus;
	return Savings_Account::deposit(amount);
}

// Withdrawal with counter and limit
// Params:
//   amount = amount to withdraw
// Return:
//   return success
bool Trust_Account::withdraw(double amount)
{
	if (amount < withdrawal_limit * balance && withdrawals < max_withdrawals)
	{
		withdrawals++;
		return Savings_Account::withdraw(amount);
	}
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Trust_Account& out) {
	os << "[Trust_Account: " << out.name << ": " << out.balance << ", " << out.int_rate << "%, withdrawals: " << out.withdrawals << "]";
	return os;
}