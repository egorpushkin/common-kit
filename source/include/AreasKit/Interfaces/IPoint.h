#ifndef IPOINT_H__AREASKIT__INCLUDED_
#define IPOINT_H__AREASKIT__INCLUDED_

namespace Areas
{

	interface IPoint : public mc::ICommon
	{

		virtual void SetLocation(double x, double y) = 0;

		virtual void SetX(double x) = 0;

		virtual void SetY(double y) = 0;

		virtual double GetX() const = 0;

		virtual double GetY() const = 0;

	};

	typedef mc::ComPtr< IPoint > IPointPtr;
	typedef const IPointPtr& IPointRef;

	typedef mc::ComPtr< IPoint, false > IPointWeak;

	// {7472eed3-d07f-48f8-8bd4-e5758fce8d1e} 
	MC_DEFINE_GUID(IID_IPoint, 
	0x7472eed3, 0xd07f, 0x48f8, 0x8b, 0xd4, 0xe5, 0x75, 0x8f, 0xce, 0x8d, 0x1e);

	typedef enum tagPointEvents
	{

		AGENTID_LOCATIONCHANGING = AGENTID_LAST_IMG_EVENT,
		AGENTID_LOCATIONCHANGED,
		AGENTID_LAST_PT_EVENT
	
	} PointEvents;

	typedef enum tagPointMethods
	{

		AGENTID_PT_SETLOCATION = AGENTID_LAST_PT_EVENT,
		AGENTID_PT_GETX,
		AGENTID_PT_GETY,
		AGENTID_LAST_PT_METHOD

	} PointMethods;

}

#endif // !IPOINT_H__AREASKIT__INCLUDED_
