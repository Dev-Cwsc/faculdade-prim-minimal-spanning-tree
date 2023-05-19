// Declarando as bibliotecas
#include <limits.h>
#include <iostream>
#include <fstream>
#include <time.h>

// Para facilitar a escrita do código e não ter que referenciar à classe std
using namespace std;

// Telas da aplicação
const string telaInicial = "========== MINIMUM SPANNING TREE (PRIM METHOD) ==========\n"
                           "|                                                       |\n"
                           "| Select an option:                                     |\n"
                           "|                                                       |\n"
                           "|    1 -> Generate minimum tree                         |\n"
                           "|    2 -> About the algorithm                           |\n"
                           "|    3 -> About this software                           |\n"
                           "|    4 -> How to use this application                   |\n"
                           "|    0 -> Exit                                          |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                                       |\n"
                           "|                                         v1.0.0        |\n"
                           "|                                                       |\n"
                           "=========================================================\n"
                           "Type a number option and press ENTER: ";

const string avisoGerarGrafo = "======================== WARNING ========================\n"
                               "|                                                       |\n"
                               "|   If the file 'grafo.txt' has been writed at the      |\n"
                               "|   wrong way, the application WILL NOT WORK correctly! |\n"
                               "|   Select '4' in main menu for more information.       |\n"
                               "|                                                       |\n"
                               "=========================================================\n";

const string avisoArquivoInvalido = "======================== WARNING ========================\n"
                                    "|                                                       |\n"
                                    "|   Error! The file 'grafo.txt' is corrupted or got     |\n"
                                    "|   deleted, please enter a valid file with the name    |\n"
                                    "|   'grafo', format '.txt' and reboot this application  |\n"
                                    "|   to continue.                                        |\n"
                                    "=========================================================\n";

const string sobreAlgoritmo = "================== ABOUT THE ALGORITHM ==================\n"
                              "|                                                       |\n"
                              "|   The PRIM algorithm consists of finding the lowest   |\n"
                              "|   cost to go through the vertices of a non-cyclic     |\n"
                              "|   graph. This implementation was made using the       |\n"
                              "|   adjacency list representation, which has asymptotic |\n"
                              "|   cost O(V+E) and is preferred when there is an input |\n"
                              "|   graph whose number of edges is less than the number |\n"
                              "|   of vertices squared (E < V^2). There is another way |\n"
                              "|   to represent a graph (not used in this software),   |\n"
                              "|   the adjacency matrix, which has an asymptotic cost  |\n"
                              "|   O(V^2).                                             |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "|   References: Introduction to Algorithms - Thomas H.  |\n"
                              "|   Cormen (third edition).                             |\n"
                              "|                                                       |\n"
                              "=========================================================\n";

const string sobreSoftware  = "================== ABOUT THIS SOFTWARE ==================\n"
                              "|                                                       |\n"
                              "|   This software was developed with the purpose of     |\n"
                              "|   demonstrating the knowledge about algorithms to     |\n"
                              "|   solve problems of graphs, acquired throughout the   |\n"
                              "|   discipline of Design and Analysis of Algorithms.    |\n"
                              "|   The main objective of this software is to           |\n"
                              "|   demonstrate the application of the PRIM algorithm   |\n"
                              "|   to find the smallest path that runs through all     |\n"
                              "|   the vertices of an input graph. This software is    |\n"
                              "|   part of the final work of the discipline and was    |\n"
                              "|   not made for profit.                                |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "|   Developed by: Carlos Willian Silva Camargos.        |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "|                                                       |\n"
                              "=========================================================\n";

const string comoUsar = "============== HOW TO USE THIS APPLICATION ==============\n"
                        "|                                                       |\n"
                        "|   1st step -> Create a txt file named 'grafo.txt' and |\n"
                        "|   place it on the same folder where this application  |\n"
                        "|   is.                                                 |\n"
                        "|   2nd step -> Open the file 'grafo.txt' and write the |\n"
                        "|   graph exactly in the following order: use the first |\n"
                        "|   line to type the number of vertices, and then type  |\n"
                        "|   each edge in the subsequent lines (only one edge    |\n"
                        "|   per line); the format of the edges is: source       |\n"
                        "|   vertex, destination vertex, and weight of the edge  |\n"
                        "|   separated by a 'space' character (' ').             |\n"
                        "|   EX: 10                                              |\n"
                        "|       0 1 6                                           |\n"
                        "|   (graph with 10 vertices and an edge connecting 0    |\n"
                        "|   vertex to 1 vertex with weight 6).                  |\n"
                        "|   3rd step -> Save the file, open this application    |\n"
                        "|   and select '1' from the main menu options.          |\n"
                        "|                                                       |\n"
                        "=========================================================\n";

