#pragma once
#include <unordered_map>
#include <vector>
#include <Resources/Transform.h>

class AnimationInfo final
{
public:
	/**
	 * @brief Default constructor
	 */
	AnimationInfo();

	/**
	 * @brief Copy constructor
	 * @param p_other The other animation to copy
	 */
	AnimationInfo(const AnimationInfo& p_other);

	/**
	 * @brief Move constructor
	 * @param p_other The other animation to move
	 */
	AnimationInfo(AnimationInfo&& p_other) noexcept;

	/**
	 * @brief Default destructor
	 */
	~AnimationInfo() = default;

	/**
	 * @brief Add the animation's local data of a bone, creates automatically the frames by pushing back data in it.
	 * @param p_boneIndex The bone
	 * @param p_localAnimPosition The vector to add
	 * @param p_localAnimRotation The quaternion to add
	 */
	void AddAnimFrame(const size_t p_boneIndex,
		const Vector3F& p_localAnimPosition,
		const Quaternion& p_localAnimRotation);

	/**
	 * @brief Update the animation's local data of a bone at a certain frame.
	 * @param p_boneIndex The bone
	 * @param p_frame The frame
	 * @param p_localAnimPosition The vector to add
	 * @param p_localAnimRotation The quaternion to add
	 */
	void UpdateAnimFrame(
		const size_t p_boneIndex,
		const size_t p_frame,
		const Vector3F& p_localAnimPosition,
		const Quaternion& p_localAnimRotation);

	/**
	 * @brief Set the key count of the animation.
	 * @param p_keyCount The new key count
	 */
	void SetKeyCount(const size_t p_keyCount);

	/**
	 * @brief Set the bone count of the animation.
	 * @param p_boneCount The new bone count
	 */
	void SetBoneCount(const size_t p_boneCount);

	/**
	 * @brief Return the pair of the animation's local frame.
	 * @param p_boneIndex The bone
	 * @param p_frame The frame
	 * @return A pair of position (first) and quaternion (second) of a bone at a certain frame
	 */
	const std::pair<Vector3F, Quaternion>& LocalAnimFrame(const size_t p_boneIndex, const size_t p_frame) const;

	/**
	 * @brief Return the key count of the animation.
	 * @return The key count
	 */
	size_t KeyCount() const;

	/**
	 * @brief Return the bone count of the animation.
	 * @return The bone count
	 */
	size_t BoneCount() const;

	/**
	 * @brief Move assignment operator
	 * @param p_other The other animation to move
	 * @return The modified animation
	 */
	AnimationInfo& operator=(const AnimationInfo& p_other) = default;

	/**
	 * @brief Move assignment operator
	 * @param p_other The animation to move
	 * @return The modified animation
	 */
	AnimationInfo& operator=(AnimationInfo&& p_other) noexcept;

private:
	size_t m_keyCount;
	size_t m_boneCount;
	std::unordered_map<size_t, std::vector<std::pair<Vector3F, Quaternion>>> m_keyFrame;
};
