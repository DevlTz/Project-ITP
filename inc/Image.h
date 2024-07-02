#ifndef IMAGE_H
#define IMAGE_H
#include <string>

//g++ -Iinclude -o decode src/decoder.cpp src/image.cpp
//g++ -Iinclude -o encode src/encode.cpp src/image.cpp 

/**
 * @brief Classe que representa uma imagem e fornece métodos para manipulação e esteganografia.
 */
class Image
{
public:
	/**
	 * @brief Estrutura que representa um pixel com componentes de cor vermelha, verde e azul.
	 */
	struct Pixel
	{
		int r; ///< Componente vermelha do pixel.
		int g; ///< Componente verde do pixel.
		int b; ///< Componente azul do pixel.
	};

	/**
	 * @brief Construtor padrão da classe Image.
	 */
	Image();

	/**
	 * @brief Carrega uma imagem de um arquivo.
	 * @param filename Nome do arquivo que contém a imagem.
	 * @return true se a imagem foi carregada com sucesso, false caso contrário.
	 */
	bool loadImage(std::string &filename);

	/**
	 * @brief Salva a imagem em um arquivo.
	 * @param filename Nome do arquivo onde a imagem será salva.
	 */
	void saveImage(std::string &filename);

	/**
	 * @brief Imprime a imagem no console.
	 */
	void printImage();

	/**
	 * @brief Inverte a imagem horizontalmente.
	 */
	void invertImage();

	/**
	 * @brief Codifica uma mensagem na imagem usando a técnica de LSB.
	 * @param message Mensagem a ser codificada na imagem.
	 */
	void encodeMessage(std::string &message);

	/**
	 * @brief Decodifica uma mensagem da imagem usando a técnica de LSB.
	 * @return Mensagem decodificada da imagem.
	 */
	std::string decodeMessage();

private:
	int width;				 ///< Largura da imagem.
	int height;				 ///< Altura da imagem.
	int maxColorValue; ///< Valor máximo de cor na imagem.
	Pixel **pixels;		 ///< Matriz de pixels que compõem a imagem.

	/**
	 * @brief Retorna o valor do último bit (LSB) de um inteiro.
	 * @param value Valor do qual o último bit será extraído.
	 * @return Último bit do valor fornecido.
	 */
	int getLastBit(int value);

	/**
	 * @brief Define o último bit (LSB) de um inteiro.
	 * @param value Valor cujo último bit será definido.
	 * @param bit Novo valor do último bit (0 ou 1).
	 * @return Novo valor com o último bit alterado.
	 */
	int setLastBit(int value, int bit);

	/**
	 * @brief Converte um caractere em um array de bits.
	 * @param ch Caractere a ser convertido.
	 * @param bits Array de inteiros onde os bits serão armazenados.
	 */
	void charToBits(char ch, int bits[8]);
};

#endif