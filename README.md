# C++ Banking Application Excerpt 

*Name:* Yvar Joseph 

*Description:* the development of a bank account simulation application making use of C++. 

## Summary
The following project is designed to build a bank account simulation application for various users, by implementing Object
Oriented Programming (OOP) principles. Initially a *BankAccount* class is developed containing the most important aspects of
a bank account e.g. account number, balance, and a vector for the storage of all accounts. Furthermore, as every bank account 
is linked to a user, a *User* subclass is founded with the user's information, such as name, age, phone number, etc. Naturally,
as with the majority of classes developed with OOP, various getters and setters are implemented to extract and set the data. 

The class's implementation, depicted in this file, demonstrates the functionality of the application. The 
*BankAccount::BankAccount(string accNumber, double bankBalance)* constructor is used to instantiate a new
account object for each new user added. Hereafter, various getters and setters, such as *BankAccount::getAccountNumber()*, 
*BankAccount::getBalance()* and *BankAccount::setAccountNumber(string updatedAccountNumber)* are implemented to
retrieve the account's account number, balance and/or set the account number respectively. 

Furthermore, various methods are implemented to simulate real-world bank account actions: tranferring, depositing and
withdrawing funds between various parties. To ensure a smooth operation, the code displayed also makes use of regex 
patterns to enforce certain requirements i.e. proper email, phone number and string-based input patterns. This ensures
all kinds of errors are easily identified as the user performs certain actions. All of these functionalities in tandem 
produce a robust and capable banking application. 

