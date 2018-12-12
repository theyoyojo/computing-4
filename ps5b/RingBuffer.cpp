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

int RingBuffer::capacity() {
  return _capacity ;
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

int16_t RingBuffer::peek(std::size_t offset) {
  if (isEmpty()) throw std::runtime_error(
    "RingBuffer peek: Cannot peek into an empty ring!") ;
  if (offset > _size) throw std::out_of_range(
    "RingBuffer peek: Cannot peek elements past the size of the buffer!") ;

  int16_t item = _buffer.at((_frontIndex + offset) % _capacity) ;

  return std::move(item) ;
}

void RingBuffer::empty() {
  _frontIndex = _backIndex = _size = 0 ;
}