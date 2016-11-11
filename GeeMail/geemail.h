#ifndef GEEMAIL_H
#define GEEMAIL_H

// Helper Functions
std::string getTime();
int getChoice();

// Login and Registraion
bool check_password(std::string pass);
int userRegister(std::string username, std::string password);
bool userLogin(std::string username, std::string pass);

// Read, Write, and Delete Messages
int countMessages(std::string receiver);
bool checkPassphrase(std::string messageid, std::string passphrase);
std::vector <std::string> getSenders(std::string receiver);
std::vector <std::string> getMessages(std::string sender, std::string receiver);
std::vector <std::string> getAllMessages(std::string receiver);
std::string getMessage(std::string messageid);
void writeMessage(std::string username, std::string receiver, std::string title, std::string message, std::string writetime, std::string readtime, std::string passphrase);
void deleteMessage(std::string messageid);

#endif

