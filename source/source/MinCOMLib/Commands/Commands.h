#ifndef COMMANDS_H__MINCOM__INCLUDED_
#define COMMANDS_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class Commands
		: public CommonImpl< ICommands >
 		, public APImpl
	{
	public:

		Commands();

		// ICommands section
		virtual result Undo();

		virtual result Redo();

		virtual bool CanUndo();

		virtual bool CanRedo();

		virtual result Add(ICommandRef command);

		virtual void Enable(bool enable);

		virtual void SetModified(bool modified);

		virtual bool IsModified();

		// ICommon section
		virtual result PostInit();

	private:

		// Private tools
		void UpdateModified();

	private:

		CoreMutex lock_;

		// Command events
		typedef enum tagState_
		{

			STATE_BASE = 0x0,
			
			STATE_UNDO,
			
			STATE_REDO

		} State_;

		typedef std::stack< ICommandPtr > CommandsList_;

		CommandsList_ undo_;

		CommandsList_ redo_;

		State_ state_;

		bool enabled_;

		bool modified_;

		int unmodifiedIndex_;

		/** . */
		ICommandEventsPtr eventsSpreader_;

	};

}

#endif // !COMMANDS_H__MINCOM__INCLUDED_
