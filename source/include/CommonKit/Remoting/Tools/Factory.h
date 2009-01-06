#ifndef FACTORY_H__REMOTING__COMMONKIT__INCLUDED_
#define FACTORY_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	mc::ICommonPtr Instantiate(mc::RefClsid clsid, Network::IHostRef host);

}

#endif // !FACTORY_H__REMOTING__COMMONKIT__INCLUDED_
