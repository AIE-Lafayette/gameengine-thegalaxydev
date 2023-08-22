#include "Component.h"


void GameEngine::Component::setEnabled(bool value)
{
	if (!m_enabled && value)
		onEnable();
	else if (m_enabled && !value)
		onDisable();

	m_enabled = value;
}