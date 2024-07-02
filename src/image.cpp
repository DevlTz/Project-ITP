#include "../inc/Image.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Classe que representa uma imagem
Image image;

// Construtor padrão da classe Image
Image::Image() : width(0), height(0), maxColorValue(0), pixels(nullptr) {}

/**
 * @brief Carrega uma imagem de um arquivo
 * @param filename Nome do arquivo que contém a imagem
 * @return true se a imagem foi carregada com sucesso, false caso contrário
 */
bool Image::loadImage(string &filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}

	string format;
	file >> format;

	if (format != "P3")
	{
		return false;
	}

	file >> width >> height >> maxColorValue;

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

/**
 * @brief Salva a imagem em um arquivo
 * @param filename Nome do arquivo onde a imagem será salva
 */
void Image::saveImage(string &filename)
{
	ofstream file(filename, ofstream::out | ofstream::trunc);
	if (!file.is_open())
	{
		cout << "Erro ao abrir o arquivo para salvar a imagem!" << endl;
		return;
	}

	file << "P3\n"
			 << width << " " << height << "\n"
			 << maxColorValue << "\n";
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			file << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b
					 << " ";
		}
		file << "\n";
	}
	file.close();
}

/**
 * @brief Imprime a imagem no console
 */
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
			cout << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b
					 << " ";
		}
		cout << "\n";
	}
}

/**
 * @brief Inverte a imagem horizontalmente
 */
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