#ifndef DADOS_H_INCLUDED
#define DADOS_H_INCLUDED
using namespace std;

template <class K>
class dados{
private:
    K Code;
    string nome;
public:
    dados(){
        Code = -1;
        nome = "null";
    }
    dados(K Key, const string& name){
        Code = Key;
        nome = name;
    }
    friend ostream& operator<<(ostream &out, dados &t)
    {
        out<<" Senha: "<<t.code();
        out<<" , Nome: "<<t.Nome();
        return out;
    }
    friend istream& operator>>(istream &in, dados &t)
    {
        cout<<"\nEscolha uma senha: ";
        in>>t.Code;
        cout<<"Escolha um nome: ";
        in>>t.nome;
        return in;
    }
    string Nome();
    K code();
};
#endif
