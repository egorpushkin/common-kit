#ifndef POINTPS_H__AREASLIB__INCLUDED_
#define POINTPS_H__AREASLIB__INCLUDED_

namespace Areas
{

	class PointPS
		: public mc::CommonImpl< IPoint > 
		, public mc::AgentImpl
		, public mc::ProxyStubImpl
		, public Components::ObjCounter
	{
	public:

		PointPS();

		// ICommon section
		DECLARE_INTERFACE_MAP()	

		// IPoint section
		virtual void SetLocation(double x, double y);

		virtual void SetX(double x);

		virtual void SetY(double y);

		virtual double GetX() const;

		virtual double GetY() const;	

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	};

}

#endif // !POINTPS_H__AREASLIB__INCLUDED_
