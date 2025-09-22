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
	// 1. Build histogram of brightness
	std::vector<int> hist(256, 0);  // 256 bins for 0-255

	int totalPixels = image.width * image.height;

	// compute grayscale + histogram
	std::vector<unsigned char> grayVals(totalPixels); // store brightness
	int idx = 0;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j, ++idx) {
			// weighted brightness for human eye perception
			unsigned char gray =
				static_cast<unsigned char>(0.299 * image(i, j, 0) +
					0.587 * image(i, j, 1) +
					0.114 * image(i, j, 2));
			grayVals[idx] = gray;
			hist[gray]++;
		}
	}

	// 2. Otsu's threshold
	double sumAll = 0;  // total intensity mass
	for (int t = 0; t < 256; ++t) sumAll += t * hist[t];

	double sumB = 0;  // background intensity sum
	int wB = 0;       // background pixel count
	int wF = 0;       // foreground pixel count

	double maxVar = 0;
	int bestThreshold = 0;

	for (int t = 0; t < 256; ++t) {
		wB += hist[t];                // background weight
		if (wB == 0) continue;

		wF = totalPixels - wB;         // foreground weight
		if (wF == 0) break;

		sumB += t * hist[t];

		double mB = sumB / wB;         // mean background
		double mF = (sumAll - sumB) / wF; // mean foreground

		double betweenVar = (double)wB * (double)wF * (mB - mF) * (mB - mF);

		if (betweenVar > maxVar) {
			maxVar = betweenVar;
			bestThreshold = t;
		}
	}

	// 3. Apply threshold to image
	idx = 0;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j, ++idx) {
			unsigned char gray = grayVals[idx];

			unsigned char val = (gray >= bestThreshold) ? 255 : 0;

			image(i, j, 0) = val;
			image(i, j, 1) = val;
			image(i, j, 2) = val;
		}
	}



}

int main()
{
	Image image = LoadImage();

	/*GrayScaleFilter(image);*/

	//BlackAndWhiteFilter(image);
	BlackAndWhiteOtsualgorithm(image);

	SaveImage(image);


	
}
