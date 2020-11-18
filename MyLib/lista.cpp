#include <iostream>
#include "lista.h"//declarações

using namespace std;


template <class K,class V>
void MyList<K,V>::Esvazia() {//esvasia a lista quando o destrutor for chamado
    Esvazia(primeiro);
    primeiro=ultimo=NULL;
}
template <class K,class V>
void MyList<K,V>::Esvazia(Cell *aux) {
    if(aux == NULL)
        return;
    Esvazia(aux->prox);
    delete aux;
}
template <class K,class V>
pair<V&,bool> MyList<K,V> :: insere(const V &val) { // função que insere no fim da lista e retorna um pair<endereço do objeto, bool>
    if (primeiro == NULL) {
        primeiro = new Cell(val);
        ultimo = primeiro;
        tam++;
        return pair<V&,bool>(primeiro->dados, true);
    } else {
        Cell *aux = new Cell(val);
        ultimo->prox = aux;
        ultimo = aux;
        tam++;
        return pair<V&,bool>(ultimo->dados, true);
    }
}
template <class K,class V>
void MyList<K,V>::mostra() {//usada apenas para testes(imprime todos os elementos da lista)
    if(tam == 0) {
        cout<< "\nA lista esta vazia. \n";
    }
    mostra(primeiro);
}

template <class K,class V>
void MyList<K,V>::mostra(Cell *aux) {//mostra recebendo o endereço da primeira posição
    if(aux==NULL) {
        return;
    }
    cout << aux->dados << "\n";
    mostra(aux->prox);
}

template <class K,class V>
pair<V&,bool> MyList<K,V>::Procura(V &D) {//true(Não existe nada com essa chave)
    return Procura(primeiro,D);
}
template <class K,class V>
pair<V&,bool> MyList<K,V>::Procura(Cell* &aux, V &D){//essa função só deve ser usada na implementação do insere do (Mapa)
    if(D.code() == aux->dados.code())
        return pair<V&,bool>(aux->dados,true);
    else
        return Procura(aux->prox, D);
}
template <class K,class V>// função que verifica se há algum objeto com a chave igual à que se quer inserir
bool MyList<K,V>::Verifica(V &D) {//true(Não existe nada com essa chave)
    if(tam==0)
        return true;
    return Verifica(primeiro,D);
}
template <class K,class V>
bool MyList<K,V>::Verifica(Cell* &aux, V &D){
    if(aux==NULL) return true;
    if(D.code() == aux->dados.code())
        return false;
    else
        return Verifica(aux->prox, D);
}

template<class K,class V>
V* MyList<K,V>::searchKey(K chave){
    return searchKey(primeiro, chave);
}
template<class K,class V>
V* MyList<K,V>::searchKey(Cell* &aux,K chave){
    if(aux==NULL) return nullptr; //se o aux chegar a um NULL, Retornaria NULL.
    if(aux->dados.code()==chave){//se a chave do aux for igual à chave que estou pesquisando
        return &aux->dados; //retorna o endereo de dados
    }else{
        return searchKey(aux->prox, chave);//senao retorna o endereço retornado pela proxima chamada.
    }
}

template <class K,class V>
bool MyList<K,V> :: excluir(const K &Key) {//exclui elemento com a chave fornecida
    Cell* an;
    an->prox=primeiro; // apenas define uma variável que será sempre o anteriior do aux
    return excluir(an, primeiro, Key);//chama o excluir passando o endereço do primeiro elemento
}
template <class K,class V>
bool MyList<K,V>::excluir(Cell *ant, Cell *aux, const K &Key) {
    if(aux==NULL) return false;

    //cout<<"kkkkk chorando\n";
    if(aux->dados.code() == Key) {// código similar ao 'escluir' do (iterador)
        if(aux==primeiro) {
            primeiro = (tam == 1) ? NULL : aux->prox;
            delete aux;
            tam--;
        } else if(aux==ultimo) {
            ultimo=ant;
            delete aux;
            ultimo->prox = NULL;
            tam--;
        } else {
            ant->prox=aux->prox;
            delete aux;
            tam--;
        }
        return true;
    } else return excluir(ant->prox, aux->prox, Key);
}
