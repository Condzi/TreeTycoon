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

	auto operator[]( size_t x ) const
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

	size_t sizeFlat() const
	{
		return data.size();
	}

	Vec2u size2D() const
	{
		return size;
	}
	bool empty() const
	{
		return data.empty();
	}
	void reset( const Vec2u& newSize, const T& value = T{} )
	{
		data.clear();
		data.resize( newSize.x * newSize.y, value );
		size = newSize;
	}

	void fill( const T& value )
	{
		std::fill( data.begin(), data.end(), value );
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

	auto begin() const
	{
		return data.begin();
	}
	auto end() const
	{
		return data.end();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}
	auto cend() const
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

	auto crbegin() const
	{
		return data.crbegin();
	}
	auto crend() const
	{
		return data.crend();
	}

private:
	Vec2u size;
	std::vector<T> data;

	size_t coordToIndex( const Vec2u& coord ) const
	{
		return size.x * coord.y + coord.x;
	}
};
}