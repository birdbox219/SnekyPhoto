#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <limits>
#include <cstdlib>


using namespace std;

// --------------------------//


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

void HeaderLine() {
	cout << "=========================================\n";
}


void SeparatorLine() {
	cout << "-----------------------------------------\n";
}



int LoadMenu()
{




	

	
		HeaderLine();
		cout << "    IMAGE PROCESSING APPLICATION V6.0\n";
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

		HeaderLine();
		cout << "  MANAGEMENT:\n";
		HeaderLine();
		cout << "  97. Show Applied Filters\n";
		cout << "  98. Save Image\n";
		cout << "  99. Undo Last Filter\n";
		cout << "  100. Redo Last Undone Filter\n";
		cout << "  101. Save and exit\n";

		cout << "\n  0. Exit\n";

		SeparatorLine();
		cout << ">> Enter your choice: ";

		int choice;
		
		while (!(std::cin >> choice)) {
			std::cout << "Invalid input. Please enter a number: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return choice;
	
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

	while (!(std::cin >> choice)) {
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

void NewFilter(stack<Image>& redoFilter , stack<string>& redoHistory)
{
	while (!redoFilter.empty()) redoFilter.pop();
	while (!redoHistory.empty()) redoHistory.pop();
}

void ClaearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
	


// --------------------------//
void GrayScaleFilter(Image& image)
{
	
	cout << "\nConverting image to grayscale..." << endl;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			
			unsigned int avg = 0;

			
			for (int k = 0; k < 3; ++k) {
				avg += image(i, j, k);
			}

			
			unsigned char gray_value = avg / 3;

			
			image(i, j, 0) = gray_value;
			image(i, j, 1) = gray_value;
			image(i, j, 2) = gray_value;
		}
	}
	cout << "Grayscale conversion complete." << endl;
	
}


//void BlackAndWhiteFilter(Image& image)
//{
//	cout << "\nConverting image to BlackaAndWhite..." << endl;
//
//	unsigned int threshold = 128;
//
//	for (int i = 0; i < image.width; ++i)
//	{
//		for (int j = 0; j < image.height; ++j)
//		{
//			unsigned int brightnes = 0;
//			
//			
//			for (int k = 0; k < 3; ++k) 
//			{
//				 brightnes+= image(i, j, k);
//			}
//
//			unsigned int avg   = brightnes / 3;
//
//			unsigned char whitVlaue = 255;
//			unsigned char blackVlaue = 0;
//
//			if (avg >= threshold)
//			{
//				image(i, j, 0) = whitVlaue;
//				image(i, j, 1) = whitVlaue;
//				image(i, j, 2) = whitVlaue;
//			}
//
//			else
//			{
//				image(i, j, 0) = blackVlaue;
//				image(i, j, 1) = blackVlaue;
//				image(i, j, 2) = blackVlaue;
//			}
//
//
//		}
//	}
//	cout << "BlackAndWhite conversion complete." << endl;
//}

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
			index++;
		}
	}

	//Otsu algorithm
	double totalBrightnesSum = 0;  
	for (int t = 0; t < 256; ++t) totalBrightnesSum += t * histogram[t];

	double sumOfbirghtnessInBackground = 0;  
	int weightOfBackground = 0;
	int weightOfForground = 0;

	double maxVar = 0;
	int Threshold = 0;

	for (int t = 0; t < 256; ++t) {
		weightOfBackground += histogram[t];                
		if (weightOfBackground == 0) continue;

		weightOfForground = totalPixels - weightOfBackground;
		if (weightOfForground == 0) break;

		sumOfbirghtnessInBackground += t * histogram[t];

		double avgBrightnesOfBackground = sumOfbirghtnessInBackground / weightOfBackground;
		double avgBrightnesOfForground = (totalBrightnesSum - sumOfbirghtnessInBackground) / weightOfForground;

		double betweenVar = 
			(double)weightOfBackground *
			(double)weightOfForground *
			(avgBrightnesOfBackground - avgBrightnesOfForground) *
			(avgBrightnesOfBackground - avgBrightnesOfForground);

		if (betweenVar > maxVar) {
			maxVar = betweenVar;
			Threshold = t;
		}
	}

	index = 0;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j, ++index) {
			
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

const char* flipTypeToString(FlipType type) {
	switch (type) {
	case Vertical: return "Vertical";
	case Horizontal: return "Horizontal";
	case both: return "Both";
	case None: return "None";
	}
	return "Unknown";
}

// Done by Mahmoud Elsayed
void CropingImageFilter(Image& image , int x , int y , int Cwidth , int Chight)
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
		image =  Cropping;
		

		
	}
	else
	{
		throw runtime_error("Image Dimesntion not compatiple");
	}
}


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
	image = risizedImage;
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








	




void infrared_color(Image& img)
{
	for (int i = 1; i < img.width; i++) {
		for (int j = 1; j < img.height; j++) {
			int R = img(i, j, 0);
			int G = img(i, j, 1);
			int B = img(i, j, 2);

			R = 255;
			G = 255 - G;
			//B = 255 - B;


			
			img(i, j, 0) = R;
			img(i, j, 1) = G;
			img(i, j, 2) = B;
		}
	}
}



