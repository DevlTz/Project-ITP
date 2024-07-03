#include "../inc/Image.h"
#include <fstream>
#include <iostream>
#include <string>
//#include <vector>
using namespace std;

/**
 * @brief Codifica uma mensagem na imagem usando a técnica de LSB
 * @param message Mensagem a ser codificada na imagem
 */
void Image::encodeMessage(std::string &message)
{
	int maxWidth = width * height * 3;

	if (message.size() * 8 > maxWidth || message.size() > 255 || message.empty())
	{
		std::cout << "Mensagem não pode ser escrita na imagem.\n";
		return;
	}

	// Codificar o tamanho da mensagem nos primeiros 8 pixels
	int messageLength = message.size();
	int bits[8];
	charToBits(static_cast<char>(messageLength), bits);

	int row = 0, col = 0, color = 0;
	for (int bitIndex = 0; bitIndex < 8; bitIndex++)
	{
		int bitValue = bits[bitIndex];

		if (color == 0)
		{
			pixels[row][col].r = setLastBit(pixels[row][col].r, bitValue);
		}
		else if (color == 1)
		{
			pixels[row][col].g = setLastBit(pixels[row][col].g, bitValue);
		}
		else
		{
			pixels[row][col].b = setLastBit(pixels[row][col].b, bitValue);
		}

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

	for (char ch : message)
	{
		int bits[8];
		charToBits(ch, bits);
		for (int bitIndex = 0; bitIndex < 8; bitIndex++)
		{
			int bitValue = bits[bitIndex];

			if (color == 0)
			{
				pixels[row][col].r = setLastBit(pixels[row][col].r, bitValue);
			}
			else if (color == 1)
			{
				pixels[row][col].g = setLastBit(pixels[row][col].g, bitValue);
			}
			else
			{
				pixels[row][col].b = setLastBit(pixels[row][col].b, bitValue);
			}

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
	}
}

/**
 * @brief Converte um caractere em um array de bits
 * @param ch Caractere a ser convertido
 * @param bits Array de inteiros onde os bits serão armazenados
 */
void Image::charToBits(char ch, int bits[8])
{
	for (int i = 7; i >= 0; --i)
	{
		bits[i] = ch % 2;
		ch /= 2;
	}
}

/**
 * @brief Define o último bit (LSB) de um inteiro
 * @param value Valor cujo último bit será definido
 * @param bit Novo valor do último bit (0 ou 1)
 * @return Novo valor com o último bit alterado
 */
int Image::setLastBit(int value, int bit) { return (value & ~1) | bit; }

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

	string message;
	cout << "Digite a mensagem para codificar: ";
	cin.ignore();
	getline(cin, message);
	image.encodeMessage(message);
	cout << "Mensagem codificada na imagem.\n";

	string outputFileName;
	cout << "Digite o nome do arquivo para salvar a imagem modificada: ";
	cin >> outputFileName;

	if (outputFileName == inputFileName)
	{
		cout << "Deseja sobrescrever a imagem? (S | N): ";
		char overwriteOption;
		cin >> overwriteOption;
		if (overwriteOption == 'S' || overwriteOption == 's')
		{
			image.saveImage(inputFileName);
			cout << "Imagem sobrescrita salva no arquivo: " << inputFileName << endl;
		}
		else
		{
			cout << "Arquivo resultante já existe.\n";
			return 1;
		}
	}
	else
	{
		image.saveImage(outputFileName);
		cout << "Imagem alterada salva no arquivo: " << outputFileName << endl;
	}

	return 0;
}