const string despedida = "===================== SEE YOU LATER =====================\n"
                         "|                                                       |\n"
                         "|                                                       |\n"
                         "|                   Shutting down...                    |\n"
                         "|                                                       |\n"
                         "|                                                       |\n"
                         "=========================================================\n";

const string opcaoInvalida = "======================== WARNING ========================\n"
                             "|                                                       |\n"
                             "|   Invalid option, please select an option displayed   |\n"
                             "|   in the main menu!                                   |\n"
                             "|                                                       |\n"
                             "|                                                       |\n"
                             "=========================================================\n";

// Structs utilizadas
struct verticeAdj
{
  int destino;
  int peso;
  verticeAdj *prox;
};

struct listaAdj
{
  verticeAdj *cabeca;
};

struct grafo
{
  int numV;
  listaAdj *vertices;
};

struct verticeMH
{
  int v;
  int chave;
};

struct minHeap
{
  int tamanho;
  int capacidade;
  int *pos;
  verticeMH **lista;
};

// Sobrecarga da função temporizadora utilizada para fazer pausas durante a exibição dos resultados
void sleep(clock_t wait)
{
  clock_t goal = (wait+clock());
  while(goal>clock());
}

verticeAdj* criarVerticeAdj(int destino, int peso)
{
  verticeAdj *novo = new verticeAdj;
  novo->destino = destino;
  novo->peso = peso;
  novo->prox = NULL;
  return novo;
}

grafo* criarGrafo(int n)
{
  grafo *novoG = new grafo;
  novoG->numV = n;
  novoG->vertices = new listaAdj[n];
  for(int i=0;i<n;i++)
  {
    novoG->vertices[i].cabeca = NULL;
  }
  return novoG;
}

void adicionaAresta(grafo *g, int fonte, int destino, int peso)
{
  verticeAdj *novoV = criarVerticeAdj(destino, peso);
  novoV->prox = g->vertices[fonte].cabeca;
  g->vertices[fonte].cabeca = novoV;

  novoV = criarVerticeAdj(fonte, peso);
  novoV->prox = g->vertices[destino].cabeca;
  g->vertices[destino].cabeca = novoV;
}

verticeMH* criaVerticeMH(int v, int chave)
{
  verticeMH *novoV = new verticeMH;
  novoV->v = v;
  novoV->chave = chave;
  return novoV;
}

minHeap* criarMinHeap(int capacidade)
{
  minHeap *novaF = new minHeap;
  novaF->pos = new int[capacidade];
  novaF->tamanho = 0;
  novaF->capacidade = capacidade;
  novaF->lista = new verticeMH*[capacidade];
  return novaF;
}

void trocaVerticeMH(verticeMH **a, verticeMH **b)
{
  verticeMH *troca = *a;
  *a = *b;
  *b = troca;
}

void minHeapify(minHeap *mh, int idx)
{
  int menor, direita, esquerda;
  menor = idx;
  direita = 2 * idx + 2;
  esquerda = 2 * idx + 1;

  if(esquerda<mh->tamanho && mh->lista[esquerda]->chave<mh->lista[menor]->chave)
  {
		menor = esquerda;
  }
  if(direita<mh->tamanho && mh->lista[direita]->chave<mh->lista[menor]->chave)
  {
		menor = direita;
  }
  if(menor!=idx)
  {
    verticeMH *menorV = mh->lista[menor];
    verticeMH *idxV = mh->lista[idx];
    mh->pos[menorV->v] = idx;
    mh->pos[idxV->v] = menor;
    trocaVerticeMH(&mh->lista[menor], &mh->lista[idx]);
    minHeapify(mh,menor);
  }
}

int estaVaziaMH(minHeap *mh)
{
  return mh->tamanho==0;
}

