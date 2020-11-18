#include <iostream>
#include <string>
#include "MyLib\lista.cpp"//implementação da lista utilizada na hash
#include "MyLib\Dados.cpp"//opbjeto dados utilisado nesse programa

//(VERIFICAR OS ARQUIVOS .h)\\
"MyLib\Dados.h" e MyLib\lista.h

#define SIZE_HASH 107
using namespace std;
template <class V>
class Iterator {
private:
    class Node {//nó do iterador
    public:
        V PontD;

        Node* prox;
        explicit Node(V x) {
            PontD = x;
            prox = NULL;
        }
    };
    bool excluir(Node *ant, Node *aux, const V &dado);
    bool InsereOrd(Node *ant, Node *aux,V data);
    void mostraIt(Node *aux);
    void Esvazia(Node* aux);
    Node *primeiro, *ultimo;
    int tam;
public:
    Node* atual;//atributo que guarda o valor atual en quanto percorre-se o iterador.
    Node* inicio(){return primeiro;}
    Iterator() {
        tam=0;
        primeiro = NULL;
        ultimo = NULL;
        atual = NULL;
    };
    ~Iterator() {
        Esvazia();
    };
    int size() {
        return tam;
    };
    bool InsereOrd(V dado);
    void mostraIt();
    void Esvazia();

    Node* operator ++(){//sobrecarga do operador '++' prefixado
        atual=atual->prox;
        return atual;
    }

    Node* operator ++(int){//sobrecarga do operador '++' posfixado
        Node* aux= atual;
        atual=atual->prox;
        return aux;
    }
    bool excluir(const V &dado);
};

template <class V>
bool Iterator<V>::excluir(const V &dado) {
    Node *aux2;
    return excluir(aux2, primeiro,dado);
}
template <class V>
bool Iterator<V>::excluir(Node *ant, Node *aux, const V &dado) {//função que exclui do iterador
    if(tam==0 || aux == NULL) {
        return false; //se o iterador estiver vazio, ou a chave não foi encontrada, retorna falso
    }
    else if(aux->PontD->code() == dado->code()) {//se encontrou a chave a excluir
        if(aux == primeiro){ //se essa chave for o primeiro elemento do iterador
            primeiro = (tam == 1) ? NULL : aux->prox;
            tam--;
            delete aux;
            return true;
        }else if(aux == ultimo){//se a chave for o ultimo elemento do iterador
            ultimo = ant;
            delete aux;
            ultimo->prox = NULL;
            tam--;
            return true;
        }else{//se a chave não está nas extremidades do iterador
            ant->prox = aux->prox;
            delete aux;
            tam--;
            return true;
        }
    } else {
        ant = aux;
        excluir(ant, aux->prox, dado);//vai para o próximo elemento recursivamente
    }
}
template <class V>
bool Iterator<V>::InsereOrd(V dado){//função insere que o usuário tem acesso
    if(tam == 0){
        Node* aux = new Node(dado);
        primeiro = ultimo = aux;
        tam++;
        return true;
    }
    Node *ant;
    return InsereOrd(ant, primeiro, dado);

}
template <class V>
bool Iterator<V>::InsereOrd(Node *ant, Node *aux,V data){// função que insere elementos ordenandos pela chave (Iterador)
    if(aux == NULL) return false;
    if(aux->PontD->code() == data->code()) return true;

    if(aux->PontD->code() < data->code()){//se o  código de aux for menor do que o código que se está a inserir
        if(aux==ultimo){//se aux for o ultimo elemento
            Node* aux2 = new Node(data);
            ultimo->prox = aux2;
            ultimo = aux2;
            tam++;
            return true;
        }else if(aux->prox->PontD->code() > data->code()){//se o código do nó seguinte for maior do que o que eu quero inserir
            Node* aux2 = new Node(data);
            aux2->prox = aux->prox;
            aux->prox = aux2;
            tam++;
            return true;
        }else{     //senao
            ant = aux;
            return InsereOrd(ant, aux->prox, data); //vou para o próximo elemento da lista
        }
    }else{//se a chave for maior do que a que eu quero inserir
        if(aux==primeiro){// se aux for o primeiro elemento
            Node* aux2 = new Node(data);
            aux2->prox = aux;
            primeiro = aux2;
            tam++;
        }else{ //se não for o primeiro elemento.
            Node* aux2 = new Node(data);
            aux2->prox = aux;
            ant->prox =aux2;
            tam++;
        }
        return true;
    }
}
template <class V>
void Iterator<V>::Esvazia() {
    Esvazia(primeiro);
    primeiro=ultimo=NULL;
}
template <class V>
void Iterator<V>::Esvazia(Node *aux) {//função que esvazia o iterador quando o destrutor é chamado
    if(aux == NULL)
        return;
    Esvazia(aux->prox);
    delete aux;
}

