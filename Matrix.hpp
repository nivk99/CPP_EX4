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
		Matrix(std::vector<double>& matrix,int row,int column) noexcept(false);
		~Matrix() = default;
		Matrix() = default;

		std::vector<double> get_matrix()const noexcept(true);
		int get_colum() const noexcept(true);

		void checkInput(const Matrix& matrix) const noexcept(false);
		static double sum(const Matrix& other) noexcept(true);
		static void add(Matrix& matrix,double scalar) noexcept(true);

        Matrix operator+(const Matrix& other) const noexcept(false);
		Matrix operator+() noexcept(true);
		Matrix operator+(double scalar)const noexcept(true);
        Matrix& operator+=(Matrix& other) noexcept(false);

        Matrix operator-( const Matrix& other) const noexcept(false);
		Matrix operator-() noexcept(true);
		Matrix operator-(double scalar)const noexcept(true);
        Matrix& operator-=(const Matrix& other) noexcept(false);

	    bool operator<(const Matrix& other) const noexcept(false);
        bool operator>(const Matrix& other) const noexcept(false);

		
        bool operator<=(const Matrix& other) const noexcept(false);
        bool operator>=(const Matrix& other) const noexcept(false); 
 

		bool operator!=(const Matrix& other) const noexcept(false);
        bool operator==(const Matrix& other) const noexcept(false);



        Matrix& operator++() noexcept(true);
        Matrix operator++(int) noexcept(true);

		Matrix& operator--()noexcept(true);
        Matrix operator--(int)noexcept(true);

		Matrix operator*(double scalar) const noexcept(true);
		Matrix& operator*=(const double& scalar) noexcept(true);
		Matrix operator*(const Matrix& other) const noexcept(false);
		Matrix& operator*=(const Matrix& other) noexcept(false);

		friend Matrix operator*(double scalar, const Matrix& matrix) noexcept(true);
		friend std::ostream& operator<<(std::ostream &out, const Matrix &matrix) noexcept(true);
        friend std::istream& operator>>(std::istream &in, Matrix &matrix) noexcept(false);

	}; 
	
	
}