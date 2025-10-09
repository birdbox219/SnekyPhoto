// =============================================
// TEAM MEMBERS AND FILTER ASSIGNMENTS HEADER
// =============================================
/* ASSIGNMENT  CS213_A1_Part2.
 * DR.Mohamed Elramly
 * Team: section : S26
 *
 * Team Members:
 * - Adham Tamer id:20240067
 * - Mahmoud Elsayed id:20240548
 * - Youssif Elnahs  id:20240699
 *
 * Filter Assignments:
 *
 * Adham Mohamed (6 Filters):
 * 1. Grayscale
 * 9. Merge Images
 * 10. Edge Detection (Sobel)
 * 11. Oil Painting
 * 17. Adjust Brightness
 * 18. Skew Image
 *
 * Mahmoud Elsayed (8 Filters):
 * 2. Black and White (Otsu Algorithm)
 * 4. Flip Image (Vertical/Horizontal/Both)
 * 5. Crop Image
 * 6. Resize Image
 * 7. Infrared Color Effect
 * 13. Sun Light Effect
 * 15. Old TV Effect
 * 16. Purple Filter
 *
 * Youssif Elnahs (4 Filters):
 * 3. Invert Colors
 * 8. Frame Image (Simple + 8 Decorative Styles)
 * 12. Blur Filter
 * 14. Rotate Image (90/180/270 degrees)
 *
 * Management Features (All Team):
 * - Undo/Redo System
 * - Filter History Tracking
 * - Image Save/Load
 * - Menu Navigation
 *
 * Project Links:
 * - GitHub Repository: [https://github.com/birdbox219/SnekyPhoto]

 * - Video Demo: [https://youtu.be/-8p5UYJaxVM]
 *
 * Date: 9 October 2025
 * Section: S26
 */

#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <limits>
#include <cstdlib>

using namespace std;

void HeaderLine();
void SeparatorLine();

// --------------------------//

// Welcome to Sneky Photo Application Source Code!
/*
⠄⠄⠄⠄⢠⣿⣿⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣯⢻⣿⣿⣿⣿⣆⠄⠄⠄
⠄⠄⣼⢀⣿⣿⣿⣿⣏⡏⠄⠹⣿⣿⣿⣿⣿⣿⣿⣿⣧⢻⣿⣿⣿⣿⡆⠄⠄
⠄⠄⡟⣼⣿⣿⣿⣿⣿⠄⠄⠄⠈⠻⣿⣿⣿⣿⣿⣿⣿⣇⢻⣿⣿⣿⣿⠄⠄
⠄⢰⠃⣿⣿⠿⣿⣿⣿⠄⠄⠄⠄⠄⠄⠙⠿⣿⣿⣿⣿⣿⠄⢿⣿⣿⣿⡄⠄
⠄⢸⢠⣿⣿⣧⡙⣿⣿⡆⠄⠄⠄⠄⠄⠄⠄⠈⠛⢿⣿⣿⡇⠸⣿⡿⣸⡇⠄
⠄⠈⡆⣿⣿⣿⣿⣦⡙⠳⠄⠄⠄⠄⠄⠄⢀⣠⣤⣀⣈⠙⠃⠄⠿⢇⣿⡇⠄
⠄⠄⡇⢿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⣠⣶⣿⣿⣿⣿⣿⣿⣷⣆⡀⣼⣿⡇⠄
⠄⠄⢹⡘⣿⣿⣿⢿⣷⡀⠄⢀⣴⣾⣟⠉⠉⠉⠉⣽⣿⣿⣿⣿⠇⢹⣿⠃⠄
⠄⠄⠄⢷⡘⢿⣿⣎⢻⣷⠰⣿⣿⣿⣿⣦⣀⣀⣴⣿⣿⣿⠟⢫⡾⢸⡟⠄.
⠄⠄⠄⠄⠻⣦⡙⠿⣧⠙⢷⠙⠻⠿⢿⡿⠿⠿⠛⠋⠉⠄⠂⠘⠁⠞⠄⠄⠄
⠄⠄⠄⠄⠄⠈⠙⠑⣠⣤⣴⡖⠄⠿⣋⣉⣉⡁⠄⢾⣦⠄⠄⠄⠄⠄⠄⠄⠄
*/

