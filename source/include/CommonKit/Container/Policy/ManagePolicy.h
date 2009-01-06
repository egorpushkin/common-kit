#ifndef MANAGEPOLICY_H__COMMON__INCLUDED_
#define MANAGEPOLICY_H__COMMON__INCLUDED_

namespace Container
{
	
	namespace Private
	{

		class ContainerSpreader
			: public mc::DispSpreader
		{
		public:

			ContainerSpreader(mc::DispId id, mc::DispParamsRef params);

			virtual bool operator()(mc::AccessEntryPair sinkPair);

		};

	}

	class Managed
		: public mc::APImpl
	{
	protected:

		virtual mc::result OnAddElement(void* const pData, bool* pCancel);

		virtual mc::result OnDeleteElement(void* const pData, int index, bool* pCancel);
		
	};

	class Unmanaged
	{
	public:	
		
		// ICommon section
		EMPTY_IMPLACE_MAP()

	protected:

		virtual mc::result OnAddElement(void* const /* pData */, bool* /* pCancel */);

		virtual mc::result OnDeleteElement(void* const /* pData */, int /* index */, bool* /* pCancel */);
	
	};

}

#endif // MANAGEPOLICY_H__COMMON__INCLUDED_
