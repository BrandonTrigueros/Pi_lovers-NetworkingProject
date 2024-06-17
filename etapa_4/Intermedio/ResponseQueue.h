#ifndef RESPONSEQUEUE_H
#define RESPONSEQUEUE_H

#include <cassert>
#include <memory>
#include <cstdlib>
#include <iostream>

class ResponseQueue {
  private:
    class queue_node {
    public:
      char* request;
      queue_node* next_request;
    };

  public:
    queue_node* head;
    queue_node* tail;

    ResponseQueue();
    ~ResponseQueue();

    void initQueue(ResponseQueue*);
    void destroyQueue(ResponseQueue*);

    bool isEmpty(ResponseQueue*);
    void enqueue(ResponseQueue*, char*);
    char* dequeue(ResponseQueue*, char*); 
    void removeFirstRequest(ResponseQueue*);
    void clearQueue(ResponseQueue*);
};

#endif