// This function prints the message and waits for the user

int LoadMenu()
{
	HeaderLine();
	cout << "    IMAGE PROCESSING APPLICATION V6.1\n";
	HeaderLine();
	cout << "\n\n";

	HeaderLine();
	cout << "  FILTERS:\n";
	HeaderLine();
	cout << "  1. Grayscale\n";
	cout << "  2. Black and White\n";
	cout << "  3. Invert Colors\n";
	cout << "  4. Flip Image\n";
	cout << "  5. Crop Image\n";
	cout << "  6. Resize Image\n";
	cout << "  7. Infrared Color Effect\n";
	cout << "  8. Frame Image\n";
	cout << "  9. Merge Images\n";
	cout << "  10. Edge Detection\n";
	cout << "  11. Oil Painting\n";
	cout << "  12. Blur\n";
	cout << "  13. Rotate Image\n";
	cout << "  14. Sun Light\n";
	cout << "  15. Old TV Effect\n";
	cout << "  16. Purple Filter\n";
	cout << "  17. Adjust Brightness\n";
	cout << "  18. Skew Image\n";

	HeaderLine();
	cout << "  MANAGEMENT:\n";
	HeaderLine();
	cout << "  97. Show Applied Filters\n";
	cout << "  98. Save Image\n";
	cout << "  99. Undo Last Filter\n";
	cout << "  100. Redo Last Undone Filter\n";
	cout << "  101. Save and exit\n";
	cout << "  102. Load New Image\n";

	cout << "\n  0. Exit\n";

	SeparatorLine();
	cout << ">> Enter your choice: ";

	int choice;
	while (!(std::cin >> choice))
	{
		std::cout << "Invalid input. Please enter a number: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return choice;
}

Image LoadImage()
{
	string filename;
	cout << "Enter Image name with it's extention: ";
	try
	{
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

void HeaderLine()
{
	cout << "=========================================\n";
}

void SeparatorLine()
{
	cout << "-----------------------------------------\n";
}

int LoadStartMenu()
{
	HeaderLine();
	cout << "    START MENU\n";
	HeaderLine();

	cout << "  1. Load Image\n";
	cout << "  2. Exit\n";

	cout << "-----------------------------------------\n";
	cout << "\n\n";
	int choice;

	while (!(std::cin >> choice))
	{
		std::cout << "Invalid input. Please enter a number: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return choice;
}

void pause()
{
	cout << "Press Enter to continue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

void NewFilter(stack<Image>& redoFilter, stack<string>& redoHistory)
{
	while (!redoFilter.empty())
		redoFilter.pop();
	while (!redoHistory.empty())
		redoHistory.pop();
}

void ClaearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// aded by Mahmoud Elsayed
// LogicFilters//
//-------------------------------------------------------------------------------------//

// --------------------------//
// Filter No.1 Grayscale (done by: Adham )
void GrayScaleFilter(Image& image)
{

	cout << "\nConverting image to grayscale..." << endl;
	for (int i = 0; i < image.width; i++)
	{
		for (int j = 0; j < image.height; j++)
		{

			unsigned int avg = 0;

			for (int k = 0; k < 3; k++)
			{
				avg += image(i, j, k);
			}

			avg /= 3;

			image(i, j, 0) = avg;
			image(i, j, 1) = avg;
			image(i, j, 2) = avg;
		}
	}
	cout << "Grayscale conversion complete " << endl;
}

// Filter No.2 Black and White using Otsu algorithm (done by: Mahmoud Elsayed )
void BlackAndWhiteOtsualgorithm(Image& image)
{
	vector<int> histogram(256, 0);
	cout << "\nConverting image to BlackaAndWhite using Otsu algorithm..." << endl;
	int totalPixels = image.width * image.height;
	int index = 0;
	vector<unsigned char> brightnesLevels(totalPixels);
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
			index++;
		}
	}

	// Otsu algorithm
	double totalBrightnesSum = 0;
	for (int t = 0; t < 256; ++t)
		totalBrightnesSum += t * histogram[t];

	double sumOfbirghtnessInBackground = 0;
	int weightOfBackground = 0;
	int weightOfForground = 0;

	double maxVar = 0;
	int Threshold = 0;

	for (int t = 0; t < 256; ++t)
	{
		weightOfBackground += histogram[t];
		if (weightOfBackground == 0)
			continue;

		weightOfForground = totalPixels - weightOfBackground;
		if (weightOfForground == 0)
			break;

		sumOfbirghtnessInBackground += t * histogram[t];

		double avgBrightnesOfBackground = sumOfbirghtnessInBackground / weightOfBackground;
		double avgBrightnesOfForground = (totalBrightnesSum - sumOfbirghtnessInBackground) / weightOfForground;

		double betweenVar =
			(double)weightOfBackground *
			(double)weightOfForground *
			(avgBrightnesOfBackground - avgBrightnesOfForground) *
			(avgBrightnesOfBackground - avgBrightnesOfForground);

		if (betweenVar > maxVar)
		{
			maxVar = betweenVar;
			Threshold = t;
		}
	}

	index = 0;
	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j, ++index)
		{

			if (brightnesLevels[index] >= Threshold)
			{
				unsigned char val = 255;
				image(i, j, 0) = val;
				image(i, j, 1) = val;
				image(i, j, 2) = val;
			}

			else
			{
				unsigned char val = 0;
				image(i, j, 0) = val;
				image(i, j, 1) = val;
				image(i, j, 2) = val;
			}
		}
	}
}

// Filter No.3 Invert Colors (done by: Youssif Elnahs )
void IvertImageFilter(Image& image)
{
	cout << "\nInverting image colors..." << endl;
	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				image(i, j, k) = 255 - image(i, j, k);
			}
		}
	}
	cout << "Color inversion complete." << endl;
}

