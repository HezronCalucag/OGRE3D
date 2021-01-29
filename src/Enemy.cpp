#include "Enemy.h"

Enemy::Enemy()
{
    //Makes enemy entity with bounding box
    enemySceneNode = nullptr;
    enemyEntity = nullptr;
    Vector3 meshBoundingBox(0.0f, 0.0f, 0.0f);

    //Collision and gravity force physics
    colShape = NULL;
    dynamicsWorld = NULL;

    //The gravity force property of enemy object
    turningForce = 20.0f;
    linearDamping = 0.2f;
    angularDamping = 0.8f;
}

Enemy::~Enemy()
{
    //Deletes enemy entity
    delete enemySceneNode;
    delete enemyEntity;

}

void Enemy::createMesh(SceneManager* scnMgr)
{
    //Creates enemy entity
    enemyEntity = scnMgr->createEntity("cube.mesh");
}

void Enemy::attachToNode(SceneNode* parent)
{
    enemySceneNode = parent->createChildSceneNode();
    enemySceneNode->attachObject(enemyEntity);
    enemySceneNode->setScale(1.0f, 1.0f, 1.0f);
    boundingBoxFromOgre(); //Attaches the bounding box on the enemy entity
}

void Enemy::setScale(float x, float y, float z)
{
    //setting the size of the enemy mesh
    enemySceneNode->setScale(x, y, z);
}

void Enemy::setRotation(Vector3 axis, Radian angle)
{
    //To allow the enemy mesh to rotate in certain directions
    Quaternion quat(angle, axis);
    enemySceneNode->setOrientation(quat);
}

void Enemy::setPosition(float x, float y, float z)
{
    //Setting the position of the enemy entity
    enemySceneNode->setPosition(x, y, z);
}

void Enemy::boundingBoxFromOgre()
{
    enemySceneNode->_updateBounds();
    const AxisAlignedBox& b = enemySceneNode->_getWorldAABB();
    Vector3 temp(b.getSize());
    meshBoundingBox = temp;
}

void Enemy::createRigidBody(float mass)
{
    //Creating rigid body of the enemy entity
    colShape = new btBoxShape(btVector3(meshBoundingBox.x / 2.0f, meshBoundingBox.y / 25.0f, meshBoundingBox.z / 2.0f));

    //Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    Quaternion quat2 = enemySceneNode->_getDerivedOrientation();
    startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

    Vector3 pos = enemySceneNode->_getDerivedPosition();
    startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    btScalar Mass(mass);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
    {
        //debugging
        colShape->calculateLocalInertia(mass, localInertia);
    }

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronises 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    body = new btRigidBody(rbInfo);

    //Set the linear and angular damping
    body->setDamping(linearDamping, angularDamping);

    //Set the user pointer to this object.
    body->setUserPointer((void*)this);
}

void Enemy::addToCollisionShapes(btAlignedObjectArray<btCollisionShape*>& collisionShapes)
{
    //Collision behaviour
    collisionShapes.push_back(colShape);
}

void Enemy::addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld)
{
    //Adds gravity force on the enemy
    this->dynamicsWorld = dynamicsWorld;
    dynamicsWorld->addRigidBody(body);
}

void Enemy::update()
{
    //Apply transformations to the rigid body
    btTransform trans;

    if (body && body->getMotionState())
    {
        body->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        enemySceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
        enemySceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
    }
}



