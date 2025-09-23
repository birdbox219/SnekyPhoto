#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <cmath>
#include <algorithm>

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

// Done by Mahmoud Elsayed
Image CropingImageFilter(Image& image , int x , int y , int Cwidth , int Chight)
{
	

	cout << "\n Croping image ..." << endl;

	Image Cropping(Cwidth , Chight );

	if ((x + Cwidth) <= image.width && (y + Chight) <= image.height)
	{
		for (int i = 0; i < Cwidth; ++i)
		{
			for (int j = 0 ; j < Chight; ++j)
			{

				int offsetx = x + i;
				int offsety = y + j;
				for (int k = 0; k < 3; ++k)
				{
					
					Cropping(i, j, k) = image(offsetx, offsety, k);
					
				}


					
			}
		}
		cout << "Cropping image complete." << endl;
		return Cropping;
		

		
	}
	else
	{
		throw runtime_error("Image Dimesntion not compatiple");
	}
}


Image ImageResizeFilter(Image& image, int newWidth, int newHight)
{
	cout << "\n Resizing image ..." << endl;
	Image risizedImage(newWidth, newHight);

	float Si = image.width / (float)newWidth;
	float Sj = image.height / (float)newHight;

	for (int i = 0; i < newWidth; ++i)
	{
		for (int j = 0 ; j < newHight; ++j)
		{
			int changei = (int)(i * Si);
			int changej = (int)(j * Sj);
			for (int k = 0; k < 3; ++k)
			{
				risizedImage(i, j, k) = image(changei, changej, k);
			}
		}
	}
	cout << "Reszing image complete." << endl;
	return risizedImage;
}

template <typename T>
T clamp_value(T v, T lo, T hi)
{
	return v < lo ? lo : (v > hi ? hi : v);
}

void InfraredImageFilter(Image& image)
{

	double minIR = 255.0f;
	double maxIR = 0.0f;
	

	for (int i =  0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{

			unsigned char R = image(i, j, 0);
			unsigned char G = image(i, j, 1);
			unsigned char B = image(i, j, 2);

			double IR = 0.8 * R + 0.15 * G + 0.05 * B;

			if (IR < minIR) minIR = IR;
			if (IR > maxIR) maxIR = IR;


			/*float Rboost = min(255.0f, R * 1.5f);
			float GMIX = min(255.0f, (R + G) / 2.0f);
			float Blower = min(255.0f, B * 0.5f);

			image(i, j, 0) = (unsigned  char)Rboost;
			image(i, j, 1) = (unsigned char)GMIX;
			image(i, j, 2) = (unsigned char)Blower;*/


			//float intensity = 0.3f * R + 0.59f * G + 0.11f * B;

			//// step 2: boost
			//intensity = std::min(255.0f, intensity * 1.3f);

			//// step 3: map to red-based false color
			//unsigned char outR = (unsigned char)intensity;
			//unsigned char outG = (unsigned char)(intensity * 0.2f); // just a little green
			//unsigned char outB = 0; // no blue

			//image(i, j, 0) = outR;
			//image(i, j, 1) = outG;
			//image(i, j, 2) = outB;



		}
	}

	double range = (maxIR - minIR);
	if (range == 0.0) range = 1.0;

	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			unsigned char R = image(i, j, 0);
			unsigned char G = image(i, j, 1);
			unsigned char B = image(i, j, 2);

			double IR = 0.8 * R + 0.15 * G + 0.05 * B;

			double IRcompat = (IR - minIR) / range * 255.0;


			//// Replace the problematic line with the following:
			//unsigned char IRboost = static_cast<unsigned char>(clamp_value(IRcompat, 0.0, 255.0));
			//image(i, j, 0) = IRboost;
			//image(i, j, 1) = IRboost;
			//image(i, j, 2) = IRboost;

			unsigned char outR = static_cast<unsigned char>(
				clamp_value(IRcompat * 1.0, 0.0, 255.0)); // main red
			unsigned char outG = static_cast<unsigned char>(
				clamp_value(IRcompat * 0.2, 0.0, 255.0)); // small green
			unsigned char outB = 0; // no blue

			image(i, j, 0) = outR;
			image(i, j, 1) = outG;
			image(i, j, 2) = outB;


		}
	}
}

#include <algorithm> // For std::min and std::max

// Assuming 'Image' class has operator() like image(x, y, channel)
void InfraredImageFilter(Image& image)
{
	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			unsigned char R_orig = image(i, j, 0);
			unsigned char G_orig = image(i, j, 1);
			unsigned char B_orig = image(i, j, 2);

			// --- Step 1: Calculate an "IR Luminance" ---
			// A common way to simulate IR is to treat the original Red channel
			// as if it contains IR information, or combine R and G heavily.
			// For this specific red-dominant effect, let's use a combination
			// that emphasizes the brighter parts, especially if they were green/red.
			// Using max(R_orig, G_orig) tends to brighten foliage effectively.
			float ir_luminance_float = (float)std::max(R_orig, G_orig);

			// Further boost or adjust for contrast if needed.
			// This can make the bright areas "glow" more.
			ir_luminance_float = std::min(255.0f, ir_luminance_float * 1.5f);
			// Clamp to 255
			unsigned char ir_luminance = (unsigned char)ir_luminance_float;


			// --- Step 2: Assign to new channels ---
			// Set the Red channel to this new "IR Luminance".
			// For the green and blue channels, we want them to be very dark,
			// or subtly influenced by the original blue channel to add depth
			// to the shadows.

			// Red channel becomes the calculated IR brightness
			unsigned char new_R = ir_luminance;

			// Green and Blue channels are significantly reduced.
			// You can experiment here:
			// - Set them to 0 for pure red.
			// - Set them to a very small fraction of the original blue/green for subtle tint.
			// - Set them to a small fraction of the new red for a lighter red.

			// For the example image, green and blue are nearly 0 in bright areas,
			// but might retain some minimal information in dark areas.
			unsigned char new_G = (unsigned char)(std::min(255.0f, B_orig * 0.1f)); // Keep some original blue in shadows
			unsigned char new_B = (unsigned char)(std::min(255.0f, B_orig * 0.1f)); // Keep some original blue in shadows

			// If you want it absolutely pure red where bright, you could do:
			// unsigned char new_G = 0;
			// unsigned char new_B = 0;
			// But a tiny bit of original blue can give depth.

			image(i, j, 0) = new_R;
			image(i, j, 1) = new_G;
			image(i, j, 2) = new_B;
		}
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
	//FlipImageFilter(image, both);
	//CropingImageFilter(image, 500 , 500, 1000 , 1000);
	//Image Cropped = CropingImageFilter(image, 960 , 0, 960, 1080);
	//Image Resized = ImageResizeFilter(image, 1000, 1000);
	InfraredImageFilter(image);
	//SaveImage(Resized);

	//SaveImage(Cropped);

	SaveImage(image);


	
}
