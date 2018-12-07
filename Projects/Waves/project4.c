
#include "wave.h"
#include "wave.c"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

//prototypes 
short charToShort();
void shortToChar(short number);
void reverse(short* left, short* right, int size);
short* speed(short* channel, double factor, int size);
void flip(short* left, short* right);
void fadeOut(short* left, short* right, int sampleRate, double seconds, int size);
void fadeIn(short* left, short* right, int sampleRate, double seconds, int size);
void volume(short* left, short* right, double scale, int size);
short* echo(short* channel, double delay, double scale, int size, int sampleRate); 

int main(int argc, char** argv) {

	int i; 

	WaveHeader header; //reads in the header information
	readHeader(&header);

	DataChunk data = header.dataChunk; //creats variable storing data chunk information
	int size = data.size/4; //size of the data variable
	FormatChunk format = header.formatChunk; //creates variable storing format chunk information

	//Error handling
	if (header.ID[0] != 'R' || header.ID[1] != 'I' || header.ID[2] != 'F' || header.ID[3] != 'F') 
		fprintf(stderr, "File is not a RIFF file\n"); 
	if (data.ID[0] != 'd' || data.ID[1] != 'a' || data.ID[2] != 't' || data.ID[3] != 'a')
		fprintf(stderr, "Data chunk is corrupted\n");
	if (format.ID[0] != 'f' || format.ID[1] != 'm' || format.ID[2] != 't' || format.ID[3] != ' ')
		fprintf(stderr, "Format chunk is corrupted\n");
	if (format.channels != 2)
		fprintf(stderr, "File is not stereo\n");
	if (format.sampleRate != 44100)
		fprintf(stderr, "File does not usre 44,100Hz sample rate\n");
	if (format.size != 16)
		fprintf(stderr, "File does not have 16-bit samples\n");
	
	short* left = malloc(sizeof(short) * size); //creates array to hold left channel information
	short* right = malloc(sizeof(short) * size); //creates array to hold right channel information 

	if (left == NULL || right == NULL)
		fprintf(stderr, "Program out of memory\n");
	
	for (i = 0; i < size; i++) { //read in the audio data
		left[i] = charToShort();
		right[i] = charToShort();
	}

	for (i = 1; argv[1][i] != '\0'; i++) { //for the length of the command
		
		if (argv[1][i] == 'r') //reverses the audio
			reverse(left, right, size - 1);

		else if (argv[1][i] == 's') { //changes the speed of the audio
			double factor = atof(argv[i + 1]); //reads the factor value from the user

			if (factor < 0) //error handling
				fprintf(stderr, "A positive number must be supplied for the speed change\n");
			
			left = speed(left, factor, size); 
			right = speed(right, factor, size);
			data.size = header.dataChunk.size / factor; //updates the data size
			header.size = sizeof(header) + data.size; //updates the header size
		}

		else if (argv[1][i] == 'f') //flips the left and right channels of the audio file
			flip(left, right);

		else if (argv[1][i] == 'o') { //fades out the end of the audio file
			double seconds = atof(argv[i + 1]); //reads the seconds value from the user
			
			if (seconds < 0) //error handling
				fprintf(stderr, "A positive number must be supplied for the fade out time\n");

			fadeOut(left, right, format.sampleRate, seconds, size);
		}

		else if (argv[1][i] == 'i') { //fades in the beginning of the audio file
			double seconds = atof(argv[i + 1]); //reads the seconds value from the user
			
			if (seconds < 0) //error handling
				fprintf(stderr, "A positive number must be supplied for the fade in time\n");

			fadeIn(left, right, format.sampleRate, seconds, size);
		}	

		else if (argv[1][i] == 'v') { //changes the volume of the audio file
			double scale = atof(argv[i + 1]); //reads the scaling value from the user

			if (scale < 0) //error handling
				fprintf(stderr, "A positive number must be supplied for the volume scale\n");

			volume(left, right, scale, size);
		}
		
		else if (argv[1][i] == 'e') { //adds an echo to the audio file
			double delay = atof(argv[i + 1]); //reads the delay value from the user
			double scale = atof(argv[i + 2]); //reads the scaling factor from the user

			if (delay < 0 || scale < 0) //error handling
				fprintf(stderr, "Positive numbers must be supplied for the echo delay and scale parameters\n");

			left = echo(left, delay, scale, size, format.sampleRate);
			right = echo(right, delay, scale, size, format.sampleRate);
			data.size = header.dataChunk.size + delay * format.sampleRate; //updates the data size		
			header.size = sizeof(WaveHeader) + header.dataChunk.size; //updates the header size
		}
			
		else //error handling, if the user entered an illegal command
			fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");	

	}

	writeHeader(&header); //writes the header information

	for (i = 0; i < size; i++) { //writes the audio information 
		shortToChar(left[i]);
		shortToChar(right[i]);
	}	

	free(left); 
	free(right);
		
	return 0;
}


