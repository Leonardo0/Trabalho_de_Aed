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

  void print() { // Pra efeito de testes mostra os atributos
    cout << CommandNee << endl;
  }

  int getPosicao() { return posicao; } 
};

template <typename T> class Lista { //template pra generalizar a lista
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

  void
  remover(int posicao) {                             // remove o elemento da posicao desejada se ela existir
    if (posicao < tamanhoAtual) {
      for (int i = posicao; i < tamanhoAtual - 1; i++) {
        programaNee[i] = programaNee[i + 1];
      }
      tamanhoAtual--;
    } else {
      cout << "Posicao invalida." << endl;
    }
  }

  void print() {                                  // outro comando pra efeito de testes que mostra os elementos
    cout << "Comandos: \n";                      // da lista
    for (int i = 0; i < tamanhoAtual; i++) {
      programaNee[i].print();
    }
    cout << endl;
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

class No { // No da pilha
public:
  int dadoDoNo; // valor do no
  No *prox;     // proximo no

  No(int dado) { // construtor
    dadoDoNo = dado;
    prox = nullptr;
  }
};

class Pilha { // fiz so o no do topo pq n entendi como fazer com o fundo mas
              // assim ta funcionando bem e ta simples
private:
  No *topo;
  int pos;

public:
  Pilha() { // construtor
    topo = nullptr;
  }

  ~Pilha() { // destrutor
    while (!estaVazia()) {
      desempilha();
    }
  }

  bool estaVazia() { // verifica se a pilha esta vazia
    return topo == nullptr;
  }

  void
  empilha(int valor) { // cria um no auxiliar e empilha ele aumentando a pilha
    No *aux = new No(valor);

    if (estaVazia()) { // sem elementos, aux se torna o topo
      topo = aux;
    } else {
      // aux aponta para antiga cabeca, se tornando o topo
      No *anterior = topo;
      aux->prox = anterior;

      topo = aux;
    }
  }

  int desempilha() { // desempilha o topo da pilha tambem com um no auxiliar
    if (estaVazia()) {
      cout << "Pilha vazia, nao e possivel desempilhar." << endl;
      return -1;
    }

    // desempilhando sempre retorna o valor ate entao
    int dado_atual = topo->dadoDoNo;

    // salva o ponteiro da cabeca ate entao, para deletar
    No *antigo = topo;
    No *prox = topo->prox;

    // cabeca agora e o proximo elemento da cabeca anterior, mesmo se nulo
    topo = prox;
    delete antigo;

    return dado_atual;
  }

  int getPos() { return pos; }
};

string chama_func_str(string k, int posicao, Lista<Nee> *lista, Pilha *pilha) {   // chama a funcao desejada 
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

void interpretar(string comando, Lista<Nee> *lista, Pilha *pilha) {
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
          } else { // se a pilha tem algum valor de retorno, voltamos para
                   // aquela linha
            linha_atual = pilha->desempilha();
          }
        } else { // processa o comando da linha atual
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
      } else {
        break;
      }

      ++linha_atual;
    }
  }
}

int main() {
  Lista<Nee> NeeList(300);
  Pilha NeeStack;
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

  cout << endl;
  cout << endl;

  string comando = "Z :";

  interpretar(comando, &NeeList, &NeeStack);
  cout << endl;
  cin.ignore();

  return 0;
}