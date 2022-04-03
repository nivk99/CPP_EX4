/**
 * @file Matrix.hpp
 * @brief This file demonstrates tests for the Matrix class
 * @date 2022-04-06
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
 * 
 */



#pragma once
#include <iostream>
#include<vector>
// #include <fstream>
// #include <sstream>
namespace zich{

	class Matrix
	{
	private:
		std::vector<double> _matrix;
		int _row;
		int _column;

	public:
		Matrix(std::vector<double>& matrix,int row,int column);
		~Matrix() = default;
		Matrix() = default;

		std::vector<double> get_matrix()const;
		int get_colum() const;
		void checkInput(const Matrix& matrix) const;

		static double sum(const Matrix& other);
		static void add(Matrix& matrix,double scalar);




        Matrix operator+(const Matrix& other) const;
		Matrix operator+();
		Matrix operator+(double scalar)const;
        Matrix& operator+=(Matrix& other);

        Matrix operator-( const Matrix& other) const;
		Matrix operator-();
		Matrix operator-(double scalar)const;
        Matrix& operator-=(const Matrix& other);

	    bool operator<(const Matrix& other) const;
        bool operator>(const Matrix& other) const;

		
        bool operator<=(const Matrix& other) const;
        bool operator>=(const Matrix& other) const;
 

		bool operator!=(const Matrix& other) const;
        bool operator==(const Matrix& other) const;



        Matrix& operator++();
        Matrix operator++(int);

		Matrix& operator--();
        Matrix operator--(int);

		Matrix operator*(double scalar) const;
		Matrix& operator*=(const double& scalar);
		Matrix operator*(const Matrix& other) const;
		Matrix& operator*=(const Matrix& other);

		friend Matrix operator*(double scalar, const Matrix& matrix);
		friend std::ostream& operator<<(std::ostream &out, const Matrix &matrix);
        friend std::istream& operator>>(std::istream &in, Matrix &matrix);

	}; 
	
	
}