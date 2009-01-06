#include "Common.h"

#include "AreasKit/AreasKit.h"

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{

	try
	{

		std::cout << "[main] Attempting to perform any test." << std::endl;

		// Instantiating CLSID_Point from shared object
		mc::ICommonPtr pointCommon = Components::InstantiateCommon(Areas::CLSID_Point);
		if ( !pointCommon ) 
			throw std::exception("[main] Error instantiating CLSID_Point.");

		// Requesting the IID_IPoint interface
		Areas::IPointPtr point(pointCommon, Areas::IID_IPoint);
		if ( !point )
			throw std::exception("[main] Failed to query the IID_IPoint.");

		std::cout << "[main] CLSID_Point instantiated successfully." << std::endl;

		point->SetLocation(10.0f, 11.0f);

		std::cout 
			<< "[main] Current location is:" 
			<< std::endl
			<< "X: " << point->GetX() << std::endl
			<< "Y: " << point->GetY() << std::endl;

	}
	catch ( std::exception& e )
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}
