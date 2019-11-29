#pragma once

#include <string>

namespace GPM
{
    /**
     * A standard 3 by 3 Matrix. Default value is an identity matrix
     */
    template <typename T>
    struct Matrix3
    {
        static_assert(std::is_arithmetic<T>::value, "Matrix3 should only be used with arithmetic types");

        T m_data[9] = { 1,0,0,
                        0,1,0,
                        0,0,1 };
#pragma region Constructors & Assignment

        constexpr Matrix3();
        ~Matrix3() = default;


        constexpr Matrix3(const T p_i0, const T p_i1, const T p_i2, 
                          const T p_i3, const T p_i4, const T p_i5,
                          const T p_i6, const T p_i7, const T p_i8);

        constexpr Matrix3(const T p_data[9]);
        constexpr Matrix3(const Matrix3& p_other);

        template<typename U>
        constexpr Matrix3(const Matrix3<U>& p_other);

        constexpr Matrix3(Matrix3&& p_other) noexcept;

        /**
        * @brief Assignment operator for Matrix3
        * @param p_other The matrix to construct from
        */
        constexpr Matrix3<T>& operator=(const Matrix3<T>& p_other);

        /**
        * @brief Assignment operator for Matrix3
        * @param p_other The matrix to construct from
        */
        template<typename U>
        constexpr Matrix3<T>& operator=(const Matrix3<U>& p_other);

        /**
         * @brief Assignment operator for Matrix3
         * @param p_other The matrix to construct from
         */
        template<typename U>
        constexpr Matrix3<T>& operator=(Matrix3<U>&& p_other) noexcept;

#pragma endregion

#pragma region Static Properties
        /**
         * @brief This is a const matrix that has 1 in the diagonal and 0 elsewhere
         */
        static Matrix3<T> identity;

        /** 
         *  @brief This is a const matrix that has 0 everywhere
         */
        static Matrix3<T> zero;
#pragma endregion 

#pragma region Properties

        T Determinant();

        static T Determinant(const Matrix3<T>& p_matrix3);

        constexpr Matrix3<T>& Transpose();
        constexpr static Matrix3<T> Transpose(const Matrix3<T>& p_matrix3);

        constexpr Vector3<T> GetColumn(const int p_column);

        template<typename U>
        constexpr void SetColumn(const int p_column, const Vector3<U>& p_vector);


        constexpr Vector3<T> GetRow(const int p_row);
        template<typename U>
        constexpr void SetRow(const int p_row, const Vector3<U>& p_vector);

        constexpr Matrix3<T>& Normalize();
        constexpr static Matrix3<T> Normalize(const Matrix3<T>& p_matrix);


        template<typename U>
        constexpr Matrix3<T>& Translate(const Vector2<U>& p_vector);
        template<typename U>
        constexpr static Matrix3<T> CreateTranslation(const Vector2<U>& p_vector);

        constexpr Matrix3<T>& Rotate(const float p_angle);
        constexpr static Matrix3<T> CreateRotation(const float p_angle);

        template<typename U>
        constexpr Matrix3<T>& Scale(const Vector2<U>& p_vector);
        template<typename U>
        constexpr static Matrix3<T> CreateScaling(const Vector2<U>& p_vector);

        template<typename U>
        constexpr static Matrix3<T> CreateTransformation(const Vector2<U>& p_pos, const float p_angle, const Vector2<U>& p_scale);

        template<typename U>
        constexpr Matrix3<T>& LookAt(const Vector3<U>& dir, const Vector3<U>& up, Matrix3<T>& m);
#pragma endregion

#pragma region Arithmetic Operations

#pragma region Add

