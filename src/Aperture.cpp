#include "Aperture.h"

ApertureRef Aperture::create() 
{
    ApertureRef view(new Aperture());
    view->setup();
    return view;
}

Aperture::Aperture()
{
}

void Aperture::setup() 
{

}
