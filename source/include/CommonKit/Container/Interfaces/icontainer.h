#ifndef ICONTAINER_H__CONTAINER__COMMONKIT__INCLUDED_
#define ICONTAINER_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

	template 
	<
		class T
	>
	interface IContainer : public mc::ICommon
	{

		virtual mc::result Add(const T& newElement) = 0;

		virtual mc::result InsertAfter(const T& newElement, const T& existingElement) = 0;

		virtual mc::result InsertAfter(const T& newElement, size_t index) = 0;

		virtual mc::result Delete(const T& value) = 0;

		virtual mc::result Delete(unsigned int index) = 0;

		virtual mc::result Clear() = 0;

		virtual size_t Size() const = 0;

		virtual mc::ComPtr< IEnumerator< T > > Find(const T& value) = 0;

		virtual size_t Where(const T& value) const = 0;

		virtual mc::ComPtr< IEnumerator< T > > Clone() = 0;

		virtual mc::result Apply(Manipulator& manipulator) = 0;

		virtual T GetAt(size_t index) = 0;

		virtual const T GetAt(size_t index) const = 0;
		
	};

	// Common containers
	typedef IContainer< mc::ICommonPtr > ICommons;

	typedef mc::ComPtr< ICommons > ICommonsPtr;
	typedef const ICommonsPtr& ICommonsRef;

	// {52cef983-561e-45ec-b1e8-39ec50ef4b74} 
	MC_DEFINE_GUID(IID_IContainer, 
	0x52cef983, 0x561e, 0x45ec, 0xb1, 0xe8, 0x39, 0xec, 0x50, 0xef, 0x4b, 0x74); 

}

#endif // !ICONTAINER_H__CONTAINER__COMMONKIT__INCLUDED_
