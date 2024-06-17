#include "ResponseQueue.h"

ResponseQueue::ResponseQueue() { }

ResponseQueue::~ResponseQueue() {
  // destroyQueue();
}

void ResponseQueue::initQueue(ResponseQueue* queue) {
  queue->head = nullptr;
  queue->tail = nullptr;
}

void ResponseQueue::destroyQueue(ResponseQueue* queue) {
  queue->clearQueue(queue);
}

bool ResponseQueue::isEmpty(ResponseQueue* queue) {
  return queue->head == NULL;
}

void ResponseQueue::enqueue(ResponseQueue* queue, char* request) {
  queue_node* new_node = (queue_node*)calloc(sizeof(queue_node), 1);

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

char* ResponseQueue::dequeue(ResponseQueue* queue, char* request) { }

void ResponseQueue::removeFirstRequest(ResponseQueue* queue) { }

void ResponseQueue::clearQueue(ResponseQueue* queue) { }
