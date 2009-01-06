#include "Common/Common.h"

#include "CommonKit/Container.h"

#include "MultiSynchro.h"

#include "CommonKit/Platform.h"

namespace MinCOM
{

	typedef Container::IEnumerator< ISynchroPtr > ISynchrosEnum_;

	typedef ComPtr< ISynchrosEnum_ > ISynchrosEnumPtr_;

	typedef const ISynchrosEnumPtr_& ISynchrosEnumRef_;
	
#ifdef WIN32

	result MultiSynchroWait(ISynchrosEnumRef_ synchros, ISynchroPtr& synchro, unsigned long milliseconds, unsigned long flags)
	{
		synchro = ISynchroPtr();	

		HANDLE* pHandles = new HANDLE[synchros->GetTotal()];
		unsigned int count = 0;
		std::vector< ISynchroPtr > localSynchros;

		for ( bool hasSync = synchros->SelectFirst() ; hasSync ; hasSync = synchros->SelectNext() )
		{
			ISynchroPtr synchro = synchros->GetSelected();

			ISynchroHandlePtr synchrosHandle(synchro, IID_ISynchroHandle);
			if ( !synchrosHandle )
				continue;

			result code = synchrosHandle->GetHandle(&pHandles[count]);
			if ( IsFailed(code) || !pHandles[count] )
				continue;

			localSynchros.push_back(synchro);
			++count;
		}

		if ( !count )
			return _E_FAIL;

		BOOL alertable = ( flags & WAIT_ALERTABLE ) ? ( TRUE ) : ( FALSE );
		BOOL waitAll = ( flags & WAIT_WAITALL ) ? ( TRUE ) : ( FALSE );

		unsigned long waitResult = ::WaitForMultipleObjectsEx(
			count, 
			pHandles, 
			waitAll, 
			milliseconds, 
			alertable);

		delete [] pHandles;

		if ( ( waitResult == WAIT_FAILED ) || 
			( waitResult >= WAIT_ABANDONED_0 && waitResult <= WAIT_ABANDONED_0 + count - 1 ) )
			return _E_FAIL;

		if ( waitResult == WAIT_IO_COMPLETION )
			return _E_FAIL;

		if ( waitResult == WAIT_TIMEOUT )
			return _S_FALSE;
		
		if ( waitResult >= WAIT_OBJECT_0 && waitResult <= WAIT_OBJECT_0 + count - 1 )	
		{
			if ( !waitAll )
				synchro = localSynchros[waitResult - WAIT_OBJECT_0];

			return _S_OK;
		}				

		// Unrecognized error code
		return _E_FAIL;
	}

#endif // WIN32


	MultiSynchro::MultiSynchro()
		: CommonImpl< IMultiSynchro >()
		, handles_(Container::CreateUnmanagedDefault< ISynchroPtr >())
		, lastSignaled_()
	{
	}
	
	MultiSynchro::~MultiSynchro()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(MultiSynchro)
		COMMON(IMultiSynchro)
		INTERFACE_(IMultiSynchro, IID_IMultiSynchro)
	END_INTERFACE_MAP()	

	// IMultiSynchro section
	result MultiSynchro::Add(ISynchroRef synchro)
	{
		return handles_->Add(synchro);
	}

	result MultiSynchro::Delete(ISynchroRef synchro)
	{
		return handles_->Delete(synchro);
	}

	result MultiSynchro::Wait(unsigned long milliseconds /* = INFINITE */, unsigned long flags /* = 0 */)
	{
		lastSignaled_ = ISynchroPtr();

		return MultiSynchroWait(handles_->Clone(), lastSignaled_, milliseconds, flags);
	}

	ISynchroPtr MultiSynchro::GetSignaled()
	{
		return lastSignaled_;
	}

}
