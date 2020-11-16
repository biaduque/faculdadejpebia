#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
Programa desenvolvido por: 
Beatriz Duque 31906621
João Pedro 31954162

Site para consulta: 

https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/

*/

//funcao input elemento e quantidade
void input(string &elemento, int &qtd){
  cout<<"Digite o elemento: ";
  cin>>elemento;
  cout<<"Digite a quantidade: ";
  cin>>qtd;
}
//funcao criada para passar a tela do sistema
//antes se chamava "LimparTela" mas modificamos para melhor entendimento
void pressione(){
  cout << endl << "Pressione qualquer tecla para continuar...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}


void inserir(map<string,int> &compras, string &elemento,int &qtd){
  while(true){
        system("clear");
        cout<<"| Digite 0 para PARAR de inserir |\n";
        cout<<"\nDigite o nome do elemento e a quantidade a inserir na lista: \n\n |EXEMPLO: elemento qtd |\n\n";
        cin>>elemento;
        if (elemento == "0"){break;}
        cin>>qtd; 
        compras[elemento]=qtd; //insere no mapa compra, a string com o nome do elemento e sua respectiva quantidade
        cout<<"\nElemento Adicionado!\n";
        pressione();
  }
}
void remover(map<string,int> &compras,string &elemento){
  cout<<"Digite o item que deseja retirar da lista: ";
  cin>>elemento;
  compras.erase(compras.find(elemento));
}
void listar(map<string,int> &compras,map<string,int>::iterator item){
  if (compras.empty()==true){cout<<"Sua lista de compras esta vazia!!!";}
  else{
    item = compras.begin(); //posicionando o ponteiro no começo
    for(int x=0;x<compras.size();x++){
      cout <<(*item).first<<" -> ";
      cout<<(*item).second<<endl;
      item++;
    }
  }
}
void atualizar(map<string,int> &compras,int &qtd,string &elemento){
  system("clear");
      if (compras.empty()==true){cout<<"Sua lista de compras esta vazia!!!";}
      else{
        cout<<"========= ATUALIZANDO A QUANTIDADE =========\n ";
        input(elemento,qtd);
        compras[elemento]=qtd;
        cout<<"Elemento atualizado! Confira a lista completa na opcao 3\n";
      }
}
void incrementar(map<string,int> &compras,int &qtd,string &elemento){
  system("clear");
      if (compras.empty()==true){cout<<"Sua lista de compras esta vazia!!!";}
      else{
        cout<<"========== INCREMENTANDO A QUANTIDADE =========\n ";
        input(elemento,qtd);
        int antes = compras[elemento]; //guarda a quantidade antiga
        compras[elemento]= qtd+antes; //incrementa com a quantidade a ser acrescentada 
        cout<<"Elemento atualizado! Confira a lista completa na opcao 3\n";
      }
}

int main() {
  map<string,int>compras; //criando o mapa de compras
  map<string,int>::iterator item; //criando para rodar a lista 
  int opc,qtd;
  string elemento;

  while (true){
    system("clear");
    cout<<"             L I S T A    D E   C O M P R A S\n";
    cout<<"================= Painel de opcoes ==================\n";
    cout<<"|0. Parar                                            |\n";
    cout<<"|1. Inserir elementos na lista de compras            |\n";
    cout<<"|2. Remover um item da lista de compras              |\n";
    cout<<"|3. Listar todos os Itens                            |\n";
    cout<<"|4. Atualizar a quantidade de um determinado Item    |\n";
    cout<<"|5. Incremente a quantidade de um determinado Item   |\n";
    cout<<"=====================================================\n\n";
    cout<<"Selecione a opcao desejada: ";
    cin>>opc;

    if (opc ==0){break;}
    else if(opc==1){inserir(compras,elemento,qtd);}
    else if(opc==2){remover(compras,elemento);}
    else if(opc==3){listar(compras,item);}
    else if(opc==4){atualizar(compras,qtd,elemento);}
    else if(opc==5){incrementar(compras,qtd,elemento);}
    pressione();
  }
}
