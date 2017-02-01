#include "ApertureApp.h"

void ApertureApp::setup()
{
    
    mSkipFrames = 0;
    mTweenVal = 4.0f;
    
    // Create the interface and give it a name.
  //  mParams = params::InterfaceGl::create( getWindow(), "App parameters", toPixels( ivec2( 200, 400 ) ) );

    mViewController = aperture::ViewController::create();
    mScene = Scene::create(mViewController);
    
    mParams = ci::params::InterfaceGl::create( ci::app::getWindow(), "App parameters", ci::app::toPixels( ci::ivec2( 200, 400 ) ) );
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
    .updateFn( [this] {
        console() << "animation updated: " << mAnimationNames[mAnimationSelection] << std::endl;
        mViewController->setAnimationState(mAnimationSelection);
    } );
    
    mParams->addButton( "Randomize", bind( &ApertureApp::randomize, this ) );
    mParams->addButton("Threshold", bind(&ApertureApp::threshold, this));
   
    mParams->addParam("Skip Frames", &mSkipFrames, false)
        .min(0)
        .max(60)
        .updateFn([this] {
            console() << "updating skipframes" << std::endl;
            mViewController->setSkipFrames(mSkipFrames);
        });
    
    mParams->addParam("Tween coeff.", &mTweenVal, false)
        .min( 1.0f )
        .max( 64.0f )
        .updateFn([this] {
            mViewController->setTweenVals(mTweenVal);
        });
    
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
