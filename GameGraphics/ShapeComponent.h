#pragma once

#include "GameEngine/TransformComponent.h"
#include "GameEngine/Component.h"
#include "GameGraphics//Color4.h"

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
        ShapeComponent() {}

        ShapeComponent(ShapeType shapeType) { m_shapeType = shapeType; }

		void setColor(unsigned int color) { m_color = color; }
        void setColor(GameGraphics::Color4 color) { m_color = color.toHex(); }
		unsigned int getColor() const { return m_color; }
        GameGraphics::Color4 getColor4() { return GameGraphics::Color4::getColorHex(m_color); }
        

		ShapeType getShapeType() { return m_shapeType; }
		void setShapeType(ShapeType shapeType) { m_shapeType = shapeType; }

        void draw() override;

    private:
        ShapeType m_shapeType;
        unsigned int m_color = 0xFFFFFFFF;
    };
}


