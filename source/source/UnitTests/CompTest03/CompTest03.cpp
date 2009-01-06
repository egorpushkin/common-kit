#include "Common.h"

#include "AreasKit/AreasKit.h"

class EventsSink
	: public mc::AgentImpl
{
public:

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef /* dispParams */, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{

		if ( Areas::AGENTID_POINTADDED == idMember )
		{
			std::cout << "[EventsSink::Invoke] AGENTID_POINTADDED signaled." << std::endl;
		}
		else if ( Areas::AGENTID_POINTDELETED == idMember )
		{
			std::cout << "[EventsSink::Invoke] AGENTID_POINTDELETED signaled." << std::endl;
		}
		else if ( Areas::AGENTID_LOCATIONCHANGED == idMember )
		{
			std::cout << "[EventsSink::Invoke] AGENTID_LOCATIONCHANGED signaled." << std::endl;
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

	static mc::ICommonPtr InstantiateSink()
	{
		mc::ICommonPtr sinkCommon = mc::ObjectCreator< EventsSink >();
		if ( !sinkCommon )
			throw std::exception("[CompTest02::InstantiateSink] Failed to instantiate events sink.");

		return sinkCommon;
	}

};

class CompTest03
{
public:

	static Areas::IAProjectPtr InstantiateProject()
	{
		// Instantiating CLSID_AreasProject from shared object
		mc::ICommonPtr projectCommon = Components::InstantiateCommon(Areas::CLSID_AreasProject);
		if ( !projectCommon ) 
			throw std::exception("[CompTest03::InstantiateArea] Error instantiating CLSID_AreasProject.");

		// Requesting the IID_IAProject interface
		Areas::IAProjectPtr project(projectCommon, Areas::IID_IAProject);
		if ( !project )
			throw std::exception("[CompTest03::InstantiateArea] Failed to query the IID_IAProject.");

		return project;
	}

	template
	<
		class Container,
		class Contained
	>
	static mc::result Add(
		const mc::ComPtr< Container >& container, 
		const mc::ComPtr< Contained >& contained)
	{
		Project::IContainerPtr projectContainer(container, Project::IID_IContainer);
		if ( !projectContainer )
			throw std::exception("[CompTest03::Add<T,U>] Failed to query the Project::IID_IContainer.");

		if ( mc::IsFailed(projectContainer->Add(mc::ICommonPtr(contained, mc::IID_ICommon))) )
			throw std::exception("[CompTest03::Add<T,U>] Failed to add item.");

		return mc::_S_OK;
	}

	static mc::ICommandsPtr AcquireCommands(Areas::IAProjectRef project)
	{
		mc::IItemPtr projectItem(project, mc::IID_IItem);
		if ( !projectItem )
			throw std::exception("[CompTest03::AcquireCommands] Failed to query the mc::IID_IItem.");

		mc::ICommandsPtr commands(
			projectItem->Acquire(mc::CLSID_Commands), 
			mc::IID_ICommands);

		if ( !commands )
			throw std::exception("[CompTest03::AcquireCommands] Failed to acquire CLSID_Commands object from project.");

		return commands;
	}

	static void Dump(Areas::IPointRef point, const mc::StringA& id)
	{
		std::cout 
			<< "[main] "
			<< id << " location is (" 
			<< point->GetX() << ", " << point->GetY()
			<< ") now." << std::endl;
	}


};

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		std::cout << "[main] Attempting to perform any test." << std::endl;

		Areas::IAProjectPtr project = CompTest03::InstantiateProject();

		std::cout << "[main] CLSID_AreasProject instantiated successfully." << std::endl;

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

		unsigned long cookie = 0;
		mc::result code = mc::Advise(
			mc::ICommonPtr(project, mc::IID_ICommon),
			sinkCommon,
			cookie);
		(void)cookie;

		if ( mc::IsFailed(code) )
			throw std::exception("[main] Failed to advise events sink.");

		std::cout << "[main] Events sink advised successfully." << std::endl;

		CompTest03::Add(project, area);

		std::cout << "[main] area successfully added into project." << std::endl;

		CompTest03::Add(area, point1);

		std::cout << "[main] point1 successfully added." << std::endl;

		CompTest03::Add(area, point2);

		std::cout << "[main] point2 successfully added." << std::endl;

		CompTest03::Add(area, point2); // Operation 3

		std::cout << "[main] point3 successfully added." << std::endl;

		point2->SetLocation(5.0f, 6.0f); // Operation 2

		std::cout << "[main] Location for point2 changed." << std::endl;

		point2->SetLocation(12.0f, 4.0f); // Operation 1

		std::cout << "[main] Location for point2 changed." << std::endl;

		CompTest03::Dump(point2, "point2");

		mc::ICommandsPtr commands = CompTest03::AcquireCommands(project);
	
		std::cout << "[main] Undo manager acquired." << std::endl;

		commands->Undo(); // Undo "Operation 1"

		CompTest03::Dump(point2, "point2");

		commands->Undo(); // Undo "Operation 2"

		CompTest03::Dump(point2, "point2");

		commands->Undo(); // Undo "Operation 3"

		commands->Redo(); // Redo "Operation 3"

		commands->Redo(); // Redo "Operation 2"

		CompTest03::Dump(point2, "point2");

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}