#ifndef ICONTAINERT_H__PROJECTKIT__INCLUDED_
#define ICONTAINERT_H__PROJECTKIT__INCLUDED_

namespace Project
{

	template 
	<
		class T
	>
	interface IContainerT : public mc::ICommon
	{

		typedef T Type_;

		typedef mc::ComPtr< Type_ > ComPtr_;
		
		typedef const ComPtr_& ComRef_;

		typedef Container::IEnumerator< ComPtr_ > IEnum_;

		typedef mc::ComPtr< IEnum_ > IEnumPtr_;

		typedef mc::ComPtr< IContainerT< T > > ContainerPtr_;

		virtual mc::result Add(ComRef_ item) = 0;

		virtual mc::result InsertAfter(ComRef_ item, ComRef_ src) = 0;

		virtual mc::result InsertAfter(ComRef_ item, unsigned int index) = 0;

		virtual mc::result Delete(ComRef_ item) = 0;

		virtual mc::result Delete(unsigned int index) = 0;

		virtual IEnumPtr_ GetItems() = 0;

	};

	// {7bba2144-d1ea-44f0-96d2-343ee88e5703} 
	MC_DEFINE_GUID(IID_IContainer, 
	0x7bba2144, 0xd1ea, 0x44f0, 0x96, 0xd2, 0x34, 0x3e, 0xe8, 0x8e, 0x57, 0x03);

}

#endif // !ICONTAINERT_H__PROJECTKIT__INCLUDED_