template <class K, class V>
class Map {
private:
    MyList<K,V> hash[SIZE_HASH];//vetor de listas encadeadas
public:
    Map() = default; //construtor padrao do mapa
    Iterator<V*> iterador;
    int FuncaoTransformacao(int Key){//função que retorna a posição no hash baseando-se na chave fornecida (int)
            return Key%SIZE_HASH;//apenas retorna o resto da divisão entre a chave e SIZE_HASH
    }
    int FuncaoTransformacao(string Key){//função que retorna a posição no hash baseando-se na chave fornecida (string)
        int fator=0; //esse será o valor da string no tipo inteiro
        for(int i=0; i<Key.size(); i++) {//percorre toda a string
            fator = fator + (int(Key.at(i)))*(i+1);//soma o fator é somado com o valor do caractere multiplicado pela sua posição na string
        }
        return fator%SIZE_HASH;//retorna o resto da divisão entre fator e SIZE_HASH
    }

    bool excluir(K Chave);

    V* pesquisa(K chave){//para pesquisar dados no mapa utilisando a chave
        V* D = hash[FuncaoTransformacao(chave)].searchKey(chave);//primeiro pesquisa na hash utilisando uma funçao da lista ("lista.cpp - linha 93")
        if(D==NULL)// se o valor retornado for null
            return NULL;
        else//se não for null  retorna o dado encontrado
            return D;
    }
    pair<V&,bool> Insere(dados<K> &x);
    V& operator [](K chave){//sobrecarga do operador []

        V D(chave,"");//cria um objeto do tipo 'dados' com a chave fornecida
        return Insere(D).first; //retorna o primeiro elemento do pair retornado pelo insere.
    }
};

template <class K, class V>
pair<V&,bool> Map<K,V>::Insere(dados<K> &x) { //função de insere
    int pos = FuncaoTransformacao(x.code());
    if(hash[pos].Verifica(x)) { //se não houver nenhum elemento com essa chave
        pair<V&,bool> par = hash[pos].insere(x);
        V* ende = &par.first;
        iterador.InsereOrd(ende);
        return par;//retorna o pair retornado pelo insere da lista
    } else {
        V& r = hash[pos].Procura(x).first;// 'dados r' recebe o objeto x retornado pelo método busca
        return pair<V&,bool>(r,false);//retorna o endereço de 'r' e false.
    }
}
template <class K, class V>
bool Map<K,V>::excluir(K Chave){//funcao para excluir dado do mapa
    int pos = FuncaoTransformacao(Chave);//calcula em qual posicao a chave se encontra na tabela hash
    V* dado = hash[pos].searchKey(Chave);//procura, dentro da posição, um dado com a mesma chave que se está pesquisando ("lista.cpp - linha 93")
    if(dado != nullptr) {//se dado não for nullptr
        iterador.excluir(dado);//primeiro exclui do iterador
        cout<<"\nExcluido com sucesso!!\n";
        return hash[pos].excluir(Chave);//depois exclui da hash ("lista.cpp - linha 107")
    }else{// se o dado é nullptr
        cout<<"\nElemento não existe\n";
        return false;
    }
}

