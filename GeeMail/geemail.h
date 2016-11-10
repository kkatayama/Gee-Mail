#ifndef GEEMAIL_H
#define GEEMAIL_H

int countMessages(std::string receiver);
std::vector <std::string> getSenders(std::string receiver);
std::vector <std::string> getMessages(std::string sender, std::string receiver);
std::string getMessage(std::string messageid);
std::string getTime();
void writeMessage(std::string username, std::string receiver, std::string title, std::string message, std::string writetime, std::string readtime, std::string passphrase);
bool check_password(std::string pass);
bool checkPassphrase(std::string messageid, std::string passphrase);
int getChoice();
bool userLogin(std::string username, std::string pass);
int userRegister(std::string username, std::string password);

#endif

