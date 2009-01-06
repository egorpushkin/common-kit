// CoreTest01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// #include <windows.h>

#include <CommonKit/MinCOM.h>

#include <iostream>
#include <vector>

#include "../../../sdk/include/loki/strongptr.h"

#ifdef _MSC_VER 
#include <crtdbg.h>
#endif // _MSC_VER



interface ITest1 : public mc::ICommon
{
public:

	typedef mc::ComPtr< ITest1 > Ptr_;

public:

	virtual void DoStuff1() = 0;

};

interface ITest2 : public mc::ICommon
{
public:

	typedef mc::ComPtr< ITest2 > Ptr_;

	typedef mc::ComPtr< ITest2, false > Weak_;

public:

	virtual void DoStuff2() = 0;

};

interface ITest3 : public mc::ICommon
{
public:

	typedef mc::ComPtr< ITest3 > Ptr_;

	typedef mc::ComPtr< ITest3, false > Weak_;

public:

	virtual void DoStuff3() = 0;

};


class Test 
	: public mc::CommonImpl< ITest1 >
	, public mc::CommonImpl< ITest2 >
{
public:

	virtual void DoStuff1()
	{

	}

	virtual void DoStuff2()
	{

	}


protected:
private:
};




int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
	int testId = 0;

	{
		
		mc::ICommon::Ptr_ common = mc::ICommon::Ptr_(new Test());

		{
			mc::ICommon::Ptr_ common1;

			common1 = common;

			mc::ICommon::Ptr_ common2(common);

			mc::ICommon::Weak_ common3(common);

			// Cannot convert between pointers to different control interfaces with 
			// different reference type (strong/week). At least one point (pointer or
			// reference type) should be the same for successful conversion.
			ITest2::Weak_ common4(common);

			ITest3::Weak_ common5(common);

			// Conversion between different weak pointers is also forbidden.
			// ITest2::Weak_ common5(common3);

			// ITest2::Weak_ common6; 
			// common6 = common3;

			{
				ITest1::Ptr_ test1(common);
				if ( test1 )
				{
					std::cout << "ITest1 found." << std::endl;
				}

				// test1 = (ITest2*)0x123;
				test1 = NULL;


				{

					ITest3::Ptr_ test3(common);
					if ( test3 )
					{
						std::cout << "ITest3 found." << std::endl;
					}

				}

			}
		}



		// Loki::StrongPtr< Test* > ptr; 

		// Test * test = new Test();
		// ITest1 * test1 = 




	}

	// UnitTest X
	//
	// 
	{
		testId = 10;

		mc::ICommon::Ptr_ common = mc::ICommon::Ptr_(new Test());
		{
			ITest2::Weak_ common1(common);
			ITest3::Weak_ common2(common);

			if ( common1 )
			{
				std::cout << testId << ": ITest2::Weak_ common1(common); succeeded." << std::endl;
			}
			if ( common2 )
			{
				std::cout << testId << ": ITest3::Weak_ common2(common); succeeded." << std::endl;
			}

			// common = NULL;

			// This will assert about the error.
			// common1->DoStuff2();

			ITest2::Ptr_ common3(common1);
			
			if ( common3 )
			{
				std::cout << testId << ": ITest2::Ptr_ common3(common1); succeeded." << std::endl;
				common3->DoStuff2();
			}

			ITest1::Ptr_ common4(common1);

			if ( common4 )
			{
				std::cout << testId << ": ITest1::Ptr_ common4(common1); succeeded." << std::endl;
				common4->DoStuff1();
			}
			
			
			
		}
	}


#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}
