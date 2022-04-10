

/**
 * @file Matrix.cpp
 * @brief This file describes all the implementations of the Matrix class
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
 * @brief This method is a constructor of the class
 * @param matrix: Vector of double numbers
 * @param row: Number of rows in the matrix
 * @param column:The column number in the matrix
 * @return New matrix
 */
	Matrix::Matrix(std::vector<double>& matrix,int row,int column) noexcept(false) 
	{
		if (row<0||column<0)
		{
			throw runtime_error("Invalid input.\n Do not enter a negative number.");

		}
		if (!(matrix.size()==row*column))
		{
			throw runtime_error("Invalid input.\n Do not insert the wrong size of vector.");
		}
		this->_matrix=matrix;
		this->_row=row;
		this->_column=column;
		
		
	}


	/**
	 * @brief This method adds a scalar to the matrix
	 * @param matrix: Vector of double numbers
	 * @param scalar: Number to be added to the matrix
	 * @return: This is a method that does not return
	 */
	void Matrix::add(Matrix& matrix,double scalar) noexcept(true) 
	{
		for (size_t i = 0; i < matrix._matrix.size(); i++)
		{
			matrix._matrix.at(i)+=scalar;
		}
		
	}


/**
 * @brief: This method tests the input of the matrix. If not correct throws an error
 * @param matrix: Vector of double numbers
 * @return: This is a method that does not return
 */
	void Matrix::checkInput(const Matrix& matrix) const noexcept(false)
	{
		if(!(this->_row==matrix._row)||!(this->_column== matrix._column))
		{
			throw runtime_error("Invalid input.\n Only matrices of the same size should be compared!.");
		}

	}


/**
 * @brief This method returns the matrix
 * @return This vector<double>
 */
	std::vector<double> Matrix::get_matrix() const noexcept(true)
	{
		return this->_matrix;
	}

/**
 * @brief This method returns the column number in the matrix
 * @return This column
 */
	int Matrix::get_colum() const noexcept(true)
	{
		return this->_column;
	}


/**
 * @brief This method returns the row number in the matrix
 * @return This row
 */

	int Matrix::get_row() const noexcept(true)
	{
		return this->_row;

	}


/**
 * New matrix = This matrix + Another matrix
 * @brief This method accepts this matrix and another matrix and connects two matrices
 * @param other: Another matrix to add
 * @return New matrix after addition
 */
	Matrix Matrix::operator+(const Matrix& other) const noexcept(false)
	 {
		checkInput( other);
		Matrix mat{*this};
		for(uint i=0;i<mat._matrix.size();i++)
		{
			mat._matrix.at(i)+=other._matrix.at(i);
		}
		 return mat;

	 }

	
/**
 * New matrix = This matrix + scalar
 * @brief This method accepts this matrix and scalar and connects a matrix to a scalar.
 * @param scalar: Another matrix to add
 * @return New matrix after addition
 */
	Matrix Matrix::operator+(double scalar)const noexcept(true)
	{
		Matrix copy{*this};
		add(copy,scalar);
		return copy;
	}

/**
 * This matrix = + This matrix 
 * @brief This method is an Onri operator on the matrix
 * @return New matrix after addition
 */
	Matrix Matrix::operator+()  noexcept(true)
	{
	
		Matrix mat{*this};
		return mat;


	}

/**
 * This matrix = This matrix + Another matrix
 * @brief This method adds to this matrix another matrix
 * @param other:Another matrix to add
 * @return Reference to the matrix
 */
    Matrix& Matrix::operator+=(Matrix& other) noexcept(false)
	{
		*this=*this+other;
		return *this;

	}

/**
 * New matrix = This matrix - Another matrix
 * @brief This method subtracts between two matrices
 * @param other:Another subtraction matrix
 * @return New matrix after subtraction
 */
    Matrix Matrix::operator-(const Matrix& other) const noexcept(false)
	{
		checkInput( other);
		Matrix mat{*this};
		for(uint i=0;i<mat._matrix.size();i++)
		{
			mat._matrix.at(i)-=other._matrix.at(i);
		}
		return mat;

	}


