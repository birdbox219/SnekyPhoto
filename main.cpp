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
				brightnes += image(i, j, k);
			}

			unsigned int avg = brightnes / 3;

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
	for (int i = 0; i < image.width; ++i) {
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
		for (int j = 0; j < image.height / 2; ++j)
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
		for (int j = 0; j < image.height; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				tmpImage = image(i, j, k);
				image(i, j, k) = image(image.width - i - 1, j, k);
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
Image CropingImageFilter(Image& image, int x, int y, int Cwidth, int Chight)
{


	cout << "\n Croping image ..." << endl;

	Image Cropping(Cwidth, Chight);

	if ((x + Cwidth) <= image.width && (y + Chight) <= image.height)
	{
		for (int i = 0; i < Cwidth; ++i)
		{
			for (int j = 0; j < Chight; ++j)
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
		for (int j = 0; j < newHight; ++j)
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
	for (int new_x = 0; new_x < targetwidth; new_x++)
	{
		for (int new_y = 0; new_y < targetheight; new_y++)
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




// =======









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





// filter edges detector made by adham.
void DetectEdges(Image& image)
{

	for (int i = 0; i < image.width; i++) {
		for (int j = 0; j < image.height; j++) {
			unsigned int avg = 0;
			for (int k = 0; k < 3; k++) {
				avg += image(i, j, k);
			}
			avg /= 3;
			image(i, j, 0) = avg;
			image(i, j, 1) = avg;
			image(i, j, 2) = avg;
		}
	}

	Image edges(image.width, image.height);
	int threshold = 30;

	for (int i = 0; i < image.width - 1; i++)
	{
		for (int j = 0; j < image.height - 1; j++)
		{
			int diff_X = abs(image(i, j, 0) - image(i + 1, j, 0));
			int diff_Y = abs(image(i, j, 0) - image(i, j + 1, 0));

			int edgeval = diff_X + diff_Y;

			if (edgeval > threshold)
			{
				edges(i, j, 0) = edges(i, j, 1) = edges(i, j, 2) = 0;
			}
			else {
				edges(i, j, 0) = edges(i, j, 1) = edges(i, j, 2) = 255;
			}
		}
	}

	image = edges;
}









// Filter No.6 Image Rotation (done by: Youssif Elnahs)


void Rotation(Image& image) {

	cout << "You Are Now on Image Rotaion Filter... :)\n";
	short degree = 0;
	cout << "Please Enter Rotation Degree: 90 - 180 - 270? ";
	cin >> degree;


	if (degree == 90) {
		Image rotated(image.height, image.width);
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
				for (int k = 0; k < 3; k++) {
					rotated(image.height - 1 - j, i, k) = image(i, j, k);
				}
			}
		}
		image = rotated;
	}

	else if (degree == 180) {
		Image rotated(image.width, image.height);
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
				for (int k = 0; k < 3; k++) {
					rotated(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
				}
			}
		}
		image = rotated;
	}

	else if (degree == 270) {
		Image rotated(image.height, image.width);
		for (int i = 0; i < image.width; i++) {
			for (int j = 0; j < image.height; j++) {
				for (int k = 0; k < 3; k++) {
					rotated(j, image.width - 1 - i, k) = image(i, j, k);
				}
			}
		}
		image = rotated;
	}
}






// Filter No.9 Image Frames (done by: Youssif Elnahs) 

void AddFrame(Image& image) {
	// choosing frame thickness
	int frameThickness;
	cout << "Enter frame thickness (in pixels):\n"
		<< "10 -> thin frame\n"
		<< "25 -> normal frame\n"
		<< ">25 -> thick frame\n"
		<< "or just type randomly: ";
	cin >> frameThickness;

	// simple frame or decorated
	int frameType;
	cout<< "\nChoose frame type:\n"
		<< "1. Simple Frame\n"
		<< "2.Decorative Frame\n"
		<< "Enter choice : ";
	cin >> frameType;

	// choosing decorated frame options
	int decorationType = 0;
	if (frameType == 2) {
		cout << "\nChoose Decorated Frame Style:\n"
			<< "1. Gradient Frame\n"
			<< "2. Mirror Frame\n"
			<< "3. Double (Layered) Frame\n"
			<< "4. Patterned Frame (Texture)\n"
			<< "5. Glow Frame\n"
			<< "6. 3D Shadow Frame\n"
			<< "7. Artistic Pattern Frame\n"
			<< "8. Blurred Frame\n"
			<< ">> ";
		cin >> decorationType;
	}

	// Choosing frame color
	int r, g, b;
	cout << "\nEnter frame color (R G B): ";
	cin >> r >> g >> b;

	int newWidth = image.width + 2 * frameThickness;
	int newHeight = image.height + 2 * frameThickness;

	Image framedImage(newWidth, newHeight);

	// Three nested loops: i → width, j → height, k → channels
	for (int i = 0; i < newWidth; i++) {
		for (int j = 0; j < newHeight; j++) {
			for (int k = 0; k < 3; k++) {
				// Check if pixel belongs to the frame region
				if (i < frameThickness || i >= newWidth - frameThickness ||
					j < frameThickness || j >= newHeight - frameThickness) {

					// Simple or Decorated
					if (frameType == 1) {
						// Simple solid color
						if (k == 0) framedImage(i, j, k) = r;
						else if (k == 1) framedImage(i, j, k) = g;
						else framedImage(i, j, k) = b;
					}
					// Decorated Frames
					else {
						switch (decorationType) {

						case 1: { // Gradient Frame
							int dist = min(min(i, newWidth - 1 - i), min(j, newHeight - 1 - j));
							double ratio = (double)dist / frameThickness;
							int base = (k == 0 ? r : (k == 1 ? g : b));
							int val = (int)(base * ratio + 255 * (1 - ratio));
							framedImage(i, j, k) = (unsigned char)min(max(val, 0), 255);
							break;
						}

						case 2: { // Mirror Frame
							int srcX = i - frameThickness;
							int srcY = j - frameThickness;

							if (srcX < 0) srcX = -srcX - 1;
							if (srcX >= image.width) srcX = 2 * image.width - srcX - 1;
							if (srcY < 0) srcY = -srcY - 1;
							if (srcY >= image.height) srcY = 2 * image.height - srcY - 1;

							srcX = max(0, min(srcX, image.width - 1));
							srcY = max(0, min(srcY, image.height - 1));

							framedImage(i, j, k) = image(srcX, srcY, k);
							break;
						}

						case 3: { // Double (Layered) Frame
							int dist = min(min(i, newWidth - 1 - i), min(j, newHeight - 1 - j));
							int outerBand = frameThickness / 3;
							int base = (k == 0 ? r : (k == 1 ? g : b));

							if (dist < outerBand)
								framedImage(i, j, k) = (unsigned char)min(base + 50, 255);
							else
								framedImage(i, j, k) = base;
							break;
						}

						case 4: { // Patterned Frame
							int stripe = 8;
							int pattern = ((i / stripe) + (j / stripe)) % 2;
							int base = (k == 0 ? r : (k == 1 ? g : b));
							framedImage(i, j, k) = (pattern == 0) ? base : (255 - base);
							break;
						}

						case 5: { // Glow Frame
							int dist = min(min(i, newWidth - 1 - i), min(j, newHeight - 1 - j));
							double ratio = 1.0 - (double)dist / frameThickness;
							int base = (k == 0 ? r : (k == 1 ? g : b));
							int val = min(255, (int)(base + ratio * 100));
							framedImage(i, j, k) = (unsigned char)val;
							break;
						}

						case 6: { // 3D Shadow Frame
							int base = (k == 0 ? r : (k == 1 ? g : b));
							if (i > newWidth - frameThickness * 0.7 || j > newHeight - frameThickness * 0.7)
								framedImage(i, j, k) = (unsigned char)(base * 0.5);  // shadowed area
							else if (i < frameThickness * 0.3 || j < frameThickness * 0.3)
								framedImage(i, j, k) = (unsigned char)min(base + 60, 255);  // light area
							else
								framedImage(i, j, k) = base;
							break;
						}

						case 7: { // Artistic Pattern Frame
							int base = (k == 0 ? r : (k == 1 ? g : b));
							int seed = (i * 31 + j * 17 + k * 13) % 255;
							framedImage(i, j, k) = (unsigned char)((base + seed) / 2);
							break;
						}

						case 8: { // Blurred Frame
							int x0 = max(0, min(i - frameThickness, image.width - 1));
							int y0 = max(0, min(j - frameThickness, image.height - 1));
							int sum = 0, count = 0;
							for (int dx = -1; dx <= 1; dx++) {
								for (int dy = -1; dy <= 1; dy++) {
									int xx = max(0, min(x0 + dx, image.width - 1));
									int yy = max(0, min(y0 + dy, image.height - 1));
									sum += image(xx, yy, k);
									count++;
								}
							}
							int avg = (count > 0) ? sum / count : (k == 0 ? r : (k == 1 ? g : b));
							framedImage(i, j, k) = (unsigned char)((avg + (k == 0 ? r : (k == 1 ? g : b))) / 2);
							break;
						}
						}
					}
				}
				else {
					// Copy pixel from original image
					framedImage(i, j, k) = image(i - frameThickness, j - frameThickness, k);
				}
			}
		}
	}

	// Replace original with framed version
	image = framedImage;
}




// Filter N0.12 - Blur Filter (done by Youssif Elnahas)

void Blur(Image& image) {
	cout << "You are now on Image Blur Filter... :)\n";

	int kernelSize = 20;
	int offset = kernelSize / 2;

	Image blurred(image.width, image.height);
	for (int x = 0; x < image.width; x++) {
		for (int y = 0; y < image.height; y++) {
			for (int c = 0; c < 3; c++) {
				int sum = 0;
				int count = 0;

				for (int i = -offset; i <= offset; i++) {
					for (int j = -offset; j <= offset; j++) {
						int nx = x + i;
						int ny = y + j;

						if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
							sum += image(nx, ny, c);
							count++;
						}
					}
				}
				blurred(x, y, c) = sum / count;
			}
		}
	}
	image = blurred;
}


int main()
{
	Image image = LoadImage();
	/*GrayScaleFilter(image);*/
	//BlackAndWhiteFilter(image);
	//BlackAndWhiteOtsualgorithm(image);
	//IvertImageFilter(image);
	//FlipImageFilter(image);
	//Rotation(image);
	//FlipImageFilterH(image);
	//FlipImageFilter(image, both);
	//CropingImageFilter(image, 500 , 500, 1000 , 1000);
	//Image Cropped = CropingImageFilter(image, 960 , 0, 960, 1080);
	//Image Resized = ImageResizeFilter(image, 2000, 2000);
	//Blur(image);
	//InfraredImageFilter(image);
	//SaveImage(Resized);
	//IR(image);
	//infrared_color(image);

	//mergeImages(image);

	//SaveImage(Cropped);
	//AddFrame(image);
	SaveImage(image);




}

