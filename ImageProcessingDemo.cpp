// A demo for converting image to gray scale

//#include <iostream>
//using namespace std;
//#include "Image_Class.h"
//
//int main() {
//    string filename;
//    cout << "Pls enter colored image name to turn to gray scale: ";
//    cin >> filename;
//
//    Image image(filename);
//
//    for (int i = 0; i < image.width; ++i) {
//        for (int j = 0; j < image.height; ++j) {
//            unsigned  int avg = 0; // Initialize average value
//
//            for (int k = 0; k < 3; ++k) {
//                avg += image(i, j, k); // Accumulate pixel values
//            }
//
//            avg /= 3; // Calculate average
//
//            // Set all channels to the average value
//            image(i, j, 0) = avg;
//            image(i, j, 1) = avg;
//            image(i, j, 2) = avg;
//        }
//    }
//
//    cout << "Pls enter image name to store new image\n";
//    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
//
//    cin >> filename;
//    image.saveImage(filename);
//
//    return 0;
//}

//#include <iostream>
//#include <string> // It's good practice to include <string> when using std::string
//#include "Image_Class.h"
//
//using namespace std;
//
//int main() {
//    string filename;
//    cout << "Pls enter colored image name to turn to gray scale: ";
//    cin >> filename;
//
//    try { // It's a good idea to wrap image loading in a try-catch block
//        Image image(filename);
//
//        // Corrected loops
//        for (int i = 0; i < image.height; ++i) {    // Correct: Iterate over rows (height)
//            for (int j = 0; j < image.width; ++j) { // Correct: Iterate over columns (width)
//
//                unsigned int avg = 0;
//                for (int k = 0; k < 3; ++k) {
//                    // Now image(i, j, k) correctly accesses row `i` and column `j`
//                    avg += image(j, i, k);
//                }
//                avg /= 3;
//
//                image(j, i, 0) = avg;
//                image(j, i, 1) = avg;
//                image(j, i, 2) = avg;
//            }
//        }
//
//        cout << "Pls enter image name to store new image\n";
//        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
//        cin >> filename;
//        image.saveImage(filename);
//
//    }
//    catch (const std::exception& e) {
//        cerr << "Error: " << e.what() << endl;
//    }
//
//    return 0;
//}

//#include <iostream>
//#include <string>
//#include "Image_Class.h"
//
//using namespace std;
//
//int main() {
//    string filename;
//    cout << "Pls enter colored image name to turn to gray scale: ";
//    cin >> filename;
//
//    try {
//        Image image(filename);
//
//        int w = image.width;
//        int h = image.height;
//        int c = image.channels; // make sure Image exposes this
//
//        cout << "Loaded " << w << "x" << h << " image with "
//            << c << " channels.\n";
//
//        // 1-channel image: already grayscale
//        if (c == 1) {
//            cout << "Image already grayscale. No conversion needed.\n";
//        }
//        // 3-channel image: normal RGB
//        else if (c == 3) {
//            for (int y = 0; y < h; ++y) {
//                for (int x = 0; x < w; ++x) {
//                    unsigned int avg = 0;
//                    for (int k = 0; k < 3; ++k) {
//                        avg += image(x, y, k);
//                    }
//                    avg /= 3;
//                    for (int k = 0; k < 3; ++k) {
//                        image(x, y, k) = static_cast<unsigned char>(avg);
//                    }
//                }
//            }
//        }
//        // 4-channel image: RGBA (preserve alpha)
//        else if (c == 4) {
//            for (int y = 0; y < h; ++y) {
//                for (int x = 0; x < w; ++x) {
//                    unsigned int avg = 0;
//                    for (int k = 0; k < 3; ++k) { // R,G,B
//                        avg += image(x, y, k);
//                    }
//                    avg /= 3;
//                    for (int k = 0; k < 3; ++k) {
//                        image(x, y, k) = static_cast<unsigned char>(avg);
//                    }
//                    // leave image(x,y,3) (alpha) untouched
//                }
//            }
//        }
//        else {
//            cerr << "Unsupported channel count (" << c << ").\n";
//            return 1;
//        }
//
//        cout << "Pls enter image name to store new image\n";
//        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
//        cin >> filename;
//        image.saveImage(filename);
//
//    }
//    catch (const std::exception& e) {
//        cerr << "Error: " << e.what() << endl;
//        return 1;
//    }
//
//    return 0;
//}


