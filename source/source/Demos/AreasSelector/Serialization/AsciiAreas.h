#ifndef ASCIIAREAS_H__AREASSELECTOR__INCLUDED_
#define ASCIIAREAS_H__AREASSELECTOR__INCLUDED_

namespace Serialization
{

	class AsciiAreas
	{

		AsciiAreas(const AsciiAreas&);
		const AsciiAreas& operator=(const AsciiAreas&);	

	public:

		AsciiAreas();
		virtual ~AsciiAreas();

		mc::result LoadProject(const mc::StringA& filename, Areas::IAProjectPtr& project);
		
		mc::result SaveProject(const mc::StringA& filename, Areas::IAProjectRef project);

	private:




	};

}

#endif // !PGMTOOL_H
