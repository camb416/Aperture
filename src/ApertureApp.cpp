#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "poScene/Scene.h"
#include "ViewController.h"


using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

class ApertureApp
: public App 
{
  public:
    void setup();
    void update();
	void draw();
    
    SceneRef mScene;
    aperture::ViewControllerRef mViewController;
};

void ApertureApp::setup()
{
    
    int screenWidth = 1200;
    int numScreens = 12;
    int screenHeight = (screenWidth * 16) / (9 * numScreens);
    
    setWindowSize(screenWidth, screenHeight );

    mViewController = aperture::ViewController::create();
    mScene = Scene::create(mViewController);
}

void ApertureApp::update()
{
    mScene->update();
}

void ApertureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mScene->draw();
}

CINDER_APP( ApertureApp, RendererGl( RendererGl::Options().msaa( 16 ) ) )