//#include <iostream>
//#include <string>
//#include "Image_Class.h"
//
//using namespace std;
//
//int main() {
//    string filename;
//    cout << "Pls enter colored image name to turn to gray scale: ";
//    cin >> filename;
//
//    try {
//        Image image(filename);
//
//        int w = image.width;
//        int h = image.height;
//        int c = image.channels;
//
//        cout << "Loaded " << w << "x" << h << " image with "
//            << c << " channels.\n";
//
//        if (c < 3) {
//            cout << "Image already grayscale (" << c << " channel[s]).\n";
//        }
//        else {
//            // We assume operator()(row,col,channel)
//            for (int row = 0; row < h; ++row) {
//                for (int col = 0; col < w; ++col) {
//                    unsigned int avg = 0;
//                    for (int k = 0; k < 3; ++k) {
//                        avg += image(row, col, k); // row, col, channel
//                    }
//                    avg /= 3;
//                    for (int k = 0; k < 3; ++k) {
//                        image(row, col, k) = static_cast<unsigned char>(avg);
//                    }
//                    // if c==4 leave alpha channel (k==3) untouched
//                }
//            }
//        }
//
//        cout << "Pls enter image name to store new image\n";
//        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
//        cin >> filename;
//        image.saveImage(filename);
//
//    }
//    catch (const std::exception& e) {
//        cerr << "Error: " << e.what() << endl;
//        return 1;
//    }
//
//    return 0;
//}


//#include <iostream>
//#include "Image_Class.h"
//#include <vector>
//#include <cmath>
//#include <algorithm>
//
//using namespace std;
//
//Image LoadImage()
//{
//	string filename;
//	cout << "Enter Image name with it's extention: ";
//	try {
//		cin >> filename;
//		Image image(filename);
//		return image;
//
//	}
//	catch (const std::exception&)
//	{
//		cout << "Failed To load";
//
//	}
//
//}
//
//
//void SaveImage(Image& image)
//{
//	string filename;
//	cout << "\nPls enter image name to store new image\n";
//	cout << "and specify extension .jpg, .bmp, .png, .tga: ";
//	cin >> filename;
//	try
//	{
//		image.saveImage(filename);
//
//		cout << "Image saved successfully";
//	}
//	catch (const std::exception&)
//	{
//		cout << "Image FAILED to save";
//	}
//}
//
//
//
//void Rotation(Image& image) {
//
//	cout << "You Are Now on Image Rotaion Filter... :)\n";
//	short degree = 0;
//	cout << "Please Enter Rotation Degree: 90 - 180 - 270? ";
//	cin >> degree;
//
//
//	if (degree == 90) {
//		Image rotated(image.height, image.width);
//		for (int i = 0; i < image.width; i++) {
//			for (int j = 0; j < image.height; j++) {
//				for (int k = 0; k < 3; k++) {
//					rotated(j, image.width - 1 - i, k) = image(i, j, k);
//				}
//			}
//		}
//		image = rotated;
//	}
//
//	else if (degree == 180) {
//		Image rotated(image.width, image.height);
//		for (int i = 0; i < image.width; i++) {
//			for (int j = 0; j < image.height; j++) {
//				for (int k = 0; k < 3; k++) {
//					rotated(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
//				}
//			}
//		}
//		image = rotated;
//	}
//
//	else if (degree == 270) {
//		Image rotated(image.height, image.width);
//		for (int i = 0; i < image.width; i++) {
//			for (int j = 0; j < image.height; j++) {
//				for (int k = 0; k < 3; k++) {
//					rotated(image.height - 1 - j, i, k) = image(i, j, k);
//				}
//			}
//		}
//		image = rotated;
//	}
//}
//
//
//
//
//int main() {
//	Image X;
//	X = LoadImage();
//	//Rotation(X);
//	SaveImage(X);
//	
//
//
//
//
//	return 0;
//}
