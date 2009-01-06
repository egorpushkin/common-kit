#ifndef TOOLSCONTAINER_H__MINCOM__COMMONKIT__INCLUDED_
#define TOOLSCONTAINER_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	template
	<
		class T
	>
	class ToolsContainer
	{

		typedef T Tool_;
		
		typedef const T& ToolRef_;

	public:

		ToolsContainer()
			: tools_()
		{
		}

		result Attach(RefIid toolId, ToolRef_ tool)
		{
			tools_.insert(ToolsPair_(toolId, tool));

			return _S_OK;
		}

		result Remit(RefIid toolId)
		{
			tools_.erase(toolId);

			return _S_OK;
		}

		Tool_ Acquire(RefIid toolId)
		{
			if ( tools_.find(toolId) == tools_.end() )
				return NULL;

			return tools_[toolId];
		}

	private:

		typedef std::pair< Iid, T > ToolsPair_;

		typedef std::map< typename ToolsPair_::first_type, typename ToolsPair_::second_type > ToolsList_;

		ToolsList_ tools_;

	};

}

#endif // !TOOLSCONTAINER_H__MINCOM__COMMONKIT__INCLUDED_
