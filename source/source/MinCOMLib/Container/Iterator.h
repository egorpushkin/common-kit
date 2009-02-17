#ifndef ITERATOR_H__MINCOM__INCLUDED_
#define ITERATOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	template
	<
		class TStdContainer,
		class TMCContainer
	>
	class Iterator
		: public CommonImpl< IIterator >
		, public CommonImpl< IPrivateIterator< TStdContainer, TMCContainer > >
	{
        using CommonImpl< IIterator >::__Cast; 
        
		typedef std::vector< ICommonPtr > StdVector_;
		typedef StdVector_::iterator StdIterator_;

	public:
        
		Iterator(ICommonRef container, const StdIterator_& stdIterator)
			: CommonImpl< IIterator >()
			, CommonImpl< IPrivateIterator< TStdContainer, TMCContainer > >()
			, container_(container)
			, stdIterator_(stdIterator)
		{
		}

		// IIterator section
		virtual ICommonPtr operator*() const
		{
			return *stdIterator_;
		}

		virtual IIteratorPtr operator++( )
		{
			return NULL;
		}

		virtual IIteratorPtr operator++( int )
		{
			return NULL;			
		}

		// IPrivateIterator section
	private:

		virtual typename TStdContainer::iterator& GetStdIterator()
		{
			return stdIterator_;
		}
		
	private:

		ICommonPtr container_;

		typename TStdContainer::iterator stdIterator_;

	};

}

#endif // !ITERATOR_H__MINCOM__INCLUDED_
