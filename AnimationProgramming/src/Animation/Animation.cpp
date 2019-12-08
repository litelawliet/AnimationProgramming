#include <Animation/Animation.h>
#include <iostream>
#include <utility>
#include <GPM/GPM.h>
#include <Input/InputManager.h>

CSimulation::CSimulation(std::string p_defaultAnimationName)
	: m_speedAnimation{ 10.0f }, m_animationName{ std::move(p_defaultAnimationName) }
{
	m_animationTransforms[RUN_ANIM] = AnimationInfo{};
	m_animationTransforms[WALK_ANIM] = AnimationInfo{};
}

void CSimulation::PopulateBonesArray()
{
	m_animationTransforms[RUN_ANIM].SetKeyCount(GetAnimKeyCount(RUN_ANIM));
	m_animationTransforms[WALK_ANIM].SetKeyCount(GetAnimKeyCount(WALK_ANIM));

	const size_t maxBones = GetSkeletonBoneCount();
	Vector3F temporaryPosition{};
	Vector4F temporaryQuaternion{};
	int boneIndex = 0;

	for (size_t i = 0; i < maxBones; ++i)
	{
		const char* boneName = GetSkeletonBoneName(static_cast<int>(i));
		if (std::strstr(boneName, "ik") != nullptr)
			continue;

		boneIndex++;

		m_bones.emplace_back();

		m_bones[i].name = boneName;
		m_bones[i].parentIndex = GetSkeletonBoneParentIndex(static_cast<int>(i));

		GetSkeletonBoneLocalBindTransform(
			static_cast<int>(i),
			temporaryPosition.x,
			temporaryPosition.y,
			temporaryPosition.z,
			temporaryQuaternion.w,
			temporaryQuaternion.x,
			temporaryQuaternion.y,
			temporaryQuaternion.z);

		m_bones[i].transform.SetTTransform(
			temporaryPosition,
			Quaternion{ temporaryQuaternion.x , temporaryQuaternion.y, temporaryQuaternion.z, temporaryQuaternion.w });
	}

	m_animationTransforms[RUN_ANIM].SetBoneCount(boneIndex);
	m_animationTransforms[WALK_ANIM].SetBoneCount(boneIndex);
	m_keyAnimKeyCount = m_animationTransforms[m_animationName].KeyCount();

	m_skinningAnimationMatrices.resize(m_animationTransforms[m_animationName].BoneCount() * 16);
}

void CSimulation::LinkBones()
{
	for (auto& bone : m_bones)
	{
		bone.parent = (bone.parentIndex == -1) ? nullptr : &m_bones[bone.parentIndex];

		if (bone.parent != nullptr)
		{
			bone.transform.SetParent(bone.parent->transform);
			bone.parent->children.push_back(&bone);
		}
	}

	for (auto& bone : m_bones)
	{
		bone.transform.InitSkeleton();
	}
}

void CSimulation::ShowBonesData()
{
	for (auto& bone : m_bones)
	{
		std::cout << "--------------------\n" << bone.name
			<< "\tParent: " << std::hex << bone.parent
			<< "\tIndex of parent: " << bone.parentIndex << "\n-------------------";
	}
}

void CSimulation::PopulateAnimation(const std::string_view& p_animationName)
{
	const size_t boneCount = m_animationTransforms[p_animationName.data()].BoneCount();
	Vector3F temporaryPosition{};
	Vector4F temporaryQuaternion;

	for (size_t i = 0; i < boneCount; ++i)
	{
		for (size_t j = 0; j < m_animationTransforms[p_animationName.data()].KeyCount(); ++j)
		{
			GetAnimLocalBoneTransform(p_animationName.data(),
				static_cast<int>(i),
				static_cast<int>(j),
				temporaryPosition.x,
				temporaryPosition.y,
				temporaryPosition.z,
				temporaryQuaternion.w,
				temporaryQuaternion.x,
				temporaryQuaternion.y,
				temporaryQuaternion.z);

			m_animationTransforms[p_animationName.data()].AddAnimFrame(
				i,
				temporaryPosition,
				Quaternion{ temporaryQuaternion.x, temporaryQuaternion.y, temporaryQuaternion.z, temporaryQuaternion.w });
		}
	}
}

std::optional<Bone*> CSimulation::GetBoneFromName(const std::string_view& p_boneName)
{
	for (auto& bone : m_bones)
	{
		if (p_boneName == bone.name)
			return &bone;
	}

	return {};
}

void CSimulation::Init()
{
	PopulateBonesArray();

	LinkBones();

	PopulateAnimation(WALK_ANIM);
	PopulateAnimation(RUN_ANIM);

	//ShowBonesData();
}

