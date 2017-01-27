#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "poScene/Scene.h"
#include "Aperture.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

class ApertureApp
: public App 
{
  public:
	void setup() override;
	void update() override;
	void draw() override;
    
    SceneRef scene;
};

void ApertureApp::setup()
{
    scene = Scene::create(Aperture::create());
}

void ApertureApp::update()
{
    scene->update();
}

void ApertureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    scene->draw();
}

CINDER_APP( ApertureApp, RendererGl )
