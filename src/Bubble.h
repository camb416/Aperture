//
//  Bubble.hpp
//  Aperture
//
//  Created by Cameron Browning on 1/27/17.
//
//

#ifndef Bubble_h
#define Bubble_h

#include "poScene/View.h"
#include "poScene/ShapeView.h"

#include <stdio.h>

using namespace po::scene;

class Bubble;
typedef std::shared_ptr<Bubble> BubbleRef;

class Bubble
: public po::scene::View
{
public:
    static BubbleRef create(int size);
    virtual ~Bubble();
    
    virtual void setup(int size);
    virtual void update();
    // virtual void draw();
    void  randomize();
    
    void  shrink();
    void  setDestSize(float destSize);
    float getDestSize(){ return mDestSize; };
    void threshold();
    
    
protected:
    Bubble();

    
private:
    // size of bubble
    float mSize;
    float mDestSize;
    
    float mTweenVal;
    
    // Circle Shape
    ShapeViewRef mShape;
    
    ci::Color mColor;
    ci::Color mHighlightColor;
    ci::Color mBoundsColor;
    
    bool mIsPressed;
    ci::vec2 mStartPos, mEndPos, mInitialPos;
    
    void onMouseDown(MouseEvent &evt);
    void onMouseUp(MouseEvent &evt);
    void onMouseDragged(MouseEvent &evt);
    void highlight(bool isHighlighted);
    void highlightChildren(bool isHighlighted);
    void highlightParent();
    

    
    
};

#endif /* Bubble_hpp */
