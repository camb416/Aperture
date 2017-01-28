#pragma once

#include "poScene/ViewController.h"

namespace aperture {

	class ViewController;
	typedef std::shared_ptr<ViewController> ViewControllerRef;

	class ViewController
		: public po::scene::ViewController
	{
	public:
		static ViewControllerRef create();

		void setup();

	protected:
		ViewController();

	private:
		//	Container to hold all the squares
		po::scene::ViewRef mContainer;


	};
}
