//
//  ApertureApp.h
//  Aperture
//
//  Created by Cameron Browning on 2/1/17.
//
//

#ifndef ApertureApp_h
#define ApertureApp_h


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

//namespace aperture{
//    class ViewController;
//    typedef std::shared_ptr<ViewController> ViewControllerRef;
//}

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
    
    void updateGUI(int a, int b);
    
private:
    
    ci::params::InterfaceGlRef mParams;
    void randomize();
    void threshold();
    
    int mPresetSelection, mAnimationSelection;
    vector<string> mPresetNames, mAnimationNames;
    int mSkipFrames;
    float mTweenVal;
    
    
    
    
};

#endif /* ApertureApp_h */
