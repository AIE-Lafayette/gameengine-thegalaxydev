#include "TransformComponent.h"
 
GameMath::Matrix4 GameEngine::TransformComponent::getGlobalMatrix()
{
	updateMatrices();
	return m_globalMatrix;
}

void GameEngine::TransformComponent::setLocalPosition(GameMath::Vector3 position)
{
	m_translation = position;
}

void GameEngine::TransformComponent::setLocalPosition(GameMath::Vector2 position)
{
	m_translation = GameMath::Vector3(position.x, position.y, 0.0f);
}

void GameEngine::TransformComponent::setLocalPosition(float x, float y)
{
	m_translation = GameMath::Vector3(x, y, 0.0f);
}


GameMath::Vector3 GameEngine::TransformComponent::getLocalPosition()
{
	updateMatrices();
	return m_translation;
}

void GameEngine::TransformComponent::setLocalRotation(GameMath::Vector3 rotation)
{
	m_rotation = rotation;
}

void GameEngine::TransformComponent::setLocalRotation(GameMath::Vector2 rotation)
{
	m_rotation = GameMath::Vector3(rotation.x, rotation.y, 0.0f);
}

void GameEngine::TransformComponent::setLocalRotation(float x, float y)
{
	m_rotation = GameMath::Vector3(x, y, 0.0f);
}

GameMath::Vector3 GameEngine::TransformComponent::getLocalRotation()
{
	updateMatrices();
	return m_rotation;
}

GameMath::Vector3 GameEngine::TransformComponent::getGlobalRotation()
{
	updateMatrices();

	GameMath::Vector3 xAxis = GameMath::Vector3(m_globalMatrix.m00, m_globalMatrix.m10, m_globalMatrix.m20);
	GameMath::Vector3 yAxis = GameMath::Vector3(m_globalMatrix.m01, m_globalMatrix.m11, m_globalMatrix.m21);
	GameMath::Vector3 zAxis = GameMath::Vector3(m_globalMatrix.m02, m_globalMatrix.m12, m_globalMatrix.m22);

	float angleX = atan2f(xAxis.y, xAxis.x);
	float angleY = atan2f(yAxis.x, yAxis.y);
	float angleZ = atan2f(zAxis.y, zAxis.x);	

	return GameMath::Vector3(angleX, angleY, angleZ);
}

void GameEngine::TransformComponent::setLocalScale(GameMath::Vector3 scale)
{
	m_scale = scale;
}

void GameEngine::TransformComponent::setLocalScale(GameMath::Vector2 scale)
{
	m_scale = GameMath::Vector3(scale.x, scale.y, 0.0f);
}

void GameEngine::TransformComponent::setLocalScale(float x, float y)
{
	m_scale = GameMath::Vector3(x,y, 0.0f);
}

GameMath::Vector3 GameEngine::TransformComponent::getLocalScale()
{
	updateMatrices();
	return m_scale;
}

GameMath::Vector3 GameEngine::TransformComponent::getGlobalPosition()
{
	updateMatrices();
	return GameMath::Vector3(m_globalMatrix.m03, m_globalMatrix.m13, m_globalMatrix.m23);
}

GameMath::Vector3 GameEngine::TransformComponent::getGlobalScale()
{
	updateMatrices();

	GameMath::Vector3 xAxis = GameMath::Vector3(m_globalMatrix.m00, m_globalMatrix.m10, m_globalMatrix.m20);
	GameMath::Vector3 yAxis = GameMath::Vector3(m_globalMatrix.m01, m_globalMatrix.m11, m_globalMatrix.m21);
	GameMath::Vector3 zAxis = GameMath::Vector3(m_globalMatrix.m02, m_globalMatrix.m12, m_globalMatrix.m22);

	return GameMath::Vector3(xAxis.getMagnitude(), yAxis.getMagnitude(), zAxis.getMagnitude());
}

GameEngine::TransformComponent* GameEngine::TransformComponent::getParent()
{
	return m_parent;
}

void GameEngine::TransformComponent::setParent(TransformComponent* parent)
{
	m_parent = parent;
}

void GameEngine::TransformComponent::updateMatrices()
{
	GameMath::Matrix4 translation = GameMath::Matrix4::createTranslation(m_translation);
	GameMath::Matrix4 rotationX = GameMath::Matrix4::createRotationX(m_rotation.x);
	GameMath::Matrix4 rotationY = GameMath::Matrix4::createRotationY(m_rotation.y);
	GameMath::Matrix4 rotationZ = GameMath::Matrix4::createRotationZ(m_rotation.z);	

	GameMath::Matrix4 rotation = rotationX * rotationY * rotationZ;

	GameMath::Matrix4 scale = GameMath::Matrix4::createScale(m_scale);

	m_localMatrix = translation * rotation * scale;

	if (m_parent)
		m_globalMatrix = m_parent->getGlobalMatrix() * m_localMatrix;
	else
		m_globalMatrix = m_localMatrix;
}