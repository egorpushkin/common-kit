#ifndef IBEHAVIOUR_H__AREASSELECTOR__INCLUDED_
#define IBEHAVIOUR_H__AREASSELECTOR__INCLUDED_

class QPainter;

namespace AreasSelector
{

	interface IBehaviour : public mc::ICommon
	{

		virtual mc::result OnPaint(QPainter& painter) = 0;

		virtual mc::result OnResize(int width, int height) = 0;

		virtual mc::result OnScroll(int dx, int dy) = 0;

		virtual mc::result OnMouseMove(int x, int y, unsigned long modifyers) = 0;

		virtual mc::result OnMousePress(int x, int y, unsigned long modifyers) = 0; 

		virtual mc::result OnMouseRelease(int x, int y, unsigned long modifyers) = 0; 

		virtual mc::result OnContextMenu(int x, int y, int globalX, int globalY) = 0; 

		virtual mc::result OnMouseWheel(int x, int y, int delta, bool horiz) = 0; 

	};

	typedef mc::ComPtr< IBehaviour > IBehaviourPtr;
	typedef const IBehaviourPtr& IBehaviourRef;

	// {9267a01b-31df-4649-9fcf-3940289793e5} 
	MC_DEFINE_GUID(IID_IBehaviour, 
	0x9267a01b, 0x31df, 0x4649, 0x9f, 0xcf, 0x39, 0x40, 0x28, 0x97, 0x93, 0xe5);

}

#endif // !IBEHAVIOUR_H__AREASSELECTOR__INCLUDED_
