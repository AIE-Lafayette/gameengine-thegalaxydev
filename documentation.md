# AIE 2023 Physics Engine Practice


## RigidBodyComponent
```cpp
class RigidBodyComponent :
    public GameEngine::Component
```
A component used to add physics to a Game Object.

### Properties
<table>
<tr> 
<td>m_staticFrictionCoefficient</td> 
<td> 
Private

```cpp
float m_staticFrictionCoefficient;
```
The static friction coefficient for the rigid body. This determines how much force is required to move the object when it is touching the ground.
</td>
</tr>
<tr> 
<td>m_dyanmicFrictionCoefficient</td> 
<td> 
Private

```cpp
float m_dyanmicFrictionCoefficient;
```
The dynamic friction coefficient for the rigid body. This determines how much force is required to to stop the object once it has started moving.
</td>
</tr>

</table>

### Methods
<table>
<tr>
<td>getDynamicFrictionCoefficient</td> 
<td>

```cpp
float getDynamicFrictionCoefficient()
```
Returns the dynamic friction coefficient value. (`m_dyanmicFrictionCoefficient`)
</td>
</tr>

<tr>
<td>setDynamicFrictionCoefficient</td> 
<td>

```cpp
void setDynamicFrictionCoefficient(float value)
```
Sets the dynamic friction coefficient value to the float given. (`m_dyanmicFrictionCoefficient`)
</td>
</tr>
<td>getStaticFrictionCoefficient</td> 
<td>

```cpp
float getStaticFrictionCoefficient()
```
Returns the static friction coefficient value. (`m_staticFrictionCoefficient`)
</td>
</tr>
<tr>
<td>setStaticFrictionCoefficient</td> 
<td>

```cpp
void setStaticFrictionCoefficient(float value)
```
Sets the static friction coefficient value to the float given. (`m_staticFrictionCoefficient`)
</td>
</tr>

<tr>
<td>applyFrictionForce</td> 
<td>

```cpp
private:
void applyFrictionForce(GamePhysics::Collision* other)
```
Calculates and applies friction forced based on a collision between two objects utilizing the averages of their dynamic and static friction coefficients. **This function is private and called internally and may have unintended results when used outside of collision resolution.**
</td>
</tr>
</table>

## InputComponent2D
```cpp
class InputComponent2D :
    public GameEngine::Component
```
A component used to retrieve directional input.

### Methods
<table>
<tr>
<td>getMoveDirection</td> 
<td>

```cpp
GameMath::Vector3 getMoveDirection()
```
Returns a normalized direction (up, down, left, or right) in 2D space based on if the user is holding W,A,S or D. The value is returned as a Vector3 for ease of use within the engine.

**Example**:

```cpp
#include "InputComponent2D.h"

InputComponent2D* inputComponent;
GameEngine::GameObject* player

void TestScene::onStart()
{
    // assign a value to the player and input component
    player = new GameObject();

    inputComponent = player->addComponent<InputComponent2D>();
}

void TestScene::onUpdate(float deltaTime)
{
    // get the move direction
    GameMath::Vector3 inputDirection = inputComponent->getMoveDirection();
    float speed = 5;

    // move the player based on the direction given
    player->getTransform()->setLocalPosition(inputDirection * speed * deltaTime);
}
```
</td>
</tr>
</table>