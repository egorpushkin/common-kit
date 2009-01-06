#ifndef ENUMERATOR_H__CONTAINER__INCLUDED_
#define ENUMERATOR_H__CONTAINER__INCLUDED_

namespace Container
{

	template 
	<
		class T,
		class StorageType
	>
	class Enumerator 
		: public mc::CommonImpl< IEnumerator<T> >
	{
		Enumerator(const Enumerator&);
		Enumerator& operator =(const Enumerator&);

	public:

		Enumerator(const StorageType* pContainer, typename StorageType::const_iterator iter)
			: pContainer_(pContainer)
			, containerIterator_(iter)
		{   
		}

		virtual ~Enumerator() {}

		// Initialization tools
		virtual void SetContainer(const StorageType* pContainer = NULL)
		{
			pContainer_ = pContainer;
		}

		// IEnumerator section
		virtual bool SelectFirst()
		{
			if ( !pContainer_ )
				return false;

			if ( pContainer_->size() == 0 )
				return false;

			containerIterator_ = pContainer_->begin();

			return true;
		}

		virtual bool SelectNext()
		{
			if ( !pContainer_ )
				return false;

			if ( pContainer_->size() == 0 )
				return false;

			if ( containerIterator_ == pContainer_->end() )
				return false;
	        
			if ( ++containerIterator_ == pContainer_->end() )
				return false;

			return true;
		}

		virtual bool SelectLast()
		{
			if ( !pContainer_ )
				return false;

			if ( pContainer_->size() == 0 )
				return false;

			containerIterator_ = pContainer_->end();
			containerIterator_--;

			return true;
		}

		virtual bool SelectPrev()
		{
			if ( !pContainer_ )
				return false;

			if ( containerIterator_ == pContainer_->begin() )
				return false;

			containerIterator_--;

			return true;
		}

		virtual T GetSelected() 
		{
			assert(pContainer_ != NULL);        

			return *containerIterator_;
		}
	    
		virtual const T GetSelected() const
		{
			assert(pContainer_ != NULL);        

			return *containerIterator_;
		}

		virtual T GetFirst()
		{
			assert(pContainer_ != NULL);    

			typename StorageType::const_iterator containerIterator = pContainer_->begin();

			return const_cast<T&>(
				static_cast<const T&>(*containerIterator)
			);
		}

		virtual const T GetFirst() const
		{
			assert(pContainer_ != NULL);    

			typename StorageType::const_iterator containerIterator = pContainer_->begin();

			return *containerIterator;
		}

		virtual T GetLast()
		{
			assert(pContainer_ != NULL);    

			typename StorageType::const_iterator containerIterator = pContainer_->end(); 
			containerIterator--;

			return const_cast<T&>(
				static_cast<const T&>(*containerIterator)
			);
		}

		virtual const T GetLast() const
		{
			assert(pContainer_ != NULL);    

			typename StorageType::const_iterator containerIterator = pContainer_->end();
			containerIterator--;

			return *containerIterator;
		}

		virtual size_t GetTotal() const
		{
			if ( !pContainer_ )
				return 0;

			return pContainer_->size();
		}

		virtual bool IsValid() const
		{
			return ( containerIterator_ != pContainer_->end() );
		}

		// ICommon section
		IMPLACE_INTERFACE_MAP()
			COMMON(IEnumerator<T>)
			INTERFACE_(IEnumerator<T>, IID_IEnumerator)
		END_INTERFACE_MAP()	

	private:

		const StorageType* pContainer_;

		typename StorageType::const_iterator containerIterator_;

	};

}

#endif // !ENUMERATOR_H__CONTAINER__INCLUDED_
