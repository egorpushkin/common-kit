#ifndef BASESPREADERS_H__AGENTS__COMMONKIT__INCLUDED_
#define BASESPREADERS_H__AGENTS__COMMONKIT__INCLUDED_

namespace MinCOM
{

	typedef std::pair< unsigned long, ICommonWeak > AccessEntryPair;

	class DispSpreader 
	{
	public:

		DispSpreader(DispId id, DispParamsRef params);

		result GetLastError() const;

		virtual bool operator()(AccessEntryPair sinkPair);

	protected:

		void SetLastError(result code);

	protected:

		result lastError_;

		DispId id_;
		DispParamsPtr params_;

	};

	// Params generators
	//////////////////////////////////////////////////////////////////////////

	// 0 parameters
	inline mc::DispParamsPtr CreateParams()
	{
		return mc::CreateParamsCore(0);	
	}

	// 1 parameters
	template 
	< typename T1 >
	mc::DispParamsPtr CreateParams(T1 p1)
	{
		mc::DispParamsPtr params = mc::CreateParamsCore(1);

		params->Set(0, mc::CommonVariant(p1)); 

		return params;	
	}

	// 2 parameters
	template 
	< typename T1, typename T2 >
	mc::DispParamsPtr CreateParams(T1 p1, T2 p2)
	{
		mc::DispParamsPtr params = mc::CreateParamsCore(2);

		params->Set(0, mc::CommonVariant(p2)); 
		params->Set(1, mc::CommonVariant(p1)); 

		return params;	
	}

	// 3 parameters
	template 
	< typename T1, typename T2, typename T3 >
	mc::DispParamsPtr CreateParams(T1 p1, T2 p2, T3 p3)
	{
		mc::DispParamsPtr params = mc::CreateParamsCore(3);

		params->Set(0, mc::CommonVariant(p3)); 
		params->Set(1, mc::CommonVariant(p2)); 
		params->Set(2, mc::CommonVariant(p1)); 

		return params;	
	}

	// 5 parameters
	template 
	< typename T1, typename T2, typename T3, typename T4, typename T5 >
	mc::DispParamsPtr CreateParams(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
	{
		mc::DispParamsPtr params = mc::CreateParamsCore(6);

		params->Set(0, mc::CommonVariant(p5)); 
		params->Set(1, mc::CommonVariant(p4)); 
		params->Set(2, mc::CommonVariant(p3)); 
		params->Set(3, mc::CommonVariant(p2)); 
		params->Set(4, mc::CommonVariant(p1)); 

		return params;	
	}

	// 6 parameters
	template 
	< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	mc::DispParamsPtr CreateParams(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
	{
		mc::DispParamsPtr params = mc::CreateParamsCore(6);

		params->Set(0, mc::CommonVariant(p6)); 
		params->Set(1, mc::CommonVariant(p5)); 
		params->Set(2, mc::CommonVariant(p4)); 
		params->Set(3, mc::CommonVariant(p3)); 
		params->Set(4, mc::CommonVariant(p2)); 
		params->Set(5, mc::CommonVariant(p1)); 

		return params;	
	}

}

#endif // !BASESPREADERS_H__AGENTS__COMMONKIT__INCLUDED_
