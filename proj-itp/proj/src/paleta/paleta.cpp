#include <fstream>
#include <string>
#include "paleta.h"

using namespace std;


static int valorHex(char c) { //coverte o hexadec
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}

static int doisDigitosHex(const string& s, int pos) {
  return valorHex(s[pos]) * 16 + valorHex(s[pos + 1]);
}

Paleta::Paleta(int tamanho) {
  this->tamanho = tamanho;           //capacidade
  this->quantidade = 0;              //inicia sem cores
  this->cores = new Cor[tamanho];    //aloca o array de cores
}


Paleta::Paleta(const string& nomeArquivo) {
  int total = 0;
  string linha;
  ifstream contagem(nomeArquivo); //contagem
  if (contagem.is_open()) {
    while (getline(contagem, linha)) {
      if (linha.size() >= 7 && linha[0] == '#') total++;
    }
    contagem.close();
  } else {
    total = 30; 
  }

  tamanho = total;
  quantidade = 0;
  cores = new Cor[tamanho]; 

  ifstream arquivo(nomeArquivo); //arq md leitura
  if (arquivo.is_open()) {
    while (getline(arquivo, linha)) {
      if (linha.size() >= 7 && linha[0] == '#') {
        Cor cor;
        cor.r = doisDigitosHex(linha, 1);
        cor.g = doisDigitosHex(linha, 3);
        cor.b = doisDigitosHex(linha, 5);
        adicionarCor(cor);
      }
    }
    arquivo.close();
  }
}

Paleta::Paleta(const Paleta& copi) {
  tamanho = copi.tamanho;
  quantidade = copi.quantidade;
  cores = new Cor[tamanho];                 //array próprio/não compartilhado
  for (int i = 0; i < quantidade; i++) {
    cores[i] = copi.cores[i];              //"copia" cada cor
  }
}

Paleta::~Paleta() {
  delete[] cores;                           //libera o array
}

int Paleta::obterTamanho() const {
  return tamanho;
}

int Paleta::obterQuantidade() const {
  return quantidade;
}

void Paleta::adicionarCor(const Cor& cor) {
  if (quantidade < tamanho) {               //se tem espaço
    cores[quantidade] = cor;                //primeira posição livre
    quantidade++;
  }
}

Cor Paleta::obterCor(int indice) {
  if (indice < 0 || indice >= quantidade) {
    return Cor {0, 0, 0};                   //índice inválido = preto
  }
  return cores[indice];
}