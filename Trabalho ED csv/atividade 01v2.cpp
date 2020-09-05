//Trabalho 01 Estrutura de Dados II
//João Pedro Leite - 31954162
//Beatriz Duque Estrada - 31906621
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class No{
private:
	No *esq, *dir; //Ponteiros para esquerda e direita
	string nome;
	float sal;
	string funcao;


public:
	No(float sal, string nome, string funcao){
		this->nome = nome;
		this->funcao = funcao;
		this->sal = sal;
		esq = NULL;
		dir = NULL;
	}
	string getNome(){
		return nome;
	}

	float getSal(){
		return sal;
	}
	string getFuncao(){
		return funcao;
	}
	No* getEsq(){
		return esq;
	}
	No* getDir(){
		return dir;
	}
	void setEsq(No *no){
		esq = no;
	}
	void setDir(No *no){
		dir = no;
	}
};


//////////////////////////////arvore//////////////////////////////
class Arvore{
	//Conjunto de nos e os varios metodos que manipulam os nos ou
	//a arvore => possiveis operacoes sobre o TAD Arvore
private:
	No *raiz;

public:
	Arvore(){
		raiz = NULL;
	}
	void inserir(float sal,string nome,string funcao ){
		if(raiz == NULL)
			raiz = new No(sal,nome,funcao);
		else
			inserirAux(raiz,sal,nome,funcao);
	}
	void inserirAux(No *no, float sal, string nome, string funcao){
		//1o) Localizar a posicao onde o no sera inserido
		//2o) Criar o no e conecta-lo a estrutura da arvore
		if(sal < no->getSal()){
			if(no->getEsq() == NULL){
				No *novo_no = new No(sal,nome,funcao);
				no->setEsq(novo_no);
			}
			else{
				inserirAux(no->getEsq(),sal,nome,funcao);
			}
		}
		else if(sal > no->getSal()){
			if(no->getDir() == NULL){
				No *novo_no = new No(sal,nome,funcao);
				no->setDir(novo_no);
			}
			else{
				inserirAux(no->getDir(),sal,nome,funcao);
			}
		}
		// se o valor ja existe na arvore nao insere
		//else
		
	}

	No* getRaiz(){
		return raiz;
	}

  	int getChave(No* no){
    int chave = no->getSal();
    return chave;
  }

	void emOrdem(No* no){
		if(no != NULL){
			emOrdem(no->getEsq());
			cout << no->getSal() << " ";
			emOrdem(no->getDir());
		}
	}

	void posOrdem(No* no){
		if(no != NULL){
			posOrdem(no->getEsq());
			posOrdem(no->getDir());
			cout << no->getSal() << " ";
		}
	}

	void preOrdem(No* no){
		if(no != NULL){
			cout << no->getSal() << " ";
			preOrdem(no->getEsq());
			preOrdem(no->getDir());
		}
	}


	void contar(No* no, int &qtd){
	    if (no != NULL){
	      qtd++;
	      contar(no->getEsq(), qtd);
	      contar(no->getDir(), qtd);
	    }
	}

	void localiza(No* no, int n, int &achou){
		if(no != NULL){
			localiza(no->getEsq(),n,achou);
			if (no->getSal()==n){achou++;}
			localiza(no->getDir(),n,achou);
			if (no->getSal()==n){achou++;}
			}
	}

	int maior(No* no, int &m){
		if(no != NULL){
			m = no->getSal();
			maior(no->getDir(),m);
		}
		return m;
	}
	string maiornome(No* no, string &m){
		if(no != NULL){
			m = no->getNome();
			maiornome(no->getDir(),m);
		}
		return m;
	}
	string maiorfuncao(No* no, string &m){
		if(no != NULL){
			m = no->getFuncao();
			maiorfuncao(no->getDir(),m);
		}
		return m;
	}
	int menor(No* no, int &m){
		if(no != NULL){
			m = no->getSal();
			menor(no->getEsq(),m);

		}
		return m;
	}
};
////////////////////////////// CSV //////////////////////////////

////////////////////////////// MAIN //////////////////////////////
int main(){
  Arvore arv;
  ifstream arq;

  arq.open("spcine.csv");//abrindo arquivo
  string funcao,salario,nome;
  float salario2;
  string line;

  ///////////////////////////// lendo o arquivo /////////////////////////////////
  while(arq.good()){
    int coluna = 0;
    //lendo linha 1 do arquivo
    getline(arq,line,'\n');
    //lendo os nomes
    while(coluna<4){
      getline(arq,line,';'); //ele passa para a proxima coluna ate chegar no nome
      coluna++;
    }
    nome = line;
    //lendo as funcoes
    getline(arq,line,';'); //funcao
    funcao = line;
    while(coluna<8){
      getline(arq,line,';'); //ele passa para a proxima coluna ate chegar no salario
      coluna++;
    }
    salario = line;
    salario.erase(0,3); //exclui o R$
    salario.erase(remove(salario.begin(), salario.end(), '.'),salario.end()); //remove o '.'
    replace(salario.begin(),salario.end(),',','.'); //troca a virgula por ponto

    if(!salario.empty()){
      //transformando float para salario
      salario2 = stof(salario);

      //inserir
      arv.inserir(salario2,nome,funcao);
    }
  }

  //maior
    int maior=0;
    string mn,mf;
    arv.maior(arv.getRaiz(),maior);
    arv.maiornome(arv.getRaiz(),mn);
    arv.maiorfuncao(arv.getRaiz(),mf);
    cout<<"\nNome:"<<mn;
    cout<<"\nFuncao:"<<mf;
    cout<<"\nSalario:"<<maior;
    //menor
    //montante	
    //media
    //mediana
	/*
	while (true) {
		system("cls");
		//ler o arquivo
		// while inserir (nome, salario, funcao)

		//inicio da analise de dados
		//maior salario (usando funcao maior)
		//menor salario (usando funcao menor)
		//montante salarios (usando funcao contar)
		//media salarial (precisa do montante e da qtd de empregados)
		//mediana
		//media de beneficios
		//total beneficios

	}
	*/
	system("pause");
	return 0;

}
