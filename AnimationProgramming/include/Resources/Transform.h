#pragma once
#include <ostream>
#include <GPM/GPM.h>

struct Transform final
{
private:
	Matrix4F m_localMatrix;
	Matrix4F m_worldMatrix;

	Matrix4F m_localAnimMatrix;
	Matrix4F m_worldAnimMatrix;

	Matrix4F m_inverseWorldMatrix;

	Transform* m_parent;
	
public:
	/**
	 * @brief Default constructor
	 */
	Transform();
	
	/**
	 * @brief Copy constructor
	 * @param p_other The other transform to copy
	 */
	Transform(const Transform& p_other);

	/**
	 * @brief Move constructor
	 * @param p_other The other transform to move
	 */
	Transform(Transform&& p_other) noexcept;

	/**
	 * @brief Default constructor
	 */
	~Transform() = default;

	/**
	 * @brief Set the T pose local matrix using position and quaternion. It will also build up the world matrix.
	 * @param p_localPosition The local position of the bone at T pose
	 * @param p_localRotation The local rotation of the bone at T pose
	 */
	void SetTTransform(
		const Vector3F& p_localPosition,
		const Quaternion& p_localRotation);

	/**
	 * @brief Set the local animation matrix using position and quaternion. It will also build up the world animated matrix.
	 * @param p_localPosition The local position of the bone at a certain frame
	 * @param p_localRotation The local rotation of the bone at a certain frame
	 * @note This method needs to be called every frame by every bone to update the final animation that has to be rendered.
	 */
	void SetAnimTransform(
		const Vector3F& p_localPosition,
		const Quaternion& p_localRotation);

	/**
	 * @brief Check if the transform has a parent.
	 * @return True if the transform has a parent, false otherwise
	 */
	bool HasParent() const;

	/**
	 * @brief Return the local T pose matrix.
	 * @return The local T pose matrix
	 */
	const Matrix4F& LocalMatrix() const;
	
	/**
	 * @brief Return the world T pose matrix.
	 * @return The world T pose matrix
	 */
	const Matrix4F& WorldMatrix() const;

	/**
	 * @brief Return the inverted world T pose matrix.
	 * @return The inverted world T pose matrix
	 */
	const Matrix4F& InverseWorldMatrix() const;

	/**
	 * @brief Set the transform's parent.
	 * @param p_parent The transform parent
	 */
	void SetParent(Transform& p_parent);

	/**
	 * @brief Call and calculate each world matrices of the current animation with their parents.
	 */
	void UpdateAnimationMatrices();

	/**
	 * @brief Call and calculate each world matrices of the animation skeleton with their parents.
	 */
	void InitSkeleton();

	/**
	 * @brief Return the local T pose position.
	 * @return The position of the local T pose matrix
	 */
	Vector3F LocalPosition() const;

	/**
	 * @brief Return the world T pose position.
	 * @return The position of the world T pose matrix
	 */
	Vector3F WorldPosition() const;

	/**
	 * @brief Return the local T pose rotation.
	 * @return The rotation of the local T pose matrix
	 */
	Quaternion LocalRotation() const;

	/**
	 * @brief Return the world T pose rotation.
	 * @return The rotation of the world T pose matrix
	 */
	Quaternion WorldRotation() const;

	/**
	 * @brief Return the local animated pose position.
	 * @return The position of the local animated pose matrix
	 */
	Vector3F LocalAnimPosition() const;

	/**
	 * @brief Return the world animated pose position.
	 * @return The position of the world animated pose matrix
	 */
	Vector3F WorldAnimPosition() const;

	/**
	 * @brief Return the local animated pose rotation.
	 * @return The position of the local animated pose matrix
	 */
	Quaternion LocalAnimRotation() const;

	/**
	 * @brief Return the world animated pose rotation.
	 * @return The position of the world animated pose matrix
	 */
	Quaternion WorldAnimRotation() const;


	/**
	 * @brief Return the local animated pose matrix.
	 * @return The local animated matrix
	 */
	const Matrix4F& LocalAnimMatrix() const;

	/**
	 * @brief Return the world animated pose matrix.
	 * @return The world animated matrix
	 */
	const Matrix4F& WorldAnimMatrix() const;

	/**
	 * @brief Copy assignment operator
	 * @param p_other The transform to copy
	 * @return The modified transform
	 */
	Transform& operator=(const Transform& p_other);

	/**
	 * @brief Move assignment operator
	 * @param p_other The transform to move
	 * @return The modified transform
	 */
	Transform& operator=(Transform&& p_other) noexcept;

	/**
	 * @brief Check equality between the current transform and another one.
	 * @param p_other The other transform to compare
	 * @return True if equals, false otherwise
	 */
	bool operator==(const Transform& p_other) const;

	/**
	 * @brief Check non-equality between the current transform and another one.
	 * @param p_other The other transform to compare
	 * @return True if equals, false otherwise
	 */
	bool operator!=(const Transform& p_other) const;
};

std::ostream& operator<<(std::ostream& p_os, const Transform& p_transform);
