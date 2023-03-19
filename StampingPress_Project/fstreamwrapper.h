//File : fstreamwrapper.h
//Name : Rohit Raut

#ifndef FSTREAMWRAPPER_H
#define FSTREAMWRAPPER_H

#include<istream>
#include<ostream>
#include<iostream>
#include<fstream>
#include <deque>
#include "TrackingDeque.h"
using namespace std;

class fstreamwrapper : public fstream {
  public:
    fstreamwrapper();
    void file_reading(string search_string, string replace_string, string filename);
    int getposition();
    void display();
    // void replace(char c);
    istream& get (char& c);
    ostream& put (char c);
    
  private:
    std::streampos getpos; ///=====1
    std::streampos putpos; ///=====0
    TrackingDeque<char> dq;
};

#endif
