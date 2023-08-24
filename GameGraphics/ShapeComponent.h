#pragma once
#include "Component.h"
#include "TransformComponent.h"

namespace GameGraphics
{
    enum ShapeType
    {
        CIRCLE,
        BOX
    };
    class ShapeComponent :
        public GameEngine::Component
    {
    public:
        ShapeComponent(ShapeType shapeType) { m_shapeType = shapeType; }

		void setColor(unsigned int color) { m_color = color; }
		unsigned int getColor() const { return m_color; }

		ShapeType getShapeType() { return m_shapeType; }
		void setShapeType(ShapeType shapeType) { m_shapeType = shapeType; }

        void draw() override;

    private:
        ShapeType m_shapeType;
        unsigned int m_color = 0xFFFFFFFF;
    };
}

