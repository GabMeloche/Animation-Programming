#pragma once
#include <string>

namespace GPM
{
	struct Quaternion final
	{
		Vector3<double> axis;
		//m_w is the real value of quaternion, this will be used to check if the quaternion is pure/identity or not.
		double w;

		static Quaternion identity;

#pragma region Constructors & Assignment
		inline Quaternion();
		/**
		 * @brief Constructor using all values
		 * @param p_x Vector part of Quaternion
		 * @param p_y Vector part of Quaternion
		 * @param p_z Vector part of Quaternion
		 * @param p_w Real value of Quaternion
		 *
		 * @note In pure/applied Maths, we write W (or real), (Xi + Yj + Zk) (or Vector)
		 */
		inline Quaternion(const double p_x, const double p_y, const double p_z, const double p_w);

		/**
		 * @brief Constructor using a scalar and a vector
		 * @param p_scalar The scalar
		 * @param p_vector The vector
		 */
		inline Quaternion(const double p_scalar, const Vector3<double>& p_vector);

		/**
		 * @brief Copy Constructor
		 * @param p_other
		 */
		inline Quaternion(const Quaternion& p_other);

		/**
		 * @brief Move Constructor
		 * @param p_other
		 */
		inline Quaternion(Quaternion&& p_other) noexcept;
		
		/**
		 * @brief Construct from rotation matrix
		 * @param p_matrix Rotation matrix
		 */
		inline Quaternion(const Matrix3<double>& p_matrix);
		
		/**
		 * @brief Construct from rotation matrix
		 * @param p_matrix Rotation matrix
		 */
		inline Quaternion(const Matrix4<double>& p_matrix);

		/**
		 * @brief Constuct a quaternion from axis and angle in radian
		 * @param p_axis
		 * @param p_angleInRadians
		 */
		inline Quaternion(const Vector3<double>& p_axis, const double p_angleInRadians);

		~Quaternion() = default;
		
		/**
		 * @brief Construct from euler angles
		 * @param p_euler A vector representing the euler angle in degree
		 */
		inline void MakeFromEuler(const Vector3<double>& p_euler);

		/**
		 * @brief Construct from euler angles
		 * @param p_x The x-angle in degree
		 * @param p_y The x-angle in degree
		 * @param p_z The x-angle in degree
		 */
		inline void MakeFromEuler(const double p_x, const double p_y, const double p_z);

		/**
		 * @brief Copy assignment
		 * @param p_other The quaternion
		 * @return The current quaternion modified
		 */
		inline Quaternion& operator=(const Quaternion& p_other) = default;

		/**
		 * @brief Move assigment
		 * @param p_other The quaternion
		 * @return The current quaternion modified 
		 */
		inline Quaternion& operator=(Quaternion&& p_other) noexcept;
#pragma endregion

#pragma region Tests & Comparisons

		/**
		 * @brief Check If the quaternion is Identity
		 * @note If the quaternion has no rotation(meaning x,y,z axis values = 0), it's Identity
		 */
		bool IsIdentity() const;

		/**
		 * @brief Check if the quaternion is pure
		 * @note If the quaternion has no real value(meaning real part = 0), it's pure
		 */
		bool IsPure() const;

		/**
		 * @brief Check if the quaternion is normalized
		 * @note A quaternion is normalized if his magnitude is equal to 1 
		 */
		bool IsNormalized() const;

		/**
		 * @brief Check is all components between the current quaternion and the other one are equals
		 * @param p_otherQuaternion The other quaternion to check with
		 */
		bool operator==(const Quaternion& p_otherQuaternion) const;

		/**
		 * @brief Check is all components between the current quaternion and the other one are different
		 * @param p_otherQuaternion The other quaternion to check with
		 */
		bool operator!=(const Quaternion& p_otherQuaternion) const;

#pragma endregion
#pragma region Arithmetic Operations

#pragma region Add
		Quaternion operator+(const Quaternion& p_otherQuaternion) const;
		Quaternion& operator+=(const Quaternion& p_otherQuaternion);

#pragma endregion
#pragma region Substract
		Quaternion operator-(const Quaternion& p_otherQuaternion) const;
		Quaternion& operator-=(const Quaternion& p_otherQuaternion);

#pragma endregion
#pragma region Multiply
		double DotProduct(const Quaternion& p_otherQuaternion) const;
		static double DotProduct(const Quaternion& p_left, const Quaternion& p_right);

		inline Quaternion operator*(const double p_scale) const;
		inline Quaternion& operator*=(const double p_scale);

		inline Quaternion operator*(const Quaternion& p_otherQuaternion) const;
		inline Quaternion& operator*=(const Quaternion& p_otherQuaternion);

		inline Quaternion operator*(const Vector3<double>& p_toMultiply) const;
		inline Quaternion& operator*=(const Vector3<double>& p_toMultiply);

#pragma endregion
#pragma endregion

#pragma region Quaternion Operations
		Quaternion& Normalize();
		static Quaternion Normalize(const Quaternion& p_quaternion);

		inline Quaternion Multiply(const Quaternion& p_quaternion) const;
		
