#include "ViewController.h"

#include "cinder/app/App.h"

#include "poScene/ShapeView.h"
#include "poScene/TextView.h"



namespace aperture {
	ViewControllerRef ViewController::create()
	{
		ViewControllerRef node(new ViewController());
		node->setup();
		return node;
	}

	ViewController::ViewController()
	{
	}
    

	void ViewController::setup()
	{
        ci::app::console() << "ViewController::setup()" << std::endl;
        
        gridWidth = 1200;
        gridHeight = 177;
        
        
        margin = 25;
        gridSizeX = 12.5;
        gridSizeY = (sqrt(3))*(float)gridSizeX/2.0f;
        offset = gridSizeX / 2;
        
        numCols = (gridWidth-margin*2)/gridSizeX;
        numRows = (gridHeight-margin*2)/gridSizeY + 2;

        mAnimState = 0;
        skipFrames = 2;
        
        mContainer = View::create();
        getView()->addSubview(mContainer);
        
        

        
        for(int i=0;i<numRows;i++){
            for(int j=0;j<numCols;j++){
                BubbleRef b = Bubble::create(12.5);
                bubbles.push_back(b);
                bubbleBuffer.push_back(0);
                mContainer->addSubview(b);
                
                
                int x = j*gridSizeX + (i%2 * offset)+margin;
                int y = i*gridSizeY + margin;
                
                b->setPosition(x,y);
                
            }
        }
        
        ci::app::getWindow()->getSignalKeyDown().connect(std::bind(&ViewController::keyPressed, this, std::placeholders::_1));

        
    }
    void ViewController::update()
    {
       // ci::app::console() << "ViewController::update()" << std::endl;
        
        // update buffer
        for(int i=0;i<bubbles.size();i++){
            bubbleBuffer.at(i) = bubbles.at(i)->getDestSize();
        }
        
        if(ci::app::getElapsedFrames()%(1+skipFrames) == 0){
        switch(mAnimState){
            case 1:
                scrollUp();
                break;
            case 2:
                scrollRight();
                  break;
            case 3:
                scrollDown();
                  break;
            case 4:
                scrollLeft();
                
                break;
            case 5:
                life();
                break;
          
            case 0:
                // do nothing
                break;
            
        }
        }
        
         
        
    }
    void ViewController::draw()
    {
        ci::app::console() << "ViewController::draw()" << std::endl;
    }
    
    void ViewController::scrollUp(){
        int numBubbles = bubbles.size();

        float buffer[numCols*2];
        
        for(int i=0;i<numCols*2;i++){
            buffer[i] = bubbles.at(i)->getDestSize();
        }

                for(int i=0;i<numBubbles-numCols*2;i++){
            BubbleRef b = bubbles.at(i);
            BubbleRef b2 = bubbles.at(i+numCols*2);
            b->setDestSize(b2->getDestSize());
        }
        for(int i=0;i<numCols*2;i++){
             bubbles.at(numBubbles-numCols*2 + i)->setDestSize(buffer[i]);
        }
        
        
    }

    void ViewController::scrollDown(){
        int numBubbles = bubbles.size();
        
        float buffer[numCols*2];
        
        for(int i=0;i<numCols*2;i++){
            buffer[i] = bubbles.at(numBubbles-numCols*2 + i)->getDestSize();
        }
        
        for(int i=numBubbles-1;i>numCols*2-1;i--){
            BubbleRef b = bubbles.at(i);
            BubbleRef b2 = bubbles.at(i-numCols*2);
            b->setDestSize(b2->getDestSize());
        }
        for(int i=0;i<numCols*2;i++){
            bubbles.at(i)->setDestSize(buffer[i]);
        }
        
        
    }
    void ViewController::scrollLeft(){
    // TODO: implement me
    }
    void ViewController::scrollRight(){
    // TODO: implement me
    }
    
    void ViewController::threshold(){
        int numBubbles = bubbles.size();
        for(int i=0;i<numBubbles;i++){
            BubbleRef b = bubbles.at(i);
            if(b->getDestSize()<12.5f/2.0f){
                b->setDestSize(0.0f);
            } else {
                b->setDestSize(12.5f);
            }
        }
    }
    
    void ViewController::life(){
        int numBubbles = bubbles.size();
        for(int i=0;i<numBubbles;i++){
            BubbleRef b = bubbles.at(i);
            int neighborCount = 0;
            for(int j=-1;j<2;j++){
                for(int k=-1;k<2;k++){
                    int whichBubble = i+k+j*numCols;
                    if(whichBubble>0 && whichBubble<numBubbles){
                        if(bubbleBuffer.at(whichBubble)>12.5f/2.0f){
                            neighborCount++;
                        }
                    }
                    
                }
            }
            if((neighborCount>3 || neighborCount<2) && b->getDestSize()>12.5f/2.0f){
                b->setDestSize(0.0f);
            } else if(neighborCount==3 && b->getDestSize()<12.5f/2.0f){
                b->setDestSize(12.5f);
            }
            
            
        }

    }
    
    void ViewController::keyPressed(ci::app::KeyEvent &key){
        ci::app::console() << key.getChar() << std::endl;
        int numBubbles;
        ci::app::console() << key.getCode() << std::endl;
        switch(key.getCode()){
       
                case 'r':
                case 'R':
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    b->randomize();
                }
                break;
                case '0':
                case ')':
                    numBubbles = bubbles.size();
                    for(int i=0;i<numBubbles;i++){
                        BubbleRef b = bubbles.at(i);
                        b->shrink();
                    }
                break;
            case '1':
            case '!':
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    b->setDestSize(12.5f);
                }
                break;

            case '5':
            case '%':
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    b->setDestSize(6.25f);
                }
                break;

            case 269: // dash
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float yScale = sin(yPos/ci::app::getWindowHeight()*M_PI)*12.5f;
                    b->setDestSize(yScale);
                }
                break;

            case '/':
            case '?':
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float xPos = b->getPosition().x;
                    float yScale = sin(yPos/ci::app::getWindowHeight()*M_PI-(float)xPos/16.0f)*12.5f;
                    b->setDestSize(yScale);
                }
                break;
            case '\\':
            case '|':
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float xPos = b->getPosition().x;
                    float yScale = sin(yPos/ci::app::getWindowHeight()*M_PI+(float)xPos/2.0f)*12.5f;
                    b->setDestSize(yScale);
                }
                break;
            case 'i':
            case 'I':
                numBubbles = bubbles.size();
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float xPos = b->getPosition().x;
                    float yScale = sin(xPos/ci::app::getWindowWidth()*M_PI)*12.5f;
                    b->setDestSize(yScale);
                }
                break;
            case 'l':
            case 'L':
                life();
                break;
            case 't':
            case 'T':
                threshold();
                break;
            case 32: // press space
                mAnimState = 0; // stop animation
                break;
            case 273:
                mAnimState = 1; // scroll up
                break;
            case 274: // down
                mAnimState = 3;
                break;
            case 275: // right
                mAnimState = 2;
                break;
            case 276: // left
                mAnimState = 4;
                break;
            case 'c':
            case 'C':
                mAnimState = 5;
                break;
         


        }
    }
}
