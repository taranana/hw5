#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void makeWords(string& current, const string& in, const string& floating, size_t index,int dashesLeft, const set<string>&dict, set<string>& results);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  set<string> results;
  string current = in;
  int dashesLeft = 0;
  for(char c : in) {
    if(c == '-') {
      dashesLeft++;
    }
  }
  makeWords(current, in ,floating, 0,dashesLeft, dict, results);
  return results;
}

// Define any helper functions here
void makeWords(string& current, const string& in, const string& floating, size_t index,int dashesLeft, const set<string>& dict, set<string>& results) {
  if(index == in.size()) {
    if(floating.empty() && dict.find(current) != dict.end()) {
      results.insert(current);
    }
    return;
  }

  if(in[index] != '-') {
    current[index] = in[index];
    makeWords(current,in,floating,index +1,dashesLeft, dict, results);
    return;
  }

  int floatingSpace = floating.size(); 

  if(dashesLeft == floatingSpace) {
    for(size_t i = 0; i < floating.size(); i++) {
      char c = floating[i];
      char old = current[index];
      current[index] = c;

      string next = floating;
      next.erase(i,1);

      makeWords(current, in, next, index + 1,dashesLeft-1, dict, results);

      current[index] = old;
    
    }
    return;
  }

  // asoidjadsj idk how to make less than 6 sec
  for(char c = 'a'; c <= 'z'; c++) {
    char old = current[index];
    current[index] = c;

    string next = floating;

    /*for(size_t i = 0; i< next.size(); i++) {
      if(next[i] == c) {
        next.erase(i,1);
        break;
      }
    } */

    if(next.find(c) < next.size()) {
      next.erase(next.find(c),1);
    }


    if((int)next.size() > dashesLeft-1) {
      current[index] = old;
      continue;
    }

  
    makeWords(current, in,next,index+1,dashesLeft-1, dict, results);

    current[index] = old;
  }
}
