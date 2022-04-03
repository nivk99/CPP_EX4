
/**
 *                                                   @test Test cases
 *                                               / --------------------\
 */


 /** 
 * @file Test.cpp
 * 
 * @brief This file demonstrates tests for the Matrix class
 * 
 * @date 2022-04-06
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
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
 * @brief
 * @param
 * @return
 */
string nospaces(string input)
{
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}



/**
 * @brief
 */
TEST_CASE("constructor"){

	SUBCASE("Bad input constructor")
	{
		std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		try
		{
			Matrix a{arr, -3, 3};
			CHECK_NOTHROW(runtime_error("Invalid input.\n Only matrices of the same size"));
		}
		catch(const std::exception& e)
		{
		}

		try
		{
			Matrix a{arr, 3, -3};
			CHECK_NOTHROW(runtime_error("Invalid input.\n Only matrices of the same size"));
		}
		catch(const std::exception& e)
		{
		}

		try
		{
			Matrix a{arr, 2, 3};
			CHECK_NOTHROW(runtime_error("Invalid input.\n Only matrices of the same size"));
		}
		catch(const std::exception& e)
		{
		}

	}

	SUBCASE("Good input constructor")
	{
		std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		std::vector<double> arr2 = {3, 0, 0, 3, 0, 0};//2*3
		std::vector<double> arr3 = {3, 0 ,0};//3*1
		std::vector<double> arr4 = {};//0*0
		try
		{
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 2, 3};
			Matrix a3{arr3, 3, 1};
			Matrix a4{arr4, 0, 0};
		}
		catch(const std::exception& e)
		{
			CHECK_NOTHROW(runtime_error("Correct input"));
		}

	}

}

TEST_CASE("input Output")
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


