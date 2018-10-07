Name:

Joel Savitz

Representation of Register Bits:

I chose to represent the register bits as a std::string because I thought it would
be an interesting exercise to simulate bit-level operators on a character string container.

I found it to be a little bit tricky.

Boost Unit Tests:

I wrote a block of tests that checks whether the constructor throws errors when given invalid initialization parameters

I wrote another two blocks of tests that check whether the step and generate functions give expected output for known
input/output combinations