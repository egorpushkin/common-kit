#ifndef POINT_H__AREASLIB__INCLUDED_
#define POINT_H__AREASLIB__INCLUDED_

namespace Areas
{

	class Point
		: public mc::CommonImpl< IPoint > 
		, public mc::APImpl
		// , public mc::AgentImpl
		, public Components::ObjCounter
	{
	public:

		Point();

		// ICommon section
		DECLARE_INTERFACE_MAP()	

		// IPoint section
		virtual void SetLocation(double x, double y);

		virtual void SetX(double x);

		virtual void SetY(double y);

		virtual double GetX() const;

		virtual double GetY() const;	

		// IAgent section
		// virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		// Event dispatchers
		mc::result OnLocationChanging(double xFrom, double yFrom, double xTo, double yTo);
		
		mc::result OnLocationChanged(double xFrom, double yFrom, double xTo, double yTo);

		// Commands
		mc::result RegisterLocatorCommand(double x, double y);

	private:

		double x_;

		double y_;

	};

}

#endif // !POINT_H__AREASLIB__INCLUDED_
