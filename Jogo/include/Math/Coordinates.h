#pragma once
#include <iostream>

using namespace std;

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

			void operator=(Coord<T> other);
			void operator+=(Coord<T> other);
			void operator-=(Coord<T> other);
			void operator*=(T scalar);

			Coord<T> operator+(Coord<T> other);
			Coord<T> operator-(Coord<T> other);
			Coord<T> operator*(T scalar);
	};

	template <typename T>
	Coord<T>::Coord(T x, T y) :x(x), y(y) {}

	template <typename T>
	Coord<T>::Coord() :x(0), y(0) {}

	template <typename T>
	Coord<T>::~Coord(){}

	template <typename T>
	void Coord<T>::operator=(Coord<T> other) {
		this->x = other.x;
		this->y = other.y;
	}

	template <typename T>
	void Coord<T>::operator+=(Coord<T> other) {
		this->x += other.x;
		this->y += other.y;
	}

	template <typename T>
	void Coord<T>::operator-=(Coord<T> other) {
		this->x -= other.x;
		this->y -= other.y;
	}

	template <typename T>
	void Coord<T>::operator*=(T scalar) {
		this->x *= scalar;
		this->y *= scalar;
	}

	template <typename T>
	Coord<T> Coord<T>::operator+(Coord<T> other) {
		return Coord<T>(this->x + other.x, this->y + other.y);
	}

	template <typename T>
	Coord<T> Coord<T>::operator-(Coord<T> other) {
		return Coord<T>(this->x - other.x, this->y - other.y);
	}

	template <typename T>
	Coord<T> Coord<T>::operator*(T scalar) {
		return Coord<T>(this->x * scalar, this->y * scalar);
	}

	template <typename T>
	ostream& operator<<(ostream& os, Coord<T> const& m) {
		return os << '(' << m.x << ',' << m.y << ')';
	}
}