void CSimulation::DrawSkeleton()
{
	for (unsigned int i = 0; i < m_bones.size(); ++i)
	{
		Bone* parent = m_bones[i].parent;
		if (parent == nullptr)
			continue;

		std::pair<Vector3F, Quaternion> beginLocalFrame;
		std::pair<Vector3F, Quaternion> endLocalFrame;

		const int beginFrame = static_cast<int>(static_cast<size_t>(m_animationElapsedTime) % m_keyAnimKeyCount);
		const int endFrame = static_cast<int>(static_cast<size_t>(m_animationElapsedTime + 1.0f) % m_keyAnimKeyCount);

		beginLocalFrame = m_animationTransforms[m_animationName].LocalAnimFrame(i, beginFrame);
		endLocalFrame = m_animationTransforms[m_animationName].LocalAnimFrame(i, endFrame);

		Vector3F interpolatedPosition = Vector3F::Lerp(
			beginLocalFrame.first,
			endLocalFrame.first,
			Tools::Utils::GetDecimalPart(m_animationElapsedTime));

		Quaternion interpolatedRotation = Quaternion::SlerpShortestPath(
			beginLocalFrame.second,
			endLocalFrame.second,
			Tools::Utils::GetDecimalPart(m_animationElapsedTime));

		m_bones[i].transform.SetAnimTransform(interpolatedPosition, interpolatedRotation);

		const Vector3F parentAnimPosition = parent->transform.WorldAnimPosition();
		const Vector3F boneAnimPosition = m_bones[i].transform.WorldAnimPosition();

		DrawLine(
			parentAnimPosition.x, parentAnimPosition.y - 15.0f, parentAnimPosition.z,
			boneAnimPosition.x, boneAnimPosition.y - 15.0f, boneAnimPosition.z,
			0.6f, 0.4f, 0.0f);
	}
}

void CSimulation::ChangeAnimation(const float p_deltaTime)
{
	if (Input::InputManager::IsKeyPressed('R'))
	{
		m_animationName = RUN_ANIM;
		m_animationElapsedTime = 0.0f;
		m_keyAnimKeyCount = m_animationTransforms[m_animationName].KeyCount();
	}
	else if (Input::InputManager::IsKeyPressed('Z'))
	{
		m_animationName = WALK_ANIM;
		m_animationElapsedTime = 0.0f;
		m_keyAnimKeyCount = m_animationTransforms[m_animationName].KeyCount();
	}
	else if (Input::InputManager::IsKeyPressed('1'))
	{
		SetAnimationFactorSpeed(AnimationFactorSpeed() + AnimationFactorSpeed() * p_deltaTime);
		if (AnimationFactorSpeed() > 25.0f)
			SetAnimationFactorSpeed(25.0f);
	}
	else if (Input::InputManager::IsKeyPressed('2'))
	{
		SetAnimationFactorSpeed(AnimationFactorSpeed() - AnimationFactorSpeed() * p_deltaTime);
		if (AnimationFactorSpeed() < 0.0f)
			SetAnimationFactorSpeed(0.0f);
	}
	else if (Input::InputManager::IsKeyPressed('3'))
	{
		SetAnimationFactorSpeed(1.0f);
	}
	else if (Input::InputManager::IsKeyPressed('B'))
	{
		// Toggle bones
	}
}

void CSimulation::FormatHardwareSkinning()
{
	for (size_t i = 0; i < m_bones.size(); i++)
	{
		const Matrix4F animatedMatrix = m_bones[i].transform.WorldAnimMatrix() * m_bones[i].transform.InverseWorldMatrix();

		for (int j = 0; j < 16; j++)
		{
			m_skinningAnimationMatrices[i * 16 + j] = animatedMatrix[j];
		}
	}

	SetSkinningPose(m_skinningAnimationMatrices.data(), m_bones.size());
}

void CSimulation::SetAnimationSpeed(const float p_speed)
{
	m_speedAnimation = p_speed;
}

void CSimulation::SetAnimationFactorSpeed(const float p_speed)
{
	m_animationFactorSpeed = p_speed;
}

float CSimulation::AnimationSpeed() const
{
	return m_speedAnimation;
}

float CSimulation::AnimationFactorSpeed() const
{
	return m_animationFactorSpeed;
}

void CSimulation::DrawAxis()
{
	// X axis
	DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

	// Y axis
	DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

	// Z axis
	DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
}

void CSimulation::Update(const float p_deltaTime)
{
	m_animationElapsedTime += p_deltaTime * m_speedAnimation * m_animationFactorSpeed;

	// Input
	ChangeAnimation(p_deltaTime);

	// Draw
	DrawAxis();

	DrawSkeleton();

	FormatHardwareSkinning();
}
