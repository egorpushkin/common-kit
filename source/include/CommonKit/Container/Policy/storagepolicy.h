#ifndef STORAGEPOLICY_H__COMMON__INCLUDED_
#define STORAGEPOLICY_H__COMMON__INCLUDED_

namespace Container
{

	template 
	<
		class T,
		class StorageType,
		template <class> class ReferencesPolicy
	>
	class CommonStorage
	{

		typedef ReferencesPolicy<T>	ReferencesPolicyInst;

	protected:

		CommonStorage();

	public:

		static mc::result Add(const T& newElement, StorageType& container)
		{
			container.push_back(newElement);
			ReferencesPolicyInst::AddRef(newElement);

			return mc::_S_OK;
		}

		static mc::result Delete(const T& value, StorageType& container)
		{
			typename StorageType::iterator position = 
				std::find(
					container.begin(), 
					container.end(),
					value
				);

			if ( position == container.end() ) 
				return mc::_S_FALSE;

			ReferencesPolicyInst::Release(value);
			container.erase(position);
			
			return mc::_S_OK;
		}

		static mc::result Clear(StorageType& container)
		{
			typename StorageType::const_iterator iterator;

			for ( iterator = container.begin() ; iterator != container.end() ; iterator++)
				ReferencesPolicyInst::Release(*iterator);

			container.clear();

			return mc::_S_OK;
		}

		static typename StorageType::iterator Find(const T& value, StorageType& container)
		{
			return 
				std::find(
					container.begin(), 
					container.end(), 
					value);
		}		

		static typename StorageType::const_iterator Find(const T& value, const StorageType& container)
		{
			return 
				std::find(
					container.begin(), 
					container.end(), 
					value);
		}	

	};

	template 
	<
		class T,
		template <class> class ReferencesPolicy
	>
	class VectorStorage 
	{
	public:
		typedef std::vector<T>      StorageType;

	private:
		typedef ReferencesPolicy<T>	ReferencesPolicyInst;
		typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

	protected:
		VectorStorage() {}

		virtual mc::result Add(const T& newElement)
		{
			return CommonStorageInst::Add(newElement, container_);
		}

		virtual mc::result InsertAfter(const T& newElement, const T& existingElement)
		{
			typename StorageType::iterator position = 
				std::find(container_.begin(), container_.end(), existingElement);
			++position;

			container_.insert(position, newElement);

			return mc::_S_OK;			
		}

		virtual mc::result InsertAfter(const T& newElement, size_t index)
		{
			/* if ( index >= container_.size() && container_.size() > 0 )
				index = container_.size() - 1; */

			container_.insert(container_.begin() + index, newElement);

			return mc::_S_OK;
		}

		virtual mc::result Delete(const T& value)
		{
			return CommonStorageInst::Delete(value, container_);
		}

		virtual mc::result Delete(unsigned int index)
		{
			if (index + 1 > container_.size())
				return mc::_S_FALSE;

			typename StorageType::iterator position = container_.begin() + index;
			
			ReferencesPolicyInst::Release(*position);

			container_.erase(position);
					
			return mc::_S_OK;
		}

		virtual typename StorageType::iterator FindCore(const T& value)
		{
			return CommonStorageInst::Find(value, container_);
		}

		virtual typename StorageType::const_iterator FindCore(const T& value) const
		{
			return CommonStorageInst::Find(value, container_);
		}

		virtual mc::result Clear()
		{
			return CommonStorageInst::Clear(container_);
		}

		typename StorageType::reference GetAt(size_t index)
		{
			return container_.at(index);
		}

		typename StorageType::const_reference GetAt(size_t index) const
		{
			return container_.at(index);
		}

		size_t Where(const T& value) const 
		{
			typename StorageType::const_iterator iter = CommonStorageInst::Find(value, container_);
			if ( iter == container_.end() )
				throw std::exception();

			return 
				CommonStorageInst::Find(value, container_) - 
				container_.begin();
		}

		StorageType container_;
	};

	template 
	<
		class T,
		template <class> class ReferencesPolicy
	>
	class ListStorage
	{
	public:
		typedef std::list<T>        StorageType;

	private:
		typedef ReferencesPolicy<T>	ReferencesPolicyInst;
		typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

	protected:
		ListStorage() {}

		virtual mc::result Add(const T& newElement)
		{
			return CommonStorageInst::Add(newElement, container_);
		}

		virtual mc::result Delete(const T& value)
		{
			return CommonStorageInst::Delete(value, container_);
		}

		virtual mc::result Delete(unsigned int index)
		{
			if (index + 1 > container_.size())
				return mc::_S_FALSE;

	/*		StorageType::iterator position = container_.begin() + index;
			container_.erase(position);*/

			return mc::_E_NOTIMPL;
		}

		virtual mc::result Clear()
		{
			return CommonStorageInst::Clear(container_);
		}

		StorageType container_;    
	};

	template 
	<
		class T,
		template <class> class ReferencesPolicy
	>
	class MapStorage
	{
	public:
		typedef std::map< typename T::first_type, typename T::second_type > StorageType;

	private:
		typedef ReferencesPolicy<T>	ReferencesPolicyInst;
		typedef CommonStorage<T, StorageType, ReferencesPolicy>	CommonStorageInst;

	protected:
		MapStorage() {}

		virtual mc::result Add(const T& newElement)
		{
			std::pair< typename StorageType::iterator, bool > iter = container_.insert(newElement);
			if ( !iter.second )
			{
				Delete(newElement);
				return Add(newElement);
			}

			ReferencesPolicyInst::AddRef(newElement);

			return ( iter.second ? mc::_S_OK : mc::_S_FALSE );
		}

		virtual mc::result InsertAfter(const T& newElement, const T& /* existingElement */)
		{
			return Add(newElement);		
		}

		virtual mc::result InsertAfter(const T& newElement, size_t /* index */)
		{
			return Add(newElement);	
		}

		virtual mc::result Delete(const T& value)
		{
			typename StorageType::iterator iter = container_.find(value.first);
			
			if ( iter == container_.end() )
				return mc::_S_FALSE;
			
			ReferencesPolicyInst::Release(*iter);
			container_.erase(iter);

			return mc::_S_OK;
		}

		virtual mc::result Delete(unsigned int index)
		{
			if (index + 1 > container_.size())
				return mc::_S_FALSE;

			/*		StorageType::iterator position = container_.begin() + index;
			container_.erase(position);*/

			return mc::_E_NOTIMPL;
		}

		virtual mc::result Clear()
		{
			typename StorageType::const_iterator iterator;

			for (iterator = container_.begin(); iterator != container_.end(); iterator++)
				ReferencesPolicyInst::Release(*iterator);

			container_.clear();

			return mc::_S_OK;
		}

		virtual typename StorageType::iterator FindCore(const T& value)
		{
			return container_.find(value.first);
		}

		virtual typename StorageType::const_iterator FindCore(const T& value) const
		{
			return container_.find(value.first);
		}

		size_t Where(const T& /* value */) const 
		{
			throw std::exception();
		}

		typename StorageType::reference GetAt(size_t /* index */)
		{
			//return StorageType::reference();
			throw std::exception();
		}

		typename StorageType::const_reference GetAt(size_t /* index */) const
		{
			//return StorageType::reference();
			throw std::exception();
		}

		StorageType container_;      
	};

}

#endif // !STORAGEPOLICY_H__COMMON__INCLUDED_
