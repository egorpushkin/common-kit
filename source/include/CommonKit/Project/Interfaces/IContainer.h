#ifndef ICONTAINER_H__PROJECTKIT__INCLUDED_
#define ICONTAINER_H__PROJECTKIT__INCLUDED_

namespace Project
{

	interface IContainer : public mc::ICommon
	{		

		typedef mc::ICommonRef ComRef_;

		typedef Container::ICommonEnumPtr IEnumPtr_;

		virtual mc::result Add(ComRef_ item) = 0;

		virtual mc::result InsertAfter(ComRef_ item, ComRef_ src) = 0;

		virtual mc::result InsertAfter(ComRef_ item, unsigned int index) = 0;

		virtual mc::result Delete(ComRef_ item) = 0;

		virtual mc::result Delete(unsigned int index) = 0;

		virtual mc::result Clear() = 0;

		virtual IEnumPtr_ GetItems() = 0;

	};

	// {7bba2144-d1ea-44f0-96d2-343ee88e5703} 
	MC_DEFINE_GUID(IID_IContainer, 
	0x7bba2144, 0xd1ea, 0x44f0, 0x96, 0xd2, 0x34, 0x3e, 0xe8, 0x8e, 0x57, 0x03);

	typedef mc::ComPtr< IContainer > IContainerPtr;
	typedef const IContainerPtr& IContainerRef;

	typedef mc::ComPtr< IContainer, false > IContainerWeak;

	typedef Container::IEnumerator< IContainerPtr > IContainersEnum;

	typedef mc::ComPtr< IContainersEnum > IContainersEnumPtr;
	typedef const IContainersEnumPtr& IContainersEnumRef;

}

#endif // !ICONTAINER_H__PROJECTKIT__INCLUDED_
