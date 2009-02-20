#ifndef VECTOR_H__MINCOM__INCLUDED_
#define VECTOR_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Vector
		: public CommonImpl< IVector >
		, public APImpl
	{
	public:

		typedef CommonImpl< IVector > ClassRoot_;   

	public:

		Vector();
		Vector(size_t count);

		// IVector section
		virtual ICommonPtr At(size_t pos);

		virtual void Clear();



		virtual IEnumeratorPtr GetEnumerator(size_t pos = 0);

		// ICommon section
		virtual result PostInit();	

	protected:

		inline bool IsPositionValid(size_t pos);

	private:

		std::vector< ICommonPtr > stdVector_;

		/** . */
		IReadWriteLockPtr lock_;

		/** . */
		DContainerPtr eventsSpreader_;

	};

}

#endif // !VECTOR_H__MINCOM__INCLUDED_
