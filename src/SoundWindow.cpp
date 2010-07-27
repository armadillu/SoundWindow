/*
 *  SoundWindow.cpp
 *  openFrameworks
 *
 *  Created by Oriol Ferrer Mesià on 23/08/09.
 *  Copyright 2009 uri.cat. All rights reserved.
 *
 */

#include "SoundWindow.h"


SoundWindow::SoundWindow(){

	soundWindow = NULL;
	numSamples = 0;
}


SoundWindow::~SoundWindow(){

	if (soundWindow != NULL)
		delete[]soundWindow;
	
	numSamples = 0;
}


void SoundWindow::create(int length, SoundWindowType windowType){

	if (soundWindow != NULL){
		delete[]soundWindow;		  
	}

	type = windowType;
	numSamples = length;
	soundWindow = new float[length]; 

	switch (windowType) {

		case SOUND_WINDOW_HANNING:
			for (int i=0; i< length; i++)
				soundWindow[i] = hanningAtPoint(i, length);
			break;

		case SOUND_WINDOW_HAMMING:
			for (int i=0; i< length; i++)
				soundWindow[i] = hammingAtPoint(i, length);
			break;

		case SOUND_WINDOW_TRIANGULAR:
			for (int i=0; i< length; i++)
				soundWindow[i] = triangularAtPoint(i, length);
			break;

		case SOUND_WINDOW_GAUSS:
			for (int i=0; i< length; i++)
				soundWindow[i] = gaussAtPoint(i, length);
			break;

		case SOUND_WINDOW_BLACKMAN_HARRIS:
			for (int i=0; i< length; i++)
				soundWindow[i] = blackmanHarrisAtPoint(i, length);
			break;

		case SOUND_WINDOW_FLAT:
			for (int i=0; i< length; i++)
				soundWindow[i] = 1.0f;
			break;

		case SOUND_WINDOW_RANDOM:
			for (int i=0; i< length; i++)
				soundWindow[i] = randomAtPoint(i, length);
			break;

		case SOUND_WINDOW_ALMOST_FLAT:
			for (int i=0; i< length; i++){
				soundWindow[i] =  powf( 2 * hanningAtPoint(i, length), 0.3 );
				soundWindow[i] = powf( soundWindow[i] , 1.5); 
				if ( soundWindow[i] > 1.0f ) soundWindow[i] = 1.0f;
			}
			break;
			;
		default:
			for (int i=0; i< length; i++)
				soundWindow[i] = 1.0f;
			printf("Undefined SoundWindowType!\n");
			break;
	}
		
}


float SoundWindow::hanningAtPoint(float point, int numSamples){
	return 0.5f * ( 1.0f - cosf ( (2.0f * M_PI * point) / ( (float)numSamples - 1.0f) ) );
}


float SoundWindow::hammingAtPoint(int point, int numSamples){
	return 0.54f - 0.46f * cosf ( (2.0f * M_PI * point) / ( (float)numSamples - 1.0f) ) ;
}


float SoundWindow::triangularAtPoint(int point, int numSamples){
 	return ( 2.0f / numSamples ) * ( ( numSamples * 0.5f ) - fabs( point - ( numSamples -1.0f ) * 0.5f ) );
}


float SoundWindow::gaussAtPoint(int point, int numSamples){
	
	float bellW = 0.4f;
	return powf ( M_E, -0.5f * powf ( ( point - ( numSamples - 1 ) * 0.5f ) / ( bellW * ( numSamples - 1 ) * 0.5f ) , 2.0f ) );
}


float SoundWindow::blackmanHarrisAtPoint(int point, int numSamples){
	
	return 0.35875f		- 0.48829f * cosf( 2.0f * M_PI * point / (numSamples-1) ) 
						+ 0.14128f * cosf( 4.0f * M_PI * point / (numSamples-1) ) 
						- 0.01168f * cosf( 6.0f * M_PI * point / (numSamples-1) );
}


float SoundWindow::randomAtPoint(int point, int numSamples){
	return rand()%1000 / 1000.0f;
}




float* SoundWindow::getWindow(){
	return soundWindow;
}


int SoundWindow::getWindowLength(){
	return numSamples;
}


char* SoundWindow::windowName(){

	if ( soundWindow != NULL ){

		switch (type) {
			case SOUND_WINDOW_HANNING: return "Hanning";
			case SOUND_WINDOW_HAMMING: return "Hamming";
			case SOUND_WINDOW_TRIANGULAR: return "Triangular";
			case SOUND_WINDOW_GAUSS: return "Gauss";
			case SOUND_WINDOW_BLACKMAN_HARRIS: return "Blackman Harris";
			case SOUND_WINDOW_FLAT: return "Flat";
			case SOUND_WINDOW_ALMOST_FLAT: return "Amost Flat";
			case SOUND_WINDOW_RANDOM: return "Random";
			default: return "Unknown SoundWindow Type";
		}
		
	}else
		return "Not Inited!";
}