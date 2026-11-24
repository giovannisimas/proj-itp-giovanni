/**
 * Declaração da classe Imagem.
 */

#pragma once

// Defina aqui a classe Imagem, conforme especificado na etapa 2 do projeto.
// Você pode reaproveitar o tipo Cor definido em paleta.h, para representar as cores dos pixels da imagem.
// Para isso, você pode definir um tipo Pixel como um alias para Cor, ou seja, Pixel será apenas outro nome para Cor.

#include "../paleta/paleta.h"
using Pixel = Cor; // Pixel agora é outro nome para Cor, representando a cor de um pixel da imagem.

// Lembre-se de:
// 1. verificar no arquivo de teste o nome correto da classe, dos métodos que você deve implementar, bem como os
//    parâmetros e tipos de retorno de cada método.
// 2. documentar a classe e seus métodos, seguindo o padrão do arquivo paleta.h.
// 3. implementar no arquivo imagem.cpp os métodos da classe.
class Imagem {
public:
    Imagem(int largura = 0, int altura = 0);
    
    Imagem(const Imagem& outra);
    
    ~Imagem();
    
    int obterLargura() const;
    
    int obterAltura() const;
    
    Pixel obterPixel(int x, int y) const; //devolve pixel
    
    void definePixel(int x, int y, const Pixel& pixel); //altera o pix
    
    bool lerPPM(const std::string& nomeArquivo);
    
    bool salvarPPM(const std::string& nomeArquivo) const;


private:
  int largura;    // quantidade de colunas
  int altura;     // quantidade de linhas
  Pixel* pixels;  // array com a largura * altura pixels, l por l
};