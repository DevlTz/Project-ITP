#include "../inc/Image.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Image image;
	string inputFileName;

	cout << "Arquivo de entrada:";
	cin >> inputFileName;

	if (!image.loadImage(inputFileName))
	{
		cout << "Erro: não foi possível carregar a imagem.\n";
		return 1;
	}

	image.printImage();
	cout << "Imagem carregada!\n";

	int option;
	cout << "Escolha uma opção:\n";
	cout << "1. Mudar a cor dos pixels\n";
	cout << "2. Codificar uma mensagem\n";
	cout << "3. Decodificar uma mensagem\n";
	cin >> option;

	if (option == 1)
	{
		int newR, newG, newB;
		cout << "Digite os novos valores para R, G e B: ";
		cin >> newR >> newG >> newB;

		image.changePixelColor(newR, newG, newB);
		cout << "Nova imagem gerada:\n";
	}

	string outputFileName;
	cout << "Digite o nome do arquivo para salvar a imagem modificada: ";
	cin >> outputFileName;

	image.saveImage(outputFileName);

	cout << "Imagem modificada salva no arquivo: " << outputFileName << endl;

	return 0;
}
