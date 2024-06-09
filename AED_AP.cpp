// Leonardo Melo Crispim
// Aline Daffiny Ferreira Gomes
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

typedef string Comando;

class Nee {
public:
  string CommandNee; // posicao da lista
  int posicao;       // posicao do comando na lista

  Nee() { // metodo construtor
    CommandNee = "";
    posicao = 0;
  }

  Nee(string comando, int pos) { // construtor com parametros
    CommandNee = comando;
    posicao = pos;
  }

  int getPosicao() { return posicao; } 
};

template <typename T>
class Lista { //template pra generalizar a lista
public:
  T *programaNee;   // Vetor
  int tamanho;      // Tamanho do vetor
  int tamanhoAtual; // Tamanho da lista

public:
  Lista(int _tamanho) { // Cria a lista com o tamanho desejado
    tamanho = _tamanho;
    tamanhoAtual = 0;
    programaNee = new T[tamanho];
  }

  ~Lista() { // Metodo destrutor
    delete[] programaNee;
  }

  void inserir(T nee) {                               // insere na lista vendo se o tamanho da lista e menor
    if (tamanhoAtual < tamanho) {                    // que o do vetor (maximo) e se for igual ao maximo
      programaNee[tamanhoAtual] = nee;               // mostra q nao e possivel
      tamanhoAtual++;
    } 
    else {
      cout << "Lista cheia, nao e possivel inserir." << endl;
    }
  }

  void remover(int posicao) {                             // remove o elemento da posicao desejada se ela existir
    if (posicao < tamanhoAtual) {
      for (int i = posicao; i < tamanhoAtual - 1; i++) {
        programaNee[i] = programaNee[i + 1];
      }
      tamanhoAtual--;
    }
    else {
      cout << "Posicao invalida." << endl;
    }
  }

  int buscar(string k) {                         // busca o comando na lista e retorna a posicao
    for (int i = 0; i < tamanhoAtual; i++) {
      if (programaNee[i].CommandNee == k) {
        return programaNee[i].posicao;
      }
    }

    return -1;                                  // Retorna -1 se nao encontrar item
  }

  int buscarPrimeiraLetra(string letra) {
    for (int i = 0; i < getTamanho(); ++i) {
      if (programaNee[i].CommandNee.at(0) == letra[0]) {
        return programaNee[i].posicao;
      }
    }
    return -1; // Retorna -1 se nao encontrar nenhuma correspondencia
  }

  int sucessor(string k) {                        // encontra a posicao do sucessor do comando 
    for (int i = 0; i < tamanhoAtual; i++) {
      if (programaNee[i].CommandNee == k) {
        int pos = programaNee[i].posicao++;
        return pos;
      }
    }
    return -1;
  }

  string Buscarpos(int pos) {                        //encontra a string do comando pela posicao
    for (int i = 0; i < tamanhoAtual; i++) {
      if (programaNee[i].posicao == pos) {
        return programaNee[i].CommandNee;
      }
    }
    return Nee().CommandNee;
  }

  T getProgramaNee(int pos) { return programaNee[pos]; }

  int getTamanho() { return tamanhoAtual; }

  int getTamanhoMax() { return tamanho; }
};

// Definicao da estrutura de no, agora como template
template <typename T>
struct No {
  T dadoDoNo;
  No* prox;

  No(T valor) : dadoDoNo(valor), prox(nullptr) {}
};

// Definicao da classe Pilha como template
template <typename T>
class Pilha {
private:
  No<T>* topo;
  int pos;

public:
  // Construtor
  Pilha() : topo(nullptr), pos(0) {}

  // Destrutor
  ~Pilha() {
    while (!estaVazia()) {
      desempilha();
    }
  }

  // Verifica se a pilha esta vazia
  bool estaVazia() const {
    return topo == nullptr;
  }

  // Empilha um valor
  void empilha(T valor) {
    No<T>* aux = new No<T>(valor);
    aux->prox = topo;
    topo = aux;
    pos++;
  }

