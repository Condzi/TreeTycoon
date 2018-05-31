/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con
{

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