void SunLightImageFilter(Image& image , int sunBrightness)
{
	



	for(int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			int R = image(i, j, 0)+sunBrightness;
			int G = image(i, j, 1) + sunBrightness/2;
			float B =  image(i, j, 2) * 0.8f;
			
			

			image(i, j, 0) = min(255, R);
			image(i, j, 1) = min(255, G);
			image(i, j, 2) = max(0.0f , B);


			
			
		}
	}

}




template <typename T>
T clamp(T value, T minValue, T maxValue) {
	if (value < minValue) return minValue;
	if (value > maxValue) return maxValue;
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

	for(int i = 0; i < image.width; ++i) {
		
		for (int j = 0; j < image.height; ++j) {

			double dx = (i - centerX) / centerX;
			double dy = (j - centerY) / centerY;

			double distance = sqrt(dx * dx + dy * dy);
			double vignette = 1.0 - vigS * pow(distance, vigP);

			if (vignette < 0.0)
			{
				vignette = 0.0;
			}
			

			

			for (int k = 0; k < 3; ++k) {
				
				int newDisotrtion = image(i, j, k);

				int jitterAmount = (rand() % noiseDistortion) + (rand() % noiseDistortion) + (rand() % noiseDistortion) - (3 * noiseDistortion / 2);
				newDisotrtion += jitterAmount;
				
				if ((j % lineSpacing) < lineThickness)
				{
					
					newDisotrtion = static_cast<int>(newDisotrtion * (1.0 - blackLInesHighlight));
				}


				newDisotrtion = static_cast<int>(newDisotrtion * vignette);

				image(i, j, k) = clamp(newDisotrtion, 0, 255); 
			}
			
		}
	}
}


void PurpleImageFilter(Image& image)
{

	int purblePower = 50;
	double R, G, B;
	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			
			R = image(i, j, 0) + purblePower;
			G = image(i, j, 1) - purblePower / 2;
			B = image(i, j, 2) + purblePower;

			image(i, j, 0) = clamp(static_cast<int>(R), 0, 255);
			image(i, j, 1) = clamp(static_cast<int>(G), 0, 255);
			image(i, j, 2) = clamp(static_cast<int>(B), 0, 255);


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
	int threshold = 20;

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

	switch(startChoice)
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

	//Image image = LoadImage();

	stack<Image> apliedFilter;
	vector<string> filterHistory;

	stack<Image> redoFilter;
	stack<string> redoHistory ;



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
				/*while (!redoFilter.empty()) redoFilter.pop();
				while (!redoHistory.empty()) redoHistory.pop();*/

				NewFilter(redoFilter, redoHistory);

				apliedFilter.push(image);
				GrayScaleFilter(image);
				filterHistory.push_back("GrayScale");

				
				pause();
				break;
			}
			case 2:
			{
				/*while (!redoFilter.empty()) redoFilter.pop();
				while (!redoHistory.empty()) redoHistory.pop();*/

				NewFilter(redoFilter, redoHistory);

				apliedFilter.push(image);
				BlackAndWhiteFilter(image);
				filterHistory.push_back("BlackAndWhite");

				pause();
				break;
			}
			case 3:
			{
				/*while (!redoFilter.empty()) redoFilter.pop();
				while (!redoHistory.empty()) redoHistory.pop();*/

				NewFilter(redoFilter, redoHistory);

				apliedFilter.push(image);
				IvertImageFilter(image);
				filterHistory.push_back("InvertColors");

				
				pause();

				break;
			}
			case 4:
			{
				/*while (!redoFilter.empty()) redoFilter.pop();
				while (!redoHistory.empty()) redoHistory.pop();*/

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
					if(!apliedFilter.empty())
					{
						cout << "No flip applied.\n";
						apliedFilter.pop();
						break;
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
				if (x < 0 || y < 0 || Cwidth <= 0 || Chight <= 0) {
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
				/*while (!redoFilter.empty()) redoFilter.pop();
				while (!redoHistory.empty()) redoHistory.pop();*/

				NewFilter(redoFilter, redoHistory);
				
				apliedFilter.push(image);
				int newWidth, newHight;
				cout << "Enter new width and height for resizing: ";
				cin >> newWidth >> newHight;
				if (newWidth <= 0 || newHight <= 0) {
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
				infrared_color(image);
				filterHistory.push_back("InfraredColor");
				pause();
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
				break;
			}

			case 99:
			{
				if (!apliedFilter.empty())
				{

					redoFilter.push(image);
					image = apliedFilter.top();
					
					apliedFilter.pop();

					if( !filterHistory.empty() )
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

			case 0:
			{
				running = false;
				cout << "Exiting application.\n";
				break;
			}
			default:
			{
				cout << "Invalid choice. Please try again.\n";
				break;
			}
			}




		}
		catch (const exception&)
		{
			cout << "\nAn error occurred. Please try again.\n";
		}
	}


	return 0;






	

	


	
}




/*
Image image = LoadImage();









SaveImage(image);
*/

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
	//Image Resized = ImageResizeFilter(image, 2000, 2000);
	//InfraredImageFilter(image);
	//SaveImage(Resized);
	//IR(image);
	//infrared_color(image);
	//DetectEdges(image);
	//RotateImageFilter90(image);
	//SunLightImageFilter(image, 25);
	//OldTVImageFilter(image);
	//PurpleImageFilter(image);
	//DetectEdges(image);


//mergeImages(image);

	//SaveImage(Cropped);

	//SaveImage(image);


