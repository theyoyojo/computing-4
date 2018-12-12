// Copyright 2018 Joel Savitz
#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <cstdint>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(int capacity) ;

  int size() ;

  int capacity() ;

  bool isEmpty() ;

  void empty() ;

  bool isFull() ;

  void enqueue(int16_t item) ;

  int16_t dequeue() ;

  int16_t peek(std::size_t offset = 0) ;

 private:
  std::vector<int16_t> _buffer ;

  std::size_t _frontIndex ;

  std::size_t _backIndex ;

  std::size_t _size ;

  std::size_t _capacity ;
} ;  // RingBuffer

#endif  // RING_BUFFER_HPP
