#include "GraphicEngine.h"
#include <iostream>
#include <cstdlib>


using namespace std;


void GraphicEngine::clearScreen()
{
  /*
  try{
    system("clear");
            
  }
  catch (exception& e)
    {
      cout << e.what() << endl;
      cout << "The game is not running on unix like machine!" << endl;
      try{
        system("cls");
                                
      }
      catch (exception& e)
        {
          cout << e.what() << endl;
          cout << "The game is not running on windows like machine! Aborting screen \
cleaning!" << endl;
                                  
        }
              
    }  
  */
  cout << "\033[2J\033[1;1H";
  //  for(int i = 0; i <1024*1024; i++)
  //    std::cout << ' ' << std::endl;
}

void GraphicEngine::printIntro()
{
   GraphicEngine::clearScreen();
   cout << "*********************************************************************************" << endl;
   cout << "* CPEG-676 Secure Systems: Project 4: Gee-Mail                                  *" << endl;
   cout << "*********************************** Authors *************************************" << endl;
   cout << "* Alparslan Sari                                                                *" << endl;
   cout << "* Kaoru (Teddy) Katayama                                                        *" << endl;
   cout << "* Pengcheng (Kevin) Zhou                                                        *" << endl;
   cout << "*********************************************************************************" << endl;
}


