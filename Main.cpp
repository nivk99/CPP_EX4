/**
 * @file Main.cpp
 * @brief This file demonstrates prints of the Matrix class
 * @date 2022-04-06
 * 
 * AUTHORS: Niv Kotek (nivk99@gmail.com)
 * 
 */


#include "Main.hpp"

int main(int argc, char const *argv[])
{
	 int num=0;
    while (true)
    {
        cout<<"Select the function you want."<<endl;
        cout<<"Select 1 for compar."<<endl;
        cout<<"Select 2 for  input Outputt."<<endl;
        cout<<"Select 3 for addition."<<endl;
        cout<<"Select 4 for subtraction."<<endl;
		cout<<"Select 5 for multiplication."<<endl;
		cout<<"Select 6 for Errors."<<endl;
        cout<<"Select 7 for exit."<<endl;
        cin>>num;

        //Select the appropriate function

        if(num==1)
        {
		//Comparison of 2 matrices
         compar();
          continue;

        }

        if (num==2)
        {
            //Input and output of a matrix
            inputOutput();
            continue;
        }

        if (num==3)
        {
           //Add to matrix
            addition();
            continue;
        }

        if(num==4)
        {
			//Subtraction for the matrix
            subtraction();
            continue;
        }
		if(num==5)
		{
			//Matrix multiplication
			multiplication();
			continue;

		}
		if (num == 6)
		{
			//Matrix class errors
			errors();
			continue;

		}

        if(num>6||num<1)
        {
            return 0;

        }

	}
	return 0;
}

/**
 * @brief This function is an example of input and output
 * @return This is a function that does not return
 */
void inputOutput()
{
	Matrix mat;
	cin>>mat;
	cout<<endl<<mat<<endl;
}

/**
 * @brief This function is an example for comparison
 * @return This is a function that does not return
 */
void compar()
{
	vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	vector<double> vect2 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	Matrix mat1{vect1, 3, 3};
	Matrix mat2{vect2, 3, 3};
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" < "<<endl<<mat2<<endl<<" = "<<endl<<(mat1<mat2)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" > "<<endl<<mat2<<endl<<" = "<<endl<<(mat1>mat2)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" >= "<<endl<<mat2<<endl<<" = "<<endl<<(mat1>=mat2)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" <= "<<endl<<mat2<<endl<<" = "<<endl<<(mat1<=mat2)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" == "<<endl<<mat2<<endl<<" = "<<endl<<(mat1==mat2)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" != "<<endl<<mat2<<endl<<" = "<<endl<<(mat1!=mat2)<<endl;


}

/**
 * @brief This function is an example of an addition
 * @return This is a function that does not return
 */
void addition()
{

	vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	vector<double> vect2 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	Matrix mat1{vect1, 3, 3};
	Matrix mat2{vect2, 3, 3};
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" + "<<endl<<mat2<<endl<<" = "<<endl<<mat1+mat2<<endl;
	Matrix mat3=mat1+=mat2;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" += "<<endl<<mat2<<endl<<" = "<<endl<<mat3<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<endl<<" + "<<endl<<mat1<<endl<<" = "<<endl<<+mat1<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<endl<<" ++ "<<endl<<mat1<<endl<< "= "<<endl<<++mat1<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" ++ "<<endl<< "= "<<endl<<mat1++<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" + "<<endl<<" 5 "<<endl<< "= "<<endl<<mat1+5<<endl;

}

/**
 * @brief This function is an example of subtraction
 * @return This is a function that does not return
 */
void subtraction()
{

	vector<double> vect1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	vector<double> vect2 = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	Matrix mat1{vect1, 3, 3};
	Matrix mat2{vect2, 3, 3};
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" - "<<endl<<mat2<<endl<<" = "<<endl<<mat1-mat2<<endl;
	Matrix mat3=mat1-=mat2;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" -= "<<endl<<mat2<<endl<<" = "<<endl<<mat3<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<endl<<" - "<<endl<<mat1<<endl<<" = "<<endl<<-mat1<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<endl<<" -- "<<endl<<mat1<<endl<< "= "<<endl<<--mat1<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<"-- "<<endl<< "= "<<endl<<mat1--<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" - "<<endl<<" 5 "<<endl<< "= "<<endl<<mat1-5<<endl;

}

