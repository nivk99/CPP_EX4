/**
 * @file Main.hpp
 * @brief This file is associated with all Main.cpp functions
 * @date 2022-04-06
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
 * 
 */


#pragma once
#include "Matrix.hpp"
#include <ctime>
using namespace zich;
using namespace std;

//Comparison of 2 matrices
void compar();

//Input and output of a matrix
void inputOutput();

//Add to matrix
void addition();

//Subtraction for the matrix
void subtraction();

//Matrix multiplication
void multiplication();

//Matrix class errors
void errors();

//
void printMat(vector<double> vect,int row,int column);