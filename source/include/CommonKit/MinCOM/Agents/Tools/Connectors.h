#ifndef CONNECTORS_H__AGENTS__COMMONKIT__INCLUDED_
#define CONNECTORS_H__AGENTS__COMMONKIT__INCLUDED_

namespace MinCOM
{

	mc::result Advise(
		ICommonRef connectee, 
		ICommonRef connector, 
		unsigned long& cookie, 
		RefIid apIid = IID_IAgent);

	mc::result Unadvise(
		ICommonRef connectee, 
		unsigned long cookie, 
		RefIid apIid = IID_IAgent);

	mc::result Connect(
		ICommonRef connectee, 
		ICommonRef connector,
		RefIid apIid = IID_IAgent);

}

#endif // !CONNECTORS_H__AGENTS__COMMONKIT__INCLUDED_
