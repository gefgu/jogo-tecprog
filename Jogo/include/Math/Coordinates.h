#pragma once

namespace Math {
	template <typename T>
	class Coord {
		public:
			T x;
			T y;
		public:
			Coord(T x, T y);
			Coord();
			~Coord();

			void operator +(Coord<T> other);
			void operator -(Coord<T> other);
			void operator *(T scalar);
			void operator /(T scalar);
	};

	template <typename T>
	Coord<T>::Coord(T x, T y) :x(x), y(y) {}

	template <typename T>
	Coord<T>::Coord() :x(0), y(0) {}

	template <typename T>
	Coord<T>::~Coord(){}
}

