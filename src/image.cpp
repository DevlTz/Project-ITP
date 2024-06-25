#include "../inc/Image.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Construtor padrão da classe Image
Image::Image() : width(0), height(0), maxColorValue(0), pixels(nullptr) {}

bool Image::loadImage(string &filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	string format;
	file >> format;

	// Verifica se o formato é P3
	if (format != "P3")
	{
		return false;
	}

	file >> width >> height >> maxColorValue;

	// Aloca memória para os pixels da imagem
	pixels = new Pixel *[height];
	for (int i = 0; i < height; i++)
	{
		pixels[i] = new Pixel[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			file >> pixels[i][j].r >> pixels[i][j].g >> pixels[i][j].b;
		}
	}
	file.close();
	return true;
};

void Image::saveImage(string &filename)
{
	ofstream file(filename);
	if (!file.is_open())
	{
		cerr << "Erro ao abrir o arquivo para salvar a imagem!" << endl;
		return;
	}
	file << "P3\n"
			 << width << " " << height << "\n"
			 << maxColorValue << "\n";
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			file << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b << " ";
		}
		file << "\n";
	}
	file.close();
}

void Image::printImage()
{
	// Imprime o cabeçalho da imagem
	cout << "P3\n"
			 << width << " " << height << "\n"
			 << maxColorValue << "\n";

	// Imprime os valores de cor (r, g, b) para cada pixel da imagem
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			cout << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b << " ";
		}
		cout << "\n";
	}
}

void Image::changePixelColor(int newR, int newG, int newB)
{
	// Itera por cada pixel da imagem e altera seus valores de cor
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			pixels[i][j].r = newR;
			pixels[i][j].g = newG;
			pixels[i][j].b = newB;
		}
	}
}

void Image::invertImage()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width / 2; ++j)
		{
			// Troca os pixels (i, j) e (i, width - j - 1)
			Pixel temp = pixels[i][j];
			pixels[i][j] = pixels[i][width - j - 1];
			pixels[i][width - j - 1] = temp;
		}
	}
}

