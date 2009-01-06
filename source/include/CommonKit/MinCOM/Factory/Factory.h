#ifndef FACTORY_H__MINCOM__COMMONKIT__INCLUDED_
#define FACTORY_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	template
	<
		class AbstractProduct, 
		typename IdentifierType,
		typename ProductCreator = AbstractProduct (*)()
	>
	class Factory 
	{

		struct Exception_ : public std::exception
		{
			const char* what() const throw() 
			{ 
				return "Unknown Type"; 
			}
		}; 

	public:

		typedef ProductCreator Creator_;

		Factory()
			: associations_()
		{
		}

		bool Register(const IdentifierType& id, ProductCreator creator)
		{
			return associations_.insert(
				typename IdToProductMap_::value_type(id, creator)
			).second;
		}
	    
		bool Unregister(const IdentifierType& id)
		{
			return associations_.erase(id) == 1;
		}
	    
		AbstractProduct CreateObject(const IdentifierType& id)
		{
			typename IdToProductMap_::iterator i = associations_.find(id);
			if (i != associations_.end())
			{
				return (i->second)();
			}
			throw Exception_();
		}

		bool CanProduce(const IdentifierType& id)
		{
			return ( associations_.find(id) != associations_.end() );
		}
	    
	private:

		typedef std::map< IdentifierType, ProductCreator > IdToProductMap_;

		IdToProductMap_ associations_;

	};	

}

#endif // !FACTORY_H__MINCOM__COMMONKIT__INCLUDED_
