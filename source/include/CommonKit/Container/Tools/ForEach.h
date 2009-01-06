#ifndef FOREACH_H__CONTAINER__COMMONKIT__INCLUDED_
#define FOREACH_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

	template
	<
		class T,
		class Function
	>
	Function& ForEach(mc::ComPtr< IEnumerator< T > > enumPtr, Function& func)
	{
		if ( !enumPtr )
			return (func);

		for (bool hasElement = enumPtr->SelectFirst(); hasElement; hasElement = enumPtr->SelectNext())
			if ( !func(enumPtr->GetSelected()) )
				break;

		return (func);
	}

}
		
#endif // !FOREACH_H__CONTAINER__COMMONKIT__INCLUDED_
