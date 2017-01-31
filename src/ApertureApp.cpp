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
    void prepareSettings(ApertureApp::Settings *settings);
    
    SceneRef mScene;
    aperture::ViewControllerRef mViewController;
};

void ApertureApp::setup()
{
    


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
void prepareSettings( ApertureApp::Settings *settings )
{
    settings->setHighDensityDisplayEnabled(); // try removing this line
    settings->setMultiTouchEnabled( false );
    
    int gridWidth = 1200;
    int numScreens = 12;
    int gridHeight = (gridWidth * 16) / (9 * numScreens);
    

    
    settings->setWindowSize(gridWidth, gridHeight);
}

CINDER_APP( ApertureApp, RendererGl( RendererGl::Options().msaa( 16 ) ), prepareSettings )
