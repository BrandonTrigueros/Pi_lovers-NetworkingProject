#include "ResponseQueue.h"

ResponseQueue::ResponseQueue() { }

ResponseQueue::~ResponseQueue() { }

void ResponseQueue::initQueue(ResponseQueue* queue) { }

void ResponseQueue::destroyQueue(ResponseQueue* queue) { }

bool ResponseQueue::isEmpty(ResponseQueue* queue) { }

void ResponseQueue::enqueue(ResponseQueue* queue, char* request) { }

char* ResponseQueue::dequeue(ResponseQueue* queue, char* request) { }

void ResponseQueue::removeFirstRequest(ResponseQueue* queue) { }

void ResponseQueue::clearQueue(ResponseQueue* queue) { }