/**
 * @brief This function is an example of multiplication
 * @return This is a function that does not return
 */
void multiplication()
{

	std::vector<double> vect1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
	std::vector<double> vect2 = {5,7.7,5.8,3,4.2,1.1,0,5,2.2};//3*3
	Matrix mat1{vect1, 3, 3};
	Matrix mat2{vect2, 3, 3};
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" * "<<endl<<mat2<<endl<<" = "<<endl<<mat1*mat2<<endl;
	Matrix mat3=mat1-=mat2;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" *= "<<endl<<mat2<<endl<<" = "<<endl<<(mat1*=mat2)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" * "<<endl<<" 5 "<<endl<<" = "<<endl<<(mat1*5)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<mat1<<endl<<" *="<<endl<<" 5 "<<endl<<" = "<<endl<<(mat1*=5)<<endl;
	cout<<"________________________________________________________"<<endl;
	cout<<" 5 "<<endl<<" *"<<endl<<mat2<<endl<<" = "<<endl<<(5*mat1)<<endl;

}


/**
 * @brief This function is an example of an error
 * @return This is a function that does not return
 */
void errors()
{
	cout<<"________________________________________________________"<<endl;
	cout<<"constructor"<<endl;
	vector<double> vect = {3, 0, 0, 0, 3, 0, 0, 0, 3};//3*3
	cout<<"________________________________________________________"<<endl;
	cout<<"Matrix(vect, -3, 3)"<<endl;
	printMat(vect, -3, 3);//The size of the rows is negative
	cout<<"________________________________________________________"<<endl;
	cout<<"Matrix(vect, 3, -3)"<<endl;
	printMat(vect, 3, -3);//The size of the rows is negative
	cout<<"________________________________________________________"<<endl;
	cout<<"Matrix(vect, 2, 3)"<<endl;
    printMat(vect, 2, 3);//The size of the rows is negative

    cout<<"________________________________________________________"<<endl;
	cout<<"multiplication"<<endl;
	vector<double> vect1 = {7,7,8,5.5,7.7,8.8,1,2,9};//3*3
	vector<double> vect2 = {5,7,5,8};//2*2
	Matrix mat1{vect1, 3, 3};
	Matrix mat2{vect2, 2, 2};
   cout<<"ma1(3*3) * mat2 (2*2)"<<endl;
	try
	{
		mat1*mat2;
	}
	catch(const std::exception& ex)
	{
		cout << "   caught exception: " << ex.what() << endl;  
	}

    cout<<"________________________________________________________"<<endl;
	cout<<"addition"<<endl;
	cout<<"ma1(3*3) + mat2 (2*2)"<<endl;
	try
	{
		mat1+mat2;
	}
	catch(const std::exception& ex)
	{
		cout << "   caught exception: " << ex.what() << endl;  
	}

	cout<<"________________________________________________________"<<endl;
	cout<<"subtraction"<<endl;
	cout<<"ma1(3*3) - mat2 (2*2)"<<endl;
	try
	{
		mat1-mat2;
	}
	catch(const std::exception& ex)
	{
		cout << "   caught exception: " << ex.what() << endl;  
	}

	cout<<"________________________________________________________"<<endl;
	cout<<"compar"<<endl;
	cout<<"ma1(3*3) < mat2 (2*2)"<<endl;
	try
	{
		bool bo=mat1<mat2;
	}
	catch(const std::exception& ex)
	{
		cout << "   caught exception: " << ex.what() << endl;  
	}


}

/**
 * @brief This function prints the errors
 * @return  This is a function that does not return
 */
void  printMat(vector<double> vect,int row,int column)
{
try {
    //Send to function and print
	Matrix mat{vect,row, column};
    cout <<mat << endl; // Exception - not a valid code
    }
     catch (exception& ex)
    {
        cout << "   caught exception: " << ex.what() << endl;  
    }

    cout<<" "<<endl;
    
}