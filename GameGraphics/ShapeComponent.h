#pragma once

#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"


namespace GameGraphics
{
    enum ShapeType
    {
        CIRCLE,
        BOX,
        CUBE,
        SPHERE
    };
    class ShapeComponent :
        public GameEngine::Component
    {
    public:
        ShapeComponent() {}

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


