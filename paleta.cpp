#include <fstream>
#include <string>
#include "paleta.h"

using namespace std;

struct Dados {
  const Paleta* dono; 
  Cor* cores;         
  int tamanho;        
  int quantidade;     
};

const int MAX_PALETAS = 1000;
static Dados tabela[MAX_PALETAS]; 

static Dados* buscar(const Paleta* p) {
  for (int i = 0; i < MAX_PALETAS; i++) {
    if (tabela[i].dono == p) return &tabela[i];
  }
  return nullptr;
}

static Dados* registrar(const Paleta* p, int tamanho) {
  Dados* d = buscar(p);
  if (d != nullptr) {
    delete[] d->cores;
  } 
  else {
    d = buscar(nullptr); // procura uma posição livre
    if (d == nullptr) return nullptr; // tabela cheia
  }

  d->dono = p;
  d->tamanho = tamanho;
  d->quantidade = 0;
  d->cores = new Cor[tamanho];
  return d;
}

static int valorHex(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}

static int doisDigitosHex(const string& s, int pos) {
  return valorHex(s[pos]) * 16 + valorHex(s[pos + 1]);
}

Paleta::Paleta(int tamanho) {
  registrar(this, tamanho);
}

Paleta::Paleta(const string& nomeArquivo) {
  int total = 0;
  string linha;
  ifstream contagem(nomeArquivo);
  if (contagem.is_open()) {
    while (getline(contagem, linha)) {
      if (linha.size() >= 7 && linha[0] == '#') total++;
    }
    contagem.close();
  } else {
    total = 30; 
  }

  registrar(this, total);

  ifstream arquivo(nomeArquivo);
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

int Paleta::obterTamanho() const {
  Dados* d = buscar(this);
  if (d == nullptr) return 0;
  return d->tamanho;
}

int Paleta::obterQuantidade() const {
  Dados* d = buscar(this);
  if (d == nullptr) return 0;
  return d->quantidade;
}

void Paleta::adicionarCor(const Cor& cor) {
  Dados* d = buscar(this);
  if (d != nullptr && d->quantidade < d->tamanho) {
    d->cores[d->quantidade] = cor;
    d->quantidade++;
  }
}

Cor Paleta::obterCor(int indice) {
  Dados* d = buscar(this);
  if (d == nullptr || indice < 0 || indice >= d->quantidade) {
    return Cor {0, 0, 0};
  }
  return d->cores[indice];
}