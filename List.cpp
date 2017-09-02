#include <iostream>
#include <cassert>
#include "List.h" 

using namespace std;
int main() {
  List <int> l;
  cout<<"Before: empty list"<<std::endl;
  l.print();
  
  l.push(2);
  cout<<"After push 2 "<<std::endl;
  l.print();
  
  l.append(3);
  cout<<"After append 3"<<std::endl;
  l.print();
  
  l.push(1);
  cout<<"After push 1 "<<std::endl;
  l.print();
  cout<< "l.front() " <<l.front()<<" l.size() "<<l.size()<<endl;
  
  cout<<"After pop twice"<<std::endl;
  l.pop();
  l.pop();
  l.print();
  cout<< "l.front() " <<l.front()<<" l.size() "<<l.size()<<endl;
  
  cout<<"After pop again and append 1"<<std::endl;
  l.pop();
  l.append(1);
  l.print();
  
  cout<<"After append 2,3,4"<<std::endl;
  l.append(2);
  l.append(3);
  l.append(4);
  cout<< "l.front() " <<l.front()<<" l.size() "<<l.size()<<endl;
  l.print();
  
  List<int>::iterator iter = l.begin();
  cout<<"After remove 2"<<std::endl;
  iter = l.remove(++iter);
  l.print();
  
  cout<<"After remove 3"<<std::endl;
  iter = l.remove(iter);
  cout<< "l.front() " <<l.front()<<" l.size() "<<l.size()<<endl;
  l.print();
  
  cout<<"After insert 5,6"<<std::endl;
  iter = l.insert(iter,5);
  iter = l.insert(iter,6);
  cout<< "l.front() " <<l.front()<<" l.size() "<<l.size()<<endl; 
  l.print();
  cout<< "l.front() " <<l.front()<<" l.size() "<<l.size()<<endl; 
  cout<<"Test copy construction"<<std::endl;
  List<int> l2(l);
  l2.print();
  
  cout<<"Test assignment operator"<<std::endl;
  List<int> l3;
  l3=l;
  l3.print();
  
  cout<<"Test find 5:"<< *l3.find(5)<<std::endl;
  
  return 0;
}
