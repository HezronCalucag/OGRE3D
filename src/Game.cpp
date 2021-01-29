/*-------------------------------------------------------------------------
Significant portions of this project are based on the Ogre Tutorials
- https://ogrecave.github.io/ogre/api/1.10/tutorials.html
Copyright (c) 2000-2013 Torus Knot Software Ltd

Manual generation of meshes from here:
- http://wiki.ogre3d.org/Generating+A+Mesh

*/

#include <exception>
#include <iostream>

#include "Game.h"

using std::cout;
using std::endl;

Game::Game() : ApplicationContext("OgreTutorialApp")
{
    dynamicsWorld = NULL;

    //Keyboard input
    wDown = false;
    aDown = false;
    sDown = false;
    dDown = false;
}


Game::~Game()
{
    //cleanup in the reverse order of creation/initialization

    ///-----cleanup_start----
    //remove the rigidbodies from the dynamics world and delete them

    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
      btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
    	btRigidBody* body = btRigidBody::upcast(obj);

    	if (body && body->getMotionState())
    	{
    		delete body->getMotionState();
    	}

    	dynamicsWorld->removeCollisionObject(obj);
    	delete obj;
    }

    //delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++)
    {
    	btCollisionShape* shape = collisionShapes[j];
    	collisionShapes[j] = 0;
    	delete shape;
    }

    //delete dynamics world
    delete dynamicsWorld;

    //delete solver
    delete solver;

    //delete broadphase
    delete overlappingPairCache;

    //delete dispatcher
    delete dispatcher;

    delete collisionConfiguration;

    //next line is optional: it will be cleared by the destructor when the array goes out of scope
    collisionShapes.clear();
}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();

    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    //Set ups everything in the application
    bulletInit();

    setupCamera();

    setupPlayer();

    setupEnemy();

    setupFloor();

    setupLights();

    setupBoxMesh();
}

void Game::setupCamera()
{
    // Create Camera
    Camera* cam = scnMgr->createCamera("myCam");

    //Setup Camera
    cam->setNearClipDistance(5);

    // Position Camera - to do this it must be attached to a scene graph and added
    // to the scene.
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(200, 300, 600);
    camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);
    camNode->attachObject(cam);

    // Setup viewport for the camera.
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(ColourValue(0, 0, 0));

    // link the camera and view port.
    cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

void Game::setupPlayer()
{
    //Getting the scene manager to organise the player object
    SceneNode* sceneRoot = scnMgr->getRootSceneNode();
    float mass = 1.0f;

    Vector3 axis(1.0, 1.0, 0.0);
    axis.normalise();

    Radian angle(Degree(25.0));

    Radian rads(Degree(25.0));

    //Make a player entity to the scene node
    player = new Player();
    player->createMesh(scnMgr);
    player->attachToNode(sceneRoot);

    //Setting up position of the player mesh
    player->setRotation(axis, rads);
    player->setRotation(axis, angle);
    player->setPosition(5.0, 0.0, 200.0);
    player->setNinjaAnimation();

    //Rigid body of the player mesh based on the mass and adds collision
    player->createRigidBody(mass);
    player->addToCollisionShapes(collisionShapes);
    player->addToDynamicsWorld(dynamicsWorld);
 
}

void Game::setupEnemy()
{
    //Getting the scene manager to organise enemy object
    SceneNode* sceneRoot = scnMgr->getRootSceneNode();
    float mass = 1.0f;

    Vector3 axis(1.0, 1.0, 0.0);
    axis.normalise();

    Radian angle(Degree(25.0));

    Radian rads(Degree(25.0));

    //Make a enemy entity to the scene node
    enemy = new Enemy();
    enemy->createMesh(scnMgr);
    enemy->attachToNode(sceneRoot);

    //Setting up position of the player mesh
    enemy->setRotation(axis, rads);
    enemy->setRotation(axis, angle);
    enemy->setPosition(5.0, 0.0, 200.0);

    //Rigid body of the enemy mesh based on the mass and adds collision
    enemy->createRigidBody(mass);
    enemy->addToCollisionShapes(collisionShapes);
    enemy->addToDynamicsWorld(dynamicsWorld);
}

void Game::bulletInit()
{
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    collisionConfiguration = new btDefaultCollisionConfiguration();

     ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
     dispatcher = new btCollisionDispatcher(collisionConfiguration);

     ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
     overlappingPairCache = new btDbvtBroadphase();

     ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
     solver = new btSequentialImpulseConstraintSolver;

     dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

     //The properties of the gravity force
     dynamicsWorld->setGravity(btVector3(0, -20, 0));
}

