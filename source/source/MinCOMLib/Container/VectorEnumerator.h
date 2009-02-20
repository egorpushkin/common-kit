#ifndef VECTORENUMERATOR_H__MINCOM__INCLUDED_
#define VECTORENUMERATOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class VectorEnumerator
		: public CommonImpl< IEnumerator >
	{
	public:

		// typedef CommonImpl< IIterator > ClassRoot_;  

	public:
        
		VectorEnumerator(IVectorRef container, IReadWriteLockRef lock, size_t pos);

		// IEnumerator section
		virtual ICommonPtr GetCurrent() const;

		virtual bool Next();  

		virtual bool Prev();  

		virtual bool HasNext() const;

		virtual bool HasPrev() const;

		virtual bool IsValid() const;

	protected:

		ICommonPtr GetContainer();
		
	private:

		IVectorWeak container_;

		IReadWriteLockWeak lock_;

		size_t pos_;

	};

}

#endif // !VECTORENUMERATOR_H__MINCOM__INCLUDED_
