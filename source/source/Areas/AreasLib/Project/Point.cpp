#include "Common/Common.h"

#include "Point.h"

#include "Project/Commands/PointLocator.h"

namespace Areas
{

	Point::Point()
		: mc::CommonImpl< Areas::IPoint >()
		, mc::APImpl()
		// , mc::AgentImpl()
		, Components::ObjCounter()
		, x_(0.0f)
		, y_(0.0f)
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Point)
		COMMON(IPoint)
		INTERFACE(IPoint)
		IMPL(mc::APImpl)
		// IMPL(mc::AgentImpl)
	END_INTERFACE_MAP()

	// IPoint section
	void Point::SetLocation(double x, double y)
	{
		// Notify sinks
		if ( mc::IsFailed(OnLocationChanging(x_, y_, x, y)) )
			return;		

		// Register command (required for undo support)
		RegisterLocatorCommand(x_, y_);
		
		// Modify object
		x_ = x;
		y_ = y;		

		// Notify sinks
		OnLocationChanged(x_, y_, x, y);
	}

	void Point::SetX(double x)
	{
		SetLocation(x, y_);
	}

	void Point::SetY(double y)
	{
		SetLocation(x_, y);
	}

	double Point::GetX() const
	{
		return x_;
	}

	double Point::GetY() const
	{
		return y_;
	}

	// IAgent section
	/* mc::result Point::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid /* iid *)
	{
		if ( AGENTID_PT_SETLOCATION == idMember )
		{
			if ( !dispParams->Get(0) || !dispParams->Get(1) )
				return mc::_E_FAIL;

			SetLocation(
				dispParams->Get(1)->toDouble(),
				dispParams->Get(0)->toDouble());
		}
		else if ( AGENTID_PT_GETX == idMember )
		{
			if ( !result )
				return mc::_E_FAIL;

			result->SetData(GetX());
		}
		else if ( AGENTID_PT_GETY == idMember )
		{
			if ( !result )
				return mc::_E_FAIL;

			result->SetData(GetY());
		}
		
		return mc::_S_OK;
	} */

	// Event dispatchers
	mc::result Point::OnLocationChanging(double xFrom, double yFrom, double xTo, double yTo)
	{
		bool cancel = false;
		mc::result code = mc::APImpl::SpreadBase(
			AGENTID_LOCATIONCHANGING, 
			CreateParams(
				mc::ItemImpl::GetLocal(),
				xFrom,
				yFrom,
				xTo,
				yTo,
				&cancel));

		if ( mc::IsFailed(code) || cancel )
			return mc::_E_FAIL;

		return mc::_S_OK;
	}

	mc::result Point::OnLocationChanged(double xFrom, double yFrom, double xTo, double yTo)
	{
		return mc::APImpl::SpreadBase(
			AGENTID_LOCATIONCHANGED, 
			CreateParams(
				mc::ItemImpl::GetLocal(),
				xFrom,
				yFrom,
				xTo,
				yTo));
	}

	// Commands
	mc::result Point::RegisterLocatorCommand(double x, double y)
	{
		mc::ICommandPtr command = mc::InstantiateCommand< PointLocator >(
			mc::CreateParams(
				mc::ItemImpl::GetLocal(), 
				x, 
				y));
		if ( !command )
			return mc::_E_FAIL;

		mc::ICommandsPtr commands(mc::ItemImpl::Acquire(mc::CLSID_Commands), mc::IID_ICommands);
		if ( !commands )
			return mc::_S_FALSE;

		return commands->Add(command);
	}

}