void Game::setupBoxMesh()
{
    Entity* box = scnMgr->createEntity("cube.mesh");
    box->setCastShadows(true);

    SceneNode* thisSceneNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    thisSceneNode->attachObject(box);

    // Axis
    Vector3 axis(1.0,1.0,0.0);
    axis.normalise();

    //angle
    Radian rads(Degree(60.0));

    //quat from axis angle
    Quaternion quat(rads, axis);

    // thisSceneNode->setOrientation(quat);
    thisSceneNode->setScale(1.0,1.0,1.0);

    //get bounding box here.
    thisSceneNode->_updateBounds();
    const AxisAlignedBox& b = thisSceneNode->_getWorldAABB(); // box->getWorldBoundingBox();
    thisSceneNode->showBoundingBox(true);
    // std::cout << b << std::endl;
    // std::cout << "AAB [" << (float)b.x << " " << b.y << " " << b.z << "]" << std::endl;

    // Now I have a bounding box I can use it to make the collision shape.
    // I'll rotate the scene node and later the collision shape.
    thisSceneNode->setOrientation(quat);

    thisSceneNode->setPosition(0,200,0);

    Vector3 meshBoundingBox(b.getSize());

    if(meshBoundingBox == Vector3::ZERO)
    {
        std::cout << "bounding voluem size is zero." << std::endl;
    }

    //create a dynamic rigidbody

    btCollisionShape* colShape = new btBoxShape(btVector3(meshBoundingBox.x/2.0f, meshBoundingBox.y/2.0f, meshBoundingBox.z/2.0f));
    std::cout << "Mesh box col shape [" << (float)meshBoundingBox.x << " " << meshBoundingBox.y << " " << meshBoundingBox.z << "]" << std::endl;
    // btCollisionShape* colShape = new btBoxShape(btVector3(10.0,10.0,10.0));
    //btCollisionShape* colShape = new btSphereShape(btScalar(1.));
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    //startTransform.setOrigin(btVector3(0, 200, 0));

    Vector3 pos = thisSceneNode->_getDerivedPosition();
    startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    Quaternion quat2 = thisSceneNode->_getDerivedOrientation();
    startTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

    btScalar mass(1.f);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
    {
        // Debugging
        //std::cout << "I see the cube is dynamic" << std::endl;
        colShape->calculateLocalInertia(mass, localInertia);
    }

    std::cout << "Local inertia [" << (float)localInertia.x() << " " << localInertia.y() << " " << localInertia.z() << "]" << std::endl;

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);

    //Link to ogre
    body->setUserPointer((void*)thisSceneNode);

    //  body->setRestitution(0.5);

    dynamicsWorld->addRigidBody(body);


}


void Game::setupFloor()
{

    // Create a plane
    Plane plane(Vector3::UNIT_Y, 0);

    // Define the plane mesh
    MeshManager::getSingleton().createPlane(
            "ground", RGN_DEFAULT,
            plane,
            1500, 1500, 20, 20,
            true,
            1, 5, 5,
            Vector3::UNIT_Z);

    // Create an entity for the ground
    Entity* groundEntity = scnMgr->createEntity("ground");

    //Setup ground entity
    // Shadows off
    groundEntity->setCastShadows(false);

    // Material - Examples is the rsources file,
    // Rockwall (texture/properties) is defined inside it.
    groundEntity->setMaterialName("Examples/Rockwall");

    // Create a scene node to add the mesh too.
    SceneNode* thisSceneNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    thisSceneNode->attachObject(groundEntity);

    //the ground is a cube of side 100 at position y = 0.
	   //the sphere will hit it at y = -6, with center at -5
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(750.), btScalar(50.), btScalar(750.)));

    collisionShapes.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
  //  groundTransform.setOrigin(btVector3(0, -100, 0));

    Vector3 pos = thisSceneNode->_getDerivedPosition();

    //Box is 100 deep (dimensions are 1/2 heights)
    //but the plane position is flat.
    groundTransform.setOrigin(btVector3(pos.x, pos.y-50.0, pos.z));

    Quaternion quat2 = thisSceneNode->_getDerivedOrientation();
    groundTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));


    btScalar mass(0.);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(mass, localInertia);

    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);

    //   body->setRestitution(0.0);

    //add the body to the dynamics world
    dynamicsWorld->addRigidBody(body);
}

