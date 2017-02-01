//
//  WallUI.hpp
//  Aperture
//
//  Created by Cameron Browning on 1/31/17.
//
//

#ifndef WallUI_h
#define WallUI_h

#include "cinder/params/Params.h"

#include <stdio.h>

namespace aperture{
    


class WallUI{

public:
    
    static WallUI & Instance(){
        static WallUI myInstance;
        ci::app::console() << "instantiating wall ui" << std::endl;
        return myInstance;
    }

    // delete copy and move constructors and assign operators
    WallUI(WallUI const&) = delete;             // Copy construct
    WallUI(WallUI&&) = delete;                  // Move construct
    WallUI& operator=(WallUI const&) = delete;  // Copy assign
    WallUI& operator=(WallUI &&) = delete;      // Move assign
    
    void setup();
    void draw();

protected:
    WallUI();
    ~WallUI();

private:
    ci::params::InterfaceGlRef	mParams;
    void button();
    
};
}
#endif /* WallUI_hpp */
