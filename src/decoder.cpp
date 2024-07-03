#include "../inc/Image.h"
#include <fstream>
#include <iostream>
#include <string>
//#include <vector>
using namespace std;

/**
 * @brief Decodifica uma mensagem da imagem usando a técnica de LSB
 * @return Mensagem decodificada da imagem
 */
std::string Image::decodeMessage()
{
	int row = 0, col = 0, color = 0;
	int messageLength = 0;

	// Ler o tamanho da mensagem codificado nos primeiros 8 pixels
	for (int bitIndex = 0; bitIndex < 8; bitIndex++)
	{
		int bitValue;
		if (color == 0)
		{
			bitValue = getLastBit(pixels[row][col].r);
		}
		else if (color == 1)
		{
			bitValue = getLastBit(pixels[row][col].g);
		}
		else
		{
			bitValue = getLastBit(pixels[row][col].b);
		}

		messageLength |= (bitValue << (7 - bitIndex));

		color = (color + 1) % 3;
		if (color == 0)
		{
			col++;
			if (col == width)
			{
				col = 0;
				row++;
			}
		}
	}

	std::string message;
	message.reserve(messageLength);

	for (int charIndex = 0; charIndex < messageLength; charIndex++)
	{
		int charValue = 0;
		for (int bitIndex = 0; bitIndex < 8; bitIndex++)
		{
			int bitValue;
			if (color == 0)
			{
				bitValue = getLastBit(pixels[row][col].r);
			}
			else if (color == 1)
			{
				bitValue = getLastBit(pixels[row][col].g);
			}
			else
			{
				bitValue = getLastBit(pixels[row][col].b);
			}

			charValue |= (bitValue << (7 - bitIndex));

			color = (color + 1) % 3;
			if (color == 0)
			{
				col++;
				if (col == width)
				{
					col = 0;
					row++;
				}
			}
		}

		message.push_back(charValue);
	}

	return message;
}

/**
 * @brief Retorna o valor do último bit (LSB) de um inteiro
 * @param value Valor do qual o último bit será extraído
 * @return Último bit do valor fornecido
 */
int Image::getLastBit(int value) { return value & 1; }

int main()
{
	Image image;
	string inputFileName;

	cout << "Insira um arquivo de entrada: ";
	cin >> inputFileName;

	if (!image.loadImage(inputFileName))
	{
		cout << "Erro: não foi possível carregar a imagem.\n";
		return 1;
	}

	image.printImage();
	cout << "Imagem carregada!\n";
	cout << "--------------------------------------------------------------------"
					"----------------------------\n";

	string decodedMessage = image.decodeMessage();
	if (!decodedMessage.empty())
	{
		cout << "Mensagem decodificada: " << decodedMessage << endl;
	}

	else
	{
		cout << "Não há mensagem codificada na imagem.\n";
	}

	return 0;
}