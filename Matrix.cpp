

/**
 * @file Matrix.cpp
 * @brief This file demonstrates tests for the Matrix class
 * @date 2022-04-06
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "Matrix.hpp"
using namespace zich;
using namespace std;


/**
 * @brief
 * @param matrix:
 * @param row:
 * @param column:
 * @return New matrix
 */
	Matrix::Matrix(std::vector<double>& matrix,int row,int column):_matrix(matrix),_row(row),_column(column)
	{
		if (row<0||column<0)
		{
			throw runtime_error("Invalid input.\n Do not enter a negative number.");

		}
		if (!(matrix.size()==row*column))
		{
			throw runtime_error("Invalid input.\n Do not insert the wrong size of vector.");
		}
		
		
	}
	void Matrix::add(Matrix& matrix,double scalar) 
	{
		for (size_t i = 0; i < matrix._matrix.size(); i++)
		{
			matrix._matrix.at(i)+=scalar;
		}
		
	}

/**
 * @brief
 * @param matrix: 
 * @return
 */
	void Matrix::checkInput(const Matrix& matrix) const
	{
		if(!(this->_row==matrix._row)||!(this->_column== matrix._column))
		{
			throw runtime_error("Invalid input.\n Only matrices of the same size should be compared!.");
		}

	}


/**
 * @brief
 * @return This vector<double>
 */
	std::vector<double> Matrix::get_matrix() const
	{
		return this->_matrix;
	}
	int Matrix::get_colum() const
	{
		return this->_column;
	}


/**
 * New matrix = This matrix + Another matrix
 * @brief
 * @param other
 * @return
 */

	Matrix Matrix::operator+(const Matrix& other) const
	 {
		checkInput( other);
		Matrix mat{*this};
		for(uint i=0;i<mat._matrix.size();i++)
		{
			mat._matrix.at(i)+=other._matrix.at(i);
		}
		 return mat;

	 }

	

	Matrix Matrix::operator+(double scalar)const
	{
		Matrix copy=*this;
		add(copy,scalar);
		return copy;
	}

/**
 * This matrix = + This matrix 
 * @brief
 * @return
 */
	Matrix Matrix::operator+() 
	{
	
		Matrix mat{*this};
		return mat;


	}

/**
 * This matrix = This matrix + Another matrix
 * @brief
 * @param other:
 * @return
 */
    Matrix& Matrix::operator+=(Matrix& other)
	{
		*this=*this+other;
		return *this;

	}

/**
 * New matrix = This matrix - Another matrix
 * @brief
 * @param other:
 * @return
 */
    Matrix Matrix::operator-(const Matrix& other) const
	{
		checkInput( other);
		Matrix mat{*this};
		for(uint i=0;i<mat._matrix.size();i++)
		{
			mat._matrix.at(i)-=other._matrix.at(i);
		}
		return mat;

	}

	Matrix Matrix::operator-(double scalar)const
	{
		Matrix copy=*this;
		add(copy,-(scalar));
		return copy;
	}

/**
 * This matrix = -This matrix
 * @brief
 * @return
 */
	Matrix Matrix::operator-() 
	{
		Matrix mat{*this};
		for(uint i=0;i<mat._matrix.size();i++)
		{
			if(mat._matrix.at(i)==0)
			{
				continue;
			}
			mat._matrix.at(i)=-mat._matrix.at(i);
		}
	
		return mat;

	}

/**
 * This matrix = This matrix - Another matrix
 * @brief
 * @param other: 
 * @return
 */
    Matrix& Matrix::operator-=(const Matrix& other)
	{
		checkInput( other);
		*this=*this-other;
		return *this;

	}

/**
 * @brief
 * @param other: 
 * @return
 */

	double Matrix::sum(const Matrix& other)
	{
		double sum=0;
		for (size_t i = 0; i < other._matrix.size(); i++)
		{
			sum+=other._matrix.at(i);
		}
		return sum;
		
	}