// Filter No.4 merge Image (done by:Adham )

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

void mergeImages(Image& image)
{
	Image img1, img2;
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

			image = Image(minw, minh);

			for (int i = 0; i < minw; i++)
			{
				for (int j = 0; j < minh; j++)
				{
					for (int c = 0; c < 3; c++)
					{
						image(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
					}
				}
			}
		}
		else if (option == 2)
		{
			if (img1.width > img2.width || img1.height > img2.height)
			{
				img2 = resizeImage(img2, img1.width, img1.height);
				image = Image(img1.width, img1.height);
			}
			else
			{
				img1 = resizeImage(img1, img2.width, img2.height);
				image = Image(img2.width, img2.height);
			}

			for (int i = 0; i < image.width; i++)
			{
				for (int j = 0; j < image.height; j++)
				{
					for (int c = 0; c < 3; c++)
					{
						image(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
					}
				}
			}
		}
	}
	else
	{
		image = Image(img1.width, img1.height);

		for (int i = 0; i < img1.width; i++)
		{
			for (int j = 0; j < img1.height; j++)
			{
				for (int c = 0; c < 3; c++)
				{
					image(i, j, c) = (img1(i, j, c) + img2(i, j, c)) / 2;
				}
			}
		}
	}

	image.saveImage("merged.png");
	cout << "merged image saved as merged.png\n";
}

// filter No.5 Flip Image (done by: Mahmoud Elsayed )
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
// Done by MahmoudELsayed
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
*/

enum FlipType
{
	None = 0,
	Vertical,
	Horizontal,
	both,
};

