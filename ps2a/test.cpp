#include <iostream>
#include <string>

#include "LFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo) {

  jsavitz::LFSR l("00111", 2);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);

  jsavitz::LFSR l2("00111", 2);
  BOOST_REQUIRE(l2.generate(8) == 198);
}

BOOST_AUTO_TEST_CASE(constructor_test) {

  // Invalid initial bit strings

  // non 0 or 1 characters
  BOOST_CHECK_THROW(jsavitz::LFSR("invalid string",0), const char *) ;

  // Too small
  BOOST_CHECK_THROW(jsavitz::LFSR("",4), const char *) ;
  BOOST_CHECK_THROW(jsavitz::LFSR("10011000101030101",4), const char *) ;

  // Out of bounds tap values (low + high)
  BOOST_CHECK_THROW(jsavitz::LFSR("1110001",-3), const char *) ;
  BOOST_CHECK_THROW(jsavitz::LFSR("1110001",100), const char *) ;

  // Can create an LFSR from 32 bits
  BOOST_CHECK_NO_THROW(jsavitz::LFSR("10110001001001110110010100101010", 23)) ;
  
  // But no more
  BOOST_CHECK_THROW(jsavitz::LFSR("101100010010011101100101001010100", 23), const char *) ;
  
}

BOOST_AUTO_TEST_CASE(step_test) {
  jsavitz::LFSR test1("011001",4) ;

  // Step() return value expected to be true then false
  BOOST_CHECK_EQUAL(test1.step(),1) ;
  BOOST_CHECK_EQUAL(test1.step(),0) ;
  BOOST_CHECK_EQUAL(test1.step(),1) ;
}

BOOST_AUTO_TEST_CASE(generate_test) {
  jsavitz::LFSR test2("01101000010", 8) ;

  // Generate yields expected value
  BOOST_CHECK_EQUAL(test2.generate(5),25) ;
  BOOST_CHECK_EQUAL(test2.generate(5),4) ;
  BOOST_CHECK_EQUAL(test2.generate(5),30) ;
}