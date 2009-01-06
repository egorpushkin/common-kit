#include <QtGui>

#include "Common/Common.h"

#include "Properties.h"

namespace Selector
{

	Properties::Properties()
		: displayPoints_(true)
		, radius_(8)
		, selectedColor_(60, 60, 200)
		, freeColor_(60, 200, 60)
		, displayLabels_(true)
		, labelXOffset_(7)
		, labelYOffset_(7)
		, labelFont_("Times", 10, QFont::Bold)
		, labelColor_(255, 255, 255)
		, displayConnections_(true)
		, connectionWidth_(3)
		, connectionColor_(255, 255, 255)
	{
	}

}