/**
 * false OR true = This matrix < Another matrix
 * @brief
 * @param other:
 * @return false OR true
 */
	bool Matrix::operator<(const Matrix& other) const
	{
		checkInput( other);
		return sum(*this)<sum(other);

	}
/**
 * false OR true = This matrix > Another matrix
 * @brief
 * @param other: 
 * @return false OR true
 */
    bool Matrix::operator>(const Matrix& other) const
	{
		checkInput( other);
		return sum(*this)>sum(other);
	}

/**
 * false OR true = This matrix <= Another matrix
 * @brief
 * @param other: 
 * @return false OR true
 */
    bool Matrix::operator<=(const Matrix& other) const
	{
		checkInput( other);
		return sum(*this)<=sum(other);
	}

/**
 * false OR true = This matrix >= Another matrix
 * @brief
 * @param other:
 * @return false OR true
 */
    bool Matrix::operator>=(const Matrix& other) const
	{
		checkInput( other);
		return sum(*this)>=sum(other);
	}
 
/**
 * false OR true = This matrix != Another matrix
 * @brief
 * @param other: 
 * @return false OR true
 */
	bool Matrix::operator!=(const Matrix& other) const
	{
		return!(*this==other);

	}

/**
 * false OR true = This matrix == Another matrix
 * @brief
 * @param other:
 * @return false OR true
 */
    bool Matrix::operator==(const Matrix& other) const
	{
	   checkInput( other);
		for(uint i=0;i<_matrix.size();i++)
		{
			if(this->_matrix.at(i)!=other._matrix.at(i))
			{
				return false;
			}
		}

		return true;

	}


/**
 * Prefix: ++matrix
 * @brief
 * @return
 */
    Matrix& Matrix::operator++()
	{
		int x=1;
		add(*this,x);
		return *this;

	}

/**
 * Postfix: matrix++
 * @brief
 * @param add:
 * @return
 */
    Matrix Matrix::operator++(int)
	{

		Matrix copy = *this;
		int x=1;
		add(copy,x);
		return copy;

	}

/**
 * Prefix: --matrix
 * @brief
 * @return
 */
	Matrix& Matrix::operator--()
	{
		int x=-1;
		add(*this,x);
		return *this;

	}

/**
 * 
 * Postfix: matrix--
 * @brief
 * @param add: 
 * @return
 */
    Matrix Matrix::operator--(int)
	{
		Matrix copy = *this;
		int x=-1;
		add(copy,x);
		return copy;
	}


/**
 * New matrix= This matrix * Scalar α
 * @brief
 * @param scalar:
 * @return
 */ 
	Matrix Matrix::operator*(double scalar) const
	{
		Matrix m{*this};
		for(uint i=0;i<m._matrix.size();i++)
		{
			m._matrix.at(i)*=scalar;
		}
		return m;

	}

/**
 * This matrix= This matrix * Scalar α
 * @brief 
 * @param scalar:
 * @return
 */
	Matrix& Matrix::operator*=(const double& scalar) 
	{
		*this=*this*scalar;
		return *this;

	}

/**
 * New matrix= This matrix * Another matrix
 * @brief
 * @param othe: 
 * @return
 */
	Matrix Matrix::operator*(const Matrix& other) const
	{
		if(this->_column!=other._row)
		{
			throw runtime_error("Invalid input.\n Only matrices of the same size should be compared!."); 
		}
		size_t size=static_cast<uint>(this->_column*other._row);
		vector<double> vect(size);
		uint col=0;
		uint row=0;
		size_t otherCol=(uint)other._column;
		double sum=0;
		for(uint k=0;k<other._column;k++)
		{
			row=0;
			for(uint i=0;i<this->_matrix.size();i++)
			{
				if(col<this->_column)
				{
					sum+=this->_matrix.at(i)*other._matrix.at(col*otherCol+k);
					col++;
					
				}
				if(col==this->_column)
				{
					vect.at(row*otherCol+k)=sum;
					sum=0;
					col=0;
					row++;
				}
			}

		}
		Matrix mat{vect,this->_row,other._column};

		return mat;

	}

	Matrix& Matrix::operator*=(const Matrix& other)
	{
		*this=*this*other;
		return *this;

	}

