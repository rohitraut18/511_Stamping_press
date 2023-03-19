//File : fstreamwrapper.cpp
//Name : Rohit Raut

#include "fstreamwrapper.h"
#include <iostream>
#include <deque>
#include <string>
#include <unistd.h>
using namespace std;

fstreamwrapper::fstreamwrapper(): getpos(0), putpos(0) {}

istream & fstreamwrapper::get(char & c) {
  seekg(getpos);
  fstream::get(c); //call inherited behavior
  getpos = fstream::tellg(); //essentially ++getpos
  return *this;
}

ostream & fstreamwrapper::put(char c) {
  seekp(putpos);
  fstream::put(c);
  putpos = fstream::tellp(); //essentially ++putpos
  return *this;
}

void fstreamwrapper::file_reading(string search_string, string replace_string, string fileName) {
  fstreamwrapper f;
  bool isemptyIP = false;
  char c;
  int match = 0;
  const char * filename = fileName.c_str();
  f.open(filename, ios:: in | ios::out);
  while (f.get(c)) {
  //if search string == replace string //////////////////////////////////////////////////////////////////////////////
    if (search_string.length() == replace_string.length()) {
      if (c == search_string[0]) {
        int num_matched = 1;
        for (int i = 1; i < replace_string.length(); ++i) {
          f.get(c);
          if (c == search_string[i]) {
            num_matched++;
          } else {
            break;
          }
        }
        if (num_matched == replace_string.length()) {
          for (int i = 0; i < num_matched; ++i) {
            f.put(replace_string[i]);
          }
        } else {
          for (int i = 0; i < num_matched; ++i) {
            f.put(search_string[i]);
          }
          f.put(c);
        }
      } else {
        f.put(c);
      }
      dq.clear();
    }


  //if search string > replace string////////////////////////////////////////////////////////////////////////////////////
    if (search_string.length() > replace_string.length()) {
      if (c == search_string[0]) {
        int i = 1;
        int num = 2;
        int num2 = 1;
        int num_matched = 0;
        num_matched++;
        for (int i = 1; i < search_string.length(); ++i) {
          f.get(c);
          if (c == search_string[i]) {
            num_matched++;
          } else {

            break;
          }
        }
        if (num_matched == search_string.length()) {
          for (int i = 0; i < replace_string.length(); ++i) {
            f.put(replace_string[i]);
          }
        } else {
          dq.push_front(c);
          f.put(search_string[0]);
          if (num_matched == 1 && f.putpos != -1) {
            f.put(dq.front());
            dq.pop_back();
          } else if (num_matched == 1 && f.putpos == -1) {
            dq.pop_back();
          } else {
            for (int i = 1; i < num_matched; ++i) {
              if (search_string[i] != search_string[0]) {
                f.put(search_string[i]);
              } else {
                if (dq.front() == search_string[1]) {
                  for (int j = 2; j < search_string.length(); ++j) {
                    f.get(c);
                    if (c == search_string[j]) {
                      num++;
                    } else {
                      f.put(search_string[0]);
                      if (dq.front() == search_string[0]) {
                        for (int j = 2; j < search_string.length(); ++j) {
                          f.get(c);
                          if (c == search_string[j]) {
                            num++;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (search_string[i] == search_string[0]) {
                    f.put(search_string[0]);
                  }
                  f.put(search_string[i]);
                  i++;
                }
              }
              if (num == search_string.length()) {
                dq.pop_back();
                for (int i = 0; i < replace_string.length(); ++i) {
                  f.put(replace_string[i]);
                }
              }
            }
          }
        }

        f.clear();
        while (!dq.empty()) {
          if (dq.front() == search_string[0]) {
            for (int i = 0; i < replace_string.length(); ++i) {
              f.clear();
              f.put(replace_string[i]);
            }
            dq.pop_back();
          } else {
            f.put(dq.back());
            dq.pop_back();
          }
        }
      } else {
        f.put(c);
      }
      dq.clear();
    } 
    
  //if search string < replace string /////////////////////////////////////////////////////////////////////////////////////////////
    else if (search_string.length() < replace_string.length()) {
      if (c == search_string[0]) {
        int num_matched = 1;
        for (int i = 1; i < search_string.length(); ++i) {
          f.get(c);
          if (c == search_string[i]) {
            num_matched++;
          } else {
            break;
          }
        }

        if (num_matched == search_string.length()) {
          f.get(c);
          if (f.getpos == -1) {

          } else {
            dq.push_front(c);
          }

          int k = 0;
          for (; k < search_string.length(); ++k) {
            f.clear();
            f.put(replace_string[k]);
          }
          if (search_string.length() != 1) {
            for (int j = k; j < replace_string.length(); ++j) {
              f.get(c);
              if (f.getpos == -1) {
                f.clear();
                f.put(replace_string[j]);
              } else {
                f.clear();
                dq.push_front(c);
                f.put(replace_string[j]);
              }
            }
          } else {
            f.put(replace_string[k]);
            k++;
          }
          while (f.get(c)) {
            dq.push_front(c);
            if (dq.back() == search_string[0]) {
              f.get(c);
              dq.push_front(c);
              for (int i = 0; i < replace_string.length(); ++i) {
                f.clear();
                f.put(replace_string[i]);
              }
              dq.pop_back();
            } else {
              f.get(c);
              f.clear();
              dq.push_front(c);
              if (k < replace_string.length() && search_string.length() == 1) {
                f.clear();
                f.put(replace_string[k]);
                k++;
              }
              f.put(dq.back());
              dq.pop_back();
            }
          }
        } else {
          for (int i = 0; i < num_matched; ++i) {
            f.put(search_string[i]);
          }
        }
        f.clear();
        while (!dq.empty()) {
          if (dq.back() == search_string[0]) {
            f.clear();
            for (int i = 0; i < replace_string.length(); ++i) {

              f.put(replace_string[i]);
            }
            dq.pop_back();
          } else {
            f.put(dq.back());
            dq.pop_back();
          }
        }
      } else {
        f.put(c);
      }
    }
  }
  dq.clear();
  f.close();
  truncate(filename, f.getposition());
}

void fstreamwrapper::display() {
  cout << "p=" << putpos << endl;
  cout << "g=" << getpos << endl;
}

int fstreamwrapper::getposition() {
  return putpos;
}