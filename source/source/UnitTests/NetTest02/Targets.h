#ifndef TARGETS_H
#define TARGETS_H

// Methods
//////////////////////////////////////////////////////////////////////////
typedef enum tagTarget1Methods
{

	T1_METHOD_1 = 0xff01,
	
	T1_METHOD_2,

	T1_METHOD_3,

	T1_METHOD_4,

	T1_METHOD_5,

	T1_METHOD_LAST
	
} 
Target1Methods;

typedef enum tagTarget2Methods
{

	T2_METHOD_1 = T1_METHOD_LAST + 1,

	T2_METHOD_2,

	T2_METHOD_3,

	T2_METHOD_4,

	T2_METHOD_5,

	T2_METHOD_LAST

} 
Target2Methods;

typedef enum tagTarget3Methods
{

	T3_METHOD_1 = T2_METHOD_LAST + 1,

	T3_METHOD_2,

	T3_METHOD_3,

	T3_METHOD_4,

	T3_METHOD_5,

	T3_METHOD_LAST

} 
Target3Methods;

// Class identifiers
//////////////////////////////////////////////////////////////////////////

// {3D7CAAC0-76A3-477f-BA68-35AD8A90A187}
MC_DEFINE_GUID(CLSID_Target1, 
0x3d7caac0, 0x76a3, 0x477f, 0xba, 0x68, 0x35, 0xad, 0x8a, 0x90, 0xa1, 0x87);

// {8dd46dc0-488d-421a-ae78-9b7e4d67a234} 
MC_DEFINE_GUID(CLSID_Target2, 
0x8dd46dc0, 0x488d, 0x421a, 0xae, 0x78, 0x9b, 0x7e, 0x4d, 0x67, 0xa2, 0x34);

// {B24A56DE-7F79-4864-B32A-5364543D4C7A}
MC_DEFINE_GUID(CLSID_CustomPoint, 
0xb24a56de, 0x7f79, 0x4864, 0xb3, 0x2a, 0x53, 0x64, 0x54, 0x3d, 0x4c, 0x7a);

// Datatypes
//////////////////////////////////////////////////////////////////////////
typedef std::stack< mc::ICommonPtr > Objects;

#endif // !TARGETS_H
