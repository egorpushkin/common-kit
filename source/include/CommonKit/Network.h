#ifndef NETWORK_H__NETWORK__COMMONKIT__INCLUDED_
#define NETWORK_H__NETWORK__COMMONKIT__INCLUDED_

// External requirements
//////////////////////////////////////////////////////////////////////////
#include "Network/External.h"


// Core
//////////////////////////////////////////////////////////////////////////
#include "Network/Interfaces/IHost.h"
#include "Network/Interfaces/IClient.h"
#include "Network/Interfaces/IServer.h"

#include "Network/Interfaces/IMessage.h"
#include "Network/Interfaces/IProtocol.h"


// Partial implementations
//////////////////////////////////////////////////////////////////////////
#include "Network/Model/HostImpl.h"
#include "Network/Model/MessageImpl.h"


// Tools
//////////////////////////////////////////////////////////////////////////
#include "Network/Tools/Utilities.h"
#include "Network/Tools/Hosts.h"


#endif // !PROJECT_H__PROJECT__COMMONKIT__INCLUDED_
