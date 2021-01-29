#include "Player.h"

Player::Player()
{
    //Makes player entity with bounding box
    ninjaSceneNode = nullptr;
    ninjaEntity = nullptr;
    Vector3 meshBoundingBox(0.0f, 0.0f, 0.0f);

    //Collision and gravity force physics
    colShape = NULL;
    dynamicsWorld = NULL;

    //The speed property of character movement
    forwardForce = -100.0f;
    leftForce = -100.0f;
    downForce = 100.0f;
    rightForce = -100.0f;
    turningForce = 20.0f;
    linearDamping = 0.2f;
    angularDamping = 0.8f;
}

Player::~Player()
{
    //Deletes player entity
    delete ninjaSceneNode;
    delete ninjaEntity;
}

void Player::createMesh(SceneManager* scnMgr)
{
    //Creates player entity
    ninjaEntity = scnMgr->createEntity("ninja.mesh");
}

void Player::attachToNode(SceneNode* parent)
{
    ninjaSceneNode = parent->createChildSceneNode();
    ninjaSceneNode->attachObject(ninjaEntity);
    ninjaSceneNode->setScale(1.0f, 1.0f, 1.0f);
    boundingBoxFromOgre(); //Attaches the bounding box on the player entity
}

void Player::setScale(float x, float y, float z)
{
    //setting the size of the player mesh
    ninjaSceneNode->setScale(x, y, z);
}

void Player::setRotation(Vector3 axis, Radian angle)
{
    //To allow the player mesh to rotate in certain directions
    Quaternion quat(angle, axis);
    ninjaSceneNode->setOrientation(quat);
}

void Player::setPosition(float x, float y, float z)
{
    //Setting the position of the player entity
    ninjaSceneNode->setPosition(x, y, z);
}

void Player::boundingBoxFromOgre()
{
    ninjaSceneNode->_updateBounds();
    const AxisAlignedBox& b = ninjaSceneNode->_getWorldAABB();
    Vector3 temp(b.getSize());
    meshBoundingBox = temp;
}

void Player::createRigidBody(float mass)
{
    //Creating rigid body of the player entity
    colShape = new btBoxShape(btVector3(meshBoundingBox.x / 2.0f, meshBoundingBox.y / 25.0f, meshBoundingBox.z / 2.0f));

    //Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    Quaternion quat2 = ninjaSceneNode->_getDerivedOrientation();
    startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

    Vector3 pos = ninjaSceneNode->_getDerivedPosition();
    startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    //Set player mass
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

void Player::addToCollisionShapes(btAlignedObjectArray<btCollisionShape*>& collisionShapes)
{
    //Collision behaviour
    collisionShapes.push_back(colShape);
}

void Player::setNinjaAnimation()
{
    //Player animation continued loop
    mNinjaAnimationState = ninjaEntity->getAnimationState("Idle1");
    mNinjaAnimationState->setLoop(true);
    mNinjaAnimationState->setEnabled(true);
    mNinjaAnimationState->setWeight(1);  
}

void Player::addToDynamicsWorld(btDiscreteDynamicsWorld* dynamicsWorld)
{
    //Adds gravity force on the player
    this->dynamicsWorld = dynamicsWorld;
    dynamicsWorld->addRigidBody(body);
}

void Player::update()
{
    //Apply transformations to the rigid body
    btTransform trans;

    if (body && body->getMotionState())
    {
        body->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        ninjaSceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
        ninjaSceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
    }
}

void Player::forward()
{
    //Create a vector in local coordinates
    btVector3 fwd(0.0f, 0.0f, forwardForce);
    btVector3 push;

    btTransform trans;

    if (body && body->getMotionState())
    {
        //get the orientation of the rigid body in world space
        body->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        //rotate the local force, into the global space
        push = quatRotate(orientation, fwd);

        //activate the body, this is essential if the body
        body->activate();

        //apply a force to the centre of the body
        body->applyCentralForce(push);
    }
}

void Player::lefts()
{
    //Create a vector in local coordinates
    btVector3 lft(-100.0f, 0.0f, leftForce);
    btVector3 push;

    btTransform trans;

    if (body && body->getMotionState())
    {
        //get the orientation of the rigid body in world space
        body->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        //rotate the local force, into the global space
        push = quatRotate(orientation, lft);

        //activate the body, this is essential if the body
        body->activate();

        //apply a force to the centre of the body
        body->applyCentralForce(push);
    }
}

void Player::downs()
{
    //Create a vector in local coordinates
    btVector3 dwn(-0.0f, -0.0f, downForce);
    btVector3 push;

    btTransform trans;

    if (body && body->getMotionState())
    {
        //get the orientation of the rigid body in world space
        body->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        //rotate the local force, into the global space
        push = quatRotate(orientation, dwn);

        //activate the body, this is essential if the body
        body->activate();

        //apply a force to the centre of the body
        body->applyCentralForce(push);
    }
}

void Player::rights()
{
    //Create a vector in local coordinates
    btVector3 rht(100.0f, 0.0f, rightForce);
    btVector3 push;

    btTransform trans;

    if (body && body->getMotionState())
    {
        //get the orientation of the rigid body in world space
        body->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        //rotate the local force, into the global space
        push = quatRotate(orientation, rht);

        //activate the body, this is essential if the body
        body->activate();

        //apply a force to the centre of the body
        body->applyCentralForce(push);
    }
}

AnimationState* Player::getAnimationState()
{
    return mNinjaAnimationState;
}

