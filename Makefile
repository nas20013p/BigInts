# Makefile for BigInts project

CXX        := g++
CXXFLAGS   := -std=c++17 -Iinclude
TESTFLAGS  := $(CXXFLAGS) -Itests


.PHONY: all
all: lab run_tests


lab: src/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@


run_tests: tests/test_all.cpp
	$(CXX) $(TESTFLAGS) $< -o $@


.PHONY: test
test: run_tests
	@./run_tests


.PHONY: clean
clean:
	rm -f lab run_tests
