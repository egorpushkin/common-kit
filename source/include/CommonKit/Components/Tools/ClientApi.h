#ifndef CLIENTAPI_H__COMPONENTS__COMMONKIT__INCLUDED_
#define CLIENTAPI_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	mc::ICommonPtr InstantiateCommon(mc::RefClsid objId);

	mc::ICommonPtr InstantiateCommon(mc::RefIid libIid, mc::RefClsid objId);

	mc::result SetCoreMode();

}

#endif // !CLIENTAPI_H__COMPONENTS__COMMONKIT__INCLUDED_
