#include <iostream>
#include "Image_Class.h"
#include <vector>

using namespace std;

Image LoadImage()
{
	string filename;
	cout << "Enter Image name with it's extention: ";
	try {
		cin >> filename;
		Image image(filename);
		return image;

	}
	catch (const std::exception&)
	{
		cout << "Failed To load";
		
	}
		
}


void SaveImage(Image& image)
{
	string filename;
	cout << "\nPls enter image name to store new image\n";
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";
	cin >> filename;
	try
	{
		image.saveImage(filename);

		cout << "Image saved successfully";
	}
	catch (const std::exception&)
	{
		cout << "Image FAILED to save";
	}
}


void GrayScaleFilter(Image& image)
{
	
	cout << "\nConverting image to grayscale..." << endl;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			// Use a larger type like unsigned int to prevent overflow when summing up channel values
			unsigned int avg = 0;

			// Accumulate pixel values for all channels (R, G, B)
			for (int k = 0; k < 3; ++k) {
				avg += image(i, j, k);
			}

			// Calculate the average value and cast it back to a byte
			unsigned char gray_value = avg / 3;

			// Set all channels to the average value to create a gray pixel
			image(i, j, 0) = gray_value;
			image(i, j, 1) = gray_value;
			image(i, j, 2) = gray_value;
		}
	}
	cout << "Grayscale conversion complete." << endl;
	
}


void BlackAndWhiteFilter(Image& image)
{
	cout << "\nConverting image to BlackaAndWhite..." << endl;

	unsigned int threshold = 128;

	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			unsigned int brightnes = 0;
			
			
			for (int k = 0; k < 3; ++k) 
			{
				 brightnes+= image(i, j, k);
			}

			unsigned int avg   = brightnes / 3;

			unsigned char whitVlaue = 255;
			unsigned char blackVlaue = 0;

			if (avg >= threshold)
			{
				image(i, j, 0) = whitVlaue;
				image(i, j, 1) = whitVlaue;
				image(i, j, 2) = whitVlaue;
			}

			else
			{
				image(i, j, 0) = blackVlaue;
				image(i, j, 1) = blackVlaue;
				image(i, j, 2) = blackVlaue;
			}


		}
	}
	cout << "BlackAndWhite conversion complete." << endl;
}

void BlackAndWhiteOtsualgorithm(Image& image)
{
	vector <int> histogram(256, 0);
	cout << "\nConverting image to BlackaAndWhite using Otsu algorithm..." << endl;
	int totalPixels = image.width * image.height;
	int index = 0; 
	vector <unsigned char> brightnesLevels(totalPixels);
	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			unsigned int brightnes = 0;
			for (int k = 0; k < 3; ++k)
			{
				brightnes += image(i, j, k);
			}
			unsigned int avg = brightnes / 3;

			brightnesLevels[index] = avg;
			histogram[avg]++;
		}
	}

	//Otsu algorithm
	double sumAll = 0;  // total intensity mass
	for (int t = 0; t < 256; ++t) sumAll += t * histogram[t];

	double sumB = 0;  // background intensity sum
	int wB = 0;       // background pixel count
	int wF = 0;       // foreground pixel count

	double maxVar = 0;
	int bestThreshold = 0;

	for (int t = 0; t < 256; ++t) {
		wB += histogram[t];                // background weight (count <= t)
		if (wB == 0) continue;        // no background pixels yet -> skip

		wF = totalPixels - wB;        // foreground weight (count > t)
		if (wF == 0) break;           // all pixels are background -> stop

		sumB += t * histogram[t];          // sum of intensities for background

		double mB = sumB / wB;               // mean intensity of background
		double mF = (sumAll - sumB) / wF;    // mean intensity of foreground

		double betweenVar = (double)wB * (double)wF * (mB - mF) * (mB - mF);

		if (betweenVar > maxVar) {
			maxVar = betweenVar;
			bestThreshold = t;
		}
	}

	index = 0;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j, ++index) {
			unsigned char gray = brightnesLevels[index];
			unsigned char val = (gray >= bestThreshold) ? 255 : 0;
			image(i, j, 0) = val;
			image(i, j, 1) = val;
			image(i, j, 2) = val;
		}
	}


}


//Done by MahmoudELsayed
void IvertImageFilter(Image& image)
{
	cout << "\nInverting image colors..." << endl;
	for (int i = 0;i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			for (int k = 0; k < 3; ++k) { 
				image(i, j, k) = 255 - image(i, j, k); 
			}
		}
	}
	cout << "Color inversion complete." << endl;
}



void FlipImageFilterV(Image& image)
{
	unsigned char tmpImage;
	cout << "\nFlipping image vertically..." << endl;
	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height / 2;++j )
		{
			for (int k = 0; k < 3; ++k)
			{
				tmpImage = image(i, j, k);
				image(i, j, k) = image(i, image.height - j - 1, k);
				image(i, image.height - j - 1, k) = tmpImage;
			}
		}
	}
		



	cout << "Vertical flip complete." << endl;
}
//Done by MahmoudELsayed
void FlipImageFilterH(Image& image)
{
	unsigned char tmpImage;
	cout << "\nFlipping image horizontaly..." << endl;
	for (int i = 0; i < image.width / 2; ++i)
	{
		for (int j = 0; j < image.height ;++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				tmpImage = image(i, j, k);
				image(i, j, k) = image(image.width - i - 1, j , k);
				image(image.width - i - 1, j, k) = tmpImage;
			}
		}
	}




	cout << "horizontal flip complete." << endl;
}

/*
ImageFlipingStateMachine
we will later implment other Fliping filters like 90-Degrees mirror diagonal, etc..
*/


enum FlipType
{
	None = 0,
	Vertical,
	Horizontal,
	both,
};

//Done by MahmoudELsayed


void FlipImageFilter(Image& image, FlipType flip)
{
	switch (flip)
	{
	case None:
		// do nothing
		break;
	case Vertical:
		FlipImageFilterV(image);
		break;
	case Horizontal:
		FlipImageFilterH(image);
		break;
	case both:

		FlipImageFilterV(image);
		FlipImageFilterH(image);

		break;
	}
}
	

int main()
{
	Image image = LoadImage();

	/*GrayScaleFilter(image);*/

	//BlackAndWhiteFilter(image);
	//BlackAndWhiteOtsualgorithm(image);
	//IvertImageFilter(image);
	//FlipImageFilter(image);
	//FlipImageFilterH(image);
	FlipImageFilter(image, both);

	SaveImage(image);


	
}
