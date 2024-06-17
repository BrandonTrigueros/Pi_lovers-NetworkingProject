#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <cassert>
#include <memory>
#include <cstdlib>
#include <iostream>

class RequestQueue {
  private:
    class queue_node {
    public:
      char* request;
      queue_node* next_request;
    };

  public:
    queue_node* head;
    queue_node* tail;

    RequestQueue();
    ~RequestQueue();

    void initQueue(RequestQueue*);
    void destroyQueue(RequestQueue*);

    bool isEmpty(RequestQueue*);
    void enqueue(RequestQueue*, char*);
    char* dequeue(RequestQueue*, char*); 
    void removeFirstRequest(RequestQueue*);
    void clearQueue(RequestQueue*);
};

#endif