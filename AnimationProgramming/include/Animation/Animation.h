#pragma once

#include <Engine/Simulation.h>
#include <string>
#include <vector>
#include <Resources/Bone.h>
#include <unordered_map>
#include <Animation/AnimationInfo.h>
#include <optional>

#define WALK_ANIM "ThirdPersonWalk.anim"
#define RUN_ANIM "ThirdPersonRun.anim"

class CSimulation final : public ISimulation
{
public:
	/**
	 * @brief Default constructor
	 * @param p_defaultAnimationName The name of the default animation. Walk animation by default.
	 */
	explicit CSimulation(std::string p_defaultAnimationName = WALK_ANIM);

	/**
	 * @brief Initialize every members, populate array of bones, linkage between them etc.
	 */
	virtual void Init() override;

	/**
	 * @brief Update loop for next frame.
	 * @param p_deltaTime Time between 2 frames
	 */
	virtual void Update(const float p_deltaTime) override;

	/**
	 * @brief Creates all bones of the animation.
	 */
	void PopulateBonesArray();

	/**
	 * @brief Store all needed data of the animation.
	 * @param p_animationName The animation name
	 */
	void PopulateAnimation(const std::string_view& p_animationName);

	/**
	 * @brief Link all bones with their relatives bones, parent and children.
	 */
	void LinkBones();

	/**
	 * @brief Static method to draw the axis of the world space from origin.
	 */
	static void DrawAxis();

	/**
	 * @brief Return a bone from his name.
	 * @param p_boneName Name of the bone
	 * @return An optional pointer to the bone, it may hold a pointer of the bone or it may be empty.
	 * @note I used std::optional as return type just for fun using C++17 features. In real cases like this one we should just use a simple pointer or smart pointer like std::shared_ptr.
	 * Return type as std::optional are really useful in situations like finding a string, get integers values that may have not be set yet in the program and so on.
	 */
	std::optional<Bone*> GetBoneFromName(const std::string_view& p_boneName);

	/**
	 * @brief Draw the mesh skeleton
	 */
	void DrawSkeleton();

	/**
	 * @brief Update the animation settings like speed.
	 * @param p_deltaTime The time between 2 frames
	 */
	void ChangeAnimation(const float p_deltaTime);

	/**
	 * @brief Prepare the data to be send for the vertex shader.
	 */
	void FormatHardwareSkinning();

	/**
	 * @brief Return the current animation speed.
	 * @return The animation speed
	 */
	float AnimationSpeed() const;
	
	/**
	 * @brief Return the current animation factor speed. It's the coefficient of the speed.
	 * @return The animation factor speed
	 */
	float AnimationFactorSpeed() const;

	/**
	 * @brief Set the animation speed. Default value is 10.0f.
	 * @param p_speed The new animation speed
	 */
	void SetAnimationSpeed(const float p_speed = 10.0f);

	/**
	 * @brief Set the animation factor speed. This is the coefficient of the speed. Default value is 1.0f;
	 * @param p_speed The new animation factor speed
	 */
	void SetAnimationFactorSpeed(const float p_speed = 1.0f);

	/**
	 * @brief Format all the data of the bones to see the relationship between their parents.
	 */
	void ShowBonesData();

private:
	std::vector<float> m_skinningAnimationMatrices;
	std::vector<Bone> m_bones{};
	size_t m_keyAnimKeyCount{};
	float m_animationElapsedTime{};
	float m_speedAnimation{};
	float m_animationFactorSpeed{ 1.0f };
	std::string m_animationName;
	std::unordered_map<std::string, AnimationInfo> m_animationTransforms;
};
