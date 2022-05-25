#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List ;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 18. Mai) (Aufgabe 3.10)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  ListNode <T>* node = nullptr;

  /* DESCRIPTION  operator*() */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return node->value;
    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.10 - Teil 1)

  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return &(node->value);
    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.10 - Teil 2)
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Preincrement-Operation for Iterator
    //      (Aufgabe 3.10 - Teil 3)
    node = node->next;
    return *this;
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.10 - Teil 4)
    ListNode <T>* n = node;
    node = node->next;
    return ListIterator<T>{n};
  }


  /* ... */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.10 - Teil 5)
    // Iterators should be the same if they refer to the same node
      if (node == x.node) {
          return true;
      }
    return false;
  } // call it: == it

  /* ... */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.10 - Teil 6)
    // Reuse operator==
      return !operator==(x);
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } 
    else {
      return ListIterator{nullptr};
    }
  }


};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* 
      get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* 
      get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    // not fully implemented yet
    // TODO: do not forget about the initialiser list! (Aufgabe 3.2)
    /* ... */
    List() : first_{ nullptr }, last_{ nullptr }, size_{ 0 }{};

    // test and implement:
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)
    List(List const& C) :size_{ 0 }, first_{ nullptr }, last_{nullptr}{
        auto x = C.first_;
        while (x!= nullptr) {
            push_back(x->value);
            x = x->next;
        }
    };
    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.14)

    //TODO: Initializer-List Konstruktor (3.15 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }


    /* ... */
    // test and implement:
    //TODO: (unifying) Assignment operator (Aufgabe 3.6)
    List& operator=(List l) {//looks pretty wancky 
        std::swap(size_,l.size_);
        std::swap(first_,l.first_);
        std::swap(last_,l.last_);
        return *this;
    };
    /* ... */
    // test and implement:

    bool operator==(List const& rhs) const
    {
        if (size() != rhs.size()) {
            return false;
        }
        auto x = first_;
        auto y = rhs.first_;
        while (x!= nullptr) {
            if (x->value != y->value) {
                return false;
            }
            x = x->next;
            y = y->next;
        }
        return true;
      //TODO: operator== (Aufgabe 3.8)
    }

    bool operator!=(List const& rhs) const
    {
        return !operator==(rhs);
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
    }

    /* ... */
    ~List() {
        clear();
      //TODO: Implement via clear-Method (Aufgabe 3.4)
    } //can not really be tested

    /* ... */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.9)
      return {first_};
    }

    /* ... */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.9)
      return {nullptr};
    }

    /* ... */ 
    // test and implement:
    //TODO: clear()-Method (Aufgabe 3.4)
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    /* ... *///////////////LEEEERE LISTE
    //TODO: member function insert (Aufgabe 3.11)
    ListIterator<T> insert(ListIterator<T> after,auto element) {
        ListNode<T>* a = new ListNode<T>{ element,nullptr,nullptr };
        a->next = after.node;
        a->prev = after.node->prev;
        if (a->prev != nullptr) {
            a->prev->next = a;
            after.node->prev = a;
        }
        else{
            first_ = a;
        }
        ++size_;
        return ListIterator<T>{ a };
    }
    /* ... */
    //TODO: member function erase (Aufgabe 3.12)
    ListIterator<T> erase(ListIterator<T> e) {
        auto prev = e.node->prev;
        auto after = e.node->next
    }
    /* ... */

    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)
    void reverse() {
        if (size_ == 0) {
            return;
        }
        for (auto x = first_;x != nullptr ; x = x->prev) {
            std::swap(x->next, x->prev);
        }
        std::swap(first_, last_);
    }

    /* ... */
    void push_front(T const& element) {
        ListNode<T>* a = new ListNode<T>{element,nullptr,first_};
        if (empty()){
            last_ = a;
        }
        else {
            first_->prev = a;
        }
        first_ = a;
        size_ += 1;
      // TODO: push_front-method (Aufgabe 3.3)
    }

    /* ... */
    void push_back(T const& element) {
        ListNode<T>* a = new ListNode<T>{ element,last_,nullptr };
        if (empty()) {
            first_ = a;
        }
        else {
            last_->next = a;
        }
        last_ = a;
        size_ += 1;
      // TODO: push_back-method (Aufgabe 3.3)
    }

    /* ... */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      else {
          auto next = first_->next;
          if (next != nullptr) {
              next->prev = nullptr;
          }
          else {
              last_ = nullptr;
          }
          delete first_;
          first_ = next;
          size_ -= 1;

      }
      // TODO: remainder of pop_front-method (Aufgabe 3.3)
    }

    /* ... */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      else {
          auto prev = last_->prev;//wird das hier auto deleted ?
          if (prev != nullptr) {
              prev->next = nullptr;
          }
          else {
              first_ = nullptr;
          }
          delete last_;
          last_ = prev;
          size_ -= 1;
      }

      // TODO: remainder of pop_back-method (Aufgabe 3.3)
    }

    /* ... */
    T& front() {
      if(empty()) {
        throw "List is empty";
      }
      return first_->value;
      // TODO: remainder of front-method (Aufgabe 3.3)
    }

    /* ... */
    T& back() {
      if(empty()) {
        throw "List is empty";
      }
      return last_->value;
      // TODO: remainder of back-method (Aufgabe 3.3)
    }

    /* ... */
    bool empty() const {
      // TODO: empty-method (Aufgabe 3.2)
        return size_ == 0;
    };


    /* ... */
    std::size_t size() const{
      // TODO: size-method (Aufgabe 3.2)      
      return size_;
  };


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* ... */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)
template <typename T>
List<T> reverse(List<T> const& l) {
    List<T> liste{l};
    liste.reverse();
    return liste;
}
/* ... */
//TODO: Freie Funktion operator+ (3.15 - Teil 2)


#endif // # define BUW_LIST_HPP