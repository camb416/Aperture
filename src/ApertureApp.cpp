// cinder
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

// poscene
#include "poScene/Scene.h"

// application
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
    
private:
    
    ci::params::InterfaceGlRef mParams;
    void randomize();
    void threshold();
    
    int mPresetSelection, mAnimationSelection;
    vector<string> mPresetNames, mAnimationNames;
    
    void updateGUI(int a, int b);
    
    
};

void ApertureApp::setup()
{
    
    // Create the interface and give it a name.
  //  mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 400 ) ) );

    mViewController = aperture::ViewController::create();
    mScene = Scene::create(mViewController);
    
    mParams = ci::params::InterfaceGl::create( ci::app::getWindow(), "App parameters", ci::app::toPixels( ci::ivec2( 200, 400 ) ) );
    mParams->addButton( "Randomize", bind( &ApertureApp::randomize, this ) );
    mParams->addButton("Threshold", bind(&ApertureApp::threshold, this));
    // Add an enum (list) selector.
    mPresetSelection = 0;
    mPresetNames = { "none", "all off", "all on", "all 50%", "horizontal","vertical", "uphill", "downhill" };
    
    mAnimationSelection = 0;
    mAnimationNames = { "paused","scroll up", "scroll right", "scroll down", "scroll left", "game of life" };
    
    
    mParams->addParam( "Preset", mPresetNames, &mPresetSelection )
    .updateFn( [this] { console() << "preset updated: " << mPresetNames[mPresetSelection] << std::endl;
        mViewController->setPreset(mPresetSelection);
    } );
    
    mParams->addParam( "Animation", mAnimationNames, &mAnimationSelection )
    .updateFn( [this] { console() << "animation updated: " << mAnimationNames[mAnimationSelection] << std::endl;
        mViewController->setAnimationState(mAnimationSelection);
    } );
    mParams->setPosition(ivec2(1930,620));
    

}

void ApertureApp::randomize(){
    mViewController->randomize();
}
void ApertureApp::threshold(){
    mViewController->threshold();
}

void ApertureApp::update()
{
    mScene->update();
    //ci::app::console() << mParams->getPosition() << std::endl;
}
void ApertureApp::updateGUI(int animState, int presetState){
     mParams->setOptions("Animation", "val=1");
}

void ApertureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mScene->draw();
    mParams->draw();
}

void prepareSettings( ApertureApp::Settings *settings )
{
    settings->setHighDensityDisplayEnabled(); // try removing this line
    settings->setMultiTouchEnabled( false );
    
    int gridWidth = 1200;
    int numScreens = 12;
    int gridHeight = (gridWidth * 16) / (9 * numScreens);
    
    settings->setWindowSize(1280, 720);
}

CINDER_APP( ApertureApp, RendererGl( RendererGl::Options().msaa( 16 ) ), prepareSettings )
