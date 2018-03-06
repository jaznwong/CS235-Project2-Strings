#include <iostream>
#include <string>
#include <vector>
using namespace std;

void separatestring(string *board, string targetstring, int elements){ //function that separates string into the given number of elements into a dynamically allocated array
  int boardposition = 0; //variable used to compare to given number of elements
  string tempstring; //variable used to add characters from targetstring one by one
  tempstring += targetstring[0]; //first character of targetstring is added to tempstring
  while (boardposition < elements) { //loop runs as long as the number of elements added to the dynamic array has not yet reached the input number of elements
  for (int i = 1; i < targetstring.length(); i++){ //loop ends after every character in targetstring has been iterated through
    if (targetstring[i-1] == targetstring[i]){ //this runs if the current character in targetstring is the same as the character before
      tempstring += targetstring[i]; //character will be added to tempstring
      if (i == targetstring.length()-1){ //if the character being looked at is the last character
        board[boardposition] = tempstring; //tempstring will be added to the dynamic array after the last character is added
      }
    }
    else { //this runs if the current character in targetstring is not the same as the character before
      board[boardposition] = tempstring; //the string containing the characters before the current character will be added to the dynamic array
      tempstring = ""; //tempstring will be reset so current character can be added
      boardposition ++; //board position is increased
      tempstring += targetstring[i]; //the current character will be added to the now emptied tempstring
      if (i == targetstring.length()-1){ //if the character being looked at is the last character
        board[boardposition] = tempstring; //tempstring will be added to the dynamic array after the last character is added
        }
      }
    }
  }
}

bool check(string *board, string targetstring, string& finalstring, int elements, int x){ //function that checks if the elements added to a string are a substring of the targetstring
  string tempfinalstring = finalstring; //whatever is in the finalstring is added to the tempfinalstring
  tempfinalstring += board[x]; //appends to finalstring the element x being looked at
    if (tempfinalstring == targetstring.substr(0, tempfinalstring.length())){ // checks if the tempfinalstring is still a substring after element x is added to the string. this is checked from the beginning of the string to the last element added
      finalstring = tempfinalstring; //if the final string is a substring of the target string, final string will now be set to the tempfinalstring that contains the added element x
      return true; //if the finalstring is a substring of the targetstring, return true
    }
}

bool Solve(string *board, vector<int> &v, string targetstring, string& finalstring, int elements){ //recursion function with backtracking that returns true when the string being checked with the added elements x is equal to the targetstring
  if (finalstring == targetstring){ //if finalstring is equal to targetstring, return true
    return true;
  }
  for (int i = 0; i < elements; i ++){ //for every element in the dynamic array
    if (check(board, targetstring, finalstring, elements, i)){ //if each element added to the string returns true through the check function:
      v.push_back(i); //the element number will be added vector v that contains the sequence of elements in targetstring
      if (Solve(board, v, targetstring, finalstring, elements)){ //if the added element to the string does not work, the last element number that was added to vector v will be removed
        return true;
        v.pop_back(); //this is the case of backtracking
      }
    }
  }
  return false;
}

int main(){
  string targetstring; //variable targetstring that holds the input string of symbols
  cout << "Input the string of symbols: ";
  cin >> targetstring;

  int elements; //variable elements that holds the input number of elements that targetstring is separated into
  cout << "Input the size of elements: ";
  cin >> elements;

  string *b = new string[elements]; //dynamically allocated array that is the size of input elements is made
  vector<int> index; //vector that holds the index of elements in targetstring
  string finalstring;
  string& p = finalstring; //finalstring is a variable passed by reference so it can be used in the check and Solve functions
  separatestring(b, targetstring, elements); //separates the targetstring into elements based on the number of elements given
  Solve(b, index, targetstring, finalstring, elements); //recursive function that adds to vector index the index of elements in targetstring
  cout << finalstring <<endl;
  for (int i = 0; i < index.size(); i++){
    cout << index[i] << " "; //prints out the index of the elements in targetstring
  }

  delete [] b; //dynamically allocated array memory is freed
  return 0;
}
