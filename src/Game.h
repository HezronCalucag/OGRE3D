#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include "OgreCameraMan.h"

/* Bullet3 Physics */
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include "Player.h"
#include "Enemy.h"

using namespace Ogre;
using namespace OgreBites;

class Game : public ApplicationContext, public InputListener
{
private:
    SceneManager* scnMgr;

    //// collision configuration.
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld;

    ///keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    //Defining the player
    Player* player;
    
    //Defining the enemy
    Enemy* enemy;

    //Defining character keyboard controls 'upDown, DownDown, leftDown, rightDown'
    bool wDown;
    bool aDown;
    bool sDown;
    bool dDown;

public:
    //Setting up objects and camera into the game class
	Game();
	virtual ~Game();

	void setup();

	void setupCamera();

    void setupPlayer();

    void setupEnemy();

	void setupBoxMesh();
    void setupFloor();

	void setupLights();

	bool keyPressed(const KeyboardEvent& evt);
    bool keyReleased(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);

	bool frameStarted (const FrameEvent &evt);
	bool frameEnded(const FrameEvent &evt);

    bool frameRenderingQueued(const FrameEvent& evt);

    void bulletInit();
};
