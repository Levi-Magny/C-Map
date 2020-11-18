#include <iostream>
#include "Dados.h"
using namespace std;

template<class K>
string dados<K>::Nome(){
    return nome;
}

template<class K>
K dados<K>::code(){
    return Code;
}
