
/**
 * @date 2022-04-06                                 @test Test cases
 *                                               / --------------------\
 */


 /** 
 * @file Test.cpp
 * 
 * @brief This file demonstrates tests for the Matrix class
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
 * 
 * 
 */


#include <iostream>
#include <fstream>
#include "doctest.h"
#include "Matrix.hpp"
#include <string>
#include <iomanip>
using namespace std;
using namespace zich;


/**
 * @brief Deletes special characters
 * @param input - String to delete special characters
 * @return string
 */
string nospaces(string input) noexcept(true)
{
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}



/**
 * ********************* @test (1) *********************
 * 
 * @brief Test for constructor. Checks negative numbers and also the size of the matrix
 */
TEST_CASE("Test 1: constructor"){

	SUBCASE("Bad input constructor")
	{
		std::vector<double> vect = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		CHECK_THROWS(Matrix(vect, -3, 3));//The size of the rows is negative
		CHECK_THROWS(Matrix(vect, 3, -3));
        CHECK_THROWS(Matrix(vect, 2, 3));
	}

	SUBCASE("Good input constructor")
	{
		std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		std::vector<double> vect2 = {3, 0, 0, 3, 0, 0};//2*3
		std::vector<double> vect3 = {3, 0 ,0};//3*1
		std::vector<double> vect4 = {};//0*0
		try
		{
			Matrix mat1{vect1, 3, 3};//3*3
			Matrix mat2{vect2, 2, 3};//2*3
			Matrix mat3{vect3, 3, 1};//3*1
			Matrix mat4{vect4, 0, 0};//0*0
		}
		catch(const std::exception& e)
		{
			CHECK_NOTHROW(runtime_error("Correct input"));
		}

	}

}


/**
 * ********************* @test (2) *********************
 * 
 * @brief Input and output test. Checks whether the output is correct and also whether incorrect input can be inserted
 */

