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
	for (int i = 0; i < image.width; i++) 
	{
		for (int j = 0; j < image.height; j++) 
		{
			
			unsigned int avg = 0;

			
			for (int k = 0; k < 3; ++k) 
			{
				avg += image(i, j, k);
			}

			
			avg /=3;

			
			image(i, j, 0) = avg;
			image(i, j, 1) = avg;
			image(i, j, 2) = avg;
		}
	}
	
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

	/*float Si = (image.width - 1.0f) / (float)newWidth ;
	float Sj = (image.height - 1.0f) / (float)newHight ;*/

	float Si = (newWidth == 1) ? 0 : (image.width - 1.0f) / (newWidth - 1.0f);
	float Sj = (newHight == 1) ? 0 : (image.height - 1.0f) / (newHight - 1.0f);

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
	if (lighten) 
	{
		factor = 1.0 + (percent / 100.0);
	}
	else 
	{
		factor = 1.0 - (percent / 100.0);
		if (factor < 0)
		{
			factor = 0;
		}
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




			//// Setting new RGB values
			img(i, j, 0) = R;
			img(i, j, 1) = G;
			img(i, j, 2) = B;
		}
	}
}

void OilPaint(Image& img, int win = 5)
{
	Image out(img.width, img.height);
	int half = win / 2;

	for (int x = 0; x < img.width; x++)
	{
		for (int y = 0; y < img.height; y++)
		{
			vector<int> cnt(256, 0);
			vector<int> sumR(256, 0), sumG(256, 0), sumB(256, 0);


			for (int dx = -half; dx <= half; dx++)
			{
				for (int dy = -half; dy <= half; dy++)
				{
					int nx = x + dx, ny = y + dy;
					if (nx >= 0 && nx < img.width && ny >= 0 && ny < img.height)
					{
						int r = img(nx, ny, 0);
						int g = img(nx, ny, 1);
						int b = img(nx, ny, 2);

						int inten = (r + g + b) / 3;

						cnt[inten]++;
						sumR[inten] += r;
						sumG[inten] += g;
						sumB[inten] += b;
					}
				}
			}


			int best = 0, mx = 0;
			for (int i = 0; i < 256; i++)
			{
				if (cnt[i] > mx)
				{
					mx = cnt[i];
					best = i;
				}
			}

			out(x, y, 0) = sumR[best] / mx;
			out(x, y, 1) = sumG[best] / mx;
			out(x, y, 2) = sumB[best] / mx;
		}
	}

	img = out;
}

void SkewImage(Image& image)
{
	float angle;
	cout << "Enter skew angle (in degrees): ";
	cin >> angle;


	float radians = angle * 3.14159265 / 180.0;
	float skew = tan(radians);


	skew = -skew;


	int newWidth = image.width + abs(skew * image.height);
	Image result(newWidth, image.height);

	int offset;
	if (skew >= 0)
	{
		offset = 0;
	}
	else
	{
		offset = abs(skew * image.height);
	}


	for (int y = 0; y < image.height; y++)
	{
		int shift = skew * y;
		for (int x = 0; x < image.width; x++)
		{
			int new_X = x + shift + offset;

			if (new_X >= 0 && new_X < result.width)
			{
				for (int k = 0; k < 3; k++)
				{
					result(new_X, y, k) = image(x, y, k);
				}
			}
		}
	}

	image = result;
}
void SobelEdge(Image& img)
{
	for (int x = 0; x < img.width; x++)
	{
		for (int y = 0; y < img.height; y++)
		{
			int sum = 0;
			for (int c = 0; c < 3; c++)
			{
				sum += img(x, y, c);
			}
			int avg = sum / 3;
			img(x, y, 0) = img(x, y, 1) = img(x, y, 2) = avg;
		}
	}


	int gx[3][3] =
	{
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};

	int gy[3][3] =
	{
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};

	Image output(img.width, img.height);
	for (int x = 1; x < img.width - 1; x++)
	{
		for (int y = 1; y < img.height - 1; y++)
		{
			int gx_sum = 0, gy_sum = 0;


			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					int pix = img(x + dx, y + dy, 0);

					gx_sum += pix * gx[dx + 1][dy + 1];
					gy_sum += pix * gy[dx + 1][dy + 1];
				}
			}


			int edge = sqrt(gx_sum * gx_sum + gy_sum * gy_sum);


			if (edge > 255)
			{
				edge = 255;
			}
			if (edge < 0)
			{
				edge = 0;
			}
			edge = 255 - edge;
			output(x, y, 0) = output(x, y, 1) = output(x, y, 2) = edge;
		}
	}

	img = output;
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
	Image Resized = ImageResizeFilter(image, 2000, 2000);
	//InfraredImageFilter(image);
	SaveImage(Resized);
	//IR(image);
	//infrared_color(image);

	//mergeImages(image);

	//SaveImage(Cropped);

	//SaveImage(image);


	
}

