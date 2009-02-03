#ifndef TOOLSMAP_H__MINCOM__INCLUDED_
#define TOOLSMAP_H__MINCOM__INCLUDED_

namespace MinCOM
{

	template
	<
		class T
	>
	class ToolsMap
	{

		typedef T Tool_;
		
		typedef const T& ToolRef_;

	public:

		ToolsMap()
			: tools_()
		{
		}

		inline void Attach(RefIid toolId, ToolRef_ tool)
		{
			tools_[toolId] = tool;
		}

		inline void Remit(RefIid toolId)
		{
			tools_.erase(toolId);
		}

		inline Tool_ Acquire(RefIid toolId)
		{
			return tools_[toolId];
		}

	private:

		std::map< Iid, Tool_ > tools_;

	};

}

#endif // !TOOLSMAP_H__MINCOM__INCLUDED_
