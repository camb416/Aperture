//
//  WallUI.cpp
//  Aperture
//
//  Created by Cameron Browning on 1/31/17.
//
//

#include "WallUI.h"

namespace aperture{
    WallUI::WallUI(){
        ci::app::console() << "WallUI Constructor" << std::endl;
    }
    WallUI::~WallUI(){
        // empty destructor
    }
    void WallUI::setup(){
        ci::app::console() << "wallui setup" << std::endl;
       // mParams->addButton( "Click me", std::bind( &WallUI::button, this ) );

    }
    
    void WallUI::draw(){
        mParams->draw();
    }
    
    void WallUI::button()
    {
        ci::app::console() << "You Clicked It!" << std::endl;
        //mParams->setOptions( "text", "label=`Clicked!`" );
    }
}
