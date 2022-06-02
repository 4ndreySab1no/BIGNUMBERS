#include<list>
#include <queue>
#include<stdio.h>

using namespace std;

int qualeomaior(list<int> A, list<int> B){ // isso serve para a continha de subtração,                                           
    list<int>::iterator itA;               //o maior número vai ser colocado encima pra facilitar o processo
    list<int>::iterator itB;

    itA = A.begin();
    itB = B.begin();

    if((A.size() > B.size()) && (*itA != 0)){
        return 1;
    } else if ((B.size() > A.size()) && (*itB != 0)){
        return 0;
    }

    for (size_t i = 0; i < A.size(); i++){
        if(*itA > *itB){
            return 1;
        } else if(*itA < *itB){
            return 0;
        }

        itA++;
        itB++;
    }

    return 2;
}

list<int> soma(list<int>, list<int>);
list<int> subtracao(list<int>, list<int>);
list<int> vezes10(list<int>);

void imprimir(list<int> N){//isso é pra imprimir
    list<int>::iterator it;
    for (it = N.begin(); it != N.end(); it++)
    {
        printf("%d", *it);
    }
    printf("\n");
    
}

list<int> criar(int *v, int n){//isso organiza os vetores em listas
    list<int> N;
    for (size_t i = 0; i < n; i++){
        N.push_back(v[i]);
    }
    return N;
}

int main(){
    list<int> N;//as listas
    list<int> M;
    
    int V1[] = {1,9,1,1,1,5};//os vetores
    int V2[] ={1,3,9};//A idéia é de fazer operações, nesse caso aqui seria: 191115 + ou - 139
    
    N = criar(V1, 6);
    M = criar(V2, 3);
    
    imprimir(N);
    imprimir(M);
    list<int> A = soma(N,M);
    imprimir(A);
    list<int> B = subtracao(N,M);
    imprimir(B);
    list<int> C; 
	C = vezes10(N);
    imprimir(C);
}

list<int> vezes10(list<int> N){//Ele coloca um zero na ultima casa do vetor, o que resulta em um numero novo
    list<int> L;
    L = N;
	L.push_back(0);          //Esse numero novo, será, 10x maior que o original
    return L;
}
void completarZeros(list<int> *A, list<int> *B){ // ele serve para por os 0 a esqueda, pra alinhar a equação
    int nA = (*A).size();
    int nB = (*B).size();
    if(nA > nB){
        int d = nA - nB;
        for (int i = 0; i < d; i++)
        {
            (*B).push_front(0);
        }
    }
}

list<int> soma(list<int> A, list<int> B){
    
    completarZeros(&A, &B);

    list<int> C;
    list<int>::iterator itA;
    list<int>::iterator itB;
    int soma, x, y, aux=0;

    itA = A.end();
    itB = B.end(); //aqui temos as listas e variáveis a serem manipuladas

    itA--;
    itB--;

    for (size_t i = 0; i < A.size(); i++){//aqui a soma é feita
        x = *itA;
        y = *itB;
		
        soma = x + y + aux;

        if(soma > 9){//passou de nove, o auxiliar recebe o 1 pra por na casa seguinte a ser somada
            aux = 1;
        } else { //não passou, o auxiliar n recebe nada
            aux = 0;
        }

        C.push_front(soma%10);
        itA--;
        itB--;
    }

    if(aux != 0){
        C.push_front(aux);
    }

    return C;
}


list<int> subtracao(list<int> A, list<int> B){
    
    completarZeros(&A, &B);

    list<int> C;
    list<int>::iterator itA;
    list<int>::iterator itB;
    int subt, x, y, cont, aux = 0;
    int aux2 = qualeomaior(A, B);

    if(aux2 == 1){// isso usa o qual é o maior, pra fazer a subtração com o maior sendo o primeiro
        itA = A.end();
        itB = B.end();
    } else {
        itA = B.end();
        itB = A.end();
    }

    itA--;
    itB--;

    for (size_t i = 0; i < A.size(); i++){//
        x = *itA;
        y = *itB;

        if(aux == 10){//é como o processo de soma, ele vai dar valores ao contador
            cont = 1; //se passar de 9, adiciona mais um pro aux adicionar
        } 
		else {
            cont = 0; //se não for, não preenche o aux
        }

        if((x - cont) - y < 0){
            aux = 10;  //se a subtração das condições for menor que zero, aux fica 10 para preencher o proximo processo
        } 
		else {
            aux = 0;
        }

        if(aux == 10){
            subt = ((x - cont) + aux) - y; //se as condições permitiram que o aux fosse 10, eles executam a subtração somando o aux
        } 									//isso garante a falta de números negativos
		else {
            subt = (x - cont) - y; //se não for, a subtração continua
        }
        
        C.push_front(subt);
        itA--;
        itB--;
    }

    if(aux != 0){
        C.push_front(aux);//se o auxiliar for 10, nós colocamos ele na equação, que nem a subtração padrão.
    }

    return C;
}