verticeMH* extrairMin(minHeap *mh)
{
  if (estaVaziaMH(mh))
  {
    return NULL;
  }

  verticeMH *raiz = mh->lista[0];
  verticeMH *ultimoV = mh->lista[mh->tamanho-1];
  mh->lista[0] = ultimoV;
  mh->pos[raiz->v] = mh->tamanho-1;
  mh->pos[ultimoV->v] = 0;
  --mh->tamanho;
  minHeapify(mh,0);
  return raiz;
}

void reduzChave(minHeap *mh, int v, int chave)
{
  int i = mh->pos[v];
  mh->lista[i]->chave = chave;

  while(i && mh->lista[i]->chave < mh->lista[(i-1)/2]->chave)
  {
    mh->pos[mh->lista[i]->v] = (i-1)/2;
		mh->pos[mh->lista[(i-1)/2]->v] = i;
		trocaVerticeMH(&mh->lista[i], &mh->lista[(i-1)/2]);
		i = (i-1)/2;
  }
}

bool estaEmMinHeap(minHeap *mh, int v)
{
  if(mh->pos[v]<mh->tamanho)
  {
    return true;
  }else
  {
    return false;
  }
}

void mostraMST(int lista[], int n)
{
  cout<< "=============== PRINTING THE EDGES OF MST ===============\n" <<endl;
  for(int i=1;i<n;i++)
  {
    cout<< "                         " << lista[i] << " <-> " << i <<endl;
    sleep(700);
  }
  cout<<endl;
  cout<< "=========================================================\n" <<endl;
}

void primMST(grafo *g)
{
  int n = g->numV;
  int mst[n];
  int chave[n];

  minHeap *mh = criarMinHeap(n);
  for (int v = 1; v < n; ++v)
  {
		mst[v] = -1;
		chave[v] = INT_MAX;
		mh->lista[v] = criaVerticeMH(v, chave[v]);
		mh->pos[v] = v;
	}

  chave[0] = 0;
	mh->lista[0] = criaVerticeMH(0, chave[0]);
	mh->pos[0] = 0;

  mh->tamanho = n;

  while(!estaVaziaMH(mh))
  {
		verticeMH *menorChaveV = extrairMin(mh);
		int u = menorChaveV->v;

		verticeAdj *pMov = g->vertices[u].cabeca;

    while(pMov!=NULL)
    {
			int v = pMov->destino;

			if(estaEmMinHeap(mh, v) && pMov->peso<chave[v])
      {
				chave[v] = pMov->peso;
				mst[v] = u;
				reduzChave(mh, v, chave[v]);
			}
			pMov = pMov->prox;
		}
	}
  mostraMST(mst, n);
}

int main()
{
  grafo *g;
  ifstream leitura("grafo.txt", ifstream::in);
  int x, v, fonte, destino, peso, cont = 0;
  bool continuar = true;
  char op;
  while(continuar==true)
  {
    system("cls"); // Comando do terminal que limpa a tela, mas só funciona no Windows!
    cout<< telaInicial;
    cin>> op;
    switch (op) // Executa a ação solicitada pelo usuário
    {
      case '1':
        system("cls");
        cout<< avisoGerarGrafo;
        system("pause"); // Comando que faz uma pausa para que o usuário consiga ler o conteúdo da mensagem, só funciona no Windows!
        system("cls");
        if(leitura.is_open()) // Se o arquivo foi aberto corretamente
        {
          while(!leitura.eof()) // Enquanto não chegar ao fim do arquivo
          {
            leitura >> x;
            if(cont==0)
            {
              v = x;
              g = criarGrafo(v);
              cont++;
            }
            else if(cont==1)
            {
              fonte = x;
              cont++;
            }
            else if(cont==2)
            {
              destino = x;
              cont++;
            }
            else if(cont==3)
            {
              peso = x;
              adicionaAresta(g,fonte,destino,peso);
              cont = 1;
            }
          }
          primMST(g);
        }
        else
        {
          cout<< avisoArquivoInvalido;
        }
        system("pause");
      break;
      case '2':
        system("cls");
        cout<< sobreAlgoritmo;
        system("pause");
      break;
      case '3':
        system("cls");
        cout<< sobreSoftware;
        system("pause");
      break;
      case '4':
        system("cls");
        cout<< comoUsar;
        system("pause");
      break;
      case '0':
        system("cls");
        cout<< despedida;
        leitura.close();
        continuar = false;
        system("pause");
      break;
      default:
        system("cls");
        cout<< opcaoInvalida;
        system("pause");
      break;
    }
  }
  return 0;
}
