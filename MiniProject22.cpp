#include <iostream>
#include <string.h>
using namespace std;


// Made by S Dhananjayan and other members of Group 22.


/* CHECK function essentially compares the input string character by character to the answer string and prints 
the result so that the user can make a better guess if they're wrong. It returns a boolean variable
"correct" which can be used to end the game. The inputs are the answer as char arr, the input as a pointer.*/
int check(char ans[6], char *q)
{
    bool status,correct;
    // We initialize correct to 1(unless a mismatch is spotted, it must be correct)
    correct = 1;
    for(int i=0;i<5;i++)
    {
        if(ans[i]==*(q+i))
        {
            cout << "Yes   ";
        }
        else    
        {
            status = 0;
            //We make correct 0 because atleast one character is not matching.
            correct = 0;
            for(int j=0;j<5;j++)
            {
                if(ans[j]==*(q+i))
                {
                    //Now the 'i'th character of input is equal to the 'j'th character of answer(i!=j). So, we make status 1.
                    status = 1;
                    break;
                }
            }
            if(status)
            {
                cout << "Half  ";
            }
            else
            {
                cout << "No    ";
            }
        }
    }
        //We are printing 5 dashes to show the result of comparison at each index.
        cout << endl << "----  ----  ----  ----  ----  " << endl;
    return correct;
}


// error_invalid_char function prints an ERROR message if the user has given k invalid characters(not in range A-Z) in the input.
void error_invalid_char(int k)
{
    //Checking if there are multiple invalid characters.
    if(k-1)
    {
        //Plural
        cout <<  k <<" characters you have entered are invalid. " << endl;
    }
    else
    {
        //Singular
        cout <<  k <<" character you have entered is invalid. " << endl;
    }
}


// no_of_tries function prints the number of tries left(t) to remind the user of the same.
void no_of_tries_left(int t)
{
    //If there are no more chances(t=0)
    if(!t)
    {
        cout << endl << "Better luck next time! You couldn't win the game. The game is over.";
    }
    //Checking if there are multiple tries left.
    else if(t-1)
    {
        //Plural
        cout << "You have " << t << " tries left" << endl;
    }
    else
    {
        //Singular
        cout << "You have " << t << " try left" << endl;
    }
}


// error_no_of_characters function prints an ERROR message if the user has given t characters in the input string. NOTE: It is called only when t!=5.
void error_no_of_characters(int t)
{
    //Checking if t is singular or plural.
    if(t-1)
    {
        cout << "You have entered " << t <<" characters which is not equal to 5 characters " << endl;
    }
    else
    {
        cout << "You have entered " << t <<" character which is not equal to 5 characters " << endl;
    }
}


// find_size function finds the size of a given string using a for loop.
int find_size(char *q)
{
    int size;
    for(size=0;size<24;size++)
    {
        if(*(q+size)=='\0')
        {
            break;
        }
    }
    return size;
}


// no_of_invalid_char function counts the no. of invalid characters(not in range A to Z) in a given string using a for loop.
int no_of_invalid_char(char *q)
{
    int count = 0;
    for(int i=0;i<5;i++)
    {
        if(*(q+i) < 'A' || *(q+i) > 'Z')
        {
            count++;
        }
    }
    return count;
}


// help function helps the user by printing the rules of the game whenever called upon.
void help()
{
    cout << "The rules of the game are as follows: \n \n 1) You have 6 attempts to find a 5 letter word \n 2) After each attempt, you will get a Yes/Half/No for each letter. Their meanings are as follows: \n     a) Yes : Correct letter at correct position. \n     b) Half: The letter is part of the answer, but at a different position. \n     c) No  : The letter does not appear in the solution. \n 3) Please enter 5 CAPITAL LETTERS only \n ";
}


// intro function gives a basic intro about the program and tells the user they type of input needed from them.
void intro()
{
    cout << " Hello World, we are Group 22. \n This is our mini project, an attempt to make a very basic version of the now trending game WORDLE. \n If you need help regarding the rules, please type 'Help' at any point during the game. \n\n Please enter 5 CAPITAL LETTERS only.\n" ;
}


// check_if_help function checks if the user needs help by seeing if the input string is Help(or any caps/small version of it.)
bool check_if_help_needed(char *q, int size)
{
    bool checked = 1;
    char dos[5] = "HELP";
    char tres[5] = "help";
    if(size==4)
    {
        for(int i=0;i<4;i++)
        {
            if(*(q+i)!=dos[i] && *(q+i)!=tres[i])
            {
                checked = 0;
                break;
            }
        }
    }
    else
    {
        checked = 0;
    }
    return checked;
}



int main() {
    //Initializing the answer string.
    char ans[6] ="ALWAR";
    //Declaring a pointer q to store input.
    char *q;
    int correct,size,count;
    //Initializing t(no. of tries left) to 6 
    int t=6;
    intro();
    //The while loop will run until t is 0(6 times, just like the Wordle Game)
    while(t--)
    {
        //Using Dynamic Memory Allocation to store the input string.
        q = new char[24];
        cin.getline (q,24);
        size = find_size(q);
        //Checking if size(input) matches with size(answer)
        if(size==5)
        {
            
            count = no_of_invalid_char(q);
            //Checking if there are no invalid characters
            if(!count)
            {
                //Checking if the input matches answer using check and storing the result in correct. 
                correct = check(ans,q);
                if(correct)
                {
                    cout << endl << "Congratulations! You have successfully completed the game in " << 6 -t << " attempt(s)";
                    break;
                }
                //If wrong and there are still 1 or more chances(t!=0)
                else if(t)
                {
                        cout << endl << "Incorrect! Please try again" << endl;
                }
            }
            else
            { 
                error_invalid_char(count);
            }
            no_of_tries_left(t);
            //Deleting the input string after processing.
            delete []q;
        }
        else
        {
            if(check_if_help_needed(q,size))
            {
                    help();
                    t++;
            }
            else
            {
                error_no_of_characters(size);
            }
            no_of_tries_left(t);
            //Deleting the input string after processing.
            delete []q;
        }
    }
    return 0;
} 