TEST_CASE("Test 2: input Output")
{
	SUBCASE("operator<<")
	{
		SUBCASE("Good input operator<<")
		{
			ostringstream os;
			std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			Matrix mat1{vect1, 3, 3};
			os << mat1;  
			/* prints:
			[3 0 0]
			[0 3 0]
			[0 0 3]
			*/

			CHECK_EQ(os.str(), "[3 0 0]\n[0 3 0]\n[0 0 3]\n");
			std::vector<double> vect2 = {1.1, 2.2, 3.3, 4.4};//2*2
			Matrix mat2{vect2, 2, 2};
			os.str(string());
			os << mat2;  
			/* prints:
			[1.1 2.2]
			[3.3 4.4]
			*/

			CHECK_EQ(os.str(), "[1.1 2.2]\n[3.3 4.4]\n");
			os.str(string());
			os<<mat1<<mat2;
			/* prints:
			[3 0 0]
			[0 3 0]
			[0 0 3]
			[1.1 2.2]
			[3.3 4.4]
			*/
			CHECK_EQ(os.str(), "[3 0 0]\n[0 3 0]\n[0 0 3]\n[1.1 2.2]\n[3.3 4.4]\n");

			std::vector<double> vect3 = {};//0*0
			Matrix mat3{vect3, 0, 0};
			os.str(string());
			os<<mat3;
			/* prints:
			[]
			*/
			CHECK_EQ(os.str(),"[]\n");

		}
	}


	SUBCASE("operator>>")
	{
		SUBCASE("Good input operator>>")
		{
			ostringstream os;

			Matrix mat;
			istringstream input1("[1 2 3], [4 5 6], [7 8 9]\n");
			input1 >> mat;
			CHECK(input1);
			os << mat; 
			/* prints:
			[1 2 3]
			[4 5 6]
			[7 8 9]
			*/
			CHECK_EQ(os.str(), "[1 2 3]\n[4 5 6]\n[7 8 9]\n");

			istringstream input2("[1.1 2.2 3.3], [4.4 5.5 6.6], [7.7 8.8 9.9]\n");
			input2 >> mat;
			CHECK(input2);
			os.str(string());
			os << mat; 
			/* prints:
			[1.1 2.2 3.3]
			[4.4 5.5 6.6]
			[7.7 8.8 9.9]
			*/
			CHECK_EQ(os.str(), "[1.1 2.2 3.3]\n[4.4 5.5 6.6]\n[7.7 8.8 9.9]\n");

			istringstream input3("  \r    \t \n\t \n  \r   \n[1.11 2.22 3.33], [4.44 5.55 6.66], [7.77 8.88 9.99]\n");
			input3 >> mat;
			CHECK(input3);
			os.str(string());
			os << mat;
			/* prints:
			[1.1 2.2 3.3]
			[4.4 5.5 6.6]
			[7.7 8.8 9.9]
			*/ 
			CHECK_EQ(os.str(), "[1.11 2.22 3.33]\n[4.44 5.55 6.66]\n[7.77 8.88 9.99]\n");




		}
		SUBCASE("Bad input operator>>")
		{
			Matrix mat;
			istringstream input1("[1 2 3}"); // '}' --> ']'
			CHECK_THROWS( input1 >> mat);

			istringstream input2("[1 2 3] ,[4 4 4]\n");// " ," --> ", "
			CHECK_THROWS( input2 >> mat);

			istringstream input3("[1 2 3], [4 4 4]");// '' --> '\n'
			CHECK_THROWS( input3 >> mat);

			istringstream input4("[1 2 3], [4 4]\n");// len(row[0])!=len(row[1]) --> len(row[0])==len(row[1])
			CHECK_THROWS( input4 >> mat);

			istringstream input5("[1 2 3], [4 4 4],\n");// ",\n" --> '\n'
			CHECK_THROWS( input5 >> mat);

			istringstream input6("[1 2 ,], [4 4 4]\n");// Invalid character(',')
			CHECK_THROWS( input6 >> mat);

			istringstream input7("[1 2 3],  [4 4 4]\n");//Double space("  ")
			CHECK_THROWS( input7 >> mat);

			istringstream input8("[1 2 3] [4 4 4]\n");// No character (',')
			CHECK_THROWS( input8 >> mat);

			istringstream input9("1 2 3], [4 4 4]\n");// No character ('[')
			CHECK_THROWS( input9 >> mat);

			istringstream input10("[1..1 2..2 3..3], [4..4 4..5 4..6]\n");//Double ("..") ".." --> '.'
			CHECK_THROWS( input10 >> mat);


		}



	}
}

/**
 * ********************* @test (3) *********************
 * 
 * @brief  Test test for addition and subtraction. Checks by matrix size
 */