/**
 * New matrix = This matrix - scalar
 * @brief This method subtracts between matrix and scalar
 * @param scalar:Number to subtract the matrix
 * @return New matrix after subtraction
 */
	Matrix Matrix::operator-(double scalar)const noexcept(true)
	{
		Matrix copy{*this};
		add(copy,-(scalar));
		return copy;
	}


/**
 * This matrix = -This matrix
 * @brief This method turns any number in the matrix into a negative
 * @return New matrix after subtraction
 */
	Matrix Matrix::operator-()  noexcept(true)
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
 * @brief This method reduces from this matrix to another matrix
 * @param other:Another subtraction matrix
 * @return Reference to the matrix after subtraction
 */
    Matrix& Matrix::operator-=(const Matrix& other) noexcept(false)
	{
		checkInput( other);
		*this=*this-other;
		return *this;

	}

/**
 * @brief This method summarizes the components in the matrix
 * @param other:  A matrix to sum 
 * @return The sum of all the matrix components
 */
	double Matrix::sum(const Matrix& other) noexcept(true)
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
 * @brief This method equates two matrices by the sum
 * @param other: Another matrix for comparison
 * @return false OR true
 */
	bool Matrix::operator<(const Matrix& other) const noexcept(false)
	{
		checkInput( other);
		return sum(*this)<sum(other);

	}
/**
 * false OR true = This matrix > Another matrix
 * @brief This method equates two matrices by the sum
 * @param other: Another matrix for comparison
 * @return false OR true
 */
    bool Matrix::operator>(const Matrix& other) const noexcept(false)
	{
		checkInput( other);
		return sum(*this)>sum(other);
	}

/**
 * false OR true = This matrix <= Another matrix
 * @brief This method equates two matrices by the sum
 * @param other: Another matrix for comparison
 * @return false OR true
 */
    bool Matrix::operator<=(const Matrix& other) const noexcept(false)
	{
		checkInput( other);
		return sum(*this)<=sum(other);
	}

/**
 * false OR true = This matrix >= Another matrix
 * @brief This method equates two matrices by the sum
 * @param other:Another matrix for comparison
 * @return false OR true
 */
    bool Matrix::operator>=(const Matrix& other) const noexcept(false)
	{
		checkInput( other);
		return sum(*this)>=sum(other);
	}
 
/**
 * false OR true = This matrix != Another matrix
 * @brief This method checks whether this matrix is not equal to another matrix
 * @param other: Another matrix for comparison
 * @return false OR true
 */
	bool Matrix::operator!=(const Matrix& other) const noexcept(false)
	{
		return!(*this==other);

	}

/**
 * false OR true = This matrix == Another matrix
 * @brief This method tests whether this matrix is equal to another matrix
 * @param other:Another matrix for comparison
 * @return false OR true
 */
    bool Matrix::operator==(const Matrix& other) const noexcept(false)
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
 * @brief This method adds one to this matrix
 * @return Reference to the matrix
 */
    Matrix& Matrix::operator++() noexcept(true)
	{
		int x=1;
		add(*this,x);
		return *this;

	}

/**
 * Postfix: matrix++
 * @brief This method adds one to a new matrix of copying
 * @param int: Distinguishes between n ++ or ++ n
 * @return New matrix after addition
 */
    Matrix Matrix::operator++(int) noexcept(true)
	{

		Matrix copy {*this};
		int x=1;
		add(copy,x);
		return copy;

	}

/**
 * Prefix: --matrix
 * @brief This Subtraction method is one of this matrix
 * @return Reference to the matrix after Subtraction
 */
	Matrix& Matrix::operator--() noexcept(true)
	{
		int x=-1;
		add(*this,x);
		return *this;

	}

