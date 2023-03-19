//File: trackingDeque.h
//Name: Rohit Raut

#ifndef TRACKINGDEQUE_H
#define TRACKINGDEQUE_H

#include <deque>
#include <iostream>
using namespace std;
template<typename TYPE>
class TrackingDeque : public std::deque<TYPE> {
  public:
    TrackingDeque();
    ~TrackingDeque();
    void push_back(const TYPE& let);
    void push_front(const TYPE& let);

  private:
    int maximum_size;
};

template<typename TYPE>
TrackingDeque<TYPE>::TrackingDeque() : maximum_size(0)
{}

template<typename TYPE>
TrackingDeque<TYPE>::~TrackingDeque()
{
  cout << "---> "<<maximum_size<< " <---\n";
}

template<typename TYPE>
void TrackingDeque<TYPE>::push_front(const TYPE& let)
{
  std::deque<TYPE>::push_front(let);
  if(std::deque<TYPE>::size() > maximum_size)
    maximum_size=std::deque<TYPE>::size();
}

template<typename TYPE>
void TrackingDeque<TYPE>::push_back(const TYPE& let)
{
  std::deque<TYPE>::push_back(let);
  if(std::deque<TYPE>::size() > maximum_size)
    maximum_size=std::deque<TYPE>::size();
}

#endif