short charToShort() { //changes two character values into one short value

	char one = getchar();
	char two = getchar();

	return ((short) (two << 8)) | one;
	
}

void shortToChar(short number) { //changes one short value back into two character values

	putchar((char)(number));
	putchar((char)(number >> 8));
		
}

void reverse(short* left, short* right, int size) { //reverses the audio 

	short temp;

	int start = 0;
	int end = size;

	while (start < end) { //three line swap for left channel
		temp = left[start];
		left[start] = left[end];
		left[end] = temp;
		start++;
		end--;
	}

	start = 0;
	end = size;

	while (start < end) { //three line swap for right channel
		temp = right[start];
		right[start] = right[end];
		right[end] = temp;
		start++;
		end--;
	}
}

short* speed(short* channel, double factor, int size) { //changes the speed of the audio file
	
	int i;

	short* data = malloc(sizeof(short) * (size / factor)); //allocates new array to hold longer or shorter audio data

	for (i = 0; i < size / factor; i++) 
		data[i] = channel[(int)(i * factor)]; //changes the audio data by the factor 

	return data;

} 

void flip(short* left, short* right) { //flips the two audio channels

	short* temp = left; //three line swaps the pointers 
	left = right;
	right = temp;

}

void fadeOut(short* left, short* right, int sampleRate, double seconds, int size) { //"fades out" the audio data
	
	int i;
	int j = 0;
	double fade = 0;

	int samples = (int)(seconds * sampleRate); //the number of samples the fading occurs

	int startFade = size - samples; //when the fade should begin

	if (size < samples) //if the size is less than the number of samples change the number of samples
		samples = size;

	if (startFade < 0) //if the fade is negative, start it at the beginning of the audio file
		startFade = 0;

	for (i = startFade, j = 0; i < size; i++, j++) { //starts at the fading point 
		fade = (1 - j/(samples - 1)) * (1 - j/(samples - 1)); //determines how much fade to add
		left[i] = (int)(left[i] * fade); //adds the fade to both channels
		right[i] = (int)(right[i] * fade);
	}
	
} 

void fadeIn(short* left, short* right, int sampleRate, double seconds, int size) { //"fades in" the audio data

	int i;

	int samples = (int)(seconds * sampleRate); //the number of samples the fading occurs
	double fade = 0;

	for (i = 0; i < samples; i++) { //starts at the beginning of the audio file until samples
		fade = (1 - (i/(samples - 1))) * (1 - (i/(samples - 1))); //determines how much fade to add
		left[i] = (int)(left[i] * fade); //adds the fade to both channels
		right[i] = (int)(right[i] * fade);
	}

}

void volume(short* left, short* right, double scale, int size) { //changes the volume of the audio

	int i;

	for (i = 0; i < size; i++) { //runs for the size of the data
		if (left[i] * scale > SHRT_MAX || right[i] * scale > SHRT_MAX) { //if adding the scale makes the data too high
			left[i] = SHRT_MAX; //set it to the max
			right[i] = SHRT_MAX;
		}
		else if (left[i] * scale < SHRT_MIN || right[i] * scale < SHRT_MIN) { //if adding the scale makes the data too low
			left[i] = SHRT_MIN; //set it to the min
			right[i] = SHRT_MIN;
		}
		else { //otherwise add the scaled data to both channels
			left[i] = left[i] * scale;
			right[i] = right[i] * scale;
		}
	}

}

short* echo(short* channel, double delay, double scale, int size, int sampleRate) { //"adds" an echo to the audio file

	int i;
	int index = 0;

	int samples = (int)(delay * sampleRate); //determines the samples when the echo starts

	short* data = malloc(sizeof(short) * (size + samples)); //allocates a new array to store echo data
	
	for (i = 0; i < size; i++) //copies over original audio data 
		data[i] = channel[i];

	for (i = samples; i < size + samples; i++) {//adds the delayed autio data to the new array
		data[i] = (int)(data[i] + (channel[index] * scale));
		index++;
	}
	
	return data;
	
}
































	
	

