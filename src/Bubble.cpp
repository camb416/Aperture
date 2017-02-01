//
//  Bubble.cpp
//  Aperture
//
//  Created by Cameron Browning on 1/27/17.
//
//
#include "cinder/Rand.h"
#include "Bubble.h"


BubbleRef Bubble::create(int size)
{
    BubbleRef ref = std::shared_ptr<Bubble>(new Bubble());
    ref->setup(size);
    return ref;
}

// TODO:
// ask someone smart WTF is going on here
Bubble::Bubble()
: mSize(50)
, mColor(ci::Color(ci::CM_HSV,1,0,1))
, mHighlightColor(ci::Color(ci::CM_HSV,1,1,1))
, mIsPressed(false)
, mStartPos(ci::vec2())
, mEndPos(ci::vec2())
, mInitialPos(ci::vec2())
, mBoundsColor(ci::Color(1.0f,1.0f,1.0f))
{
}

Bubble::~Bubble()
{
}

void Bubble::setup(int size)
{
   // ci::app::console() << "Bubble::setup()" << std::endl;
    mDestSize = size;
    mSize = 1;

    mShape = ShapeView::createCircle(mSize);
    mShape->setAlignment(Alignment::CENTER_CENTER);

    mColor = ci::Color(ci::CM_HSV, 1,0,1);
    mHighlightColor = ci::Color(ci::CM_HSV, 1,0,1);

    mShape->setFillColor(mColor);
    addSubview(mShape);
    
    // TODO:
    // ask someone smart WTF is going on here
 //   getSignal(MouseEvent::DOWN_INSIDE).connect(std::bind(&Bubble::onMouseDown, this, std::placeholders::_1));
    
    mTweenVal = ci::randFloat(16.0f)+16.0f;
    

}
void Bubble::update(){
  //  ci::app::console() << "bubble update" << std::endl;
    mSize += (mDestSize-mSize)/mTweenVal;
    mShape->setSize(ci::vec2(mSize));
    mShape->setScale(mSize);
    mShape->setFillColor(ci::Color(1,1,1));
//    mShape->render();

}
void Bubble::setTweenVal(float tweenVal){
    mTweenVal = tweenVal;
}

//void Bubble::draw(){
//   // ci::app::console() << "bubble draw" << std::endl;
//}

void Bubble::onMouseDown(MouseEvent &evt)
{
	ci::app::console() << "Bubble::onMouseDown()" << std::endl;
}

void Bubble::onMouseDragged(MouseEvent &evt)
{
	ci::app::console() << "Bubble::onMouseDragged()" << std::endl;
}

void Bubble::onMouseUp(MouseEvent &evt)
{
	ci::app::console() << "Bubble::onMouseUp()" << std::endl;
}

void Bubble::highlight(bool isHighlighted)
{
	ci::app::console() << "Bubble::highlight()" << std::endl;
}

void Bubble::highlightChildren(bool isHighlighted)
{
	ci::app::console() << "Bubble::highlightChildren()" << std::endl;
}

void Bubble::randomize(){
    mDestSize = ci::randFloat(12);
}
void Bubble::shrink(){
    setDestSize(0.0f);
}
void Bubble::setDestSize(float destSize){
    mDestSize = destSize;
}
void Bubble::threshold(){
    if(mDestSize>=0.5f*12){
        mDestSize = 12;
    } else {
        mDestSize = 0.0f;
    }
}

