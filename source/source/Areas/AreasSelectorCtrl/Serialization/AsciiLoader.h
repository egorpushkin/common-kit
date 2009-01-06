#ifndef ASCIIAREAS_H__AREASSELECTOR__INCLUDED_
#define ASCIIAREAS_H__AREASSELECTOR__INCLUDED_

namespace Serialization
{

	class AsciiLoader
		: public mc::CommonImpl< AreasSelector::ILoader >
	{
	public:

		AsciiLoader();
		
		// ICommon section
		DECLARE_INTERFACE_MAP()

		// ILoader section
		mc::result LoadProject(const mc::StringA& filename, Areas::IAProjectPtr& project);
		
		mc::result SaveProject(const mc::StringA& filename, Areas::IAProjectRef project);

	};

}

#endif // !PGMTOOL_H
