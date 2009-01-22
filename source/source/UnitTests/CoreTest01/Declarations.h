#ifndef DECLARATIONS_H__INCLUDED_
#define DECLARATIONS_H__INCLUDED_

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
		std::cout << "Test::DoStuff1" << std::endl;
	}

	virtual void DoStuff2()
	{

	}


protected:
private:
};

#endif // !DECLARATIONS_H__INCLUDED_
