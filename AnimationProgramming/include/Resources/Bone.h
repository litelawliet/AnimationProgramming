#pragma once

#include <vector>
#include <string>
#include <Resources/Transform.h>

struct Bone final
{
	Transform transform;
	Bone* parent;
	int parentIndex;
	std::string name;
	std::vector<Bone*> children;

	/**
	 * @brief Default constructor
	 */
	Bone();

	/**
	 * @brief Copy constructor
	 * @param p_other The other bone to copy
	 */
	Bone(const Bone& p_other) = default;

	/**
	 * @brief Move constructor
	 * @param p_other The other bone to move
	 */
	Bone(Bone&& p_other) noexcept;

	/**
	 * @brief Default destructor
	 */
	~Bone() = default;

	/**
	 * @brief Copy assignment operator.
	 * @param p_other The other bone to copy
	 * @return The current bone modified
	 */
	Bone& operator=(const Bone& p_other) = default;

	/**
	 * @brief Move assignment operator.
	 * @param p_other The other bone to move
	 * @return The current bone modified
	 */
	Bone& operator=(Bone&& p_other) noexcept;

	/**
	 * @brief Check equality between the current bone and another one.
	 * @param p_other The other bone to compare
	 * @return True if equals, false otherwise
	 */
	bool operator==(const Bone& p_other) const;

	/**
	 * @brief Check non-equality between the current bone and another one.
	 * @param p_other The other bone to compare
	 * @return True if equals, false otherwise
	 */
	bool operator!=(const Bone& p_other) const;
};
