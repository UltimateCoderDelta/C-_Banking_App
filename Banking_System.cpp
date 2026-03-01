#include "BankAccount.hpp"

const regex accountNumberRe("\\w{2}\\d{2}\\w{4}\\d{6}\\d{8}");
const regex firstNameRe("\\w{2,16}"); 
const regex lastNameRe("\\w{2,21}");
const regex emailRe("^[\\w - \\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
const regex phoneRe("^[\\+]?[(]?[0-9]{3}[)]?[-\\s\\.]?[0-9]{3}[-\\s\\.]?[0-9]{4,6}"); 
const regex birthDayRe("(0[1-9]|1[0-9]|2[0-9]|3[01]).(0[1-9]|1[012]).([19]{2})?([1-9]{2})");

BankAccount::BankAccount(string accNumber, double bankBalance) : accountNumber(accNumber), balance(bankBalance) {}

BankAccount::BankAccount(){} //empty constructor 


string BankAccount::getAccountNumber() const {
   return accountNumber;
}

double BankAccount::getBalance() const {
   return balance;
}

void BankAccount::setAccountNumber(string updatedAccountNumber) {
      //ensure the account number is valid (not exceeding 30 alphanumeric characters)
      int patternFound = regex_search(updatedAccountNumber, accountNumberRe); 
      if ((updatedAccountNumber.length() == 22) && patternFound == 1) {
           accountNumber = updatedAccountNumber;
       }
      else {
        cout << "Invalid bank account number" << endl;
        return;
       }
}

void BankAccount::setBalance(double updatedBalance) {
     // ensure that the balance does not exceed 250K
     if (updatedBalance > 250000) {
        cout << "Balance exceeds account limits" << endl;
        return;
     }
     //if successful, update account balance
     balance = updatedBalance;
}

//Create a new account method
void BankAccount::createAccount(string accountNumber, double initialBalance) {
    int accountNumberValid = regex_search(accountNumber, accountNumberRe); 

    //Ensure the account number is valid
    if (accountNumberValid != 1 || initialBalance < 0) {
       cout << "Error in creating user account, please check the account number or balance is valid" << endl; 
       return;
    }
    //If all is valid, proceed and create a new account object
    auto newAccount = BankAccount(accountNumber, initialBalance); 
    //push new account to bank accounts vector
    bankAccounts.push_back(newAccount);
}

void BankAccount::printBankAccounts() const {
    cout << "Listing Bank Accounts " << endl; 
    for (auto account : bankAccounts) {
        cout << "\nNumber: " << account.getAccountNumber() << "\n Account Balance: "<< account.getBalance()<<endl;
    } 
}

//findAccount method
unique_ptr<BankAccount> BankAccount::findAccount(string accountNumber) {
   //Ensure the account number is valid
   int accountNumberValid = regex_search(accountNumber, accountNumberRe); 

   if (accountNumberValid != 1) {
      cout << "Invalid account number" << endl;
      return nullptr; 
   }
   
   //If the account number is valid, search for it
   for (auto account : bankAccounts) {
       //check if the account number matches
       if (account.getAccountNumber() == accountNumber) {
          cout << "Account fetch successful" << endl;
          return make_unique<BankAccount>(account); 
       }
   }
   //if the account was not found, return nullptr 
   cout << "Failed to fetch account" << endl;
   
   return nullptr;
}

//transferMoney function
int BankAccount::transferMoney(string source, string target, double amount) {
    int sourceAccountNumber = regex_search(source, accountNumberRe); 
    int targetAccountNumber = regex_search(target, accountNumberRe);

    //check if both accounts are valid
    if ((sourceAccountNumber != 1 || targetAccountNumber != 1)) {
        cout << "Source or target account is invalid" << endl;
        return 2;
    }

    //if the accounts are valid, check that the amount for the source account is correct
    unique_ptr<BankAccount> tempBankAccountSource;
    unique_ptr<BankAccount> tempBankAccountTarget; 

    for (auto account : bankAccounts) {
        if (account.getAccountNumber() == source) {
            cout << "Source account accessed" << endl;
            tempBankAccountSource = make_unique<BankAccount>(account);
        }

        if (account.getAccountNumber() == target) {
           cout << "Target Account accessed" << endl;
           tempBankAccountTarget = make_unique<BankAccount>(account);
        }
    }
    //if the source account is found, check that the amount is not invalid
    if (amount > tempBankAccountSource->getBalance()) {
       // let the user know and return error code 3
       cout << "Insufficient funds for transfer" << endl; 

       return 3;
    }
    //if there are sufficient funds, perform the transaction to the target account
    tempBankAccountTarget->setBalance((tempBankAccountTarget->getBalance() + amount));

    //reduce source bank account amount by amount
    tempBankAccountSource->setBalance((tempBankAccountSource->getBalance() - amount)); 

    cout << "Transfer amount of $" << amount << " successful" << endl;
     
    return 1;
}

//

//Implementing transaction class
void BankAccount::Transaction::deposit(BankAccount& account, double depositAmount) {
   //Ensure the depositAmount added to balance does not exceed 250K
   if ((depositAmount + account.getBalance()) > 250000) {
       cout << "Balance exceeds account limits" << endl;
       return;
   } 
   //otherwise add the deposit to balance
   cout << "Making deposit " << endl;

   double deposited = depositAmount + account.getBalance();
   
   account.setBalance(deposited);
}

void BankAccount::Transaction::withdraw(BankAccount& account, double withdrawAmount) {
    //Ensure withdrawl amount is valid wrt to the account balance
    if (account.getBalance() < withdrawAmount) {
       cout << "Insufficient account balance" << endl;
       return;
    }

    //If the withdrawal amount exceeds the balance, remove amount from balance and update balance
    double withdrawDiff = account.getBalance() - withdrawAmount;
    account.setBalance(withdrawDiff); 

    cout << "Withdrawal successful\nCurrent balance: " << account.getBalance() << endl;
}

//Transaction constructor
BankAccount::Transaction::Transaction() {}

//User class
BankAccount::User::User(int usrId, string fName, string lName, string email, string phnNumber, string bthDate) {
     userId = usrId; 
     firstName = fName; 
     lastName = lName; 
     email = email; 
     phoneNumber = phnNumber; 
     birthDate = bthDate;
}

BankAccount::User::User(){}

int BankAccount::User::getUserId() const {
    return userId;
}
string BankAccount::User::getFirstName() const {
   return firstName;
}

string BankAccount::User::getLastName() const {
   return lastName;
}

string BankAccount::User::getEmail() const {
   return email;
}

string BankAccount::User::getPhoneNumber() const {
   return phoneNumber;
}

string BankAccount::User::getbirthDate() const {
   return birthDate;
}

vector<map<int, BankAccount>> BankAccount::User::getUserAccounts() const {
   return userAccounts;
}

//Function to handle name validation
void nameValidator(string name, int validatorValue, string nameType) {
    if ((name.length() < 1) && (validatorValue != 1)) {
       cout << "Invalid " << nameType << endl;
       return; 
    }
}

//Setters 
void BankAccount::User::setFirstName(string updatedFirstName) {

   int validNamePattern = regex_search(updatedFirstName, firstNameRe);
   nameValidator(updatedFirstName, validNamePattern, "first name");
   //if the name is valid, update the firstName field
   firstName = updatedFirstName; 
}

void BankAccount::User::setLastName(string updatedLastName){
     int validNamePattern = regex_search(updatedLastName, lastNameRe); 
     nameValidator(updatedLastName, validNamePattern, "last name");
     //if the name is valid, update the firstName field
     lastName = updatedLastName;
}

void BankAccount::User::setEmail(string updatedEmail) {
     //validate the email
     int validEmailPattern = regex_search(updatedEmail, emailRe); 
     //Ensure the email is valid
     if (validEmailPattern != 1) {
        cout << "Invalid email" << endl;
        return;
     }

     //If the email is valid, update it
     email = updatedEmail;
}

void BankAccount::User::setPhoneNumber(string updatedPhoneNumber) {
     int phoneNumberPatternValid = regex_search(updatedPhoneNumber, phoneRe); 
     //ensure the phone number is valid
     if (phoneNumberPatternValid != 1) {
        cout << "Invalid phone number" << endl;
        return; 
     }

     //if the phone number is valid, update it
     phoneNumber = updatedPhoneNumber;
}

void BankAccount::User::setBirthDate(string updatedBirthDate) {
     int birthDayPatternValid = regex_search(updatedBirthDate, birthDayRe); 

     //ensure the birth date is valid
     if (birthDayPatternValid != 1) {
        cout << "Invalid birth date" << endl;
        return;
     }
     //if valid, update the birth day
     birthDate = updatedBirthDate; 
}

vector<BankAccount> BankAccount::getBankAccounts() const {
    return bankAccounts;
}

//link each user to a bank account
void BankAccount::User::linkAccount(int userId, string accountNumber, vector<BankAccount>& bankAccounts) {
     int accountPatternValid = regex_search(accountNumber, accountNumberRe); 

     if (accountPatternValid != 1) {
        cout << "Invalid account number" << endl;
        return; 
     }

     // if the account number is valid, search for the id to ensure it exists 
     for (auto user : usersList) {
        //ensure the user ID exists
        if (userId == user.getUserId()) {
           // if so, ensure the account entered is valid
           for (auto account : bankAccounts) {
               if (accountNumber == account.getAccountNumber()) {
                 // if the account number is valid add it to the vector map
                 map<int, BankAccount> userAccount = {{userId, account}}; 
                 //add map to the vector
                 userAccounts.push_back(userAccount);
                 //end the function if found and added
                 cout << "User account successfully linked for user " << user.getFirstName() << " " << user.getLastName() << endl;
                 //end the function 
                 return;
               } 
           } 
        } 
     }
     //if the user is not found, let the user know
     cout << "No matching user id or account number " << endl;
}

//Create user
void BankAccount::User::addUser(int userId,
                                string fName,
                                string lName,
                                string email,
                                string phnNumber,
                                string bthDate) {

//Ensure the userId isn't present in the user list
   //if the usersList is not empty, ensure the ID doesn't already exist
   for (auto user : usersList) {
      if (userId == user.getUserId()) {
         cout << " User already exists " << endl;
         return; 
      } 
   }
 //else if the user doesn't exist, create it and add them 
 User newUser = User(userId, fName, lName, email, phnNumber, bthDate);

 usersList.push_back(newUser);

 cout << "User successfully added " << endl;
}