TEST_CASE("Test 3: Addition and subtraction")
{
	SUBCASE("operator+")
	{
		SUBCASE("Bad input operator+")
		{
			std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> vect2 = {3, 0, 0, 3, 0, 0};//2*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 2, 3};
			CHECK_THROWS(mat1+mat2);//Matrices not of the same size

			std::vector<double> vect3 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> vect4 = {3, 0, 0};//3*1
			Matrix mat3{vect3, 3, 3};
			Matrix mat4{vect4, 3, 1};
			CHECK_THROWS(mat3+mat4);//Matrices not of the same size

			std::vector<double> vect5 = {};//0*0
			std::vector<double> vect6 = {3};//1*1
			Matrix mat5{vect5, 0, 0};
			Matrix mat6{vect6, 1, 1};
			CHECK_THROWS(mat5+mat6);//Matrices not of the same size


		}

		SUBCASE("Good input operator+")
		{
			ostringstream os;

			std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> vect2 = {-3, 0, 0, 0, -3, 0, 0, 0, -3};//3*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 3, 3};
			Matrix mat12=mat1+mat2;
			os.str(string());
			os<<mat12;
			CHECK(nospaces(os.str()) == nospaces(           "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));
			
			vect1 = {1, 2, 4, 3};//2*2
			vect2 = {5, 4, 1, 7};//2*2
			Matrix mat3{vect1, 2, 2};
			Matrix mat4{vect2, 2, 2};
			Matrix mat34=mat3+mat4;
			os.str(string());
			os<<mat34;
			CHECK(nospaces(os.str()) == nospaces(           "[6 6]\n"
															"[5 10]"));

			vect1 = {1, 2, 3, 1.5, 5, 6};//2*3
			vect2 = {0, 5, -4, -1.5, 10, 0};//2*3
			Matrix mat5{vect1, 2, 3};
			Matrix mat6{vect2, 2, 3};
			Matrix mat56=mat5+mat6;
			os.str(string());
			os<<mat56;
			CHECK(nospaces(os.str()) == nospaces(           "[1 7 -1]\n"
															"[0 15 6]"));

		}

	}

	SUBCASE("operator+=")
	{
		SUBCASE("Bad  input operator+=")
		{
			std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> vect2 = {3, 0, 0, 3, 0, 0};//2*3
			std::vector<double> vect3 = {};//0*0
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 2, 3};
			Matrix mat3{vect3, 0, 0};
			CHECK_THROWS(mat1+=mat2);//Matrices not of equal sizes
			CHECK_THROWS(mat1+=mat3);//Matrices not of equal sizes

		}

		SUBCASE("Good  input operator+=")
		{
			ostringstream os;

			std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> vect2 = {-3, 0, 0, 0, -3, 0, 0, 0, -3};//3*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 3, 3};
			mat1+= mat2;
			os.str(string());
			os<<mat1;

			CHECK(nospaces(os.str()) == nospaces(           "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));
			
			os.str(string());
			os<<mat2;

			CHECK(nospaces(os.str()) == nospaces(           "[-3 0 0]\n"
															"[0 -3 0]\n"
															"[0 0 -3]"));


			std::vector<double> vect3 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> vect4 = {0,0,0,0,0,0,0,0,0};//3*3
			Matrix mat3{vect3, 3, 3};
			Matrix mat4{vect4, 3, 3};
			mat3+=mat4;
			os.str(string());
			os<<mat3;
			CHECK(nospaces(os.str()) == nospaces(           "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));

		}



	}
	SUBCASE("operator+()")
	{
		ostringstream os; 

		std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		Matrix mat1{vect1, 3, 3};
		+mat1;
		os.str(string());
		os<<mat1;
		CHECK(nospaces(os.str()) == nospaces(               "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));
		
		Matrix mat2=+mat1;
		os.str(string());
		os<<mat2;
		CHECK(nospaces(os.str()) == nospaces(               "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));
		

	}
	SUBCASE("operator-()")
	{
		ostringstream os; 

		std::vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		Matrix mat1{vect1, 3, 3};
		-mat1;
		os.str(string());
		os<<mat1;
		CHECK(nospaces(os.str()) == nospaces(               "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));
		Matrix mat2=-mat1;
		os.str(string());
		os<<mat2;
		CHECK(nospaces(os.str()) == nospaces(               "[-3 0 0]\n"
															"[0 -3 0]\n"
															"[0 0 -3]"));


	}

	SUBCASE("operator-")
	{

		SUBCASE("Bad  input operator-")
		{
			std::vector<double> vect1 = {1, 3, 1, 0, 1, 2};//3*2
			std::vector<double> vect2 = {0, 0, 7, 5};//4*1
			Matrix mat1{vect1, 3, 2};
			Matrix mat2{vect2, 4, 1};
			CHECK_THROWS(mat1-mat2);//Matrices not of equal sizes
			CHECK_THROWS(mat2-mat1);//Matrices not of equal sizes

		}

		SUBCASE("Good  input operator-")
		{
			ostringstream os; 

			std::vector<double> vect1 = {1, 3, 1, 0, 1, 2};//3*2
			std::vector<double> vect2 = {0, 0, 7, 5, 2, 1};//3*2
			Matrix mat1{vect1, 3, 2};
			Matrix mat2{vect2, 3, 2};
            Matrix mat12=mat1-mat2;
			os.str(string());
			os<<mat12;
			CHECK(nospaces(os.str()) == nospaces(            "[1 3]\n"
															"[-6 -5]\n"
															"[-1 1]"));
			
			std::vector<double> vect3 = {2, 8, 0, 9};//2*2
			std::vector<double> vect4 = {5, 6, 11, 3};//2*2
			Matrix mat3{vect3, 2, 2};
			Matrix mat4{vect4, 2, 2};
		    Matrix mat34=mat3-mat4;
			os.str(string());
			os<<mat34;
			CHECK(nospaces(os.str()) == nospaces(            "[-3 2]\n"
															"[-11 6]"));

		}



	}

	SUBCASE("operator=-")
	{
		SUBCASE("Bad  input operator=-")
		{
			std::vector<double> vect1 = {1, 3, 1, 0, 1, 2};//3*2
			std::vector<double> vect2 = {0, 0, 7, 5};//4*1
			Matrix mat1{vect1, 3, 2};
			Matrix mat2{vect2, 4, 1};
			CHECK_THROWS(mat1-=mat2);//Matrices not of equal sizes

		}
		SUBCASE("Good  input operator=-")
		{
			ostringstream os; 

			std::vector<double> vect1 = {2, 4, 2, 8, 2, 12};//3*2
			std::vector<double> vect2 = {3, 24, 27, 3, 0, 9};//3*2
			Matrix mat1{vect1, 3, 2};
			Matrix mat2{vect2, 3, 2};
			mat1-=mat2;
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(           "[-1 -20]\n"
															"[-25 5]\n"
															"[2 3]"));

		}



	}
	SUBCASE("operator++")//++matrix
	{
		SUBCASE("Good  input operator++")
		{
			ostringstream os; 

			std::vector<double> vect1 = {0, 0, 0, 0, 0, 0};//3*2
			Matrix mat1{vect1, 3, 2};
			++mat1;
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(           "[1 1]\n"
															"[1 1]\n"
															"[1 1]"));
			
			std::vector<double> vect2 = {1.1, 1.1, 1.1, 1.1, 1.1, 1.1};//3*2
			Matrix mat2{vect2, 3, 2};
			CHECK(&mat2==&++mat2);
		    os.str(string());
			os<<mat2;
			CHECK(nospaces(os.str()) == nospaces(           "[2.1 2.1]\n"
															"[2.1 2.1]\n"
															"[2.1 2.1]"));							

		

		}


	}
	SUBCASE("operator++(int)")//matrix++
	{
		SUBCASE("Good  input operator++(int)")
		{
			ostringstream os; 

			std::vector<double> vect1 = {0, 0, 0, 0, 0, 0};//3*2
			Matrix mat1{vect1, 3, 2};
			mat1++;
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(           "[0 0]\n"
															"[0 0]\n"
															"[0 0]"));

			
			Matrix mat2= mat1++;
			os.str(string());
			os<<mat2;
			CHECK(nospaces(os.str()) == nospaces(           "[1 1]\n"
															"[1 1]\n"
															"[1 1]"));


			

		}



	}


	SUBCASE("operator--")//--matrix
	{
		SUBCASE("Good  input operator--")
		{
			ostringstream os;
			std::vector<double> vect1 = {1.1,1.1, 1.1, 1.1, 1.1, 1.1};//3*2
			Matrix mat1{vect1, 3, 2};
			--mat1;
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(           "[0.1 0.1]\n"
															"[0.1 0.1]\n"
															"[0.1 0.1]"));


		    --mat1;
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(           "[-0.9 -0.9]\n"
															"[-0.9 -0.9]\n"
															"[-0.9 -0.9]"));



		}

	}
	SUBCASE("operator--(int)")//matrix--
	{
		SUBCASE("Good  input operator--(int)")
		{
			ostringstream os;
			std::vector<double> vect1 = {1.1,1.1, 1.1, 1.1, 1.1, 1.1};//3*2
			Matrix mat1{vect1, 3, 2};
			mat1--;
			os.str(string());
			os<<mat1;

			CHECK(nospaces(os.str()) == nospaces(           "[1.1 1.1]\n"
															"[1.1 1.1]\n"
															"[1.1 1.1]"));
			Matrix mat2 =mat1--;
			os.str(string());
			os<<mat2;
			CHECK(nospaces(os.str()) == nospaces(           "[0.1 0.1]\n"
															"[0.1 0.1]\n"
															"[0.1 0.1]"));




		}



	}





}

/**
 * ********************* @test (4) *********************
 * 
 * @brief  The multiplication test. Result tests and also whether it is possible to multiply between 2 matrices
 */
TEST_CASE("Test 4: multiplication")
{

	SUBCASE("operator*(double scalar)")
	{
		ostringstream os;

		std::vector<double> vect1 = {5,7,3.3,5.5,7.7,8.8,3,2,0};//3*3
		Matrix mat1{vect1, 3, 3};
		Matrix mat2=mat1*5;
		os.str(string());
		os<<mat2;
		CHECK(nospaces(os.str()) == nospaces(               "[25 35 16.5]\n"
															"[27.5 38.5 44]\n"
															"[15 10 0]"));	
		os.str(string());
		os<<mat1;	
		CHECK(nospaces(os.str()) == nospaces(               "[5 7 3.3]\n"
															"[5.5 7.7 8.8]\n"
															"[3 2 0]"));	

		Matrix mat3=mat1*0;
		os.str(string());
		os<<mat3;
		CHECK(nospaces(os.str()) == nospaces(               "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));	
	


	}
	SUBCASE("operator*=(double scalar)")
	{
		ostringstream os;

		std::vector<double> vect1 = {5,7,3.3,5.5,7.7,8.8,3,2,0};//3*3
		Matrix mat1{vect1, 3, 3};
		mat1*=5;
		os.str(string());
		os<<mat1;
		CHECK(nospaces(os.str()) == nospaces(               "[25 35 16.5]\n"
															"[27.5 38.5 44]\n"
															"[15 10 0]"));	

		mat1*=0;
		os.str(string());
		os<<mat1;
		CHECK(nospaces(os.str()) == nospaces(               "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));	


	}
	SUBCASE("operator*(Matrix other)")
	{
		SUBCASE("Good  input operator*(Matrix other)")
		{
			ostringstream os;
			std::vector<double> vect1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> vect2 = {5,7.7,5.8,3,4.2,1.1,0,5,2.2};//3*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 3, 3};
			Matrix mat3=mat1*mat2;
			os.str(string());
			os<<mat3;
			CHECK(nospaces(os.str()) == nospaces(               "[56 123.3 65.9]\n"
																"[50.6 118.69 59.73]\n"
																"[11 61.1 27.8]"));	
			
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(               "[7 7 8]\n"
																"[5.5 7.7 8.8]\n"
																"[1 2 9]"));	
			os.str(string());
			os<<mat2;
			CHECK(nospaces(os.str()) == nospaces(               "[5 7.7 5.8]\n"
																"[3 4.2 1.1]\n"
																"[0 5 2.2]"));	

		}
		SUBCASE("Bad input operator*(Matrix other)")
		{
			std::vector<double> vect1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> vect2 = {1,2,3,4,5,6};//2*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 2, 3};
			CHECK_THROWS(mat1*mat2);//Matrices not of equal sizes (3*3) x (2*3)
		
			
		}
		



	}

	SUBCASE("operator*=(Matrix other)")
	{
		SUBCASE("Good  input operator*=(Matrix other)")
		{
			ostringstream os;
			std::vector<double> vect1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> vect2 = {5,7.7,5.8,3,4.2,1.1,0,5,2.2};//3*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 3, 3};
			mat1*=mat2;
			os.str(string());
			os<<mat1;
			CHECK(nospaces(os.str()) == nospaces(               "[56 123.3 65.9]\n"
																"[50.6 118.69 59.73]\n"
																"[11 61.1 27.8]"));	
			os.str(string());
			os<<mat2;
			CHECK(nospaces(os.str()) == nospaces(               "[5 7.7 5.8]\n"
																"[3 4.2 1.1]\n"
																"[0 5 2.2]"));	




		}
		SUBCASE("Bad input operator*=(Matrix other)")
		{
			std::vector<double> vect1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> vect2 = {1,2,3,4,5,6};//2*3
			Matrix mat1{vect1, 3, 3};
			Matrix mat2{vect2, 2, 3};
			CHECK_THROWS(mat1*=mat2);//Matrices not of equal sizes (3*3) x (2*3)

			
		}


	}
	SUBCASE("operator*(double scalar,Matrix matrix)")
	{
		ostringstream os;

		std::vector<double> vect1 = {5,7,3.3,5.5,7.7,8.8,3,2,0};//3*3
		Matrix mat1{vect1, 3, 3};
		Matrix mat2=5*mat1;
		os.str(string());
		os<<mat2;
		CHECK(nospaces(os.str()) == nospaces(               "[25 35 16.5]\n"
															"[27.5 38.5 44]\n"
															"[15 10 0]"));	
		os.str(string());
		os<<mat1;	
		CHECK(nospaces(os.str()) == nospaces(               "[5 7 3.3]\n"
															"[5.5 7.7 8.8]\n"
															"[3 2 0]"));



	}


}



/**
 * ********************* @test (5) *********************
 * 
 * @brief  Comparative tests. Checks whether unequal size matrices can be compared
 */
TEST_CASE("Test 5: compare")
{
	SUBCASE("Bad  input operator <, >,=>,<= ,==,!=")
	{
		bool bo;
		std::vector<double> vect1 = {1, 3, 1, 0, 1, 2};//3*2
		std::vector<double> vect2 = {0, 0, 7, 5};//4*1
		Matrix mat1{vect1, 3, 2};
		Matrix mat2{vect2, 4, 1};
		CHECK_THROWS(bo=mat1>mat2);//Unequal sizes
		CHECK_THROWS(bo=mat1>=mat2);//Unequal sizes
		CHECK_THROWS(bo=mat1<mat2);//Unequal sizes
		CHECK_THROWS(bo=mat1<=mat2);//Unequal sizes
		CHECK_THROWS(bo=mat1==mat2);//Unequal sizes
		CHECK_THROWS(bo=mat1!=mat2);//Unequal sizes

	}
	SUBCASE("Good  input operator <, >,>=,<=,==,!=")
	{
		std::vector<double> vect1 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> vect2 = {3, 24, 27, 3, 0, 9};//3*2--66
		Matrix mat1{vect1, 3, 2};
		Matrix mat2{vect2, 3, 2};
		CHECK_EQ(true,mat2>mat1);
		CHECK_EQ(false,mat2<mat1);
		CHECK_EQ(true,mat2>=mat1);
		CHECK_EQ(false,mat2<=mat1);

		std::vector<double> vect3 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> vect4 = {12, 4,6, 6, 2, 0};//3*2--66
		Matrix mat3{vect3, 3, 2};
		Matrix mat4{vect4, 3, 2};
		CHECK_EQ(true,mat3>=mat4);
		CHECK_EQ(true,mat3<=mat4);

		std::vector<double> vect5 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> vect6 = {12, 4,0, 0, 8, 6};//3*2--30
		Matrix mat5{vect5, 3, 2};
		Matrix mat6{vect6, 3, 2};
		CHECK_EQ(true,mat3>=mat4);
		CHECK_EQ(true,mat3<=mat4);


		std::vector<double> vect7 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> vect8 = {2, 4, 2, 8, 2, 12};//3*2--30
		Matrix mat7{vect7, 3, 2};
		Matrix mat8{vect8, 3, 2};
		CHECK_EQ(true, mat7==mat8);
		CHECK_EQ(false,mat7!=mat8);

	}


}











