#ifndef DELETEROLLBACK_H__PROJECTLIB__INCLUDED_
#define DELETEROLLBACK_H__PROJECTLIB__INCLUDED_

namespace Project
{

	class DeleteRollback
		: public mc::CommandImpl
#ifdef _COMPLIB
		, public Components::ObjCounter
#endif // _COMPLIB
	{
	public:

		DeleteRollback();

		// ICommand section
		virtual mc::result Configure(mc::DispParamsRef params);

		virtual mc::result Undo();

	private:

		IContainerWeak container_;

		mc::ICommonPtr item_;

		unsigned int index_;

	};

}

#endif // !DELETEROLLBACK_H__PROJECTLIB__INCLUDED_
