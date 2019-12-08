#include <Resources/Bone.h>

Bone::Bone()
	: parent{ nullptr }, parentIndex{ -1 }, name{ "" }
{
}

Bone::Bone(Bone&& p_other) noexcept
	: transform{ p_other.transform },
	parent{ p_other.parent }, parentIndex{ p_other.parentIndex },
	name{ p_other.name }, children{ p_other.children }
{
}

Bone& Bone::operator=(Bone&& p_other) noexcept
{
	children = p_other.children;
	transform = p_other.transform;
	parent = p_other.parent;
	name = p_other.name;
	parentIndex = p_other.parentIndex;

	return *this;
}

bool Bone::operator==(const Bone& p_other) const
{
	return children == p_other.children && transform == p_other.transform && parent == p_other.parent && name == p_other.name && parentIndex == p_other.parentIndex;
}

bool Bone::operator!=(const Bone& p_other) const
{
	return children != p_other.children || transform != p_other.transform || parent != p_other.parent || name != p_other.name || parentIndex != p_other.parentIndex;
}
