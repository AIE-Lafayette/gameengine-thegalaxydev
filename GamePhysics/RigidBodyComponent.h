#pragma once
#include <Component.h>
#include <GameMath/Vector3.h>
#include <GameMath/Vector2.h>


namespace GamePhysics 
{
    class RigidBodyComponent :
        public GameEngine::Component
    {
    public:
        // Velocity
        GameMath::Vector3 getVelocity3D() { return m_velocity; }
        void setVelocity3D(GameMath::Vector3 value) { m_velocity = value; }
        void setVelocity3D(float x, float y, float z) { m_velocity = GameMath::Vector3(x, y, z); }

        GameMath::Vector2 getVelocity2D() { return GameMath::Vector2(m_velocity.x, m_velocity.y); }
        void setVelocity2D(GameMath::Vector2 value) { m_velocity = GameMath::Vector3(value.x, value.y, m_velocity.z); }
        void setVelocity2D(float x, float y) { m_velocity = GameMath::Vector3(x, y, m_velocity.z); }

        // Acceleration
        GameMath::Vector3 getAcceleration3D() { return m_acceleration; }
        void setAcceleration3D(GameMath::Vector3 value) { m_acceleration = value; }

        GameMath::Vector2 getAcceleration2D() { return GameMath::Vector2(m_acceleration.x, m_acceleration.y); }
        void setAcceleration2D(GameMath::Vector2 value) { m_acceleration = GameMath::Vector3(value.x, value.y, m_acceleration.z); }

        // Mass
        float getMass() { return m_mass; }
        void setMass(float value) { m_mass = value; }

        // Gravity
        float getGravity() { return m_gravity; }
        void setGravity(float value) { m_gravity = value; }

        void applyForce(GameMath::Vector3 force);
        void applyForce(GameMath::Vector2 force);
        void applyForce(float x, float y, float z);
        void applyForce(float x, float y);

        void applyForceToGameObject(RigidBodyComponent* other, GameMath::Vector3 force);
        void applyForceToGameObject(RigidBodyComponent* other, GameMath::Vector2 force);

        void update(double deltaTime) override;

    private:
        float m_mass = 1;
        float m_gravity = 9.81f;
        GameMath::Vector3 m_velocity = GameMath::Vector3();
        GameMath::Vector3 m_acceleration = GameMath::Vector3();
    };
}
