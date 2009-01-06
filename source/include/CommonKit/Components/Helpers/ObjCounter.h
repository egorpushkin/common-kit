#ifndef OBJCOUNTER_H__COMPONENTS__COMMONKIT__INCLUDED_
#define OBJCOUNTER_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class ObjCounter
	{
	protected:
		
		ObjCounter();
		virtual ~ObjCounter();
				
	public:

		static bool CanUnload();

		static void Lock(bool lock);

	protected:

		unsigned long Increment();

		unsigned long Decrement();		

	private:

		static void NotifyOnUnload();	
		
	protected:

		static bool lock_;

		static unsigned long count_;
		
	};
}

#endif // !OBJCOUNTER_H__COMPONENTS__COMMONKIT__INCLUDED_