char menu();
int main(){//exemplo de uso do mapa, demosntrando funcionamento dass propriedades
    Map<int,dados<int>> a;//cria o mapa dizendo qual o tipo da chave e o tipo do objeto guardado
    static dados<int> d, *T;//cria variáveis do tipo dados que serão usadas no programa
    char op,s;//variáveis para guardar respostas do usuário
    int pass;// "   "   "   "   "       "       "       "
    bool may;// "   "   "   "   "       "       "       "
    op = menu();// 'op' guarda a escolha do usuário
    while(op != 's' && op !='S') {// enquanrto o usuário não digitar 's' no menu
        switch (op) {
            case 'a'://se o usuário escolheu 'a' ou 'A'
            case 'A':
                cout << "A seguir insira os dados do usuario:\n";
                cin >> d;//lê um tipo dados ("dados.h" e dados.cpp)
                cout << "\nOs dados sao: " << d << endl;
                cout << "\nDeseja confirmar?[s/n]... ";
                cin >> s;
                if (s == 's' || s == 'S'){
                    a.Insere(d); //se o usuário escolher inserir, chama o insere do mapa
                    system("pause");
                }
                break;
            case 'b'://se o usuário escolheu 'b' ou 'B'
            case 'B':
                cout << "\nInsira a senha de usuario: ";
                cin >> pass;
                T = a.pesquisa(pass);//primeiro pesquisa para saber de qual usuário se trata, ou ainda, se existe.
                if (T == NULL) {
                    cout << "\nO usuario nao existe!!!\n";
                    system("pause");//apenas volta para o menu
                    break;
                } else {//se o usuário existe
                    cout << "Deletar usuário |" << *T << "| ?[s/n]\n";
                    cin>>s;//confirma se o usuário deseja deletar o objeto
                    if (s == 's' || s == 'S') {
                        if (a.excluir(pass))//chama o excluir do mapa
                            cout << "Show!\n";// se excluir corretamente
                        else
                            cout << "\nFalha ao excluir\n";//se, por algum motivo, não excluir
                    } else {
                        cout << "Cancelando Operacao...\n";//caso o usuario tenha optado por não excluir o objeto
                    }
                    system("pause");
                }
                break;
            case 'c'://se o usuário escolheu 'c' ou 'C'
            case 'C':
                cout << "\nInsira a senha de usuario: ";
                cin>>pass;
                T = a.pesquisa(pass);
                if(T == nullptr)
                    cout<<"\nUsuario nao existe!!!\n";
                else
                    cout<<*T<<endl;

                system("pause");
                break;
            case 'd'://se o usuário escolheu 'd' ou 'D'
            case 'D':
                cout<<"\nInsira a senha do usuario, e o novo nome: \n";
                cin>>d;
                a[d.code()] = d;
                cout<<"\nDados cadastrados:\n";
                break;
            case 'e'://se o usuário escolheu 'e' ou 'E'
            case 'E':
                may = false;
                cout<<"Quantos usuarios deseja ver? ";// o programa mostrará a quantidade de objetos que o usuário atual deseja ver, ordenados pelas chaves
                while(!may){
                    cout<<"\n-> ";
                    cin>>pass;
                    int i=0;
                    if(pass<=a.iterador.size()){
                        for(a.iterador.atual = a.iterador.inicio(); i<pass; a.iterador++, i++){//explo do uso da sobrecarga do operador '++'
                            cout<<*a.iterador.atual->PontD<<endl;//imprime o dado na posição atual
                        }
                        may = true;// para sair do laço
                    }else{
                        cout<<"Ha apenas "<<a.iterador.size()<<" usuarios.";
                    }
                }
                system("pause");
                break;
            default://caso não seja nenhuma das opções acima
                cout<<"Opcao invalida\n";
        }
        op = menu();
    }
    return 0;
}
char menu(){//menu
    char resp;
    system("cls");
    cout<<"_______ Testando Mapa _______\n";
    cout<<"Insira a opcao desejada:\n";
    cout<<"[A] Para cadastrar um novo Usuario\n";
    cout<<"[B] Para excluir um Usuario\n";
    cout<<"[C] Para Pesquisar um Usuario\n";
    cout<<"[D] Para Alterar o nome de um Usuario\n";
    cout<<"[E] Para Pesquisar os n primeiros usuarios (ordenados pela senha)\n";
    cout<<"[S] Para sair\n";
    cout<<"\nInsira...";
    cin>>resp;
    return resp;

}
