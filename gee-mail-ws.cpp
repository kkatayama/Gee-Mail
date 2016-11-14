#include <vector>
#include <iostream>
#include "GeeMail/geemail.h"

using namespace std;

int main (int argc, char ** argv){
   if(argc < 4)
   {
      // width height number_of_mines
      cout << "500" << endl;
      return 1;
   }

   /*
    * 0 User Registration
    * 1 User Login
    * 2 Read Message
    * 3 Write Message
    * 4 Delete Message
    * 5 Summary - Read All Message
    */
   string pmode = argv[1]; // 1 User Login
   string username = argv[2];
   string password = argv[3];

   vector <string> senders;
   vector <string> messages;
   
  bool logged_in = false;
  
  logged_in = userLogin(username, password);
  if(!logged_in && pmode!="0")
  {
    cout << "104" << endl;
    return 11;
  }    
  

   // 0 User Registration
   if (pmode=="0")
   {
       // Do User registration here
       int checkRegister = userRegister(username, password);
       // return 0: success
       if(checkRegister==0)
       {
           cout << "10" << endl;
           return 0;
       }
       // return 1: username exists
       else if(checkRegister==1)
       {
           cout << "20" << endl;
           return 1;
       }
       // return 2: password too weak
       else if(checkRegister==2)
       {
           cout << "30" << endl;
           return 2;
       }
       else
       {
           cout << "99" << endl;
           return 3;
       }
   }
   //1 User Login
   else if (pmode=="1")
   {
      //bool logged_in = false;
      //logged_in = userLogin(username, password);
      if(logged_in)
      {
         cout << "100" << endl;
         return 10;
      }
      else
      {
        cout << "104" << endl;
        return 11;
      }
        
   }
   // 2 Read a Message
   else if (pmode=="2")
   {
      if(argc != 6)
      {
         cout << "504" << endl;
         return 1;
      }
      string messageid = argv[4];
      string passphrase = argv[5];
      bool checkPP = checkPassphrase(messageid, passphrase);
      if(checkPP) 
      {
        string plaintext = getMessage(messageid);
        cout << plaintext << endl;
        return 0;
      }
      else
      {
        cout << "404" << endl;
        return 2;
      }
   }
   // 3 Write Message
   else if (pmode=="3")
   {
      if(argc != 8)
      {
         cout << argc << endl;
         cout << "503" << endl;
         //cout << argv[0] << endl;
         //cout << argv[1] << endl;
         //cout << argv[2] << endl;
         //cout << argv[3] << endl;
         //cout << argv[4] << endl;
         //cout << argv[5] << endl;
         //cout << argv[6] << endl;
         //cout << argv[7] << endl;
         //cout << argv[8] << endl;
         return 1;
      }
      cout << argv[0] << endl;
      cout << argv[1] << endl;
      cout << argv[2] << endl;
      cout << argv[3] << endl;
      cout << argv[4] << endl;
      cout << argv[5] << endl;
      cout << argv[6] << endl;
      cout << argv[7] << endl;
      string timestamp = getTime();
      string receiver = argv[4];
      string title = argv[5];
      string passphrase = argv[6];
      string message = argv[7];

      writeMessage(username, receiver, title, message, timestamp, "0", passphrase);
      cout << "300" << endl;
      return 0;
   }
   //4 Delete Message
   else if (pmode=="4")
   {
      if(argc != 6)
      {
         cout << "504" << endl;
         return 1;
      }
      string messageid = argv[4];
      string passphrase = argv[5];
      bool checkPP = checkPassphrase(messageid, passphrase);
      if(checkPP) 
      {
        deleteMessage(messageid);
        cout << "4" << endl;
        return 0;
      }
      else
      {
        cout << "404" << endl;
        return 2;
      }
   }
   else if(pmode=="5")
   {
      vector <string> mymsg;
      mymsg = getAllMessages(username);

      if(mymsg.size()==0)
      {
        return 0; // No Error
      }

      int msgTOT = countMessages(username);
      
      if(mymsg.size()!=msgTOT)
      {
        cout << msgTOT << endl;
        cout << mymsg.size() << endl;
        cout << "Inconsistent Messages!" << endl;
        return 2;
      }

      for (int i = 0; i<mymsg.size(); i++) {
         cout << mymsg[i] << endl;
      }

      return 1; // Sucessfully executed!
   }



//cout << pmode << endl;
//cout << username << endl;
//cout << password <<endl;
}