/**
 * Postfix: matrix--
 * @brief This Subtraction method is one of a new matrix of copying
 * @param int: Distinguishes between n ++ or ++ n
 * @return New matrix after Subtraction
 */
    Matrix Matrix::operator--(int) noexcept(true)
	{
		Matrix copy {*this};
		int x=-1;
		add(copy,x);
		return copy;
	}


/**
 * New matrix= This matrix * Scalar α
 * @brief This method multiplies by a scalar matrix
 * @param scalar:
 * @return New matrix after doubling in scalar
 */ 
	Matrix Matrix::operator*(double scalar) const noexcept(true)
	{
		Matrix copy{*this};
		for(uint i=0;i<copy._matrix.size();i++)
		{
			copy._matrix.at(i)*=scalar;
		}
		return copy;

	}

/**
 * This matrix= This matrix * Scalar α
 * @brief This method doubles that matrix in the scalar
 * @param scalar:
 * @return Reference to the matrix after multiplication
 */
	Matrix& Matrix::operator*=(const double& scalar) noexcept(true)
	{
		*this=*this*scalar;
		return *this;

	}

/**
 * New matrix= This matrix * Another matrix
 * @brief This method multiplies a matrix by another matrix
 * @param othe: Another matrix for multiplication
 * @return New matrix after multiplication by another matrix
 */
	Matrix Matrix::operator*(const Matrix& other) const noexcept(false)
	{
		//If it is not possible to multiply between two matrices according to the rules of algebra
		if(this->_column!=other._row)
		{
			throw runtime_error("Invalid input.\n Only matrices of the same size should be compared!."); 
		}

		size_t size=static_cast<uint>(this->_column*other._row);//Size of the new matrix
		vector<double> vect(size);//Vector insert the new values after multiplication
		uint col=0;//Column to multiply
		uint row=0;//Row multiply
		size_t otherCol=(uint)other._column;
		double sum=0;//Amount of row double column (by multiplication matrices)
		for(uint k=0;k<other._column;k++)
		{
			row=0;
			for(uint i=0;i<this->_matrix.size();i++)
			{
				//Duplicate a row in a column
				if(col<this->_column)
				{
					sum+=this->_matrix.at(i)*other._matrix.at(col*otherCol+k);
					col++;
					
				}

				//Finish a row row in a column
				if(col==this->_column)
				{
					vect.at(row*otherCol+k)=sum;
					sum=0;
					col=0;
					row++;
				}
			}

		}
		//Introducing values to a new matrix after multiplication
		Matrix mat{vect,this->_row,other._column};

		return mat;

	}

/**
 * This matrix= This matrix * Another matrix
 * @brief This method multiplies a matrix by another matrix
 * @param other: Another matrix for multiplication
 * @return This matrix after multiplication by another matrix
 */
	Matrix& Matrix::operator*=(const Matrix& other) noexcept(false)
	{
		*this=*this*other;
		return *this;

	}

/**
 * New matrix = Scalar α * Another matrix 
 * @brief This method gets a different number and matrix and multiplies
 * @param scalar:Scalar for doubling
 * @param matrix: Matrix for multiplication
 * @return New matrix after multiplication by the matrix in the scalar
 */
	 Matrix zich::operator*(double scalar, const Matrix& matrix) noexcept(true)
	 {
		 return matrix*scalar;
		 
	 }

/**
 * ostream concatenation 
 * @brief This method is the standard output method for the user screen
 * @param out: Reference from ostream
 * @param matrix:Matrix output
 * @return Output to screen
 */
	std::ostream& zich::operator<<(std::ostream& out, const Matrix& matrix) noexcept(true)
	{
		int j=0;
		//If the matrix is empty
		if(matrix._matrix.empty())
		{
			out<<"[]"<<endl;
		}

		//Loop beyond the entire wheelbarrow
		for(uint i=0;i<matrix._matrix.size();i++,j++)
		{
			//Open a row in the matrix
			if(j==0)
			{
				out<<"[";
			}

			//Close row
			if(j+1==matrix._column)
			{
				j=-1;
				out<<matrix._matrix.at(i)<<"]"<<endl;
			}
			//New number
			else if(j<matrix._column)
			{
				out<<matrix._matrix.at(i)<<" ";
			}


		}

		return out;

	}

