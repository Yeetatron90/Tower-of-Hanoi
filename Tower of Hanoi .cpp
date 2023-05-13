#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

// This function creates the initial stack of pancakes of given size and stores them in the vector passed by reference.
void create_pancake(int pancakenum, vector<string>& Pancakes) {
    string pancake = "";
    for (int i=0; i<pancakenum; i++) {
        // Each pancake has i+1 X's on it.
        for (int j=0; j<=i; j++) {
            pancake += "X";
        }
        Pancakes.push_back(pancake);
        pancake = "";
    }
}

// This function shuffles the stack of pancakes randomly
//Parameter: The number of pancakes and the vector Copy, so that an loop the times of the size of the vector can be performed. 
void shuffle_pancakes(int pancakenum, vector<string>& Copy) 
{
    srand(time(0));
    for (int i = 0; i < pancakenum; i++) 
    {
      //The following algorithm produces a number that must be smaller than the size of the vector but yet is random using time(0)
        int randomindex = rand() % (pancakenum - i) + i;
        swap(Copy[i], Copy[randomindex]);
    }

}

//This function restores the pancake in case the user chooses to select to reboot the pancakes. 
//Parameter: The vector copy and the vector Copycopy, so that an opearation of equation can be performed. 
void shuffle_back(vector<string>& Copy, vector<string>& Copycopy)
{
    Copy = Copycopy;
}


// This function prints the stack of pancakes. Both parameters allow for loop.
void print_pancakes(int pancakenum, vector<string>& Copy) {
    for (int i=0; i<pancakenum; i++) {
        cout << Copy[i] << endl;
    }
}

// This function starts the game and allows the player to flip the pancakes, all this .
void play_game(int pancakenum, vector<string>& Copy, vector<string>& Pancakes) {
    int flipnum;
    int stepcounter = 0;
    while (Copy != Pancakes) {
        cout << "Flipped " << stepcounter << " times. Where do you want to flip? Enter the number you desire: ";
        cin >> flipnum;
        // We only need to flip the top flipnum pancakes, so we swap the topmost pancake with the flipnum-th pancake, 
        // the second topmost with the flipnum-1-th pancake, and so on.
        for (int i=0; i <= flipnum/2-1; i++) {
            swap(Copy[i], Copy[flipnum-1-i]);
        }
        print_pancakes(pancakenum, Copy);
        stepcounter ++; //For recording step numbers.
    }
    cout << "Congrats! Solved in: " << stepcounter << " steps!\n";
}

// This function creates the menu that is used for looping. 
void menu(int which, int pancakenum, vector<string>& Copycopy, vector<string>& Copy, vector<string>& Pancakes)
{
  //Infinite loop
    while (true) {
        cout << "1=new game, 2=old game, 0=quit: ";
        cin >> which;
  //Menu logistics
        if (which == 1) {
            create_pancake(pancakenum, Pancakes);
            Copy = Pancakes;
            Copycopy = Pancakes;
            shuffle_pancakes(pancakenum, Copy);
            print_pancakes(pancakenum, Copy);
            play_game(pancakenum, Copy, Pancakes);
            shuffle_back(Copy, Copycopy);
        }
        else if (which == 2)
        {
          //
            shuffle_back(Copy, Copycopy);
            print_pancakes(pancakenum, Copy);
            play_game(pancakenum, Copy, Pancakes);
            shuffle_back(Copy, Copycopy);
        }
        else if (which == 0)
        {
            cout << "CYA!";
        break;
        }
        else
        {
            cout << "Invalid choice. Please enter 1, 2, or 0.\n";
        }
    }
}


int main() {
        vector<string> Pancakes; // This vector stores the initial stack of pancakes.
        vector<string> Copy; // This vector will store the shuffled stack of pancakes for the current game.
        vector<string> Copycopy; // This vector stores the initial shuffled stack of pancakes, for reference when checking if the game is solved and saved in case for reboot.
        int pancakenum;
        int which;

  //Asking for the number/level/rows of the pancake.
        cout << "Welcome to pancake game! How many pancakes do you want (between 2 to 20)? Please tell me: ";
        cin >> pancakenum;

  //The game itself, first time has to be hard-wired in an effort to enter the loop.
        create_pancake(pancakenum, Pancakes);
        Copy = Pancakes;
        shuffle_pancakes(pancakenum, Copy);
//Copying the generated vector into another independent vector to allow for reboot if the user selects 2.
        for (int i=0; i<Copy.size(); i++)
        {
        Copycopy.push_back(Copy[i]);
         }
    
        print_pancakes(pancakenum, Copy);
        play_game(pancakenum, Copy, Pancakes);

//The menu is hard-coded the first time, with menu function embedded in each choices.
        cout << "1=new game, 2=old game, 0=quit: ";
        while(cin >> which, which != 0)
          {
            if (which == 1) {
            create_pancake(pancakenum, Pancakes);
            Copy = Pancakes;
            Copycopy = Pancakes;
            shuffle_pancakes(pancakenum, Copy);
            print_pancakes(pancakenum, Copy);
            play_game(pancakenum, Copy, Pancakes);
            shuffle_back(Copy, Copycopy);
            menu(which,pancakenum, Copy, Copycopy, Pancakes);
        }
            else if (which == 2)
            {
              shuffle_back(Copy, Copycopy);
              print_pancakes(pancakenum, Copy);
              play_game(pancakenum, Copy, Pancakes);
              shuffle_back(Copy, Copycopy);
              menu(which,pancakenum, Copy, Copycopy, Pancakes);
            }
            else if (which == 0)
            {
              cout <<"CYA";
              break;
            }
          }
  }