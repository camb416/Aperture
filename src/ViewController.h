#pragma once

#include "poScene/ViewController.h"

#include "Bubble.h"

namespace aperture {

	class ViewController;
	typedef std::shared_ptr<ViewController> ViewControllerRef;

	class ViewController
		: public po::scene::ViewController
	{
	public:
		static ViewControllerRef create();

		void setup();
        void update();
        void draw();
        


	protected:
		ViewController();

	private:
        

		//	Container to hold all the squares
		po::scene::ViewRef mContainer;
        
        void keyPressed(ci::app::KeyEvent &key);
        
        std::vector<BubbleRef> bubbles;
        std::vector<float> bubbleBuffer;
        
        void scrollUp();
        void scrollRight();
        void scrollDown();
        void scrollLeft();
        void life();
        void threshold();
        
        int screenWidth, screenHeight;
        int gridWidth, gridHeight;
        
        
        int numCols, numRows;
        
        
        
        int gridSizeX;
        int gridSizeY;
        int offset;
        
        int margin;
        
        int mAnimState;
        int skipFrames;

        



	};
}
