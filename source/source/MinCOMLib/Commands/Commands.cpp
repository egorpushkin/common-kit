#include "Common/Common.h"

#include "Commands.h"

namespace MinCOM
{

	Commands::Commands()
		: CommonImpl< ICommands >()
		, mc::APImpl()
		, lock_()
		, undo_()
		, redo_()
		, state_(STATE_BASE)
		, enabled_(true)
		, modified_(false)
		, unmodifiedIndex_(0)
	{
	}

	// IAgent section
	result Commands::Undo()
	{
		CoreMutexLock locker(lock_);

		if ( !CanUndo() )
			return _S_FALSE;

		state_ = STATE_UNDO;
		
		// Get top command
		ICommandPtr command = undo_.top();

		// Release command from list
		undo_.pop();

		// Undo current operation
		result code = command->Undo();

		state_ = STATE_BASE;

		// Update modified state
		UpdateModified();

		return code;
	}

	result Commands::Redo()
	{
		CoreMutexLock locker(lock_);

		if ( !CanRedo() )
			return _S_FALSE;

		state_ = STATE_REDO;

		// Get top command
		ICommandPtr command = redo_.top();

		// Release command from list
		redo_.pop();

		// Undo current operation
		result code = command->Undo();

		state_ = STATE_BASE;

		// Update modified state
		UpdateModified();

		return code;
	}

	bool Commands::CanUndo()
	{
		CoreMutexLock locker(lock_);
		return ( enabled_ && !undo_.empty() );
	}

	bool Commands::CanRedo()
	{
		CoreMutexLock locker(lock_);
		return ( enabled_ && !redo_.empty() );
	}

	result Commands::Add(ICommandRef command)
	{
		CoreMutexLock locker(lock_);

		if ( !enabled_ )
			return _S_FALSE;

		switch ( state_ )
		{
		case STATE_BASE:
		{
			undo_.push(command);

			while ( !redo_.empty() )
				redo_.pop();

			// Update modified state
			UpdateModified();

			break;
		}
		case STATE_UNDO:
		{
			redo_.push(command);

			break;
		}
		case STATE_REDO:
		{
			undo_.push(command);

			break;
		}
		}

		return _S_OK;
	}

	void Commands::Enable(bool enable)
	{
		CoreMutexLock locker(lock_);

		enabled_ = enable;

		if ( !enabled_ )
		{
			while ( !undo_.empty() )
				undo_.pop();

			while ( !redo_.empty() )
				redo_.pop();

			modified_ = false;
			unmodifiedIndex_ = 0;
		}
	}

	void Commands::SetModified(bool modified)
	{
		CoreMutexLock locker(lock_);

		if ( !enabled_ ) 
			return;

		if ( modified_ == modified )
			return;

		// Update state
		modified_ = modified;

		// Remember current position if project goes to unmodified state
		if ( !modified_ )
			unmodifiedIndex_ = (int)undo_.size();
		
		// Notify all about project modification
		OnModifiedChanged(modified_);
	}

	bool Commands::IsModified()
	{
		CoreMutexLock locker(lock_);
		return modified_;
	}

	// Private tools
	void Commands::UpdateModified()
	{
		bool modified = modified_;

		modified_ = ( unmodifiedIndex_ != (int)undo_.size() );
		
		if ( modified != modified_ )
			OnModifiedChanged(modified_);
	}

	// Event dispatchers
	mc::result Commands::OnModifiedChanged(bool modified)
	{
		/* return mc::APImpl::SpreadBase(
			AGENTID_MODIFIEDCHANGED, 
			CreateParams(
				modified)); */
		// TODO: 
		return _E_NOTIMPL;
	}

}