		inline double Norm() const;
		constexpr inline double NormSquare() const;
		double GetAngle() const;

		Quaternion& Inverse();
		static Quaternion Inverse(const Quaternion& p_quaternion);

		Quaternion& Conjugate();
		static Quaternion Conjugate(const Quaternion& p_quaternion);

		Quaternion& ConvertToUnitNormQuaternion();


		Vector3<double> GetRotationAxis() const;

		double AngularDistance(const Quaternion& p_other) const;

		double GetXAxisValue() const;
		double GetYAxisValue() const;
		double GetZAxisValue() const;
		double GetRealValue() const;

		void SetXAxisValue(const double p_xValue);
		void SetYAxisValue(const double p_yValue);
		void SetZAxisValue(const double p_zValue);
		void SetRealValue(const double p_realValue);

		/**
		 * @brief Creates a rotation with the specified forward and upwards directions.
		 * @param p_forward Forward direction
		 * @param p_upwards Upwards direction
		 */
		Quaternion LookRotation(const Vector3<double>& p_forward, const Vector3<double>& p_upwards = Vector3<double>::up) const;

		/**
		 * @brief Create a quaternion out of an axis and angle
		 * @param p_axis The axis
		 * @param p_angle The angle
		 */
		static Quaternion CreateFromAxisAngle(const Vector3<double>& p_axis, const double p_angle);
		
		/**
		 * @brief Interpolation between two quaternions
		 * @param p_start Start quaternion
		 * @param p_end End quaternion
		 * @param p_alpha Coefficient
		 */
		static Quaternion Lerp(const Quaternion& p_start, const Quaternion& p_end, const double p_alpha);

		/**
		 * @brief Smoothly interpolate between two quaternions
		 * @param p_start Start quaternion
		 * @param p_end End quaternion
		 * @param p_alpha Coefficient
		 */
		static Quaternion Slerp(const Quaternion& p_start, const Quaternion& p_end, const double p_alpha);

		/**
		 * @brief Normalized interpolate between two quaternions
		 * @param p_start Start quaternion
		 * @param p_end End quaternion
		 * @param p_alpha Coefficient
		 */
		static Quaternion Nlerp(const Quaternion& p_start, const Quaternion& p_end, const double p_alpha);
		
		/**
		 * @param p_position
		 * @param p_pivot
		 */
		Vector3<double> RotateRelativeToPivot(const Vector3<double>& p_position, const Vector3<double>& p_pivot) const;
		
		/**
		 * @param p_position
		 * @param p_pivot
		 * @param p_eulerAngles
		 */
		static Vector3<double> RotateRelativeToPivot(const Vector3<double>& p_position, const Vector3<double>& p_pivot,
			const Vector3<double>& p_eulerAngles);
		
		/**
		* @param p_position
		* @param p_pivot
		* @param p_quaternion
		*/
		static Vector3<double> RotateRelativeToPivot(const Vector3<double>& p_position, const Vector3<double>& p_pivot,
			Quaternion& p_quaternion);

		/**
		 * @param p_toRotate
		 */
		Vector3<double> RotateVector(const Vector3<double>& p_toRotate) const;

		/**
		* @brief Rotate the vector of a certain angle around an arbitrary axis
		* @param p_angle The angle
		* @param p_axis The axis
		* @param p_vectorToRotate Vector to rotate
		*/
		static Vector3<double> RotateVectorAboutAngleAndAxis(const double p_angle, const Vector3<double>& p_axis, const Vector3<double>& p_vectorToRotate);

#pragma endregion
#pragma region Conversions
		/**
		 * @brief Transform the current quaternion to a unit quaternion
		 */
		Quaternion ToUnitNormQuaternion();

		/**
		 * @brief Transform the current quaternion to euler angles in degrees
		 */
		Vector3<double> ToEuler() const;

		/**
		 * @brief Create a quaternion from euler in degrees
		 * @param p_euler The euler angle in degree
		 */
		static Quaternion ToQuaternion(const Vector3<double>& p_euler);

		/**
		 * @brief Create a quaternion from yaw, pitch and roll angle in degrees
		 * @param p_yaw The yaw angle
		 * @param p_pitch The pitch angle
		 * @param p_roll The roll angle
		 */
		static Quaternion ToQuaternion(const double p_yaw, const double p_pitch, const double p_roll);

		/**
		 * @brief Transform the current quaternion to string
		 */
		std::string ToString() const;

		/**
		 * @brief Transform a quaternion to string
		 * @param p_quaternion The quaternion to turn into string
		 */
		static std::string ToString(const Quaternion& p_quaternion);

		/**
		 * @brief Return a Matrix3 of double out of the quaternion
		 */
		Matrix3<double> ToMatrix3() const;

		/**
		 * @brief Return a Matrix4 of double out of the quaternion
		 */
		Matrix4<double> ToMatrix4() const;
#pragma endregion
	};

	std::ostream& operator<<(std::ostream& p_stream, const Quaternion& p_quaternion);
}

#include <GPM/Quaternion/Quaternion.inl>