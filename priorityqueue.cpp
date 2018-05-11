#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	if(size_ == 0){nodes_.resize(1);}
    nodes_.push_back(kv);
    ++size_;
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
    return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {
	removeNode(1);
}

bool PriorityQueue::isEmpty() const {
    return size_ == 0;
}

size_t PriorityQueue::size() const {
    return nodes_.size() - 1;
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
	return result;
}

void PriorityQueue::heapifyUp(size_t i) {

    while(nodes_[i].first < nodes_[i/2].first){
        std::swap(nodes_[i], nodes_[i/2]);
        heapifyUp(i/2);
    }
}

void PriorityQueue::heapifyDown(size_t i) {
	size_t rChild = 2*i + 1;
    size_t lChild = 2*i;
    size_t heapify;

    if((lChild <= size_) && nodes_[i] > nodes_[lChild]){
        heapify = lChild;
    }
    else heapify = i;
    if((rChild <= size_) && nodes_[i] > nodes_[rChild]){
        heapify = rChild;
    }

    if(heapify != i){
        std::swap(nodes_[i], nodes_[heapify]);
        heapifyDown(heapify);
    }

}

void PriorityQueue::removeNode(size_t i) {
    std::swap(nodes_[i], nodes_[size_]);
    nodes_.pop_back();
    --size_;
    heapifyDown(i);
}

Key PriorityQueue::getKey(size_t i) {
    return nodes_[i].first;
}

Value PriorityQueue::getValue(size_t i) {
    return nodes_[i].second;
}

