#ifndef PROPERTIES_H__AREASSELECTOR__INCLUDED_
#define PROPERTIES_H__AREASSELECTOR__INCLUDED_

namespace AreasSelector
{

	class Properties
	{
	public:

		Properties();

	public:

		bool displayPoints_;

		int radius_;

		QColor selectedColor_;

		QColor freeColor_;

		bool displayLabels_;

		int labelXOffset_;

		int labelYOffset_;

		QFont labelFont_;

		QColor labelColor_;

		bool displayConnections_;

		int connectionWidth_;

		QColor connectionColor_;

	};

	typedef Loki::SmartPtr< Properties > PropertiesPtr;

	typedef const PropertiesPtr& PropertiesRef;

}

#endif // !PROPERTIES_H__AREASSELECTOR__INCLUDED_
