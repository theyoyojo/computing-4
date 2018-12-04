// Copyright 2018 Joel Savitz
#define BOOST_TEST_MODULE jsavitz
#include <boost/test/unit_test.hpp>

#include "RingBuffer.hpp"

BOOST_AUTO_TEST_CASE(RingBuffer_isEmpty) {
  RingBuffer rb(2) ;


  BOOST_REQUIRE(rb.isEmpty() == true) ;

  rb.enqueue(10) ;

  BOOST_REQUIRE(rb.isEmpty() == false) ;

  rb.dequeue() ;

  BOOST_REQUIRE(rb.isEmpty() == true) ;

  rb.enqueue(10) ;
  rb.enqueue(20) ;

  BOOST_REQUIRE(rb.isEmpty() == false) ;

  rb.dequeue() ;
  rb.dequeue() ;

  BOOST_REQUIRE(rb.isEmpty() == true) ;
}

BOOST_AUTO_TEST_CASE(RingBuffer_overload) {
  RingBuffer rb(10) ;

  for (int i = 0; i < 10; ++i) {
    rb.enqueue(i) ;
  }


  BOOST_REQUIRE_THROW(rb.enqueue(11), std::runtime_error) ;

  rb.dequeue() ;
  BOOST_REQUIRE_NO_THROW(rb.enqueue(11)) ;

  auto loadThreehundredSevens = [&](RingBuffer& buff) {
    for (int i = 0; i < 300; i++) buff.enqueue(7) ;
  } ;

  BOOST_REQUIRE_THROW(loadThreehundredSevens(rb), std::runtime_error) ;
}

BOOST_AUTO_TEST_CASE(RingBuffer_peek) {
  RingBuffer rb(20) ;

  BOOST_REQUIRE_THROW(rb.peek(), std::runtime_error) ;

  rb.enqueue(10) ;

  BOOST_REQUIRE_NO_THROW(rb.peek()) ;

  BOOST_REQUIRE(rb.peek() == 10) ;

  rb.dequeue() ;

  BOOST_REQUIRE_THROW(rb.peek(), std::runtime_error) ;
}

BOOST_AUTO_TEST_CASE(RingBuffer_size) {
  RingBuffer rb(300) ;

  BOOST_REQUIRE(rb.size() == 0) ;

  rb.enqueue(1) ;

  BOOST_REQUIRE(rb.size() == 1) ;

  for (int i = 1 ; i < 300; ++i) {
    rb.enqueue(1) ;
  }

  BOOST_REQUIRE(rb.size() == 300) ;

  for (int i = 0 ; i < 100; ++i) {
    rb.dequeue() ;
  }
  BOOST_REQUIRE(rb.size() == 200) ;
  for (int i = 0 ; i < 200; ++i) {
    rb.dequeue() ;
  }
  BOOST_REQUIRE(rb.size() == 0) ;
}

BOOST_AUTO_TEST_CASE(RingBuffer_isFull) {
  RingBuffer rb(2) ;

  BOOST_REQUIRE(rb.isFull() == false) ;

  rb.enqueue(2) ;

  BOOST_REQUIRE(rb.isFull() == false) ;

  rb.enqueue(2) ;

  BOOST_REQUIRE(rb.isFull() == true) ;

  rb.dequeue() ;

  BOOST_REQUIRE(rb.isFull() == false) ;
  rb.dequeue() ;
  BOOST_REQUIRE(rb.isFull() == false) ;
}

BOOST_AUTO_TEST_CASE(RingBuffer_dataFidelity) {
  RingBuffer rb(10) ;

  for (int i = 0; i < 5 ; ++i) {
    rb.enqueue(i) ;
  }
  for (int i = 0; i < 5 ; ++i) {
    rb.dequeue() ;
  }

  for (int i = 0; i < 10 ; ++i) {
    rb.enqueue(i) ;
  }

  for (int i = 0; i < 10 ; ++i) {
    BOOST_REQUIRE(rb.dequeue() == i) ;
  }
}
