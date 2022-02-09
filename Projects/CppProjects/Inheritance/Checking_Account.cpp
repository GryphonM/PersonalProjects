#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance, double fee) 
	: Account{ name, balance }, fee{ fee } {
}

// Withdrawal with fee
// Params:
//   amount = amount to withdraw
// Return:
//   return success
bool Checking_Account::withdraw(double amount) 
{
	return Account::withdraw(amount + fee);
}

std::ostream& operator<<(std::ostream& os, const Checking_Account& out)
{
	os << "[Checking_Account: " << out.name << ": " << out.balance << "]";
	return os;
}