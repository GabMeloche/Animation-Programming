#pragma once
// Make your .inl here in include folder.

namespace GPM
{
    struct Quaternion;

	template<typename T>
	struct Vector3
	{
        static_assert(std::is_arithmetic<T>::value, "Vector3 should only be used with arithmetic types");
		
        constexpr Vector3(const T p_x, const T p_y, const T p_z) : x{ p_x }, y{ p_y }, z{ p_z }{}
        template<typename U>
        constexpr Vector3(const Vector3<U>& p_other);
        template<typename U>
        constexpr Vector3(Vector3<U>&& p_other) noexcept;

        Vector3() = default;
		T x;
		T y;
		T z;

        template<typename U>
        constexpr Vector3<T> Add(const Vector3<U>& p_vector);
        template<typename U>
        constexpr Vector3<T> Add(const Vector3<T>& p_left, const Vector3<U>& p_right);
        template<typename U>
        constexpr void Substract(const Vector3<U>& p_vector);
        template<typename U>
        constexpr void Multiply(const Vector3<U>& p_vector);
        template<typename U>
        constexpr void Divide(const Vector3<U>& p_vector);
        constexpr void Set(T p_x, T p_y, T p_z);
        constexpr void Scale(T p_factor);
        constexpr void Normalize();
        constexpr Vector3<T> Normalized() const;
        constexpr std::string ToString();

        template<typename U>
        constexpr T Dot(const Vector3<U>& p_vector) const;
        template<typename U>
        constexpr T Angle(const Vector3<U>& p_vector) const;

        constexpr T Magnitude() const;

        static Vector3<T> forward;
        static Vector3<T> right;
        static Vector3<T> up;
        static Vector3<T> zero;
        static Vector3<T> one;

        template<typename U>
		constexpr inline Vector3<T> Cross(const Vector3<U>& p_other) const;
        template<typename U>
        constexpr static Vector3<T> Cross(const Vector3<T>& p_vectorA, const Vector3<U>& p_vectorB);
        template<typename U>
        constexpr static Vector3<T> Lerp(Vector3<T>& p_vectorA, Vector3<U>& p_vectorB, const T p_factor);
        template<typename U>
        constexpr static Vector3<T> Slerp(Vector3<T>& p_vectorA, Vector3<U>& p_vectorB, const T p_factor);
        template<typename U>
        constexpr static T Distance(const Vector3<T>& p_vectorA, const Vector3<U>& p_vectorB);
        template<typename U>
        constexpr static bool Equals(const Vector3<T>& p_vectorA, const Vector3<U>& p_vectorB);
        
        //template<std::enable_if_t<std::is_floating_point<T>::value, float> = 0>
        /*constexpr Vector3<T> RotateVector(const float p_angle, const Vector3<T>& p_axis)
        {
            const Quaternion p{ 0, *this };

            //normalize the axis
            const Vector3F uAxis = p_axis.Normalized();

            //create the real quaternion
            Quaternion q{ p_angle, uAxis };

            //convert quaternion to unit norm quaternion
            q.ConvertToUnitNormQuaternion();

            const Quaternion qInverse = Inverse(q);

            const Quaternion rotatedVector = q * p * qInverse;

            return rotatedVector.axis;
        }*/

        template<typename U>
        constexpr inline Vector3<T>& operator +=(const Vector3<U> p_vector);
        template<typename U>
        constexpr inline Vector3<T>& operator -=(const Vector3<U> p_vector);
        template<typename U>
        constexpr inline Vector3<T>& operator *=(const Vector3<U> p_vector);
		constexpr inline Vector3<T>& operator *=(const T p_scalar);
        template<typename U>
        constexpr inline Vector3<T>& operator /=(const Vector3<U> p_vector);

        template<typename U>
        constexpr inline Vector3<T> operator+(const Vector3<U>& p_other) const;
        template<typename U>
        constexpr inline Vector3<T> operator-(const Vector3<U>& p_vector) const;
        template<typename U>
        constexpr inline Vector3<T>& operator=(const Vector3<U>& p_other);
        template<typename U>
        constexpr inline Vector3<T> operator/(const Vector3<U>& p_vector) const;
        template<typename U>
        constexpr inline Vector3<T> operator *(const Vector3<U>& p_vector) const;
        constexpr inline Vector3<T> operator *(const T& p_scalar) const;

        template<typename U>
        constexpr inline bool operator==(const Vector3<U>& p_vector) const;
        template<typename U>
        constexpr inline bool operator!=(const Vector3<U>& p_vector) const;

	};

    template <typename T>
    constexpr std::ostream& operator<<(std::ostream & p_stream, const Vector3<T> & p_vector);

    using Vector3F = GPM::Vector3<float>;
    using Vector3L = GPM::Vector3<long>;
    using Vector3U = GPM::Vector3<unsigned int>;
    using Vector3I = GPM::Vector3<int>;
    using Vector3D = GPM::Vector3<double>;
}

#include <GPM/Vector/Vector3.inl>
