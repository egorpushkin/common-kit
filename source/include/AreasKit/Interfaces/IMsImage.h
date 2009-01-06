#ifndef IMSIMAGE_H__AREASKIT__INCLUDED_
#define IMSIMAGE_H__AREASKIT__INCLUDED_

namespace Areas
{

	interface IMsImage : public mc::ICommon
	{
		
		virtual mc::result SetSrcName(const mc::StringA& imageSrc) = 0;

		virtual mc::StringA GetSrcName() = 0;

	};

	typedef mc::ComPtr< IMsImage > IMsImagePtr;
	typedef const IMsImagePtr& IMsImageRef;

	// {1fa11aea-fa03-4e7d-b0b7-3807b7efb84d} 
	MC_DEFINE_GUID(IID_IMsImage, 
	0x1fa11aea, 0xfa03, 0x4e7d, 0xb0, 0xb7, 0x38, 0x07, 0xb7, 0xef, 0xb8, 0x4d);

	enum
	{
		AGENTID_IMGCHANGED = 0x00010001,
		AGENTID_LAST_IMG_EVENT
	};

}

#endif // !IMSIMAGE_H__AREASKIT__INCLUDED_
