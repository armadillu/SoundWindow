#include "testApp.h"
#include "stdio.h"

#define NUM_SAMPLES	256

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255,255,255);

	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)

	sampleRate 			= 44100;
	phase 				= 0;
	freq				= 0;
	time				= 0;
	
	volume				= 0.9f;
	lAudio = new float[NUM_SAMPLES];
	rAudio = new float[NUM_SAMPLES];
	ofSoundStreamSetup(2,0,this, sampleRate,NUM_SAMPLES, 4);

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	soundWin.create(NUM_SAMPLES, SoundWindow::SOUND_WINDOW_BLACKMAN_HARRIS);
	num = 10;

}


//--------------------------------------------------------------
void testApp::update(){
	
	time += 1./ofGetFrameRate();
}


//--------------------------------------------------------------
void testApp::draw(){


	// draw the left:
	ofSetColor(0x333333);
	ofRect(10,100,NUM_SAMPLES,200);
	ofSetColor(0xFFFFFF);
	for (int i = 0; i < NUM_SAMPLES; i++){
		ofLine(10+i,200,10+i,200+lAudio[i]*100.0f);
	}

	// draw the right:
	ofSetColor(0x333333);
	ofRect(20+NUM_SAMPLES,100,NUM_SAMPLES,200);
	ofSetColor(0xFFFFFF);
	for (int i = 0; i < NUM_SAMPLES; i++){
		ofLine(20+NUM_SAMPLES+i,200,20+NUM_SAMPLES+i,200+rAudio[i]*100.0f);
	}

	ofSetColor(0x333333);
	char reportString[255];
	sprintf(reportString, "freq: %f  phase: %f  window: %s\n[+ / -] to choose window", freq, phase, soundWin.windowName());

	ofDrawBitmapString(reportString,80,380);

}


//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){

	for (int i = 0; i < bufferSize; i++){
		
		float loopPercent = i / (float)bufferSize;
		
		float sample;
		
//		sample =  sin (  loopPercent * freq * 0.1 + phase * time * 0.1);
		
//		int steps = 1 + phase * 0.05;
//		sample = -1 + ((int)(freq*loopPercent)%(steps) ) / (steps*0.5f);
		
		sample = sin ( loopPercent * 0.2 * freq * (1 + 0.3 * sin ( ( mouseX / (float)ofGetWidth()) * 15 * time ) ) );

		
		//monkey too loud!
		//sample = phase  * 0.1* cos ( loopPercent * freq );
		
				
//quantize sample
//		int q = num;
//		if (q < 1) q = 1;
//		sample = ((int)(sample * q) %q ) / (float)q;

		
		//im on monkey branch!
		
		
		

//copy to buffer
		
		float * hanwin = soundWin.getWindow();
		
		lAudio[i] = output[i*nChannels    ] = sample * volume * hanwin[i];
		rAudio[i] = output[i*nChannels + 1] = sample * volume * hanwin[i];
	}

}


void testApp::keyPressed( int key ){

	switch (key) {
		
		case '+':
			num++;
			break;

		case '-':
			num--;
			break;
	}
	
	SoundWindow::SoundWindowType type = (SoundWindow::SoundWindowType)((SoundWindow::SOUND_WINDOW_HANNING) + (num%7));
	soundWin.create(NUM_SAMPLES, type);

}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	int width = ofGetWidth();
	float height = (float)ofGetHeight();
	float heightPct = ((height-y) / height);
	targetFrequency = 2000.0f * heightPct;
	
	freq = mouseY;
	phase = mouseX;
}
