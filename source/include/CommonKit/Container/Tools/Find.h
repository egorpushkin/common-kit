#ifndef FIND_H__CONTAINER__COMMONKIT__INCLUDED_
#define FIND_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

	template
	<
		class T
	>
	class IndexLocator
	{
	public:

		IndexLocator(unsigned int index)
			: index_(index)
			, current_(0)
			, found_(false)
			, element_()
		{
		}

		bool operator ()(const T argument)
		{
			if ( current_++ == index_ )
			{
				element_ = argument;
				found_ = true;
				return false;
			}
			return true;
		}

		bool IsFound()
		{
			return found_;
		}

		T GetFound()
		{
			return element_;
		}

	private:

		unsigned int index_;
		unsigned int current_;
		bool found_;
		T element_;

	};

	template
	<
		class T
	>
	class MapKeyLocator
	{

		MapKeyLocator& operator =(const MapKeyLocator&);

	public:

		MapKeyLocator(T& pair)
			: pair_(pair)
			, found_(false)
		{
		}

		bool operator ()(const T argument)
		{
			if ( argument.first == pair_.first )
			{
				pair_.second = argument.second;
				found_ = true;
				return false;
			}
			return true;
		}

		bool IsFound()
		{
			return found_;
		}

	private:

		T& pair_;
		bool found_;

	};

	template
	<
		class T
	>
	class MapValueLocator
	{

		MapValueLocator& operator =(const MapValueLocator&);

	public:

		MapValueLocator(T& pair)
			: pair_(pair)
			, found_(false)
		{
		}

		bool operator ()(const T argument)
		{
			if ( argument.second == pair_.second )
			{
				pair_.first = argument.first; 
				found_ = true;
				return false;
			}
			return true;
		}

		bool IsFound()
		{
			return found_;
		}

	private:

		T& pair_;
		bool found_;

	};

/*
	template
	<
		class T
	>
	bool MapCompareTool(const T& pair1, const T& pair2)
	{
		return ( pair1.first == pair2.second );
	}

	template
	<
		class T,
		class CompareTool< T >
	>
	result Find(mc::ComPtr< IEnumerator< T > > enumPtr, T& value)
	{
		AccessPointPair pointPair(iid, NULL);
		Container::MapKeyLocator<AccessPointPair> locator(pointPair);
		Container::ForEach(accessPoints_->Clone(), locator);

		accessPoint = pointPair.second;


		return ;
	}
*/

}

#endif // !FIND_H__CONTAINER__COMMONKIT__INCLUDED_
