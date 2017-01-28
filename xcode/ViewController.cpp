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
        
        int screenWidth = 1200;
        int screenHeight = 177;
        
        
        int numCols, numRows;
        
        
        
        int gridSizeX = 12.5;
        int gridSizeY = (sqrt(3))*(float)gridSizeX/2.0f;
        int offset = gridSizeX / 2;
        
        numCols = screenWidth/gridSizeX;
        numRows = screenHeight/gridSizeY + 2;

        
        mContainer = View::create();
        getView()->addSubview(mContainer);
        
        

        
        for(int i=0;i<numRows;i++){
            for(int j=0;j<numCols;j++){
                BubbleRef b = Bubble::create(12.5);
                bubbles.push_back(b);
                mContainer->addSubview(b);
                
                
                int x = j*gridSizeX + (i%2 * offset);
                int y = i*gridSizeY;
                
                b->setPosition(x,y);
                
            }
        }
        
        ci::app::getWindow()->getSignalKeyDown().connect(std::bind(&ViewController::keyPressed, this, std::placeholders::_1));

        
    }
    void ViewController::update()
    {
       // ci::app::console() << "ViewController::update()" << std::endl;
        
         
        
    }
    void ViewController::draw()
    {
        ci::app::console() << "ViewController::draw()" << std::endl;
    }
    void ViewController::keyPressed(ci::app::KeyEvent &key){
        ci::app::console() << key.getChar() << std::endl;
        int numBubbles;
        switch(key.getChar()){
                case 'r':
                case 'R':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    b->randomize();
                }
                break;
                case '0':
                case ')':
                    numBubbles = bubbles.size();
                    ci::app::console() << "num subviews: " << numBubbles << std::endl;
                    for(int i=0;i<numBubbles;i++){
                        BubbleRef b = bubbles.at(i);
                        b->shrink();
                    }
                break;
            case '1':
            case '!':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    b->setSize(12.5f);
                }
                break;

            case '5':
            case '%':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    b->setSize(6.25f);
                }
                break;

            case '-':
            case '_':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float yScale = sin(yPos/ci::app::getWindowHeight()*M_PI)*12.5f;
                    b->setSize(yScale);
                }
                break;

            case '/':
            case '?':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float xPos = b->getPosition().x;
                    float yScale = sin(yPos/ci::app::getWindowHeight()*M_PI-xPos)*12.5f;
                    b->setSize(yScale);
                }
                break;
            case '\\':
            case '|':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float xPos = b->getPosition().x;
                    float yScale = sin(yPos/ci::app::getWindowHeight()*M_PI+xPos/2.0f)*12.5f;
                    b->setSize(yScale);
                }
                break;
            case 'i':
            case 'I':
                numBubbles = bubbles.size();
                ci::app::console() << "num subviews: " << numBubbles << std::endl;
                for(int i=0;i<numBubbles;i++){
                    BubbleRef b = bubbles.at(i);
                    float yPos = b->getPosition().y;
                    float xPos = b->getPosition().x;
                    float yScale = sin(xPos/ci::app::getWindowWidth()*M_PI)*12.5f;
                    b->setSize(yScale);
                }
                break;


        }
    }
}
