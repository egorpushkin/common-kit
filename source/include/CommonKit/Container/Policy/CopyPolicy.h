#ifndef COPYPOLICY_H__COMMON__INCLUDED_
#define COPYPOLICY_H__COMMON__INCLUDED_

namespace Container
{

	template 
	<
		class T,
		class StorageType
	>
	class Copy
	{

		const Copy& operator=(const Copy&);

	protected:

		Copy(const StorageType& container)
			: container_(container)
		{
		}

		IEnumerator<T>* CloneEnumerator(typename StorageType::const_iterator iter)
		{
			Enumerator<T, StorageType>* pEmumerator = 
				new Enumerator<T, StorageType>(&container_, iter);

			IEnumerator<T>* piEmumerator = NULL;
			mc::result r = pEmumerator->QueryInterface(IID_IEnumerator, (void**)&piEmumerator);

			if ( r != mc::_S_OK )
				return NULL;

			return piEmumerator;
		}

	private:

		const StorageType& container_;

	};

	template 
	<
		class T,
		class StorageType
	>
	class NoCopy
	{
	protected:

		NoCopy(const StorageType& container)
			: piEnumerator_(NULL)
		{
			Enumerator<T, StorageType>* pEnumerator = 
				new Enumerator<T, StorageType>(&container);
	        
			mc::result r = pEnumerator->QueryInterface(IID_IEnumerator, (void**)&piEnumerator_);

			assert(r == mc::_S_OK);
			assert(piEnumerator_ != NULL);
		}

		~NoCopy()
		{
			piEnumerator_->Release();
		}

		IEnumerator<T>* CloneEnumerator(typename StorageType::const_iterator /* iter */)
		{
			piEnumerator_->AddRef();

			return piEnumerator_;
		}

	private:

		IEnumerator<T>*     piEnumerator_;

	};

}

#endif // !COPYPOLICY_H__COMMON__INCLUDED_
