/**
 * @file Matrix.hpp
 * @brief This file describes all the Matrix class methods
 * @date 2022-04-06
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
 * 
 */

#pragma once
#include <iostream>
#include<vector>

namespace zich{

	class Matrix
	{
	private:
		std::vector<double> _matrix;//Vector in the form of a matrix
		int _row;// Number of rows
		int _column;// Number of columns

	public:
	   //constructor and destructor
		Matrix(std::vector<double>& matrix,int row,int column) noexcept(false);
		~Matrix() = default;
		Matrix() = default;
        
		//getesrs
		std::vector<double> get_matrix()const noexcept(true);
		int get_colum() const noexcept(true);
		int get_row() const noexcept(true);
        
		//Help functions
		void checkInput(const Matrix& matrix) const noexcept(false);
		static double sum(const Matrix& other) noexcept(true);
		static void add(Matrix& matrix,double scalar) noexcept(true);
        
		//Connection operator
        Matrix operator+(const Matrix& other) const noexcept(false);
		Matrix operator+() noexcept(true);
		Matrix operator+(double scalar)const noexcept(true);
        Matrix& operator+=(Matrix& other) noexcept(false);
		Matrix& operator++() noexcept(true);
        Matrix operator++(int) noexcept(true);
       
	    //Subtraction operator
        Matrix operator-( const Matrix& other) const noexcept(false);
		Matrix operator-() noexcept(true);
		Matrix operator-(double scalar)const noexcept(true);
        Matrix& operator-=(const Matrix& other) noexcept(false);
		Matrix& operator--()noexcept(true);
        Matrix operator--(int)noexcept(true);

        //Comparison operator by sum
	    bool operator<(const Matrix& other) const noexcept(false);
        bool operator>(const Matrix& other) const noexcept(false);
        bool operator<=(const Matrix& other) const noexcept(false);
        bool operator>=(const Matrix& other) const noexcept(false);

		//Value comparison operator
		bool operator!=(const Matrix& other) const noexcept(false);
        bool operator==(const Matrix& other) const noexcept(false);


       //Duplication operator
		Matrix operator*(double scalar) const noexcept(true);
		Matrix& operator*=(const double& scalar) noexcept(true);
		Matrix operator*(const Matrix& other) const noexcept(false);
		Matrix& operator*=(const Matrix& other) noexcept(false);
        
		//Duplication operator by friend
		friend Matrix operator*(double scalar, const Matrix& matrix) noexcept(true);

		//Input and output operator by friend
		friend std::ostream& operator<<(std::ostream &out, const Matrix &matrix) noexcept(true);
        friend std::istream& operator>>(std::istream &in, Matrix &matrix) noexcept(false);

	}; 
	
	
}