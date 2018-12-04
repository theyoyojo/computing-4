// Copyright 2018 Joel Savitz
#include "RingBuffer.hpp"
#include <stdexcept>
#include <utility>

RingBuffer::RingBuffer(int capacity) : _buffer(capacity, 0), _size(0) {
  if (capacity < 1) throw std::invalid_argument(
    "RingBuffer constructor: Capacity must be greater than 0!") ;

  _capacity = capacity ;

  _frontIndex = _backIndex = 0 ;
}

int RingBuffer::size() {
  return _size ;
}

bool RingBuffer::isEmpty() {
  return _size == 0 ;
}

bool RingBuffer::isFull() {
  return _size == _capacity ;
}

void RingBuffer::enqueue(int16_t item) {
  if (isFull()) throw std::runtime_error(
    "RingBuffer enqueue: Cannot enqueue to a full ring!") ;

  _buffer.at(_backIndex) = item ;

  ++_size ;
  _backIndex = (_backIndex + 1) % _capacity ;
}

int16_t RingBuffer::dequeue() {
  if (isEmpty()) throw std::runtime_error(
    "RingBuffer dequeue: Cannot dequeue from an empty ring!") ;

  int16_t item = _buffer.at(_frontIndex) ;

  --_size ;
  _frontIndex = (_frontIndex + 1) % _capacity ;

  return std::move(item) ;
}

int16_t RingBuffer::peek() {
  if (isEmpty()) throw std::runtime_error(
    "RingBuffer peek: Cannot peek into an empty ring!") ;

  int16_t item = _buffer.at(_frontIndex) ;

  return std::move(item) ;
}
