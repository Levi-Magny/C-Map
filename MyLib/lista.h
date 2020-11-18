#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
using namespace std;

template <class K, class V>
class MyList {
private:
    class Cell {
    public:
        V dados;

        Cell* prox;
        explicit Cell(V x) {
            dados = x;
            prox = NULL;
        }
    };
    bool excluir(Cell *ant, Cell *aux, const K &Ke);
    bool Verifica(Cell* &aux, V &D);
    V* searchKey(Cell* &aux,K chave);
    pair<V&,bool> Procura(Cell* &aux, V &D);
    void Esvazia(Cell *aux);
    void mostra(Cell *aux);
    void mostraIt(Cell *aux);
    Cell *primeiro, *ultimo;
    int tam;
public:
    MyList() {
        tam=0;
        primeiro = NULL;
        ultimo = NULL;
    };
    ~MyList() {
        Esvazia();
    };
    int size() {
        return tam;
    };
    V begin(){
        return primeiro->dados;
    }
    V end(){
        return ultimo->dados;
    }
    pair<V&,bool> insere(const V &val);
    pair<V&,bool> Procura(V &D);
    bool Verifica(V &D);
    void Esvazia();
    void mostra();
    void mostraIt();
    V* searchKey(K chave);
    bool excluir(const K &Key);
    //void InsereEsp();
};
#endif