/**
 * New matrix = Scalar α * Another matrix 
 * @brief
 * @param scalar:
 * @param matrix:
 * @return
 */
	 Matrix zich::operator*(double scalar, const Matrix& matrix)
	 {
		 return matrix*scalar;
		 
	 }

/**
 * ostream concatenation 
 * @brief
 * @param out:
 * @param matrix:
 * @return
 */
	std::ostream& zich::operator<<(std::ostream& out, const Matrix& matrix)
	{
		int j=0;
		if(matrix._matrix.empty())
		{
			out<<"[]"<<endl;
		}
		for(uint i=0;i<matrix._matrix.size();i++,j++)
		{
			if(j==0)
			{
				out<<"[";
			}
			if(j+1==matrix._column)
			{
				j=-1;
				out<<matrix._matrix.at(i)<<"]"<<endl;
			}
			else if(j<matrix._column)
			{
				out<<matrix._matrix.at(i)<<" ";
			}


		}

		return out;

	}

/**
 * istream 
 * @brief
 * @param in:
 * @param matrix:
 * @return
 */
   std::istream& zich::operator>>(std::istream& in, Matrix& matrix)
	{
		vector<double> mat;
		int row=0;
		int column=0;
		int checkColumn=-1;
		double num=0;
		string str;
		bool checkingDotCharacter=true;
		while(in.peek() == ' ' || in.peek() == '\t'||in.peek()=='\n'||in.peek()=='\r')
		{
            in.ignore();
		}
	    char getInput = in.get(); 
		if(getInput != '[')
		{
			throw invalid_argument("Invalid input\n");

		}
         while(getInput != '\n' && getInput != istream::eofbit)
		 {
			str="";
			checkingDotCharacter=true;
			 if(getInput=='[')
			 {
				getInput=in.get();

				 while (getInput!=']')
				 {
					 if(getInput==' ')
					 {
						column++;
						checkingDotCharacter=true;
						istringstream ss(str);
						double n=0;
						ss >> n;
						mat.push_back(n);
						str="";
						getInput=in.get();
						continue;
					 }
					 if((getInput>='0'&& getInput<='9')||(getInput=='.'&&checkingDotCharacter))
					 {
						 str+=getInput;
						 if(getInput=='.')
						 {
							checkingDotCharacter=false;

						 }
					     getInput=in.get();

					 }
					 else
					 {
						throw invalid_argument("Invalid input!\n");

					 }
				 }

				column++;
				istringstream ss(str);
				ss >> num;
				mat.push_back(num);
				 

			 }
			 if(getInput==']')
			 {
				 getInput=in.get();
				 if(getInput == '\n' || getInput == istream::eofbit)
				 {
					 row++;
					 break;
				 }
				 if(getInput==',')
				 {
					getInput=in.get();
					 if(getInput==' ')
					 {
						 if(checkColumn==-1)
						 {
							 checkColumn=column;
						 }
						 if(checkColumn!=column)
						 {
							throw invalid_argument("Invalid input!\n");

						 }
						row++;
						column=0;
						getInput=in.get();
					 }

				 }
				 else
				 {
					throw invalid_argument("Invalid input!\n");
				 }
			 }
			 else
			 {
				throw invalid_argument("Invalid input!\n");
			
			 }
		 }
		 if(mat.size()!=row*column)
		 {
			throw invalid_argument("Invalid input!\n");

		 }
		 matrix._matrix=mat;
		 matrix._row=row;
		 matrix._column=column;
		return in;

	}
	