#ifndef COMPTR_H__MINCOM__COMMONKIT__INCLUDED_
#define COMPTR_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	template
	<
		typename T,
		bool Strong = true
	>
	class ComPtr 
		: public StrongPtr< T, Strong >
	{
	public:

		ComPtr() 
			: StrongPtr< T, Strong >()
		{
		}

		ComPtr( const ComPtr & rhs )
			: StrongPtr< T, Strong >(rhs)
		{
		}

		template
		<
			bool S1
		>
		ComPtr( const ComPtr< T, S1 > & rhs )
			: StrongPtr< T, Strong >( rhs )
		{
		}

		template
		<
			bool S1
		>
		ComPtr( ComPtr< T, S1 > & rhs )
			: StrongPtr< T, Strong >( rhs )
		{
		}

		ComPtr(T* rhs)
			: StrongPtr< T, Strong >( rhs )
		{
		}

		template
		<
			typename T1
		>
		ComPtr(T1* rhs, mc::RefIid iid)
			: StrongPtr< T, Strong >()
		{
			if ( rhs )
			{
				T* pointer = NULL;
				rhs->QueryInterface(iid, (void**)&pointer);
				StrongPtr< T, Strong >::SetPointer(pointer);
			}
		}

		template
		<
			typename T1
		>
		ComPtr(const ComPtr< T1, true > & rhs, mc::RefIid iid)
			: StrongPtr< T, Strong >()
		{
			T* pointer = NULL;
			if ( rhs )
			{
				result code = rhs->QueryInterface(iid, (void**)&pointer);
				if ( IsFailed(code) || !pointer )
					return;

				Merge(rhs);
				StrongPtr< T, Strong >::SetPointer(pointer);				
			}
		}

		template
		<
			typename T1
		>
		ComPtr(ComPtr< T1, true > & rhs, mc::RefIid iid)
			: StrongPtr< T, Strong >()
		{
			T* pointer = NULL;

			if ( rhs )
			{
				result code = rhs->QueryInterface(iid, (void**)&pointer);
				if ( IsFailed(code) || !pointer )
					return;

				Merge(rhs);
				StrongPtr< T, Strong >::SetPointer(pointer);
			}
		}

		friend inline ComPtr<T, true> GetStrong(const ComPtr& rhs)
		{
			return ComPtr<T, true>(rhs);
		}

		friend inline ComPtr<T, false> GetWeak(const ComPtr& rhs)
		{
			return ComPtr<T, false>(rhs);
		}

	protected:

		template
		<
			typename T1
		>
		bool Merge( const ComPtr< T1, true > & rhs )
		{
			return StrongPtr< T, Strong >::Merge( *const_cast< ComPtr< T1, true >* >(&rhs) );
		}

	};

}

namespace std
{
    /**
     * Specialization of std::less for ComPtr
     * \ingroup SmartPointerGroup
     */
    template
    <
        typename T,
        bool S
    >
    struct less< MinCOM::ComPtr< T, S > >
        : public binary_function<
            MinCOM::ComPtr< T, S >,
            MinCOM::ComPtr< T, S >, bool >
    {
        bool operator () (
            const MinCOM::ComPtr< T, S > & lhs,
            const MinCOM::ComPtr< T, S > & rhs ) const
        {
            return less< T* >()( lhs.GetPointer(), rhs.GetPointer() );
        }
    };
}

#endif // !COMPTR_H__MINCOM__COMMONKIT__INCLUDED_
