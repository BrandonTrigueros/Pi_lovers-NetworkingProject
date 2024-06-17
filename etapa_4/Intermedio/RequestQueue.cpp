#include "RequestQueue.h"

RequestQueue::RequestQueue() {
}

RequestQueue::~RequestQueue() {
}

void RequestQueue::initQueue(RequestQueue* queue) {
  queue->head = nullptr;
  queue->tail = nullptr;
}

void RequestQueue::destroyQueue(RequestQueue* queue) {
  queue->clearQueue(queue);
}

bool RequestQueue::isEmpty(RequestQueue* queue) {
  return queue->head == NULL;
}

void RequestQueue::enqueue(RequestQueue* queue, char* request) {
  queue_node* new_node = (queue_node*) calloc(sizeof(queue_node), 1);
  if (new_node) {
    new_node->request = request;
    if (queue->tail) {
      queue->tail = queue->tail->next_request = new_node;
    } else {
      queue->head = queue->tail = new_node;
    }
    std::cout << "Request enqueued: " << request << std::endl;
  }
}

char* RequestQueue::dequeue(RequestQueue* queue, char* request) {

}

void RequestQueue::removeFirstRequest(RequestQueue* queue) {

}

void RequestQueue::clearQueue(RequestQueue* queue) {

}

