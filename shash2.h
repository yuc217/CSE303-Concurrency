#pragma once
#include <mutex>
#include <iostream>
/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist implementation.
///       In addition, the API now allows for multiple keys on each
///       operation.
class shash2 {
struct node{
    int value;
    node * next;
  };

  struct sentinel{
    node * head;
    std::mutex mtx;
  };

  int num;
  sentinel * bucket;
    
public:
  bool myinsert(int key,node * head) {
    if(!head){  // if head NULL insert into head
      head = new node();
      head -> value = key;
    } else {
      node * current = head;
      node * new_node = new node();
      new_node -> value = key;
      if(current->value > key){  // inserted key is less than head, be head
    head = new_node;
    new_node -> next = current;
    return true;
      } else if (current->value == key) {
    return false;  // already exist
      } else { // key > head
    while(current -> next && current->next->value <= key){ 
      if(current->next->value == key){
        return false; //already exist
      } else {  // key > next-val
        current = current -> next;
      }
    } // now key < next-val
    new_node -> next = current -> next;
    current -> next = new_node; // insert after current
      }
    }
    return true;
  }

  bool myremove(int key, node * head) {
    node * current = head;
    node * last;
    if(!current){  // if head is NULL
      return false;
    }
    if(current -> value == key){ // if head is the key
      head = current -> next;
      delete(current);
      return true;
    }
    last = current;
    current = current -> next;
    while(current){
      if(current -> value == key){
    last -> next = current -> next;
    delete(current);
    return true;
      }
      last = current;
      current = current -> next;
    }
    return false;
  }

  bool mylookup(int key, node * head) {
    node * current = head;
    if(!head){ // head null
      return false;
    }
    while(current){
      if(current -> value == key) return true;
      current = current -> next;
    }
    return false;
  }
    /// insert /num/ values from /keys/ array into the hash, and return the
    /// success/failure of each insert in /results/ array.
    void insert(int* keys, bool* results, int num) { }
    /// remove *key* from the list if it was present; return true if the key
    /// was removed successfully.
    void remove(int* keys, bool* results, int num) { }
    /// return true if *key* is present in the list, false otherwise
    void lookup(int* keys, bool* results, int num) { }
    /// constructor code goes here
    shash2(unsigned _buckets) { }
};
