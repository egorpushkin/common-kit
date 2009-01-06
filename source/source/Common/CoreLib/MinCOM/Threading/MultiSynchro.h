#ifndef MULTISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_
#define MULTISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class MultiSynchro 
		: public CommonImpl< IMultiSynchro >
	{
	public:

		MultiSynchro();
		virtual ~MultiSynchro();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IMultiSynchro section
		virtual result Add(ISynchroRef synchro);

		virtual result Delete(ISynchroRef synchro);

		virtual result Wait(unsigned long milliseconds = INFINITE, unsigned long flags = 0);

		virtual ISynchroPtr GetSignaled();

	private:

		typedef Container::IContainer< ISynchroPtr > ISynchros_;

		typedef ComPtr< ISynchros_ > ISynchrosPtr_;

		ISynchrosPtr_ handles_;

		ISynchroPtr lastSignaled_;

	};

}

#endif // !MULTISYNCHRO_H__MINCOM__COMMONKIT__INCLUDED_
