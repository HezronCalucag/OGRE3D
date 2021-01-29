#ifndef Enemy_H_
#define Enemy_H_

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

class Enemy
{


private:

    //Makes an enemy entity
    SceneNode* enemySceneNode; /**< Scene graph node */
    Entity* enemyEntity;
    AnimationState* mEnemyAnimationState;

    //Makes a boundingbox for the enemy mesh
    SceneNode* boxSceneNode;
    Entity* box;
    Vector3 meshBoundingBox;

    //Physical properties of an enemy such as rigid body, collision and gravity
    btCollisionShape* colShape;
    btRigidBody* body;
    btDiscreteDynamicsWorld* dynamicsWorld;

    //Making instances of enemy variables
    float turningForce;
    btScalar linearDamping;
    btScalar angularDamping;

public:

    //Setting the enemy class
    Enemy();

    ~Enemy();

    void createMesh(SceneManager* scnMgr);

    void attachToNode(SceneNode* parent);

    void setScale(float x, float y, float z);

    void setRotation(Vector3 axis, Radian angle);

    void setPosition(float x, float y, float z);

    void boundingBoxFromOgre();

    void createRigidBody(float mass);

    void addToCollisionShapes(btAlignedObjectArray<btCollisionShape*>& collisionShapes);

    void addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld);

    void update();

};

#endif// ENEMY_h_