bool Game::frameStarted(const Ogre::FrameEvent &evt)
{
  //Be sure to call base class - otherwise events are not polled.
  ApplicationContext::frameStarted(evt);

  if (this->dynamicsWorld != NULL)
  {
      //Apply new forces
      if (wDown) 
      {
          player->forward();
      }

      if (aDown)
      {
          player->lefts();
      }

      if (sDown)
      {
          player->downs();
      }

      if (dDown)
      {
          player->rights();
      }
    
      // Bullet can work with a fixed timestep
      //dynamicsWorld->stepSimulation(1.f / 60.f, 10);

      // Or a variable one, however, under the hood it uses a fixed timestep
      // then interpolates between them.

     dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);

     // update positions of all objects
     for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
     {
         btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
         btRigidBody* body = btRigidBody::upcast(obj);
         btTransform trans;

         if (body && body->getMotionState())
         {
            body->getMotionState()->getWorldTransform(trans);

            /* https://oramind.com/ogre-bullet-a-beginners-basic-guide/ */
            void *userPointer = body->getUserPointer();
            if (userPointer && !player)
            {
              btQuaternion orientation = trans.getRotation();
              Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(userPointer);
              sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
              sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
            }

          }
          else
          {
            trans = obj->getWorldTransform();
          }
     }
     //Updates the player and enemy physics to the application
     player->update();

     enemy->update();
   }
  return true;
}


bool Game::frameEnded (const Ogre::FrameEvent &evt)
{
  if (this->dynamicsWorld != NULL)
  {
      // Bullet can work with a fixed timestep
      //dynamicsWorld->stepSimulation(1.f / 60.f, 10);

      // Or a variable one, however, under the hood it uses a fixed timestep
      // then interpolates between them.

       dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);
  }
  return true;
}

bool Game::frameRenderingQueued(const FrameEvent& evt)
{
    //Selects animation on the player
    player->getAnimationState()->addTime(evt.timeSinceLastFrame);

    return true;
}

void Game::setupLights()
{
    // Setup Abient light
    scnMgr->setAmbientLight(ColourValue(0, 0, 0));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);

    // Add a spotlight
    Light* spotLight = scnMgr->createLight("SpotLight");

    // Configure
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Light::LT_SPOTLIGHT);
    spotLight->setSpotlightRange(Degree(35), Degree(50));


    // Create a schene node for the spotlight
    SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    spotLightNode->setDirection(-1, -1, 0);
    spotLightNode->setPosition(Vector3(200, 200, 0));

    // Add spotlight to the scene node.
    spotLightNode->attachObject(spotLight);

    // Create directional light
    Light* directionalLight = scnMgr->createLight("DirectionalLight");

    // Configure the light
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
    directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));

    // Setup a scene node for the directional lightnode.
    SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(0, -1, 1));

    // Create a point light
    Light* pointLight = scnMgr->createLight("PointLight");

    // Configure the light
    pointLight->setType(Light::LT_POINT);
    pointLight->setDiffuseColour(0.3, 0.3, 0.3);
    pointLight->setSpecularColour(0.3, 0.3, 0.3);

    // setup the scene node for the point light
    SceneNode* pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // Configure the light
    pointLightNode->setPosition(Vector3(0, 150, 250));

    // Add the light to the scene.
    pointLightNode->attachObject(pointLight);

}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    std::cout << "Got key event" << std::endl;
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }

    //When pressed, the player moves
    if (evt.keysym.sym == SDLK_UP)
    {
        wDown = true;
    }

    if (evt.keysym.sym == SDLK_LEFT)
    {
        aDown = true;
    }

    if (evt.keysym.sym == SDLK_DOWN)
    {
        sDown = true;
    }

    if (evt.keysym.sym == SDLK_RIGHT)
    {
        dDown = true;
    }

    return true;
}

bool Game::keyReleased(const KeyboardEvent& evt)
{
    cout << "Got key up event" << endl;
 
    //when released, the player stops moving
    if (evt.keysym.sym == SDLK_UP)
    {
        wDown = false;
    }

    if (evt.keysym.sym == SDLK_LEFT)
    {
        aDown = false;
    }

    if (evt.keysym.sym == SDLK_DOWN)
    {
        sDown = false;
    }

    if (evt.keysym.sym == SDLK_RIGHT)
    {
        dDown = false;
    }

    return true;
}


bool Game::mouseMoved(const MouseMotionEvent& evt)
{
	std::cout << "Got Mouse" << std::endl;
	return true;
}
