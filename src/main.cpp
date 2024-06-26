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
	cout << "1. Codificar uma mensagem\n";
	cout << "2. Decodificar uma mensagem\n";
	cout << "3. Inverter imagem\n";
	cin >> option;

	if (option == 3)
	{
		image.invertImage();
		cout << "Imagem invertida com sucesso!\n";
	}
	
	string outputFileName;
	cout << "Digite o nome do arquivo para salvar a imagem modificada:";
	cin >> outputFileName;

	image.saveImage(outputFileName);

	cout << "Imagem modificada salva no arquivo: " << outputFileName << endl;

	return 0;
}
