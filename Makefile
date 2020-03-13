###############################################################################
## -->Makefile<--
###############################################################################
##
## Programmer : Noah Klein
## Instructor : Price
## Class      : CS5201 Spring 2020
## Assignment : Homework 4 - Implicit Solvers, p-norms, and Insulin/Glucose 
##					Dynamics
## Filename   : Makefile
##
###############################################################################

###############################################################################
#This makefile will build an executable for the 2020-sp-a-hw3-nekgr8 directory.
###############################################################################

CXX = /usr/bin/g++
FLAGS = -W -Wall -g -pedantic-errors
OBJECTS = driver.o\
          PID.o

.SUFFIXES: .cpp

.cpp.o: $<
	${CXX} -c ${FLAGS} $< -o $@

default: all

all: hw4.out

hw4.out: ${OBJECTS}
	${CXX} ${FLAGS} ${OBJECTS} -o $@

clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f hw4.out > /dev/null 2>&1
	-@rm -f ${OBJECTS} > /dev/null 2>&1
	
# Dependency lists for the various source files
driver.o: driver.cpp\
          MyVector.h\
          MyVector.hpp\
          IGsolver.h\
          IGsolver.hpp\
          Heun.h\
          Heun.hpp\
          PID.h
	g++ -c driver.cpp
	
PID.o: PID.cpp\
       MyVector.h\
       MyVector.hpp\
       PID.h
	g++ -c PID.cpp