// Done by MahmoudELsayed

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

const char* flipTypeToString(FlipType type)
{
	switch (type)
	{
	case Vertical:
		return "Vertical";
	case Horizontal:
		return "Horizontal";
	case both:
		return "Both";
	case None:
		return "None";
	}
	return "Unknown";
}

// Filter No.6 Image Rotation (done by: Youssif Elnahs)
void RotateImageFilter(Image& image)
{

	cout << "You Are Now on Image Rotaion Filter... :)\n";
	short degree = 0;
	cout << "Please Enter Rotation Degree: 90 - 180 - 270? ";
	cin >> degree;

	if (degree == 90)
	{
		Image rotated(image.height, image.width);
		for (int i = 0; i < image.width; i++)
		{
			for (int j = 0; j < image.height; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					rotated(image.height - 1 - j, i, k) = image(i, j, k);
				}
			}
		}
		image = rotated;
	}

	else if (degree == 180)
	{
		Image rotated(image.width, image.height);
		for (int i = 0; i < image.width; i++)
		{
			for (int j = 0; j < image.height; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					rotated(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
				}
			}
		}
		image = rotated;
	}

	else if (degree == 270)
	{
		Image rotated(image.height, image.width);
		for (int i = 0; i < image.width; i++)
		{
			for (int j = 0; j < image.height; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					rotated(j, image.width - 1 - i, k) = image(i, j, k);
				}
			}
		}
		image = rotated;
	}
}

// Filter No.7 AdjustBrightness (done by: Adham )
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
				if (newval > 255)
					newval = 255;
				if (newval < 0)
					newval = 0;
				img(i, j, k) = newval;
			}
		}
	}
}

// Filter No.8 Crop Image (done by: Mahmoud Elsayed )
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
		image = Cropping;
	}
	else
	{
		throw runtime_error("Image Dimesntion not compatiple");
	}
}

// Filter No.9 Image Frames (done by: Youssif Elnahs)

