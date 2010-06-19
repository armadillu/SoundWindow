#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "SoundWindow.h"

class testApp : public ofBaseApp{

	public:


		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
		void keyPressed( int key );

		void audioRequested (float * input, int bufferSize, int nChannels);

		int		sampleRate;
		float 	volume;

		float 	* lAudio;
		float   * rAudio;

		//------------------- for the simple sine wave synthesis
		float 	targetFrequency;
		float	freq;
		float 	phase;
	
		double time;
	
		int		num;
	
		SoundWindow soundWin;
};

#endif
