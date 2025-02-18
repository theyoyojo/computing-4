// Copyright 2015 fredm@cs.uml.edu for 91.204 Computing IV
// Wed Mar 25 06:32:17 2015

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <stdint.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "RB.hpp"

BOOST_AUTO_TEST_CASE(RBcontructor) {
	// normal constructor
	BOOST_REQUIRE_NO_THROW(RB(100));

	// this should fail
	BOOST_REQUIRE_THROW(RB(0), std::exception);
	BOOST_REQUIRE_THROW(RB(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RBenque_dequeue) {
	RB rb(100);

	rb.enqueue(2);
	rb.enqueue(1);
	rb.enqueue(0);

	BOOST_REQUIRE(rb.dequeue() == 2);
	BOOST_REQUIRE(rb.dequeue() == 1);
	BOOST_REQUIRE(rb.dequeue() == 0);

	BOOST_REQUIRE_THROW(rb.dequeue(), std::runtime_error);
}