/**
 * istream 
 * @brief This method receives from the user and inserts into the matrix
 * @param in:Reference to the input of istream
 * @param matrix:A matrix in which we insert the input
 * @return Reference to input
 */
   std::istream& zich::operator>>(std::istream& in, Matrix& matrix) noexcept(false)
	{
		vector<double> mat;//Temporary matrix insert
		int row=0;//The number of rows of the matrix in the input
		int column=0;//Number of columns in the input matrix
		int checkColumn=-1;//Check that the number of columns is equal
		double num=0;//Income of a number
		string str;//A string of the number
		bool checkingDotCharacter=true;//Check that there is no invalid dot character

       
	   //If there are initially saved characters of space, line drop and more
		while(in.peek() == ' ' || in.peek() == '\t'||in.peek()=='\n'||in.peek()=='\r')
		{
            in.ignore();
		}

        
	    char getInput = in.get(); 
		//If the first character is incorrect
		if(getInput != '[')
		{
			throw invalid_argument("Invalid input. The first character is invalid\n");

		}

         
		 //Loop until row descends or ends
         while(getInput != '\n' && getInput != istream::eofbit)
		{
			str="";
			checkingDotCharacter=true;
			 if(getInput=='[')//Open a row in the matrix
			{
				getInput=in.get();

				 while (getInput!=']')//Loop until the row closes
				 {
					 if(getInput==' ')//If there is a new number in the row
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
					 //Checks that the character is a number or a dot
					 if((getInput>='0'&& getInput<='9')||(getInput=='.'&&checkingDotCharacter))
					 {
						 str+=getInput;
						 if(getInput=='.')
						 {
							checkingDotCharacter=false;

						 }
					     getInput=in.get();

					 }
					 //The received character is not a number or the number you typed is incorrect
					 else
					 {
						throw invalid_argument("Invalid input! The received character is not a number or the number you typed is incorrect\n");

					 }
				 }

				column++;//Add the last number in the row
				istringstream ss(str);
				ss >> num;
				mat.push_back(num);

			}

			 if(getInput==']')
			{
				 getInput=in.get();

				 //If the absorption of the matrix has ended
				 if(getInput == '\n' || getInput == istream::eofbit)
				 {
					 row++;
					 break;
				 }
				 //Move to a new row in the matrix
				 if(getInput==',')
				 {
					getInput=in.get();
					 if(getInput==' ')
					 {
						 if(checkColumn==-1)
						 {
							 checkColumn=column;
						 }
						 //Checks that the number of columns is not equal
						 if(checkColumn!=column)
						 {
							throw invalid_argument("Invalid input! The number of columns is not equal\n");

						 }
						row++;//Adding the number of rows
						column=0;
						getInput=in.get();
					 }

				 }
				 //The new row in an invalid matrix.
				 else
				 {
					throw invalid_argument("Invalid input! The new row in an invalid matrix.\n");
				 }
			}

			 //Invalid close or open line character
			 else
			{
				throw invalid_argument("Invalid input! Invalid close or open line character\n");
			
			}
		}
        
		//Finally check if the size of the vectors is not equal to the number of rows multiplied by the number of columns
		if(mat.size()!=row*column)
		{
			throw invalid_argument("Invalid input! The vector size is not equal to the number of columns multiplied by the number of rows\n");

		}
		
		//Enter the values
		matrix._matrix=mat;
		matrix._row=row;
		matrix._column=column;


		return in;

	}
	