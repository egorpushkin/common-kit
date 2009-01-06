#ifndef ADDROLLBACK_H__PROJECTLIB__INCLUDED_
#define ADDROLLBACK_H__PROJECTLIB__INCLUDED_

namespace Project
{

	class AddRollback
		: public mc::CommandImpl
#ifdef _COMPLIB
		, public Components::ObjCounter
#endif // _COMPLIB
	{
	public:

		AddRollback();

		// ICommand section
		virtual mc::result Configure(mc::DispParamsRef params);

		virtual mc::result Undo();

	private:

		IContainerWeak container_;
		
		mc::ICommonPtr item_;

	};

}

#endif // !ADDROLLBACK_H__PROJECTLIB__INCLUDED_