        /**
         * @brief Add other matrix to the current matrix
         * @param p_other : The other matrix you want to add to the current one
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& Add(const Matrix3<U>& p_other);

        /**
         * @brief Add left matrix to the right matrix
         * @param p_left : The first matrix you want to add
         * @param p_right : The second matrix to be added to the first one
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr static Matrix3<T> Add(const Matrix3<T>& p_left, const Matrix3<U>& p_right);

        /**
         * @brief Return the summation of other matrix and current matrix
         * @param p_other : The other matrix you want to add
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr Matrix3<T> operator+(const Matrix3<U>& p_other) const;

        /**
         * @brief Add other matrix to the current matrix
         * @param p_other : The other matrix you want to add to the current one
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& operator+=(const Matrix3<U>& p_other);

#pragma endregion
#pragma region Subtract

        /**
         * @brief Subtract other matrix to the current matrix
         * @param p_other : The matrix you want to subtract to the current one
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& Subtract(const Matrix3<U>& p_other);

        /**
         * @brief Subtract left matrix to the right matrix
         * @param p_left : The first matrix you want to subtract to
         * @param p_right : The second matrix to be subtracted from the first one
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr static Matrix3<T> Subtract(const Matrix3<T>& p_left, const Matrix3<U>& p_right);

        /**
         * @brief Return the subtraction of other matrix and current matrix
         * @param p_other : The matrix you want to subtract to the current one
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr Matrix3<T> operator-(const Matrix3<U>& p_other) const;

        /**
         * @brief Subtract other matrix to the current matrix
         * @param p_other : The matrix you want to subtract to the current one
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& operator -=(const Matrix3<U>& p_other);

#pragma endregion
#pragma region Multiply

        /**
         * @brief Multiply scalar to elements
         * @param p_scalar : The value you want to scale the matrix with
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& Multiply(U p_scalar);

        /**
         * @brief Multiply matrix with another matrix.
         * @param p_other : The matrix you want to use as a scalar
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& Multiply(const Matrix3<U>& p_other);

        /**
         * @brief Multiply scalar to matrix left
         * @param p_left : Multiply this matrix by the other parameter
         * @param p_scalar : Multiply this scalar to the other parameter
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr static Matrix3<T> Multiply(const Matrix3<T>& p_left, U p_scalar);

        /**
         * @brief Multiply scalar to matrix left
         * @param p_left : Multiply this matrix by the other parameter
         * @param p_right : Multiply this matrix to the other parameter
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr static Matrix3<T> Multiply(const Matrix3<T>& p_left, const Matrix3<U>& p_right);

        /**
        * @brief Multiply matrix to the current matrix
        * @param p_other : Multiply this matrix to the current one
        * @return The copy of the Matrix operation result
        */
        template<class U>
        constexpr Matrix3<T> operator*(const Matrix3<U>& p_other) const;


        template<class U>
        constexpr Matrix3<T> operator*(const U p_other) const;

        template<class U>
        Matrix3<T>& operator*=(const U p_other);
        
        /**
        * @brief Multiply matrix to the current matrix
        * @param p_other : Multiply this matrix to the current one
        * @return The current Matrix modified
        */
        template<class U>
        Matrix3<T>& operator*=(const Matrix3<U>& p_other);

#pragma endregion

#pragma region Divide

        /**
         * @brief Multiply scalar to elements
         * @param p_scalar : The value you want to scale the matrix with
         * @return The current Matrix modified
         */
        template<typename U>
        Matrix3<T>& Divide(U p_scalar);

        /**
         * @brief Multiply scalar to matrix left
         * @param p_left : Multiply this matrix by the other parameter
         * @param p_scalar : Multiply this scalar to the other parameter
         * @return The copy of the Matrix operation result
         */
        template<typename U>
        constexpr static Matrix3<T> Divide(const Matrix3<T>& p_left, const U p_scalar);


        template<class U>
        constexpr Matrix3<T> operator/(const U p_other) const;

        template<class U>
        Matrix3<T>& operator/=(const U p_other);

#pragma endregion

#pragma endregion

#pragma region Tests & Comparisons
        /**
         * @brief Return true if the two matrices are identical
         * @param p_other The matrix used for the checkup
         * @return True or false
         */
        constexpr bool Equals(const Matrix3<T>& p_other) const;

        /**
         * @brief Return true if the two matrices are identical
         * @param p_left The left matrix
         * @param p_right The right matrix
         * @return True or false
         */
        constexpr static bool AreEqual(const Matrix3<T>& p_left, const Matrix3<T>& p_right);

        /**
         * @brief Return true if the two matrices are identical
         * @param p_left The left matrix
         * @param p_right The right matrix
         * @return True or false
         */
        constexpr static bool IsIdentity(const Matrix3<T>& p_other);

        /**
         * @brief Return true if the two matrices are identical
         * @param p_other The matrix used for the checkup
         * @return True or false
         */
        constexpr bool operator==(const Matrix3<T>& p_other) const;

        /**
         * @brief Return true if the two matrices are different
         * @param p_other The matrix used for the checkup
         * @return True or false
         */
        constexpr bool operator!=(const Matrix3<T>& p_other) const;
#pragma endregion

#pragma region Conversions
        /**
         * @brief function used to debug values from the matrix
         */
        constexpr std::string ToString();

        /**
        * @brief Function used to debug values from the matrix
        * @param p_matrix The matrix to print
        */
        constexpr static std::string ToString(const Matrix3<T>& p_matrix);

#pragma endregion
    };// end struct Matrix3

    
#pragma region Outside Operators

    template <typename T>
    constexpr std::ostream& operator<<(std::ostream& p_stream, const Matrix3<T>& p_matrix3);
#pragma endregion

    using Matrix3F = Matrix3<float>;
    using Matrix3L = Matrix3<long>;
    using Matrix3I = Matrix3<int>;
    using Matrix3D = Matrix3<double>;
}// end Namespace GPM

#include <GPM/Matrix/Matrix3.inl>