  // Desempilha o topo da pilha
  T desempilha() {
    if (estaVazia()) {
      cout << "Pilha vazia, nao e possivel desempilhar." << endl;
      return T(); // Retorna um valor padrao do tipo T
    }

    T dado_atual = topo->dadoDoNo;
    No<T>* antigo = topo;
    topo = topo->prox;
    delete antigo;
    pos--;

    return dado_atual;
  }

  // Retorna a posicao atual (tamanho da pilha)
  int getPos() const {
    return pos;
  }
};

string chama_func_str(string k, int posicao, Lista<Nee> *lista, Pilha<int> *pilha) {   // chama a funcao desejada 
  string temp = "";
  int func = 0;

  temp = k.substr(0, 1);
  func = lista->buscarPrimeiraLetra(temp);
  temp = lista->Buscarpos(func + 1);

  pilha->empilha(posicao);

  return temp;
}

void prox(string &proximo, int &tam, int &posicao, Lista<Nee> *lista) { // coloca o proximo comando na string e define seu tamanho
  posicao++;
  proximo = lista->Buscarpos(posicao);
  tam = proximo.length();
}

string comando_sem_tab(string comando) { // remove os tabs do comando
  int tam = (int)comando.length();

  if (tam > 0) {
    int ponto_inicial = -1;
    for (int i = 0; i < tam; i++) {
      char atual =
          comando.at(i); // itera char por char ate nao ser um espaco/tab
      if (atual != ' ' && atual != '\t') {
        ponto_inicial = i;
        break;
      }
    }

    // se encontramos o indice de inicio
    if (ponto_inicial != -1) {
      return comando.substr(ponto_inicial);
    }
  }

  return string("");
}

void interpretar(string comando, Lista<Nee> *lista, Pilha<int> *pilha) {
  const int tam = (int)lista->tamanhoAtual;
  int inicio = lista->buscar(comando); // busca a posicao do comando na lista

  if (inicio != -1) {
    int linha_atual = inicio + 1;

    while (true) {
      if (linha_atual != tam) {
        string cmd_atual = lista->Buscarpos(linha_atual);
        if (cmd_atual.empty()) {
          // linha vazia, retorna do metodo
          if (pilha->estaVazia()) {
            break; // sai do loop
          }
          else { // se a pilha tem algum valor de retorno, voltamos para
                   // aquela linha
            linha_atual = pilha->desempilha();
          }
        }
        else { // processa o comando da linha atual
          string sem_tab = comando_sem_tab(cmd_atual);

          if (sem_tab.length() == 1) {                 // chamada de funcao
            string func = sem_tab.substr(0, 1) + " :"; // monta nome da funcao
            pilha->empilha(linha_atual);       // salva a linha atual na pilha
            linha_atual = lista->buscar(func); // linha atual agora e a funcao
          }

          // sem tokenizar, infelizmente vai ser preciso ficar validando tamanho
          // de string e usando substrings
          else if (sem_tab.length() >= 5) { // "PRINT"
            if (sem_tab.substr(0, 5) == "PRINT") {
              string numero = sem_tab.substr(6);
              int numero_i = atoi(numero.c_str()); // converte string para
                                                   // inteiro usando <cstring>
              cout << numero_i << " ";
            }
          }
        }
      }
      else {
        break;
      }

      ++linha_atual;
    }
  }
}

int main() {
  Lista<Nee> NeeList(300);
  Pilha<int> NeeStack;
  int pos = 0;

  char linha[128];

  while (true) { // leitura de dados
    Nee nee;

    cin.getline(linha, sizeof(linha));
    nee.CommandNee = string(linha);

    nee.posicao = pos;
    NeeList.inserir(nee);
    pos++;

    if (nee.CommandNee == "~") {
      break;
    }
  }

  string comando = "Z :";

  interpretar(comando, &NeeList, &NeeStack);
  cout << endl;
  cin.ignore();

  return 0;
}