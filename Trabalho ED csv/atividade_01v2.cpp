//Trabalho 01 Estrutura de Dados II
//João Pedro Leite - 31954162
//Beatriz Duque Estrada - 31906621
#include <iostream>
#include <string>
#include <sstream> //para a funcao de analisar os caracteres 
#include <fstream> //para a funcao de ler o arquivo
#include <algorithm> //para a funcao replace

using namespace std;
//cria nó que vai auxiliar na lista ligada (caso existam valores iguais, eles sao adicionados em uma lista) 
class Node{
	public:
		int n;
		string nome, func;
		Node * prox;
	Node(float number,string name, string funcao){
		n = number;
		nome = name;
		func = funcao;
		prox = NULL;
	}
	void setProx(Node * p){prox = p;}
	
	float getInfo(){return n;}
	string getNome(){return nome;}
	string getFuncao(){return func;}
	Node * getProx(){return prox;}
};
//classe lista ligada para o Nó
class ListaLigada{
	public:
		Node * prim;
		int qtdCelulas;
	ListaLigada() {
		prim = NULL;
		qtdCelulas = 0;
	}
	void insereFim(int i,string name,string funcao){
		Node *no=prim;
		Node *novo;
		novo = new Node(i,name,funcao);
		
		if (prim==NULL){prim=novo;}
		else{
			while(no->getProx()!=NULL){
				no = no->getProx();
			}
			no->setProx(novo);
		}
		
	}
	
	void print() {
			Node *no=prim;
            while (no != NULL) {
            	cout<<"NOME:"<< no->getNome()<< "\n";
            	cout<<"FUNCAO:"<<no->getFuncao()<<"\n";
                cout <<"SALARIO:"<< no->getInfo() <<"\n";
                no = no->getProx();
            }
    }
};
//criacao da classe No 
class No{
private:
	No *esq, *dir; //Ponteiros para esquerda e direita
	string nome;
	float sal;
	string funcao;
	ListaLigada list; //cria a lista ja que cada no vai ser o primeiro elemento da lista caso existam valores iguais 

public:
	No(float sal, string nome, string funcao){
		this->nome = nome;
		this->funcao = funcao;
		this->sal = sal;
		esq = NULL;
		dir = NULL;
	}
	string getNome(){return nome;}

	float getSal(){return sal;}
	string getFuncao(){return funcao;}
	No* getEsq(){return esq;}
	No* getDir(){return dir;}
	void setEsq(No *no){esq = no;}
	void setDir(No *no){dir = no;}
	void printaLista(){list.print();}
	void insereLista(float sal,string nome,string funcao){list.insereFim(sal,nome,funcao);}
};

//////////////////////////////arvore//////////////////////////////
class Arvore{
	//Conjunto de nos e os varios metodos que manipulam os nos ou
	//a arvore => possiveis operacoes sobre o TAD Arvore
private:
	No *raiz;
	float montante;
	int qtd;

public:
	Arvore(){
		raiz = NULL;
		montante=0;
		qtd=0;
	}
	void inserir(float sal,string nome,string funcao ){
		if(raiz == NULL)
			raiz = new No(sal,nome,funcao);
		else
			inserirAux(raiz,sal,nome,funcao);
			
		montante=montante+sal;// incrementa o total de salario 
		qtd++; //incrementa a quantidade de elementos na arvore (nó)
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
		else{ //se o valor for igual, é criada uma lista ligada para que estes nao se percam ou sejam excluidos dos calculos.
			no->insereLista(no->getSal(),no->getNome(),no->getFuncao());
		}

	}

	No* getRaiz(){return raiz;}
  	float getChave(No* no){float chave = no->getSal();return chave;}

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

	No *maior(No* no){
		if(no != NULL){ 
		//se a direita dele possuir um valor, ele continuara a descer a arvore 
			if (no->getDir()!= NULL){return maior(no->getDir());}
		}
		return no; //percorre até o final da arvore ate encontrar o nó maior e o retorna 
	}

	No *menor(No* no){
		if(no != NULL){
			if (no->getEsq()!= NULL){return menor(no->getEsq());}
		}
		return no;
	}
	
	float getMontante(){return montante;}
	int getQtd(){return qtd;}
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
	int opc;
	No *no,*no2;
	while (true){
		system("cls");
		cout<<"1. Printar o(s) maior(es) salario(s)\n";
		cout<<"2. Printar o(s) menores(es) salario(s)\n";
		cout<<"3. Calcular o Montante dos salarios\n";
		cout<<"4. Calcular a media dos salarios\n";
		cout<<"5. Printa a quantidade de dados coletados\n";
		cout<<"Digite a opcao desejada:";
		cin>>opc;
		if (opc == 0) {
			break;
		} else if (opc == 1) { //maior
			no = arv.maior(arv.getRaiz());
    		cout<<"\n======== MAIORES SALARIOS ========="; //printa primeiramente o no raiz 
    		cout<<"\nNOME:"<<no->getNome();
    		cout<<"\nFUNCAO:"<<no->getFuncao();
    		cout<<"\nSALARIO:"<<no->getSal();
    		no->printaLista(); //percorre a lista ligada para verificar se existem valores iguais e entao, printa-los
    		cout<<"\n";
		} else if (opc == 2) {//menor
			no2 = arv.menor(arv.getRaiz());
		    cout<<"\n======== MENORES SALARIOS =========";
			cout<<"\nNOME:"<<no2->getNome();
		    cout<<"\nFUNCAO:"<<no2->getFuncao();
		    cout<<"\nSALARIO:"<<no2->getSal();
		    no2->printaLista(); 
		    cout<<"\n";
		} else if (opc == 3) {
			//montante
		    cout<<"\n======== MONTANTE =========";
		    printf("\nR$%.2f",arv.getMontante());
		    cout<<"\n";
		} else if (opc == 4) {
			//media salarial 
		    cout<<"\n======== MEDIA =========";
		    cout<<"\nR$"<<arv.getMontante()/arv.getQtd()<<"\n";
		} else if (opc == 5) {	
			cout<<"\nA Quandidade de dados analisados foi:"<<arv.getQtd()<<"\n";
		}
		else{cout<<"\n\nA opcao digitada eh invalida.\n\n";}
    	system("\npause\n");
    	
	}
	return 0;
}
