/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con
{
// 2 Dimensional array. Data can be accesed like that: array[x][y].
template <typename T>
class FixedArray2D final
{
	static_assert( std::is_default_constructible_v<T> );

public:
	FixedArray2D() = default;
	FixedArray2D( const Vec2u& size_ ) :
		size( size_ ),
		data( size.x * size.y )
	{}

	auto operator[]( size_t x )
	{
		struct Helper final
		{
			T& operator[]( size_t y )
			{
				return arr->at( { xCoord,y } );
			}

			FixedArray2D<T>* arr;
			size_t xCoord;
		};

		return Helper{ this, x };
	}

	Vec2u size2D() const
	{
		return size;
	}
	Vec2u count() const
	{
		return data.size();
	}
	bool empty() const
	{
		return data.empty();
	}
	void reset( const Vec2u& newSize )
	{
		data.clear();
		data.resize( newSize.x * newSize.y );
		size = newSize;
	}

	T& at( const Vec2u& coord )
	{
		return data.at( coordToIndex( coord ) );
	}
	const T& at( const Vec2u& coord ) const
	{
		return data.at( coordToIndex( coord ) );
	}

	auto begin()
	{
		return data.begin();
	}
	auto end()
	{
		return data.end();
	}

	auto cbegin()
	{
		return data.cbegin();
	}
	auto cend()
	{
		return data.cend();
	}

	auto rbegin()
	{
		return data.rbegin();
	}
	auto rend()
	{
		return data.rend();
	}

	auto crbegin()
	{
		return data.crbegin();
	}
	auto crend()
	{
		return data.crend();
	}

private:
	Vec2u size;
	std::vector<T> data;

	size_t coordToIndex( const Vec2u& coord )
	{
		return size.x * coord.x + coord.y;
	}
};
}