TEST_CASE("Addition and subtraction")
{
	SUBCASE("operator+")
	{
		SUBCASE("Bad input operator+")
		{
			std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> arr2 = {3, 0, 0, 3, 0, 0};//2*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 2, 3};
			CHECK_THROWS(a1+a2);

			std::vector<double> arr3 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> arr4 = {3, 0, 0};//3*1
			Matrix a3{arr3, 3, 3};
			Matrix a4{arr4, 3, 1};
			CHECK_THROWS(a3+a4);

			std::vector<double> arr5 = {};//0*0
			std::vector<double> arr6 = {3};//1*1
			Matrix a5{arr5, 0, 0};
			Matrix a6{arr6, 1, 1};
			CHECK_THROWS(a5+a6);


		}

		SUBCASE("Good input operator+")
		{
			ostringstream os;

			std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> arr2 = {-3, 0, 0, 0, -3, 0, 0, 0, -3};//3*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 3, 3};
			Matrix a12=a1+a2;
			os.str(string());
			os<<a12;
			CHECK(nospaces(os.str()) == nospaces(           "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));
			
			arr1 = {1, 2, 4, 3};//2*2
			arr2 = {5, 4, 1, 7};//2*2
			Matrix a3{arr1, 2, 2};
			Matrix a4{arr2, 2, 2};
			Matrix a34=a3+a4;
			os.str(string());
			os<<a34;
			CHECK(nospaces(os.str()) == nospaces(           "[6 6]\n"
															"[5 10]"));

			arr1 = {1, 2, 3, 1.5, 5, 6};//2*3
			arr2 = {0, 5, -4, -1.5, 10, 0};//2*3
			Matrix a5{arr1, 2, 3};
			Matrix a6{arr2, 2, 3};
			Matrix a56=a5+a6;
			os.str(string());
			os<<a56;
			CHECK(nospaces(os.str()) == nospaces(           "[1 7 -1]\n"
															"[0 15 6]"));

		}

	}

	SUBCASE("operator+=")
	{
		SUBCASE("Bad  input operator+=")
		{
			std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> arr2 = {3, 0, 0, 3, 0, 0};//2*3
			std::vector<double> arr3 = {};//0*0
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 2, 3};
			Matrix a3{arr3, 0, 0};
			CHECK_THROWS(a1+=a2);
			CHECK_THROWS(a1+=a3);

		}

		SUBCASE("Good  input operator+=")
		{
			ostringstream os;

			std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> arr2 = {-3, 0, 0, 0, -3, 0, 0, 0, -3};//3*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 3, 3};
			a1+= a2;
			os.str(string());
			os<<a1;

			CHECK(nospaces(os.str()) == nospaces(           "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));
			
			os.str(string());
			os<<a2;

			CHECK(nospaces(os.str()) == nospaces(           "[-3 0 0]\n"
															"[0 -3 0]\n"
															"[0 0 -3]"));


			std::vector<double> arr3 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
			std::vector<double> arr4 = {0,0,0,0,0,0,0,0,0};//3*3
			Matrix a3{arr3, 3, 3};
			Matrix a4{arr4, 3, 3};
			a3+=a4;
			os.str(string());
			os<<a3;
			CHECK(nospaces(os.str()) == nospaces(           "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));

		}



	}
	SUBCASE("operator+()")
	{
		ostringstream os; 

		std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		Matrix a1{arr1, 3, 3};
		+a1;
		os.str(string());
		os<<a1;
		CHECK(nospaces(os.str()) == nospaces(               "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));
		
		Matrix a2=+a1;
		os.str(string());
		os<<a2;
		CHECK(nospaces(os.str()) == nospaces(               "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));
		

	}
	SUBCASE("operator-()")
	{
		ostringstream os; 

		std::vector<double> arr1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
		Matrix a1{arr1, 3, 3};
		-a1;
		os.str(string());
		os<<a1;
		CHECK(nospaces(os.str()) == nospaces(               "[3 0 0]\n"
															"[0 3 0]\n"
															"[0 0 3]"));
		Matrix a2=-a1;
		os.str(string());
		os<<a2;
		CHECK(nospaces(os.str()) == nospaces(               "[-3 0 0]\n"
															"[0 -3 0]\n"
															"[0 0 -3]"));


	}

	SUBCASE("operator-")
	{

		SUBCASE("Bad  input operator-")
		{
			std::vector<double> arr1 = {1, 3, 1, 0, 1, 2};//3*2
			std::vector<double> arr2 = {0, 0, 7, 5};//4*1
			Matrix a1{arr1, 3, 2};
			Matrix a2{arr2, 4, 1};
			CHECK_THROWS(a1-a2);
			CHECK_THROWS(a2-a1);

		}

		SUBCASE("Good  input operator-")
		{
			ostringstream os; 

			std::vector<double> arr1 = {1, 3, 1, 0, 1, 2};//3*2
			std::vector<double> arr2 = {0, 0, 7, 5, 2, 1};//3*2
			Matrix a1{arr1, 3, 2};
			Matrix a2{arr2, 3, 2};
            Matrix a12=a1-a2;
			os.str(string());
			os<<a12;
			CHECK(nospaces(os.str()) == nospaces(            "[1 3]\n"
															"[-6 -5]\n"
															"[-1 1]"));
			
			std::vector<double> arr3 = {2, 8, 0, 9};//2*2
			std::vector<double> arr4 = {5, 6, 11, 3};//2*2
			Matrix a3{arr3, 2, 2};
			Matrix a4{arr4, 2, 2};
		    Matrix a34=a3-a4;
			os.str(string());
			os<<a34;
			CHECK(nospaces(os.str()) == nospaces(            "[-3 2]\n"
															"[-11 6]"));

		}



	}

	SUBCASE("operator=-")
	{
		SUBCASE("Bad  input operator=-")
		{
			std::vector<double> arr1 = {1, 3, 1, 0, 1, 2};//3*2
			std::vector<double> arr2 = {0, 0, 7, 5};//4*1
			Matrix a1{arr1, 3, 2};
			Matrix a2{arr2, 4, 1};
			CHECK_THROWS(a1-=a2);

		}
		SUBCASE("Good  input operator=-")
		{
			ostringstream os; 

			std::vector<double> arr1 = {2, 4, 2, 8, 2, 12};//3*2
			std::vector<double> arr2 = {3, 24, 27, 3, 0, 9};//3*2
			Matrix a1{arr1, 3, 2};
			Matrix a2{arr2, 3, 2};
			a1-=a2;
			os.str(string());
			os<<a1;
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

			std::vector<double> arr1 = {0, 0, 0, 0, 0, 0};//3*2
			Matrix a1{arr1, 3, 2};
			++a1;
			os.str(string());
			os<<a1;
			CHECK(nospaces(os.str()) == nospaces(           "[1 1]\n"
															"[1 1]\n"
															"[1 1]"));
			
			std::vector<double> arr2 = {1.1, 1.1, 1.1, 1.1, 1.1, 1.1};//3*2
			Matrix a2{arr2, 3, 2};
			CHECK(&a2==&++a2);
		    os.str(string());
			os<<a2;
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

			std::vector<double> arr1 = {0, 0, 0, 0, 0, 0};//3*2
			Matrix a1{arr1, 3, 2};
			a1++;
			os.str(string());
			os<<a1;
			CHECK(nospaces(os.str()) == nospaces(           "[0 0]\n"
															"[0 0]\n"
															"[0 0]"));

			
			Matrix a2= a1++;
			os.str(string());
			os<<a2;
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
			std::vector<double> arr1 = {1.1,1.1, 1.1, 1.1, 1.1, 1.1};//3*2
			Matrix a1{arr1, 3, 2};
			--a1;
			os.str(string());
			os<<a1;
			CHECK(nospaces(os.str()) == nospaces(           "[0.1 0.1]\n"
															"[0.1 0.1]\n"
															"[0.1 0.1]"));


		    --a1;
			os.str(string());
			os<<a1;
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
			std::vector<double> arr1 = {1.1,1.1, 1.1, 1.1, 1.1, 1.1};//3*2
			Matrix a1{arr1, 3, 2};
			a1--;
			os.str(string());
			os<<a1;

			CHECK(nospaces(os.str()) == nospaces(           "[1.1 1.1]\n"
															"[1.1 1.1]\n"
															"[1.1 1.1]"));
			Matrix a2 =a1--;
			os.str(string());
			os<<a2;
			CHECK(nospaces(os.str()) == nospaces(           "[0.1 0.1]\n"
															"[0.1 0.1]\n"
															"[0.1 0.1]"));




		}



	}





}

TEST_CASE("multiplication")
{

	SUBCASE("operator*(double scalar)")
	{
		ostringstream os;

		std::vector<double> arr1 = {5,7,3.3,5.5,7.7,8.8,3,2,0};//3*3
		Matrix a1{arr1, 3, 3};
		Matrix a2=a1*5;
		os.str(string());
		os<<a2;
		CHECK(nospaces(os.str()) == nospaces(               "[25 35 16.5]\n"
															"[27.5 38.5 44]\n"
															"[15 10 0]"));	
		os.str(string());
		os<<a1;	
		CHECK(nospaces(os.str()) == nospaces(               "[5 7 3.3]\n"
															"[5.5 7.7 8.8]\n"
															"[3 2 0]"));	

		Matrix a3=a1*0;
		os.str(string());
		os<<a3;
		CHECK(nospaces(os.str()) == nospaces(               "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));	
	


	}
	SUBCASE("operator*=(double scalar)")
	{
		ostringstream os;

		std::vector<double> arr1 = {5,7,3.3,5.5,7.7,8.8,3,2,0};//3*3
		Matrix a1{arr1, 3, 3};
		a1*=5;
		os.str(string());
		os<<a1;
		CHECK(nospaces(os.str()) == nospaces(               "[25 35 16.5]\n"
															"[27.5 38.5 44]\n"
															"[15 10 0]"));	

		a1*=0;
		os.str(string());
		os<<a1;
		CHECK(nospaces(os.str()) == nospaces(               "[0 0 0]\n"
															"[0 0 0]\n"
															"[0 0 0]"));	


	}
	SUBCASE("operator*(Matrix other)")
	{
		SUBCASE("Good  input operator*(Matrix other)")
		{
			ostringstream os;
			std::vector<double> arr1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> arr2 = {5,7.7,5.8,3,4.2,1.1,0,5,2.2};//3*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 3, 3};
			cout<<a1*a2;
			Matrix a3=a1*a2;
			os.str(string());
			os<<a3;
			CHECK(nospaces(os.str()) == nospaces(               "[56 123.3 65.9]\n"
																"[50.6 118.69 59.73]\n"
																"[11 61.1 27.8]"));	
			
			os.str(string());
			os<<a1;
			CHECK(nospaces(os.str()) == nospaces(               "[7 7 8]\n"
																"[5.5 7.7 8.8]\n"
																"[1 2 9]"));	
			os.str(string());
			os<<a2;
			CHECK(nospaces(os.str()) == nospaces(               "[5 7.7 5.8]\n"
																"[3 4.2 1.1]\n"
																"[0 5 2.2]"));	

		}
		SUBCASE("Bad input operator*(Matrix other)")
		{
			std::vector<double> arr1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> arr2 = {1,2,3,4,5,6};//2*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 2, 3};
			CHECK_THROWS(a1*a2);
		
			
		}
		



	}

	SUBCASE("operator*=(Matrix other)")
	{
		SUBCASE("Good  input operator*=(Matrix other)")
		{
			ostringstream os;
			std::vector<double> arr1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> arr2 = {5,7.7,5.8,3,4.2,1.1,0,5,2.2};//3*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 3, 3};
			a1*=a2;
			os.str(string());
			os<<a1;
			CHECK(nospaces(os.str()) == nospaces(               "[56 123.3 65.9]\n"
																"[50.6 118.69 59.73]\n"
																"[11 61.1 27.8]"));	
			os.str(string());
			os<<a2;
			CHECK(nospaces(os.str()) == nospaces(               "[5 7.7 5.8]\n"
																"[3 4.2 1.1]\n"
																"[0 5 2.2]"));	




		}
		SUBCASE("Bad input operator*=(Matrix other)")
		{
			std::vector<double> arr1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
			std::vector<double> arr2 = {1,2,3,4,5,6};//2*3
			Matrix a1{arr1, 3, 3};
			Matrix a2{arr2, 2, 3};
			CHECK_THROWS(a1*=a2);

			
		}


	}
	SUBCASE("operator*(double scalar,Matrix matrix)")
	{
		ostringstream os;

		std::vector<double> arr1 = {5,7,3.3,5.5,7.7,8.8,3,2,0};//3*3
		Matrix a1{arr1, 3, 3};
		Matrix a2=5*a1;
		os.str(string());
		os<<a2;
		CHECK(nospaces(os.str()) == nospaces(               "[25 35 16.5]\n"
															"[27.5 38.5 44]\n"
															"[15 10 0]"));	
		os.str(string());
		os<<a1;	
		CHECK(nospaces(os.str()) == nospaces(               "[5 7 3.3]\n"
															"[5.5 7.7 8.8]\n"
															"[3 2 0]"));



	}


}




TEST_CASE("compare")
{
	SUBCASE("Bad  input operator <, >,=>,<= ,==,!=")
	{
		bool bo;
		std::vector<double> arr1 = {1, 3, 1, 0, 1, 2};//3*2
		std::vector<double> arr2 = {0, 0, 7, 5};//4*1
		Matrix a1{arr1, 3, 2};
		Matrix a2{arr2, 4, 1};
		CHECK_THROWS(bo=a1>a2);
		CHECK_THROWS(bo=a1>=a2);
		CHECK_THROWS(bo=a1<a2);
		CHECK_THROWS(bo=a1<=a2);
		CHECK_THROWS(bo=a1==a2);
		CHECK_THROWS(bo=a1!=a2);

	}
	SUBCASE("Good  input operator <, >,>=,<=,==,!=")
	{
		std::vector<double> arr1 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> arr2 = {3, 24, 27, 3, 0, 9};//3*2--66
		Matrix a1{arr1, 3, 2};
		Matrix a2{arr2, 3, 2};
		CHECK_EQ(true,a2>a1);
		CHECK_EQ(false,a2<a1);
		CHECK_EQ(true,a2>=a1);
		CHECK_EQ(false,a2<=a1);

		std::vector<double> arr3 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> arr4 = {12, 4,6, 6, 2, 0};//3*2--66
		Matrix a3{arr3, 3, 2};
		Matrix a4{arr4, 3, 2};
		CHECK_EQ(true,a3>=a4);
		CHECK_EQ(true,a3<=a4);

		std::vector<double> arr5 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> arr6 = {12, 4,0, 0, 8, 6};//3*2--30
		Matrix a5{arr5, 3, 2};
		Matrix a6{arr6, 3, 2};
		CHECK_EQ(true,a3>=a4);
		CHECK_EQ(true,a3<=a4);


		std::vector<double> arr7 = {2, 4, 2, 8, 2, 12};//3*2 -- 30
		std::vector<double> arr8 = {2, 4, 2, 8, 2, 12};//3*2--30
		Matrix a7{arr7, 3, 2};
		Matrix a8{arr8, 3, 2};
		CHECK_EQ(true, a7==a8);
		CHECK_EQ(false,a7!=a8);

	}


}










