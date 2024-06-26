#include "../../inc/Image.h"
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
		cout << "Arquivo original não existe.\n";
		return 0;
	}
    else if (image.loadImage(inputFileName) == )
	{
		cout << "Arquivo original não existe.\n";
		return 0;
	}




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

