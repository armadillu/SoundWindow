#ifndef SOUND_WINDOW
#define SOUND_WINDOW
/*
 *  SoundWindow.h
 *  openFrameworks
 *
 *  Created by Oriol Ferrer Mesià on 23/08/09.
 *  Copyright 2009 uri.cat. All rights reserved.
 *
 */

#include <Math.h>	//M_PI



class SoundWindow{

	public:

		typedef enum{
			SOUND_WINDOW_HANNING = 100,
			SOUND_WINDOW_HAMMING,
			SOUND_WINDOW_TRIANGULAR,
			SOUND_WINDOW_GAUSS,
			SOUND_WINDOW_BLACKMAN_HARRIS,
			SOUND_WINDOW_FLAT,
			SOUND_WINDOW_RANDOM
	
		}SoundWindowType; 

		SoundWindow();
		~SoundWindow();
		
		void	create(int length, SoundWindowType windowType = SOUND_WINDOW_HANNING);
		float*	getWindow();
		int		getWindowLength();
		char*	windowName();

	private:
	
		float	hanningAtPoint(int point, int numSamples);
		float	hammingAtPoint(int point, int numSamples);
		float	triangularAtPoint(int point, int numSamples);
		float	gaussAtPoint(int point, int numSamples);
		float	blackmanHarrisAtPoint(int point, int numSamples);
		float	randomAtPoint(int point, int numSamples);
	
		bool	inited;
		int		numSamples;
		float*	soundWindow;
		SoundWindowType type;
		
};

#endif