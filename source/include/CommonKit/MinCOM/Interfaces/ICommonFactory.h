#ifndef ICOMMONFACTORY_H__MINCOM__COMMONKIT__INCLUDED_
#define ICOMMONFACTORY_H__MINCOM__COMMONKIT__INCLUDED_

interface ICommonFactory: public ICommon
{
    virtual result        LockServer(bool lock) = 0;
    virtual result        CreateInstance(REFIID iid, void** ppObject) = 0;
};

typedef ComPtr< ICommonFactory > ICommonFactoryPtr;
typedef ComPtr< ICommonFactory, false > ICommonFactoryWeak;

// {08f73b9a-2777-4676-85f2-0236e16cff5a} 
DEFINE_GUID(IID_ICommonFactory, 
0x08f73b9a, 0x2777, 0x4676, 0x85, 0xf2, 0x02, 0x36, 0xe1, 0x6c, 0xff, 0x5a);

#endif // !ICOMMONFACTORY_H__MINCOM__COMMONKIT__INCLUDED_
