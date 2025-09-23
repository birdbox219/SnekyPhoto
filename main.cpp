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
// merged filter done by Adham.

Image resizeImage(const Image& original, int targetwidth, int targetheight)
{

	Image resized(targetwidth, targetheight);
	int originalwidth = original.width;
	int originalheight = original.height;
	for (int new_x = 0;new_x < targetwidth;new_x++)
	{
		for (int new_y = 0;new_y < targetheight;new_y++)
		{
			int old_x = new_x * originalwidth / targetwidth;
			int old_y = new_y * originalheight / targetheight;
			for (int k = 0; k < 3; k++)
			{
				resized(new_x, new_y, k) = original(old_x, old_y, k);
			}
		}
	}
	return resized;
}







//template <typename T>
//T clamp_value(T v, T lo, T hi)
//{
//	return v < lo ? lo : (v > hi ? hi : v);
//}
//
//void InfraredImageFilter(Image& image)
//{
//
//	double minIR = 255.0f;
//	double maxIR = 0.0f;
//	
//
//	for (int i =  0; i < image.width; ++i)
//	{
//		for (int j = 0; j < image.height; ++j)
//		{
//
//			unsigned char R = image(i, j, 0);
//			unsigned char G = image(i, j, 1);
//			unsigned char B = image(i, j, 2);
//
//			double IR = 0.8 * R + 0.15 * G + 0.05 * B;
//
//			if (IR < minIR) minIR = IR;
//			if (IR > maxIR) maxIR = IR;
//
//
//			/*float Rboost = min(255.0f, R * 1.5f);
//			float GMIX = min(255.0f, (R + G) / 2.0f);
//			float Blower = min(255.0f, B * 0.5f);
//
//			image(i, j, 0) = (unsigned  char)Rboost;
//			image(i, j, 1) = (unsigned char)GMIX;
//			image(i, j, 2) = (unsigned char)Blower;*/
//
//
//			//float intensity = 0.3f * R + 0.59f * G + 0.11f * B;
//
//			//// step 2: boost
//			//intensity = std::min(255.0f, intensity * 1.3f);
//
//			//// step 3: map to red-based false color
//			//unsigned char outR = (unsigned char)intensity;
//			//unsigned char outG = (unsigned char)(intensity * 0.2f); // just a little green
//			//unsigned char outB = 0; // no blue
//
//			//image(i, j, 0) = outR;
//			//image(i, j, 1) = outG;
//			//image(i, j, 2) = outB;
//
//
//
//		}
//	}
//
//	double range = (maxIR - minIR);
//	if (range == 0.0) range = 1.0;
//	for (int i = 0; i < image.width; ++i)
//	{
//		for (int j = 0; j < image.height; ++j)
//		{
//			unsigned char R = image(i, j, 0);
//			unsigned char G = image(i, j, 1);
//			unsigned char B = image(i, j, 2);
//
//			double IR = 0.8 * R + 0.15 * G + 0.05 * B;
//
//			double IRcompat = (IR - minIR) / range * 255.0;
//
//
//			//// Replace the problematic line with the following:
//			//unsigned char IRboost = static_cast<unsigned char>(clamp_value(IRcompat, 0.0, 255.0));
//			//image(i, j, 0) = IRboost;
//			//image(i, j, 1) = IRboost;
//			//image(i, j, 2) = IRboost;
//
//			unsigned char outR = static_cast<unsigned char>(
//				clamp_value(IRcompat * 1.0, 0.0, 255.0)); // main red
//			unsigned char outG = static_cast<unsigned char>(
//				clamp_value(IRcompat * 0.2, 0.0, 255.0)); // small green
//			unsigned char outB = 0; // no blue
//
//			image(i, j, 0) = outR;
//			image(i, j, 1) = outG;
//			image(i, j, 2) = outB;
//
//
//		}
//	}
//}

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

