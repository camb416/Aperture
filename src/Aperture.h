#pragma once

#include "poScene/View.h"

class Aperture;
typedef std::shared_ptr<Aperture> ApertureRef;

class Aperture
: public po::scene::View
{
public:
    static ApertureRef create();
    
    void setup();
    
protected:
	Aperture();

private:

};
