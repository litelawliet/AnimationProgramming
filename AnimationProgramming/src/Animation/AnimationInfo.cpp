#include <Animation/AnimationInfo.h>
#include <stdexcept>

AnimationInfo::AnimationInfo()
	: m_keyCount{ 0 }, m_boneCount{ 0 }
{
}

AnimationInfo::AnimationInfo(const AnimationInfo& p_other)
	: m_keyCount{ p_other.KeyCount() }, m_boneCount{ p_other.m_boneCount }
{
	m_keyFrame = p_other.m_keyFrame;
}

AnimationInfo::AnimationInfo(AnimationInfo&& p_other) noexcept
	: m_keyCount{ p_other.KeyCount() }, m_boneCount{ p_other.m_boneCount }
{
	m_keyFrame = p_other.m_keyFrame;
}

void AnimationInfo::AddAnimFrame(
	const size_t p_boneIndex,
	const Vector3F& p_localAnimPosition,
	const Quaternion& p_localAnimRotation)
{
	m_keyFrame[p_boneIndex].emplace_back(std::make_pair(p_localAnimPosition, p_localAnimRotation));
}

void AnimationInfo::UpdateAnimFrame(
	const size_t p_boneIndex,
	const size_t p_frame,
	const Vector3F& p_localAnimPosition,
	const Quaternion& p_localAnimRotation)
{
	m_keyFrame[p_boneIndex][p_frame] = std::make_pair(p_localAnimPosition, p_localAnimRotation);
}

void AnimationInfo::SetKeyCount(const size_t p_keyCount)
{
	m_keyCount = p_keyCount;
}

void AnimationInfo::SetBoneCount(const size_t p_boneCount)
{
	m_boneCount = p_boneCount;
}

size_t AnimationInfo::BoneCount() const
{
	return m_boneCount;
}

AnimationInfo& AnimationInfo::operator=(AnimationInfo&& p_other) noexcept
{
	m_keyCount = p_other.m_keyCount;
	m_boneCount = p_other.m_boneCount;
	m_keyFrame = p_other.m_keyFrame;

	return *this;
}

const std::pair<Vector3F, Quaternion>& AnimationInfo::LocalAnimFrame(const size_t p_boneIndex, const size_t p_frame) const
{
	if (m_keyFrame.count(p_boneIndex) > 0)
	{
		if (p_frame < m_keyFrame.at(p_boneIndex).size())
			return m_keyFrame.at(p_boneIndex)[p_frame];

		throw std::out_of_range("Animation Matrix unattainable, p_frame is out of range");
	}

	throw std::out_of_range("Animation Matrix unattainable, p_boneIndex is out of range");
}

size_t AnimationInfo::KeyCount() const
{
	return m_keyCount;
}