void mergeImages()
{
	Image img1, img2, result;
	string name1, name2;

	cout << "enter first image filename: ";
	cin >> name1;
	cout << "enter second image filename: ";
	cin >> name2;

	if (!img1.loadNewImage(name1) || !img2.loadNewImage(name2))
	{
		cout << "failed to load images\n";
		return;
	}

	if (img1.width != img2.width || img1.height != img2.height)
	{
		cout << "images not same size.\n";
		cout << "choose option:\n";
		cout << "1 - merge common area only\n";
		cout << "2 - resize smaller image to match larger one\n";
		int option;
		cin >> option;

		if (option == 1)
		{
			int minw = min(img1.width, img2.width);
			int minh = min(img1.height, img2.height);

			result = Image(minw, minh);

			for (int i = 0; i < minw; i++)
			{
				for (int j = 0; j < minh; j++)
				{
					for (int c = 0; c < 3; c++)
					{
						result(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
					}
				}
			}
		}
		else if (option == 2)
		{
			if (img1.width > img2.width || img1.height > img2.height)
			{
				img2 = resizeImage(img2, img1.width, img1.height);
				result = Image(img1.width, img1.height);
			}
			else
			{
				img1 = resizeImage(img1, img2.width, img2.height);
				result = Image(img2.width, img2.height);
			}

			for (int i = 0; i < result.width; i++)
			{
				for (int j = 0; j < result.height; j++)
				{
					for (int c = 0; c < 3; c++)
					{
						result(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
					}
				}
			}
		}
	}
	else
	{
		result = Image(img1.width, img1.height);

		for (int i = 0; i < img1.width; i++)
		{
			for (int j = 0; j < img1.height; j++)
			{
				for (int c = 0; c < 3; c++)
				{
					result(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
				}
			}
		}
	}

	result.saveImage("merged.png");
	cout << " merged image saved as merged.png\n";
}

// brightness filter done by adham.
void AdjustBrightness(Image& img, bool lighten, int percent)
{
	double factor;
	if (lighten) {
		factor = 1.0 + (percent / 100.0);
	}
	else {
		factor = 1.0 - (percent / 100.0);
		if (factor < 0) factor = 0;
	}

	for (int i = 0; i < img.width; i++)
	{
		for (int j = 0; j < img.height; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				int newval = img(i, j, k) * factor;
				if (newval > 255) newval = 255;
				if (newval < 0) newval = 0;
				img(i, j, k) = newval;
			}
		}
	}
}
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

void infrared_color(Image& img)
{
	for (int i = 1; i < img.width; i++) {
		for (int j = 1; j < img.height; j++) {
			int R = img(i, j, 0);
			int G = img(i, j, 1);
			int B = img(i, j, 2);

			R = 255;
			G = 255 - G;
			B = 255 - B;

			// Further boost or adjust for contrast if needed.
			// This can make the bright areas "glow" more.
			ir_luminance_float = std::min(255.0f, ir_luminance_float * 1.5f);
			// Clamp to 255
			unsigned char ir_luminance = (unsigned char)ir_luminance_float;

			/*R = min(255.0f, R * 1.5f);
			G = min(255.0f, R - G);
			B = min(255.0f, B * 0.3f);*/

			//float new_R = std::min(255.0f, R * 1.5f);
			//float new_G = std::min(255.0f, new_R - G); // Use the modified R for this calculation.
			//float new_B = 255.0f - B;

			// Explicitly cast the float results back to an integer type
			// before assigning them to the image pixels.
			/*img(i, j, 0) = static_cast<int>(new_R);
			img(i, j, 1) = static_cast<int>(new_G);
			img(i, j, 2) = static_cast<int>(new_B);*/

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

			//// Setting new RGB values
			img(i, j, 0) = R;
			img(i, j, 1) = G;
			img(i, j, 2) = B;
		}
	}
}

//inline double clampd(double v, double lo = 0.0, double hi = 1.0) {
//	if (v < lo) return lo;
//	if (v > hi) return hi;
//	return v;
//}
//inline double lerp(double a, double b, double t) { return a + (b - a) * t; }
//
//// Small struct for palette mapping
//struct RGBf { double r, g, b; };
//
//// Multi-stop red-hot palette
//static RGBf colormap_redhot(double t) {
//	t = clampd(t, 0.0, 1.0);
//
//	if (t < 0.05) { return { 1.0, 0.98, 0.92 }; }   // pale cream
//	if (t > 0.95) { return { 1.0, 1.0, 1.0 }; }     // white core
//
//	double t2 = (t - 0.05) / 0.90;
//	const double stops[] = { 0.0, 0.25, 0.55, 0.8, 1.0 };
//	const double rv[] = { 0.0, 0.3, 1.0, 1.0, 1.0 };
//	const double gv[] = { 0.0, 0.02, 0.0, 0.6, 1.0 };
//	const double bv[] = { 0.0, 0.0, 0.0, 0.0, 0.9 };
//
//	int seg = 0;
//	while (seg < 4 && t2 > stops[seg + 1]) ++seg;
//	double segT = (t2 - stops[seg]) / (stops[seg + 1] - stops[seg]);
//	return {
//		lerp(rv[seg], rv[seg + 1], segT),
//		lerp(gv[seg], gv[seg + 1], segT),
//		lerp(bv[seg], bv[seg + 1], segT)
//	};
//}
//
//// Box blur (simple, separable)
//static void blur_channel(std::vector<double>& img, int w, int h, int radius) {
//	if (radius <= 0) return;
//	std::vector<double> tmp(w * h, 0.0);
//
//	// horizontal
//	for (int y = 0; y < h; ++y) {
//		double sum = 0.0;
//		int row = y * w;
//		for (int x = 0; x <= radius && x < w; ++x) sum += img[row + x];
//		for (int x = 0; x < w; ++x) {
//			int addX = std::min(w - 1, x + radius);
//			int subX = std::max(0, x - radius - 1);
//			if (x > 0) { sum += img[row + addX]; sum -= img[row + subX]; }
//			int left = std::max(0, x - radius);
//			int right = std::min(w - 1, x + radius);
//			tmp[row + x] = sum / (right - left + 1);
//		}
//	}
//	// vertical
//	for (int x = 0; x < w; ++x) {
//		double sum = 0.0;
//		for (int y = 0; y <= radius && y < h; ++y) sum += tmp[y * w + x];
//		for (int y = 0; y < h; ++y) {
//			int addY = std::min(h - 1, y + radius);
//			int subY = std::max(0, y - radius - 1);
//			if (y > 0) { sum += tmp[addY * w + x]; sum -= tmp[subY * w + x]; }
//			int top = std::max(0, y - radius);
//			int bottom = std::min(h - 1, y + radius);
//			img[y * w + x] = sum / (bottom - top + 1);
//		}
//	}
//}
//
//// Percentile helper
//static double percentile(std::vector<double> arr, double p) {
//	std::sort(arr.begin(), arr.end());
//	double idx = p * (arr.size() - 1);
//	int i0 = (int)std::floor(idx), i1 = (int)std::ceil(idx);
//	if (i0 == i1) return arr[i0];
//	double t = idx - i0;
//	return lerp(arr[i0], arr[i1], t);
//}
//
//// === MAIN FUNCTION ===
//void IR(Image& image) {
//	int w = image.width, h = image.height, N = w * h;
//	std::vector<double> ir(N);
//
//	// Step 1: IR luminance
//	for (int y = 0;y < h;++y) {
//		for (int x = 0;x < w;++x) {
//			unsigned char R = image(x, y, 0);
//			unsigned char G = image(x, y, 1);
//			unsigned char B = image(x, y, 2);
//			ir[y * w + x] = clampd((0.8 * R + 0.15 * G + 0.05 * B) / 255.0);
//		}
//	}
//
//	// Step 2: percentile stretch
//	double low = percentile(ir, 0.005);
//	double high = percentile(ir, 0.999);
//	if (high - low < 1e-6) high = low + 1e-6;
//	for (double& v : ir) { v = clampd((v - low) / (high - low)); }
//
//	// Step 3: gamma
//	double gamma = 0.85;
//	for (double& v : ir) v = pow(v, gamma);
//
//	// Step 4: bloom
//	std::vector<double> bright(N);
//	for (int i = 0;i < N;++i) bright[i] = (ir[i] > 0.6) ? (ir[i] - 0.6) / 0.4 : 0.0;
//	blur_channel(bright, w, h, 25);
//	for (int i = 0;i < N;++i) ir[i] = clampd(ir[i] + bright[i] * 1.2);
//
//	// Step 5: color map and write back
//	for (int y = 0;y < h;++y) {
//		for (int x = 0;x < w;++x) {
//			int idx = y * w + x;
//			RGBf c = colormap_redhot(ir[idx]);
//			image(x, y, 0) = (unsigned char)(clampd(c.r) * 255);
//			image(x, y, 1) = (unsigned char)(clampd(c.g) * 255);
//			image(x, y, 2) = (unsigned char)(clampd(c.b) * 255);
//		}
//	}
//}

	

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
