#include <Resources/Transform.h>

Transform::Transform()
	: m_localMatrix{ Matrix4F::identity },
	m_worldMatrix{ Matrix4F::identity }, m_parent{ nullptr }
{
}

Transform:: Transform(const Transform& p_other)
	: m_localMatrix{ p_other.m_localMatrix },
	m_worldMatrix{ p_other.m_worldMatrix },
	m_parent{ p_other.m_parent }
{}

Transform::Transform(Transform&& p_other) noexcept
	: m_localMatrix{ p_other.m_localMatrix },
	m_worldMatrix{ p_other.m_worldMatrix },
	m_parent{ p_other.m_parent }
{
}

void Transform::SetTTransform(const Vector3F& p_localPosition,
	const Quaternion& p_localRotation)
{
	m_localMatrix = Matrix4F::identity;
	m_worldMatrix = Matrix4F::identity;

	m_localMatrix = Matrix4<float>::CreateTransformation(p_localPosition, p_localRotation, Vector3F::one);

	m_worldMatrix = HasParent() ? m_parent->WorldMatrix() * m_localMatrix : m_localMatrix;
	m_inverseWorldMatrix = Matrix4F::Inverse(m_worldMatrix);
}

void Transform::SetAnimTransform(const Vector3F& p_localPosition,
	const Quaternion& p_localRotation)
{
	m_localAnimMatrix = Matrix4F::identity;
	m_worldAnimMatrix = Matrix4F::identity;

	m_localAnimMatrix = Matrix4<float>::CreateTransformation(p_localPosition, p_localRotation, Vector3F::one);

	m_worldAnimMatrix = HasParent()
		? m_parent->WorldAnimMatrix() * m_localMatrix * m_localAnimMatrix
		: m_localMatrix * m_localAnimMatrix;
}

bool Transform::HasParent() const
{
	return m_parent != nullptr;
}

const Matrix4F& Transform::LocalMatrix() const
{
	return m_localMatrix;
}

const Matrix4F& Transform::WorldMatrix() const
{
	return m_worldMatrix;
}

const Matrix4F& Transform::InverseWorldMatrix() const
{
	return m_inverseWorldMatrix;
}

void Transform::SetParent(Transform& p_parent)
{
	m_parent = &p_parent;

	InitSkeleton();
}

void Transform::UpdateAnimationMatrices()
{
	// Frame Anim
	m_worldAnimMatrix = Matrix4F::identity;
	m_worldAnimMatrix = HasParent()
		? m_parent->WorldAnimMatrix() * m_localMatrix * m_localAnimMatrix
		: m_localMatrix * m_localAnimMatrix;
}

void Transform::InitSkeleton()
{
	// T-POSE
	m_worldMatrix = Matrix4F::identity;
	m_worldMatrix = HasParent() ? m_parent->WorldMatrix() * m_localMatrix : m_localMatrix;

	m_inverseWorldMatrix = Matrix4F::Inverse(m_worldMatrix);
}

Vector3F Transform::LocalPosition() const
{
	return { m_localMatrix[3], m_localMatrix[7], m_localMatrix[11] };
}

Vector3F Transform::WorldPosition() const
{
	return { m_worldMatrix[3], m_worldMatrix[7], m_worldMatrix[11] };
}

Quaternion Transform::LocalRotation() const
{
	const Matrix3F rotationMatrix(
		m_localMatrix[0], m_localMatrix[1], m_localMatrix[2],
		m_localMatrix[4], m_localMatrix[5], m_localMatrix[6],
		m_localMatrix[8], m_localMatrix[9], m_localMatrix[10]);
	return { rotationMatrix };
}

Quaternion Transform::WorldRotation() const
{
	const Matrix3F rotationMatrix(
		m_worldMatrix[0], m_worldMatrix[1], m_worldMatrix[2],
		m_worldMatrix[4], m_worldMatrix[5], m_worldMatrix[6],
		m_worldMatrix[8], m_worldMatrix[9], m_worldMatrix[10]);
	return { rotationMatrix };
}

Vector3F Transform::LocalAnimPosition() const
{
	return { m_localAnimMatrix[3], m_localAnimMatrix[7], m_localAnimMatrix[11] };
}

Vector3F Transform::WorldAnimPosition() const
{
	return { m_worldAnimMatrix[3], m_worldAnimMatrix[7], m_worldAnimMatrix[11] };
}

Quaternion Transform::LocalAnimRotation() const
{
	const Matrix3F rotationMatrix(
		m_localAnimMatrix[0], m_localAnimMatrix[1], m_localAnimMatrix[2],
		m_localAnimMatrix[4], m_localAnimMatrix[5], m_localAnimMatrix[6],
		m_localAnimMatrix[8], m_localAnimMatrix[9], m_localAnimMatrix[10]);
	return { rotationMatrix };
}

Quaternion Transform::WorldAnimRotation() const
{
	const Matrix3F rotationMatrix(
		m_worldAnimMatrix[0], m_worldAnimMatrix[1], m_worldAnimMatrix[2],
		m_worldAnimMatrix[4], m_worldAnimMatrix[5], m_worldAnimMatrix[6],
		m_worldAnimMatrix[8], m_worldAnimMatrix[9], m_worldAnimMatrix[10]);

	return { rotationMatrix };
}

const Matrix4F& Transform::LocalAnimMatrix() const
{
	return m_localAnimMatrix;
}

const Matrix4F& Transform::WorldAnimMatrix() const
{
	return m_worldAnimMatrix;
}

Transform& Transform::operator=(const Transform& p_other)
{
	m_localMatrix = p_other.m_localMatrix;
	m_worldMatrix = p_other.m_worldMatrix;

	return *this;
}

Transform& Transform::operator=(Transform&& p_other) noexcept
{
	m_localMatrix = p_other.m_localMatrix;
	m_worldMatrix = p_other.m_worldMatrix;

	return *this;
}

bool Transform::operator==(const Transform& p_other) const
{
	return m_localMatrix == p_other.m_localMatrix && m_worldMatrix == p_other.m_worldMatrix;
}

bool Transform::operator!=(const Transform& p_other) const
{
	return m_localMatrix != p_other.m_localMatrix || m_worldMatrix != p_other.m_worldMatrix;
}

std::ostream& operator<<(std::ostream& p_os, const Transform& p_transform)
{
	p_os << "\nLocal:\n" << p_transform.LocalMatrix() << "\nWorld:\n" << p_transform.WorldMatrix() << "\nLocalAnim:\n"
		<< p_transform.LocalAnimMatrix() << "\nWorldAnim:\n" << p_transform.WorldAnimMatrix();

	return p_os;
}
