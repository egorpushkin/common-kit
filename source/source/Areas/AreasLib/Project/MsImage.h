#ifndef MSIMAGE_H__AREASLIB__INCLUDED_
#define MSIMAGE_H__AREASLIB__INCLUDED_

namespace Areas
{

	class MsImage
		: public mc::CommonImpl< IMsImage > 
		, public mc::APImpl
		, public Components::ObjCounter
	{
	public:

		MsImage();
		virtual ~MsImage();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// Areas::IMsImage section
		virtual mc::result SetSrcName(const mc::StringA& imageSrc);

		virtual mc::StringA GetSrcName();		

	private:

		// Event dispatchers
		mc::result OnSrcNameChanged();

		// Commands
		mc::result RegisterNameCommand(const mc::StringA& name);

	private:

		mc::StringA srcName_;

	};

}

#endif // !MSIMAGE_H__AREASLIB__INCLUDED_
