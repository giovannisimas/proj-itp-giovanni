#include <fstream>
#include <string>
#include "imagem.h"

using namespace std;

Imagem::Imagem(int largura, int altura) {
  if (largura < 0) largura = 0;            //larguras negativas não existem
  if (altura < 0) altura = 0;              //alturas negativas não existem

  this->largura = largura;
  this->altura = altura;

  pixels = new Pixel[largura * altura];    //um único array: célula (x, y) = y * largura + x
  for (int i = 0; i < largura * altura; i++) {
    pixels[i] = Pixel {0, 0, 0};           // todos os pixels começam pretos
  }
}

Imagem::Imagem(const Imagem& outra) {
  largura = outra.largura;
  altura = outra.altura;
  pixels = new Pixel[largura * altura];    //matriz própria, não compartilhada
  for (int i = 0; i < largura * altura; i++) {
    pixels[i] = outra.pixels[i];           //copia cada pixel
  }
}

Imagem::~Imagem() {
  delete[] pixels;                         //libera a matriz
}

int Imagem::obterLargura() const {
  return largura;
}

int Imagem::obterAltura() const {
  return altura;
}

Pixel Imagem::obterPixel(int x, int y) const {
  if (x < 0 || x >= largura || y < 0 || y >= altura) {
    return Pixel {0, 0, 0};                //coordenada inválida: preto
  }
  return pixels[y * largura + x];          //linha y, coluna x
}

void Imagem::definePixel(int x, int y, const Pixel& pixel) {
  if (x >= 0 && x < largura && y >= 0 && y < altura) {   //coordenada válida?
    pixels[y * largura + x] = pixel;
  }
}

bool Imagem::lerPPM(const string& nomeArquivo) {
  ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) return false;    //arquivo inexistente

  //cabeçalho: código, largura, altura e valor máximo
  string codigo;
  int novaLargura, novaAltura, maximo;
  arquivo >> codigo >> novaLargura >> novaAltura >> maximo;
  if (arquivo.fail() || codigo != "P3" || novaLargura < 0 || novaAltura < 0) {
    return false;                          //não é um PPM (P3) válido
  }

  //redimensiona se as dimensões forem diferentes
  if (novaLargura != largura || novaAltura != altura) {
    delete[] pixels;                       //libera a matriz antiga
    largura = novaLargura;
    altura = novaAltura;
    pixels = new Pixel[largura * altura];  //aloca a nova
    for (int i = 0; i < largura * altura; i++) {
      pixels[i] = Pixel {0, 0, 0};
    }
  }

  //pixels: três valores (R G B) para cada pixel, linha por linha
  for (int i = 0; i < largura * altura; i++) {
    arquivo >> pixels[i].r >> pixels[i].g >> pixels[i].b;
    if (arquivo.fail()) return false;      //faltaram valores no arquivo
  }
  return true;
}

bool Imagem::salvarPPM(const string& nomeArquivo) const {
  ofstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) return false;    //não foi possível criar o arquivo

  arquivo << "P3\n";                              //código
  arquivo << largura << " " << altura << "\n";    //dimensões
  arquivo << 255 << "\n";                         //valor máximo de cada componente

  for (int y = 0; y < altura; y++) {              //uma linha da imagem por linha do arquivo
    for (int x = 0; x < largura; x++) {
      Pixel p = pixels[y * largura + x];
      arquivo << p.r << " " << p.g << " " << p.b << "  ";
    }
    arquivo << "\n";
  }
  arquivo.close();
  return true;
}