#include "Common.h"

#include "AreasKit/AreasKit.h"

class EventsSink
	: public mc::AgentImpl
{
public:

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{

		if ( Areas::AGENTID_POINTADDED == idMember )
		{
			std::cout << "[EventsSink::Invoke] AGENTID_POINTADDED signaled." << std::endl;
		}
		else if ( Areas::AGENTID_LOCATIONCHANGED == idMember )
		{
			std::cout << "[EventsSink::Invoke] AGENTID_LOCATIONCHANGED signaled." << std::endl;
		}
		else if ( Areas::AGENTID_LOCATIONCHANGING == idMember )
		{
			assert( dispParams->GetCount() == 6 );

			bool* pCancel = dispParams->Get(0)->toPBool();
			double newX = dispParams->Get(2)->toDouble();
			double newY = dispParams->Get(1)->toDouble();

			assert( pCancel != NULL );

			std::cout 
				<< "[EventsSink::Invoke] AGENTID_LOCATIONCHANGING signaled ("
				<< newX << ", " << newY 
				<< ")." << std::endl;

			if ( newX > 10 )
			{
				std::cout << "[EventsSink::Invoke] Operation skipped (\"newX > 10\" condition)." << std::endl;
				*pCancel = true;
			}
		}

		return mc::_S_OK;
	}

};

class CompTest02
{
public:

	static Areas::IAreaPtr InstantiateArea()
	{
		// Instantiating CLSID_Area from shared object
		mc::ICommonPtr areaCommon = Components::InstantiateCommon(Areas::CLSID_Area);
		if ( !areaCommon ) 
			throw std::exception("[CompTest02::InstantiateArea] Error instantiating CLSID_Area.");

		// Requesting the IID_IArea interface
		Areas::IAreaPtr area(areaCommon, Areas::IID_IArea);
		if ( !area )
			throw std::exception("[CompTest02::InstantiateArea] Failed to query the IID_IArea.");

		return area;
	}

	static Areas::IPointPtr InstantiatePoint()
	{
		// Instantiating CLSID_Point from shared object
		mc::ICommonPtr pointCommon = Components::InstantiateCommon(Areas::CLSID_Point);
		if ( !pointCommon ) 
			throw std::exception("[CompTest02::InstantiatePoint] Error instantiating CLSID_Point.");

		// Requesting the IID_IPoint interface
		Areas::IPointPtr point(pointCommon, Areas::IID_IPoint);
		if ( !point )
			throw std::exception("[CompTest02::InstantiatePoint] Failed to query the IID_IPoint.");

		return point;
	}

	static mc::result AddPoint(Areas::IAreaRef area, Areas::IPointRef point)
	{
		Project::IContainerPtr pointsContainer(area, Project::IID_IContainer);
		if ( !pointsContainer )
			throw std::exception("[CompTest02::AddPoint] Failed to query the Project::IID_IContainer.");

		if ( mc::IsFailed(pointsContainer->Add(mc::ICommonPtr(point, mc::IID_ICommon))) )
			throw std::exception("[CompTest02::AddPoint] Failed to add point.");

		return mc::_S_OK;
	}

	static mc::ICommonPtr InstantiateSink()
	{
		mc::ICommonPtr sinkCommon = mc::ObjectCreator< EventsSink >();
		if ( !sinkCommon )
			throw std::exception("[CompTest02::InstantiateSink] Failed to instantiate events sink.");

		return sinkCommon;
	}

	static unsigned long AdviseSink(Areas::IAreaRef area, mc::ICommonRef sink)
	{
		unsigned long cookie = 0;
		mc::result code = mc::Advise(
			mc::ICommonPtr(area, mc::IID_ICommon),
			sink,
			cookie);

		if ( mc::IsFailed(code) )
			throw std::exception("[CompTest02::AdviseSink] Failed to advise events sink.");

		return cookie;
	}

	static void UnadviseSink(Areas::IAreaRef area, unsigned long cookie)
	{
		mc::result code = mc::Unadvise(
			mc::ICommonPtr(area, mc::IID_ICommon),
			cookie);

		if ( mc::IsFailed(code) )
			throw std::exception("[CompTest02::UnadviseSink] Failed to unadvise events sink.");
	}

};

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		std::cout << "[main] Attempting to perform any test." << std::endl;

		Areas::IAreaPtr area = CompTest02::InstantiateArea();

		std::cout << "[main] CLSID_Area instantiated successfully." << std::endl;

		Areas::IPointPtr point1 = CompTest02::InstantiatePoint();

		std::cout << "[main] CLSID_Point instantiated successfully." << std::endl;

		Areas::IPointPtr point2 = CompTest02::InstantiatePoint();

		std::cout << "[main] CLSID_Point instantiated successfully." << std::endl;

		Areas::IPointPtr point3 = CompTest02::InstantiatePoint();

		std::cout << "[main] CLSID_Point instantiated successfully." << std::endl;

		mc::ICommonPtr sinkCommon = CompTest02::InstantiateSink();

		std::cout << "[main] EventsSink instantiated successfully." << std::endl;

		CompTest02::AddPoint(area, point1);
		
		std::cout << "[main] point1 successfully added." << std::endl;

		unsigned long cookie = CompTest02::AdviseSink(area, sinkCommon);

		std::cout << "[main] Events sink advised successfully." << std::endl;

		CompTest02::AddPoint(area, point2);

		std::cout << "[main] point2 successfully added." << std::endl;

		CompTest02::AddPoint(area, point2);

		std::cout << "[main] point3 successfully added." << std::endl;

		point2->SetLocation(5.0f, 6.0f);

		std::cout << "[main] Location for point2 changed." << std::endl;

		point2->SetLocation(12.0f, 4.0f);

		std::cout << "[main] Location for point2 changed." << std::endl;

		std::cout 
			<< "[main] point2 location is (" 
			<< point2->GetX() << ", " << point2->GetY()
			<< ")." << std::endl;

		CompTest02::UnadviseSink(area, cookie);

		std::cout << "[main] Events sink unadvised successfully." << std::endl;

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}