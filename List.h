// Implementaion of a singly linked list
// Notes:
// 1. Use a dummy head pointer to avoid checking for an empty list
// References : Stanford's linked list tutorials : http://cslibrary.stanford.edu/
// Mark Allen Weiss - Data structures

// Steps to take:
//1. Define the list interface 
//2. Define List private data
//3. Define the const_iterator protected, private and public member functions
//4. Define iterator is-a const_iterator
//5. Re-use existing functionality (!=, post-incr etc)
// Do not expose Node * to outside world i.e constructors should be protected

#pragma once
template <typename T>

class List {

  private :
    class Node {
      public:
        T data;
        Node *next;

        Node () : data (T()), next(NULL) {}
        Node (const T &v) :data(v), next(NULL) {}
    };

    Node * _head;
    size_t _size;

  public:

    class const_iterator { 
      public:
        const_iterator () : _current (NULL) {}
        const_iterator& operator ++ () {
          _current = _current->next;
          return *this;
        }
        const_iterator operator ++ (int) {
          const_iterator temp = *this;
          ++(*this); //use the pre-increment here
          return temp;
        }
        //return a const object
        const T& operator * () const {
          return retrieve();
        }
        // compare the pointers
        // need not provide these operators for non-const iterators
        // only functions that return iterator or T need to impelment both
        // A const iterator can operate on a non-const object but not vice-versa

        bool operator == ( const const_iterator& rhs) const {
          return this->_current == rhs._current;
        }
        bool operator != (const const_iterator& rhs) const {
          return !(*this== rhs);
        }

      protected:
        Node * _current;
        const_iterator (Node *n) : _current(n) {} //make this protected. no need to expose naked pointers
        T & retrieve () const { return _current->data;}

        friend class List <T>; // the enclosing class does not have access 
    };

    class iterator : public const_iterator {

      public:
        iterator () {} //need to define this otherwise the no arg constructor will not be called
        iterator& operator ++ () {
          this->_current = this->_current->next;
          return *this;
        }
        iterator operator ++ (int) {
          iterator temp = *this;
          ++(*this); //use the pre-increment here
          return temp;
        }

        // two versions need to be provided - const and non-const
        T& operator * () {
          return this->retrieve();
        }
        const T& operator * () const {
          return const_iterator::operator *();
        }
      protected:
        iterator (Node *n) : const_iterator(n) {}
        friend class List <T>;
    };


  private:
    void init() {
      _head = new Node;
      _head->next = NULL;
      _size=0;
    }

    // does all the work
    void push (Node *&n, T v) { 
      Node *item = new Node (v);
      item->next = n;
      n = item;
      ++_size;
    }

  public:
    List () : _size(0) {
      init();
    }
    ~List () {
      clear();
    }

    // iterator access
    List::iterator begin () { return iterator(_head->next);}
    List::const_iterator begin() const { return const_iterator(_head->next);}
    List::iterator end() { return iterator(NULL);}
    List::const_iterator end() const { return const_iterator(NULL);}

    //assignment operator
    List <T> & operator = (const List <T>  &rhs) {
      // check this 
      // not exception safe - what happens if new throws 
      // current list has already been deleted
      if (this != &rhs) { 
        clear();
        init();
        List::const_iterator iter = rhs.begin();
        push(*iter);
        ++iter;
        List::iterator ins = this->begin();
        while (iter != rhs.end()) {
          ins = this->insert(ins, *iter);
          ++iter;
        }
      }
      return *this;
    }
    //copy constructor
    List (const List <T>  &rhs) {
      init();
      *this = rhs; 
    }
    
    bool empty() { return (_size ==0); }
    size_t size() { return _size;}

    T& front () { 
      assert (_size>0); 
      return *begin();
    } 

    void clear() {
      List::const_iterator iter = begin();
      while (iter != end()) {
        List::iterator temp(iter._current->next);
        delete iter._current;
        iter=temp;
      }
      delete _head;
      _size=0;
    }
    void push (T v) { //push @_head of LL
      push(_head->next,v); 
    }
    void append (T v) {
      
      // find the end
      // preserve O(N) complexity
      // O(1) by maintaining _tail

      List::iterator iter = begin();
      if (begin() == end()) {
        push (_head->next,v);
        return;
      }
      while (iter._current->next != NULL) {
        ++iter;
      }
      push(iter._current->next,v);
    }
    void pop() {
      assert(_size > 0);
      remove(begin());
    }
    List::iterator insert (List::iterator iter,  T v) {
      Node *n = iter._current;
      push(n->next,v);
      return iterator(n->next);
    }
    List::iterator find (T item){
      List::iterator iter = begin();
      while (iter != end() ) {
        if (*iter == item) 
          return iter;
        ++iter;
      }
      return end();
    }
    //remove node @iter
    List::iterator remove (List::iterator item) {
      if (item == end())
        return end();
      List::iterator iter = begin();
      Node *prev = _head;
      bool found = false;
      // find the item
      while (iter != end() ) {
        if (iter == item) {
          found = true;
          break;
        }
        prev = iter._current;
        ++iter;
      }
      // delete nodes and reorder the pointers
      if (found) {
        Node *pointo = iter._current->next;
        delete iter._current;
        prev->next = pointo;
        --_size;
        return iterator(pointo);
      }
      return end();
    
    }
    void print () {
      for (List::const_iterator iter= begin(); iter!=end(); ++iter)
        std::cout<<*iter<<" ";
      std::cout<<std::endl;
    }
};


