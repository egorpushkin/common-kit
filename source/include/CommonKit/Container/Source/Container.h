#ifndef CONTAINER_H__COMMON__INCLUDED_
#define CONTAINER_H__COMMON__INCLUDED_

namespace Container
{

	template 
	<
		class T,
		template <class, template <class> class > class StoragePolicy = VectorStorage,
		template <class, class> class CopyPolicy = Copy,
		template <class> class ReferencesPolicy = WithRefs,
		class ManagePolicy = Managed
	>
	class Container
		: public mc::CommonImpl< IContainer<T> >
		, private ManagePolicy
		, private StoragePolicy< T, ReferencesPolicy >
		, private CopyPolicy< T, typename StoragePolicy< T, ReferencesPolicy >::StorageType >
	{    
		Container(const Container&);
		Container& operator =(const Container&);

		typedef StoragePolicy< T, ReferencesPolicy > StoragePolicyInst;
		typedef CopyPolicy< T, typename StoragePolicyInst::StorageType > CopyPolicyInst;

	public:    

		Container()
			: StoragePolicyInst()
			, CopyPolicyInst(StoragePolicyInst::container_)
		{
		}

		virtual ~Container() 
		{
			Clear();
		}

		// IContainer section
		virtual mc::ComPtr< IEnumerator< T > > Clone()
		{
			return mc::ComPtr< IEnumerator< T > >(
				CopyPolicyInst::CloneEnumerator(
					StoragePolicyInst::container_.begin()
				)
			);
		}

		virtual mc::result Add(const T& newElement)
		{
			bool cancel = false;
			if ( mc::IsFailed(ManagePolicy::OnAddElement((void *const)&newElement, &cancel)) || cancel )
				return mc::_E_CANCELED;

			return StoragePolicyInst::Add(newElement);
		}

		virtual mc::result InsertAfter(const T& newElement, const T& existingElement)
		{
			bool cancel = false;
			if ( mc::IsFailed(ManagePolicy::OnAddElement((void *const)&newElement, &cancel)) || cancel )
				return mc::_E_CANCELED;

			return StoragePolicyInst::InsertAfter(newElement, existingElement);
		}

		virtual mc::result InsertAfter(const T& newElement, size_t index)
		{
			bool cancel = false;
			if ( mc::IsFailed(ManagePolicy::OnAddElement((void *const)&newElement, &cancel)) || cancel )
				return mc::_E_CANCELED;

			return StoragePolicyInst::InsertAfter(newElement, index);
		}

		virtual mc::result Delete(const T& value)
		{
			bool cancel = false;
			if ( mc::IsFailed(ManagePolicy::OnDeleteElement((void *const)&value, -1, &cancel)) || cancel )
				return mc::_E_CANCELED;

			return StoragePolicyInst::Delete(value);
		}

		virtual mc::result Delete(unsigned int index)
		{
			bool cancel = false;
			if ( mc::IsFailed(ManagePolicy::OnDeleteElement(NULL, index, &cancel)) || cancel )
				return mc::_E_CANCELED;

			return StoragePolicyInst::Delete(index);
		}

		virtual size_t Size() const
		{
			return StoragePolicyInst::container_.size();
		}

		virtual mc::result Clear()
		{
			return StoragePolicyInst::Clear();
		}

		virtual mc::ComPtr< IEnumerator< T > > Find(const T& value)
		{
			return mc::ComPtr< IEnumerator< T > >(
				CopyPolicyInst::CloneEnumerator(
					StoragePolicyInst::FindCore(value)
				)
			);
		}

		virtual size_t Where(const T& value) const
		{
			return StoragePolicyInst::Where(value);
		}

		virtual mc::result Apply(Manipulator& manipulator)
		{		
		#ifdef _MSC_VER
			#pragma warning(push)
			#pragma warning(disable: 4239)
		#endif

			return manipulator(
				StoragePolicyInst::container_.begin(), 
				StoragePolicyInst::container_.end());

		#ifdef _MSC_VER
			#pragma warning( pop ) 
		#endif
		}

		virtual T GetAt(size_t index)
		{
			return StoragePolicyInst::GetAt(index);
		}

		virtual const T GetAt(size_t index) const
		{
			return StoragePolicyInst::GetAt(index);
		}

		// ICommon section
		IMPLACE_INTERFACE_MAP()			
			COMMON(IContainer<T>)			
			INTERFACE_(IContainer<T>, IID_IContainer)
			IMPL(ManagePolicy)
		END_INTERFACE_MAP()	

	};

}

#endif // !CONTAINER_H__COMMON__INCLUDED_
