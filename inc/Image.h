#ifndef IMAGE_H
#define IMAGE_H
#include <string>

class Image {
	private:
		struct Pixel {
			int r, g, b;
		};

		int width, height, maxColorValue;
		Pixel** pixels;

	public:
		Image();
		bool loadImage(std::string &filename);
    void saveImage(std::string &filename);
		void printImage();
		void changePixelColor(int newR, int newG, int newB);
		void invertImage();
		int getLastBit(int value);
		int setLastBit(int value, int bit);
};

#endif
