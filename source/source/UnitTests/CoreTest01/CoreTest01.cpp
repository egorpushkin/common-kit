#include "stdafx.h"

#ifdef _MSC_VER 
#include <crtdbg.h>
#endif // _MSC_VER

bool Test1();
bool Test2();
bool Test3();
bool Test4();

// {2CC32701-BFC6-4ccf-B4B3-F5F28BD967E0}
const mc::Guid mc::TypeInfo< ITest1 >::iid_ = 
 	{ 0x2cc32701, 0xbfc6, 0x4ccf, 0xb4, 0xb3, 0xf5, 0xf2, 0x8b, 0xd9, 0x67, 0xe0 };

#include <boost/bind.hpp>

class Locker
{
public:

	mc::result Lock()
	{
		std::cout << "Locked!" << std::endl;
		return mc::_S_OK;
	}

	mc::result Unlock()
	{
		std::cout << "Unlocked!" << std::endl;
		return mc::_S_OK;
	}

};

namespace _attempt1
{

template
<
	typename R
>
class FunctorImpl
{
public:
	typedef R ResultType;
	virtual R operator()() = 0;
};

template 
<
	class FunctorImplBase,
	typename PointerToObj,
    typename PointerToMemFn
>
class MemFunHandler : public FunctorImplBase
{
public:
	MemFunHandler(const PointerToObj& pObj, PointerToMemFn pMemFn) 
		: pObj_(pObj), pMemFn_(pMemFn)
    {}

	virtual typename FunctorImplBase::ResultType operator()()
	{
		return (pObj_->*pMemFn_)();
	}

private:
	PointerToObj pObj_;
    PointerToMemFn pMemFn_;
};

class LockerHolder
{
public:

	template 
	<
		class LockerClass,
		class MemberFn
	>
	LockerHolder(LockerClass ptr, MemberFn lockFn, MemberFn unlockFn)
		: lockImpl_( new MemFunHandler< FunctorImpl< mc::result >, LockerClass, MemberFn>(ptr, lockFn) )
		, unlockImpl_( new MemFunHandler< FunctorImpl< mc::result >, LockerClass, MemberFn>(ptr, unlockFn) )
	{
		(*lockImpl_)();	
	}	

	~LockerHolder()
	{
		(*unlockImpl_)();	
	}
	
private:

	std::auto_ptr< FunctorImpl< mc::result > > lockImpl_; 
	std::auto_ptr< FunctorImpl< mc::result > > unlockImpl_; 

};

}

namespace _attempt2
{

template 
<
	class ResultType = mc::result
>
class LockerHolder
{
public:
	template 
	<
		class LockerClass,
		class MemberFn
	>
	LockerHolder(LockerClass ptr, MemberFn lockFn, MemberFn unlockFn)
		: lock_(ptr, lockFn)
		, unlock_(ptr, unlockFn)
	{
		lock_();
	}
	~LockerHolder()
	{
		unlock_();
	}
private:
	Loki::Functor< ResultType > lock_;
	Loki::Functor< ResultType > unlock_;
};

}

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
	
	Locker l;
	mc::Strong< ITest1 > test1( mc::Class< Test >::Create() );
	{		
		//LockerHolder lh(&l, &Locker::Lock, &Locker::Unlock);


		// Loki::Functor< mc::result > lock(&l, &Locker::Lock);
		// lock();

		

		// Loki::Functor<> lock1(test1, &ITest1::DoStuff1);
		// lock1();

		_attempt2::LockerHolder<> lh( &l, &Locker::Lock, &Locker::Unlock );
		// _attempt2::LockerHolder lh( test1, &ITest1::DoStuff1, &ITest1::DoStuff1);

			

	}
	
	//size_t t = sizeof(mc::Variant);
	//std::cout << t << std::endl;

	// Test1();
	// Test2();
	// Test3();
	// Test4();

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}
