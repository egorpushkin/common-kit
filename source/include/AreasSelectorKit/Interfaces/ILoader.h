#ifndef ILOADER_H__AREASSELECTOR__INCLUDED_
#define ILOADER_H__AREASSELECTOR__INCLUDED_

namespace AreasSelector
{

	interface ILoader : public mc::ICommon
	{

		virtual mc::result LoadProject(const mc::StringA& filename, Areas::IAProjectPtr& project) = 0;

		virtual mc::result SaveProject(const mc::StringA& filename, Areas::IAProjectRef project) = 0;

	};

	typedef mc::ComPtr< ILoader > ILoaderPtr;
	typedef const ILoaderPtr& ILoaderRef;

	// {60e03e6c-1bfc-43a8-991b-1d65304dbef8} 
	MC_DEFINE_GUID(IID_ILoader, 
	0x60e03e6c, 0x1bfc, 0x43a8, 0x99, 0x1b, 0x1d, 0x65, 0x30, 0x4d, 0xbe, 0xf8);
	
}

#endif // !ILOADER_H__AREASSELECTOR__INCLUDED_
