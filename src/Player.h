#ifndef PLAYER_H_
#define PLAYER_H_

/* Ogre3d Graphics*/
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include "OgreCameraMan.h"

/* Bullet3 Physics */
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

using namespace Ogre;
using namespace OgreBites;

class Player
{


private:

    //Makes a player entity
    SceneNode* ninjaSceneNode; /**< Scene graph node */
    Entity* ninjaEntity;
    AnimationState* mNinjaAnimationState;

    //Makes a boundingbox for the player mesh
    SceneNode* boxSceneNode;
    Entity* box;
    Vector3 meshBoundingBox;

    //Physical properties of a player such as rigid body, collision and gravity
    btCollisionShape* colShape;
    btRigidBody* body;
    btDiscreteDynamicsWorld* dynamicsWorld;

    //Making instances of player variables
    float forwardForce;
    float leftForce;
    float downForce;
    float rightForce;
    float turningForce;
    btScalar linearDamping;
    btScalar angularDamping;
    
public:

    //Setting the player class
    Player();

    ~Player();

    void createMesh(SceneManager* scnMgr);

    void attachToNode(SceneNode* parent);

    void setScale(float x, float y, float z);

    void setRotation(Vector3 axis, Radian angle);

    void setPosition(float x, float y, float z);

    void boundingBoxFromOgre();

    void createRigidBody(float mass);

    void addToCollisionShapes(btAlignedObjectArray<btCollisionShape*> &collisionShapes);

    void addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld);

    void setMass(float mass);

    void update();

    void forward();

    void lefts();

    void downs();

    void rights();

    void setNinjaAnimation();

    //Gets the animation from the file
    AnimationState* getAnimationState();
};

#endif// PLAYER_h_