void AddFrameImageFilter(Image& image)
{
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
	cout << "\nChoose frame type:\n"
		<< "1. Simple Frame\n"
		<< "2.Decorative Frame\n"
		<< "Enter choice : ";
	cin >> frameType;

	// choosing decorated frame options
	int decorationType = 0;
	if (frameType == 2)
	{
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
	for (int i = 0; i < newWidth; i++)
	{
		for (int j = 0; j < newHeight; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				// Check if pixel belongs to the frame region
				if (i < frameThickness || i >= newWidth - frameThickness ||
					j < frameThickness || j >= newHeight - frameThickness)
				{

					// Simple or Decorated
					if (frameType == 1)
					{
						// Simple solid color
						if (k == 0)
							framedImage(i, j, k) = r;
						else if (k == 1)
							framedImage(i, j, k) = g;
						else
							framedImage(i, j, k) = b;
					}
					// Decorated Frames
					else
					{
						switch (decorationType)
						{

						case 1:
						{ // Gradient Frame
							int dist = min(min(i, newWidth - 1 - i), min(j, newHeight - 1 - j));
							double ratio = (double)dist / frameThickness;
							int base = (k == 0 ? r : (k == 1 ? g : b));
							int val = (int)(base * ratio + 255 * (1 - ratio));
							framedImage(i, j, k) = (unsigned char)min(max(val, 0), 255);
							break;
						}

						case 2:
						{ // Mirror Frame
							int srcX = i - frameThickness;
							int srcY = j - frameThickness;

							if (srcX < 0)
								srcX = -srcX - 1;
							if (srcX >= image.width)
								srcX = 2 * image.width - srcX - 1;
							if (srcY < 0)
								srcY = -srcY - 1;
							if (srcY >= image.height)
								srcY = 2 * image.height - srcY - 1;

							srcX = max(0, min(srcX, image.width - 1));
							srcY = max(0, min(srcY, image.height - 1));

							framedImage(i, j, k) = image(srcX, srcY, k);
							break;
						}

						case 3:
						{ // Double (Layered) Frame
							int dist = min(min(i, newWidth - 1 - i), min(j, newHeight - 1 - j));
							int outerBand = frameThickness / 3;
							int base = (k == 0 ? r : (k == 1 ? g : b));

							if (dist < outerBand)
								framedImage(i, j, k) = (unsigned char)min(base + 50, 255);
							else
								framedImage(i, j, k) = base;
							break;
						}

						case 4:
						{ // Patterned Frame
							int stripe = 8;
							int pattern = ((i / stripe) + (j / stripe)) % 2;
							int base = (k == 0 ? r : (k == 1 ? g : b));
							framedImage(i, j, k) = (pattern == 0) ? base : (255 - base);
							break;
						}

						case 5:
						{ // Glow Frame
							int dist = min(min(i, newWidth - 1 - i), min(j, newHeight - 1 - j));
							double ratio = 1.0 - (double)dist / frameThickness;
							int base = (k == 0 ? r : (k == 1 ? g : b));
							int val = min(255, (int)(base + ratio * 100));
							framedImage(i, j, k) = (unsigned char)val;
							break;
						}

						case 6:
						{ // 3D Shadow Frame
							int base = (k == 0 ? r : (k == 1 ? g : b));
							if (i > newWidth - frameThickness * 0.7 || j > newHeight - frameThickness * 0.7)
								framedImage(i, j, k) = (unsigned char)(base * 0.5); // shadowed area
							else if (i < frameThickness * 0.3 || j < frameThickness * 0.3)
								framedImage(i, j, k) = (unsigned char)min(base + 60, 255); // light area
							else
								framedImage(i, j, k) = base;
							break;
						}

						case 7:
						{ // Artistic Pattern Frame
							int base = (k == 0 ? r : (k == 1 ? g : b));
							int seed = (i * 31 + j * 17 + k * 13) % 255;
							framedImage(i, j, k) = (unsigned char)((base + seed) / 2);
							break;
						}

						case 8:
						{ // Blurred Frame
							int x0 = max(0, min(i - frameThickness, image.width - 1));
							int y0 = max(0, min(j - frameThickness, image.height - 1));
							int sum = 0, count = 0;
							for (int dx = -1; dx <= 1; dx++)
							{
								for (int dy = -1; dy <= 1; dy++)
								{
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
				else
				{
					// Copy pixel from original image
					framedImage(i, j, k) = image(i - frameThickness, j - frameThickness, k);
				}
			}
		}
	}

	// Replace original with framed version

	image = framedImage;
}

// filter edges detector made by adham.
// Filter No.10 Edge Detection (done by: Adham )

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
// made by Adham
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
		{-1, 0, 1} };

	int gy[3][3] =
	{
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1} };

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

// Filter No.11 Resize Image (done by: Mahmoud Elsayed )

void ImageResizeFilter(Image& image, int newWidth, int newHight)
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
	image = risizedImage;
}

// Filter N0.12 - Blur Filter (done by Youssif Elnahas)

void Blur(Image& image)
{
	cout << "You are now on Image Blur Filter... :)\n";

	int kernelSize = 20;
	int offset = kernelSize / 2;

	Image blurred(image.width, image.height);
	for (int x = 0; x < image.width; x++)
	{
		for (int y = 0; y < image.height; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				int sum = 0;
				int count = 0;

				for (int i = -offset; i <= offset; i++)
				{
					for (int j = -offset; j <= offset; j++)
					{
						int nx = x + i;
						int ny = y + j;

						if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height)
						{
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

// Filter No.13 - Sun Light Effect (done by Mahmoud Elsayed)
void SunLightImageFilter(Image& image, int sunBrightness)
{

	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{
			int R = image(i, j, 0) + sunBrightness;
			int G = image(i, j, 1) + sunBrightness / 2;
			float B = image(i, j, 2) * 0.8f;

			image(i, j, 0) = min(255, R);
			image(i, j, 1) = min(255, G);
			image(i, j, 2) = max(0.0f, B);
		}
	}
}

// Filter No.15 - Old TV Effect (done by Mahmoud Elsayed)
// we were using C++14 so we couldn't use std::clamp from <algorithm> and we used it alot so we made our own version of it.

template <typename T>
T Clamp(T value, T minValue, T maxValue)
{
	if (value < minValue)
		return minValue;
	if (value > maxValue)
		return maxValue;
	return value;
}

void OldTVImageFilter(Image& image)
{

	GrayScaleFilter(image);
	int noiseDistortion = 30;
	double blackLInesHighlight = 0.3;
	int lineThickness = 5;
	int lineSpacing = 10;

	double vigS = 0.4;
	double vigP = 2.5;
	double centerX = image.width / 2.0;
	double centerY = image.height / 2.0;

	for (int i = 0; i < image.width; ++i)
	{

		for (int j = 0; j < image.height; ++j)
		{

			double dx = (i - centerX) / centerX;
			double dy = (j - centerY) / centerY;

			double distance = sqrt(dx * dx + dy * dy);
			double vignette = 1.0 - vigS * pow(distance, vigP);

			if (vignette < 0.0)
			{
				vignette = 0.0;
			}

			for (int k = 0; k < 3; ++k)
			{

				int newDisotrtion = image(i, j, k);

				int jitterAmount = (rand() % noiseDistortion) + (rand() % noiseDistortion) + (rand() % noiseDistortion) - (3 * noiseDistortion / 2);
				newDisotrtion += jitterAmount;

				if ((j % lineSpacing) < lineThickness)
				{

					newDisotrtion = static_cast<int>(newDisotrtion * (1.0 - blackLInesHighlight));
				}

				newDisotrtion = static_cast<int>(newDisotrtion * vignette);

				image(i, j, k) = ::Clamp(newDisotrtion, 0, 255);
			}
		}
	}
}

// Filter No.16 - Purple Filter (done by Mahmoud Elsayed)
void PurpleImageFilter(Image& image)
{

	int purblePower = 50;
	double R, G, B;
	for (int i = 0; i < image.width; ++i)
	{
		for (int j = 0; j < image.height; ++j)
		{

			R = image(i, j, 0) + purblePower;
			G = image(i, j, 1) - purblePower / 2;
			B = image(i, j, 2) + purblePower;

			image(i, j, 1) = ::Clamp(static_cast<int>(G), 0, 255);
			image(i, j, 0) = ::Clamp(static_cast<int>(R), 0, 255);
			image(i, j, 2) = ::Clamp(static_cast<int>(B), 0, 255);
		}
	}
}

// Filter No.17 - Infrared Color Filter (done by Mahmoud Elsayed)
void infraredColorImageFilter(Image& img)
{
	for (int i = 1; i < img.width; i++)
	{
		for (int j = 1; j < img.height; j++)
		{
			int R = img(i, j, 0);
			int G = img(i, j, 1);
			int B = img(i, j, 2);

			R = 255;
			G = 255 - G * 0.98f;
			B = 255 - B * 0.95f;

			img(i, j, 0) = R;
			img(i, j, 1) = G;
			img(i, j, 2) = B;
		}
	}
}

// by Adham
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

int main()
{
	Image image;

	cout << R"(

   _____            __         ____  __          __      
  / ___/____  ___  / /____  __/ __ \/ /_  ____  / /_____ 
  \__ \/ __ \/ _ \/ //_/ / / / /_/ / __ \/ __ \/ __/ __ \				
 ___/ / / / /  __/ ,< / /_/ / ____/ / / / /_/ / /_/ /_/ /
/____/_/ /_/\___/_/|_|\__, /_/   /_/ /_/\____/\__/\____/				
                     /____/                                 
                                             
                                                                                                              
)" << "\n";

	cout << "                 (c) 2025 Mahmoud elsayed Games. All Rights Reserved.\n\n";

	int startChoice = LoadStartMenu();

	switch (startChoice)
	{
	case 1:
		image = LoadImage();
		break;

	case 2:
		cout << "Exiting the program. \n";
		return 0;
	default:
		cout << "Invalid choice. Exiting the program.\n";
		return 0;
		break;
	}

	stack<Image> apliedFilter;
	vector<string> filterHistory;

	stack<Image> redoFilter;
	stack<string> redoHistory;

	bool running = true;

	while (running)
	{
		ClaearScreen();

		try
		{

			int choice = LoadMenu();

			switch (choice)
			{
			case 1:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				GrayScaleFilter(image);
				filterHistory.push_back("GrayScale");
				pause();
				break;
			}
			case 2:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				BlackAndWhiteOtsualgorithm(image);
				filterHistory.push_back("BlackAndWhite");
				pause();
				break;
			}
			case 3:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				IvertImageFilter(image);
				filterHistory.push_back("InvertColors");
				pause();
				break;
			}
			case 4:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);

				HeaderLine();
				cout << "Choose flip type:\n";
				cout << "1. Vertical\n";
				cout << "2. Horizontal\n";
				cout << "3. Both\n";
				cout << "0. None (cancel)\n";
				HeaderLine();

				int flipChoice;
				cin >> flipChoice;

				FlipType flipType = None;
				switch (flipChoice)
				{
				case 1:
					flipType = Vertical;
					break;
				case 2:
					flipType = Horizontal;
					break;
				case 3:
					flipType = both;
					break;
				case 0:
					flipType = None;
					break;
				default:
					cout << "Invalid choice. No flip applied.\n";
					flipType = None;
					break;
				}
				if (flipType != None)
				{
					FlipImageFilter(image, flipType);
					cout << "Applied " << flipTypeToString(flipType) << " flip.\n";
					filterHistory.push_back(string(flipTypeToString(flipType)) + "Flip");
				}
				else
				{
					if (!apliedFilter.empty())
					{
						cout << "No flip applied.\n";
						apliedFilter.pop();
					}
				}
				pause();
				break;
			}
			case 5:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				int x, y, Cwidth, Chight;
				cout << "Enter x, y, width, height for cropping: ";
				cin >> x >> y >> Cwidth >> Chight;
				if (x < 0 || y < 0 || Cwidth <= 0 || Chight <= 0)
				{
					cout << "Invalid crop parameters.\n";
					apliedFilter.pop();
					break;
				}
				CropingImageFilter(image, x, y, Cwidth, Chight);
				filterHistory.push_back("Croping");
				pause();
				break;
			}
			case 6:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				int newWidth, newHight;
				cout << "Enter new width and height for resizing: ";
				cin >> newWidth >> newHight;
				if (newWidth <= 0 || newHight <= 0)
				{
					cout << "Invalid dimensions.\n";
					apliedFilter.pop();
					break;
				}
				ImageResizeFilter(image, newWidth, newHight);
				filterHistory.push_back("Resizing");
				pause();
				break;
			}
			case 7:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				infraredColorImageFilter(image);
				filterHistory.push_back("InfraredColor");
				pause();
				break;
			}
			case 8:
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				AddFrameImageFilter(image);
				filterHistory.push_back("AddFrame");
				pause();
				break;
			}
			case 9: // Merge Images - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				mergeImages(image);
				filterHistory.push_back("Merge Images");
				pause();
				break;
			}
			case 10: // Edge Detection - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				SobelEdge(image);
				filterHistory.push_back("Edge Detection");
				pause();
				break;
			}
			case 11: // Oil Painting - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				OilPaint(image);
				filterHistory.push_back("Oil Painting");
				pause();
				break;
			}
			case 12: // Blur - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				Blur(image);
				filterHistory.push_back("Blur");
				pause();
				break;
			}
			case 13: // Rotate Image - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				RotateImageFilter(image);
				filterHistory.push_back("Rotate Image");
				pause();
				break;
			}
			case 14: // Sun Light - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				int brightness;
				cout << "Enter sun brightness level (0-100): ";
				cin >> brightness;
				SunLightImageFilter(image, brightness);
				filterHistory.push_back("Sun Light");
				pause();
				break;
			}
			case 15: // Old TV Effect - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				OldTVImageFilter(image);
				filterHistory.push_back("Old TV Effect");
				pause();
				break;
			}
			case 16: // Purple Filter - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				PurpleImageFilter(image);
				filterHistory.push_back("Purple Filter");
				pause();
				break;
			}
			case 17: // Adjust Brightness - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				int percent;
				string lightenChoice;
				cout << "Do you want to lighten or darken? (lighten/darken): ";
				cin >> lightenChoice;
				cout << "Enter percentage (0-100): ";
				cin >> percent;
				bool lighten = (lightenChoice == "lighten");
				AdjustBrightness(image, lighten, percent);
				filterHistory.push_back("Adjust Brightness");
				pause();
				break;
			}
			case 18: // Skew Image - NEW
			{
				NewFilter(redoFilter, redoHistory);
				apliedFilter.push(image);
				SkewImage(image);
				filterHistory.push_back("Skew Image");
				pause();
				break;
			}
			case 97:
			{
				if (apliedFilter.empty())
				{
					cout << "No filters applied yet.\n";
				}
				else
				{
					cout << "Applied filters history: [";
					for (size_t i = 0; i < filterHistory.size(); ++i)
					{
						cout << filterHistory[i];
						if (i < filterHistory.size() - 1)
						{
							cout << ", ";
						}
					}
					cout << "]\n";
					cout << "Total: " << filterHistory.size() << " filter(s)\n";
				}
				pause();
				break;
			}
			case 98:
			{
				SaveImage(image);
				pause();
				break;
			}
			case 99:
			{
				if (!apliedFilter.empty())
				{
					redoFilter.push(image);
					image = apliedFilter.top();
					apliedFilter.pop();
					if (!filterHistory.empty())
					{
						redoHistory.push(filterHistory.back());
						filterHistory.pop_back();
					}
					cout << "Undid last filter.\n";
				}
				else
				{
					cout << "No filters to undo.\n";
				}
				pause();
				break;
			}
			case 100:
			{
				if (!redoFilter.empty())
				{
					apliedFilter.push(image);
					image = redoFilter.top();
					redoFilter.pop();
					if (!redoHistory.empty())
					{
						filterHistory.push_back(redoHistory.top());
						redoHistory.pop();
					}
					cout << "Redid last undone filter.\n";
				}
				else
				{
					cout << "No filters to redo.\n";
				}
				pause();
				break;
			}
			case 101:
			{
				running = false;
				SaveImage(image);
				cout << "Exiting application.\n";
				break;
			}

			case 102:
			{
				cout << "\nLoading a new image...\n";
				image = LoadImage();

				// Clear all applied filters and histories for a fresh start
				while (!apliedFilter.empty())
					apliedFilter.pop();
				filterHistory.clear();

				while (!redoFilter.empty())
					redoFilter.pop();
				while (!redoHistory.empty())
					redoHistory.pop();

				cout << "New image loaded successfully. Filters reset.\n";
				pause();
				break;
			}
			case 0:
			{
				running = false;
				cout << "Exiting application.\n";
				break;
			}
			default:
			{
				cout << "Invalid choice. Please try again.\n";
				pause();
				break;
			}
			}
		}
		catch (const exception& e)
		{
			cout << "\nAn error occurred: " << e.what() << endl;
			cout << "Please try again.\n";
			pause();
		}
	}
	return 0;
}
