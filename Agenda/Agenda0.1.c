/* 
==============================================================================================================================
1-Faça uma agenda capaz de incluir, apagar, buscar e listar quantas pessoas o usuário desejar, 
porém, toda a informação incluída na agenda deve ficar num único lugar chamado: “void *pBuffer”.

2-Não pergunte para o usuário quantas pessoas ele vai incluir. 
Não pode alocar espaço para mais pessoas do que o necessário.

3-Cada pessoa tem nome[10], idade e telefone.

4-O trabalho que vale nota será uma continuação deste.

5-Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.

6-Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)

7-Não pode usar struct em todo o programa.

8-Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.

9-Implementar a base de dados da agenda usando lista duplamente ligada

10-Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.
================================================================================================================================
Pessoa
nome[10]char // idade[1]int // telefone[1]int
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ======================================Declaração de Variáveis=================================

void **pTracker;                
void **pNext;
void **pPrev;    

void *pHead;                                    // Ponteiro que guarda o Buffer ( endereço do primeiro e ultimo )                                
void *pPosition;                                // Ponteiro que guarda o próximo endereço vazio no buffer

void *pPeople;                                  // Ponteiro que guarda a Pessoa
char *pName;                                    // Ponteiro que guarda o nome a ser adcionado ao pessoa
char *pNameNode;
int  *pAge;                                     // Ponteiro que guarda a idade a ser adcionado ao pessoa
int  *pNumber;                                  // Ponteiro que guarda o numero a ser adcionado ao pessoa

int *pResult;
int *pCounterPeople;                            // Ponteiro que guarda o número de Pessoas na agenda
int *pMenu;                                     // Ponteiro que guarda a opção do menu
int *pContador;                                 // Ponteiro usado como contador em laços de repetição

// ======================================Declaração de Funções Menu====================================

void Menu();        //OK
void Insert();      //OK
void Apagar_r();    
void Buscar_r();
void Listar_r();    

// ======================================Declaração de Funções Memória=================================

void PUSH();
void POP();
void RESET();
void CLOSE();


/*
====================
Int Main

Main
====================
*/
int main () {
    pNext = (void**)malloc(sizeof(void**));
    pPrev = (void**)malloc(sizeof(void**));
    pMenu = (int*)malloc( sizeof( int ) ); 
    pCounterPeople = (int*)malloc( sizeof( int ) ); 

    *(int*)pCounterPeople = 0; // Numero de Pessoas na Lista

    pHead = (void*)malloc(sizeof(void));
    pHead = NULL;

    printf( "==============================\n" );
    printf( "Bem vindo a Agenda\n" );
    printf( "==============================\n" );

    Menu();

    free( pMenu );
    free( pCounterPeople );
    free( pHead );
    return 0;
}

/*
====================
Menu

Acessa o menu
====================
*/
void Menu() {
    printf( "==============================\n" );
    printf( "Escolha uma das opcoes a seguir: \n" );
    printf( "1. Incluir pessoa\n2. Apagar pessoa\n3. Buscar pessoa\n4. Listar Agenda\n5. Sair\n");
    printf( "==============================\n" );
    scanf("%d", pMenu);

    if ( *(int*)pMenu == 1 ) {
        Insert();
    }

    if ( *(int*)pMenu == 2 ) {
        Apagar_r();
    }

    if ( *(int*)pMenu == 3 ) {
        Buscar_r();
    }

    if ( *(int*)pMenu == 4 ) {
        Listar_r();
    }

    if ( *(int*)pMenu == 5 ) {
    printf( "Obrigado!" );
    }
}

/*
====================
Insert

Insert a People
on Agend
====================
*/
void Insert() {

pPeople = malloc( 10* sizeof(char) + 2*sizeof(int) + 2*sizeof(void**) );
pPosition = pPeople;

pName = ( char* )malloc( 10 * sizeof( char ));
pAge = ( int* )malloc( sizeof( int ) );
pNumber = ( int* )malloc( sizeof( int ) );

// Acrescenta Nome
printf( "Digite o nome da pessoa: \n" );
scanf( "%s", ( char* ) pName );
memcpy( pPosition, pName, 10* sizeof( char ));
pPosition += 10 * sizeof( char );

// Acrescenta Idade
printf( "Digite a Idade da pessoa: \n" );
scanf( "%d", pAge );
memcpy( pPosition, pAge, sizeof( int ));
pPosition += sizeof( int );

// Acrescenta Numero
printf( "Digite o numero da pessoa: \n" );
scanf( "%d", pNumber );
memcpy( pPosition, pNumber, sizeof( int ));
pPosition += sizeof( int );

PUSH( pPeople );
free( pNumber );
free( pName );
free( pAge );
Menu();
}

/*
====================
RESET

Starts the linked list
====================
*/
void RESET( ) {

//============header=================//
pHead = malloc(2*sizeof(void**));
*(void**)pHead = pPeople;
pTracker = pHead;

pHead += sizeof(void**);
*(void**)pHead = pPeople;
pHead -= sizeof(void**);
//===================================//

pPosition = *(void**)pHead;
pPosition += sizeof 10* sizeof(char) + 2*sizeof(int);
*(void**)pPosition = NULL;
pPosition += sizeof(void**);
*(void**)pPosition = NULL; 

}

/*
====================
PUSH

Insert element on linked list
====================
*/
void PUSH( ) {
pContador = ( int* )malloc( sizeof( int ) );

if ( pHead == NULL ) {
    RESET( pPeople );
*(int*)pCounterPeople = *(int*)pCounterPeople + 1;
}

else{
pResult = malloc(sizeof(int));    
pNameNode = malloc(10*sizeof(char));

pTracker = (void**)pHead;

    for (*( int* )pContador = 0; *( int* )pContador < *( int* )pCounterPeople; *( int* )pContador++) {               
    
    pNext = *( void** )pTracker + sizeof 10* sizeof(char) + 2*sizeof(int);
    pPrev = *( void** )pTracker + sizeof 10* sizeof(char) + 2*sizeof(int) + sizeof(void**);   
            
            // recebendo o nome da pessoa no nó
            memcpy (pNameNode, *(void**)pTracker, 10*sizeof(char) );  
            // pName já tem o nome da ultima pessoa adicionada
            *(int*)pResult = strcmp( pName, pNameNode);              
            
            if (*(int*)pResult < 0) {
            // Se for na primeira quer dizer que a head será trocada
                if (*(int*)pContador == 0) {            
                    
                    pPosition = pPeople;
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int );
                    
            // aprensento a head anterior como sendo o next dele
                    memcpy (pPosition,  ( void** )pTracker , sizeof( void** ) );
                    pPosition += sizeof(void**);  
                    
            // Atualizando o FIRST da HEAD              
                    *( void** )pPosition = NULL;                                      
                    *( void** )pHead = pPeople;                   
                    break;
                }

            // está no meio da lista
                else {
                    pPosition = pPeople;

            // atualizando o NEXT e PREV 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) ;  
                    memcpy (pPosition, ( void** )pNext, sizeof( void** ) );
                    pPosition + sizeof( void** ) ;  
                    memcpy (pPosition, ( void** )pPrev, sizeof( void** ) );

            // Atualizar o Prev do NEXT do People
                    pPosition = (void**)pPrev;                 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) ; 
                    memcpy (pPosition, ( void** )pTracker, sizeof( void** ) );
                                      

            // Atualizar o NEXT do PREV do People
                    pPosition = (void**)pNext;                 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) + sizeof(void**) ; 
                    memcpy (pPosition, ( void** )pTracker, sizeof( void** ) );
                    break;
                }
            }
            
            else if (*(int*)pResult > 0) {
            // LAST
                if (*(int*)pContador == *( int* )pCounterPeople -1 ) { 
                    pPosition = pPeople;

            // aprensento a last anterior como PREV 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) + sizeof( void** );  
                    memcpy (pPosition, ( void** )pTracker, sizeof( void** ) );

            // nada depois dele por ser LAST
                    pPosition -= sizeof(void**);                    
                    *(void**)pPosition = NULL;                   

            // atualizando o last no ponteiro HEAD
                    pPosition = pHead;
                    pPosition += sizeof( void** );               
                    memcpy (pPosition, ( void** )pTracker, sizeof( void** ) );
                    break;
                }

                else {
                pTracker = (void**)pNext;
                }
            }

            else if (*(int*)pResult == 0)
            {
            pPosition = pPeople;

            // atualizando o NEXT e PREV 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) ;  
                    memcpy (pPosition, ( void** )pNext, sizeof( void** ) );
                    pPosition + sizeof( void** ) ;  
                    memcpy (pPosition, ( void** )pPrev, sizeof( void** ) );

            // Atualizar o Prev do NEXT do People
                    pPosition = (void**)pPrev;                 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) ; 
                    memcpy (pPosition, ( void** )pTracker, sizeof( void** ) );
                                      

            // Atualizar o NEXT do PREV do People
                    pPosition = (void**)pNext;                 
                    pPosition += sizeof 10* sizeof( char ) + 2*sizeof( int ) + sizeof(void**) ; 
                    memcpy (pPosition, ( void** )pTracker, sizeof( void** ) );
                    break;
            }
    }
pTracker = (void**)pHead;
pNext = *( void** )pTracker + sizeof 10* sizeof(char) + 2*sizeof(int) ;  
*(int*)pCounterPeople = *(int*)pCounterPeople + 1;
}

free( pNameNode );
free( pResult );
}


/*
====================
Apagar_r

Apaga uma pessoa da 
Agenda
====================
*/
void Apagar_r() {

*(int*)pCounterPeople = *(int*)pCounterPeople - 1;
Menu();
}

/*
====================
Buscar_r

Apaga uma pessoa da 
Agenda
====================
*/
void Buscar_r() {
pName = (char*)malloc(10*sizeof(char));
pContador = ( int* )malloc( sizeof( int ) );

printf( "Essa busca será feita usando o número de telefone! \n" );
printf( "Digite o nome desejado: " );
scanf("%s", ( char* )pName );

free( pContador );
free( pName );

Menu();
}
/*
====================
Listar_r

Lista todas pessoas
na Agenda
====================
*/
void Listar_r() {  
pName = ( char* )malloc( 10 * sizeof( char ));
pAge = ( int* )malloc( sizeof( int ) );
pNumber = ( int*)malloc( sizeof( int ) );
pTracker = pHead;

    do {  
    pNext = *( void** )pTracker + sizeof 10* sizeof(char) + 2*sizeof(int);  
    pPosition = *( void** )pTracker;

    memcpy( pName, pPosition, 10 * sizeof( char ) );
    printf( "O nome da pessoa é: %s \n", pName );
    pPosition += 10 * sizeof( char );

    //Imprime a idade
    memcpy(pAge, pPosition, sizeof( int ) );
    printf( "Idade: %d \n", *( int* ) pAge );
    pPosition += sizeof( int );

    //Imprime o numero 
    memcpy(pNumber, pPosition, sizeof( int) );
    printf("Numero: %d \n", *(int*)pNumber );
    pPosition += sizeof( int );
    
    pTracker = pNext;
    } while ( *( void** )pTracker != NULL);

free( pName );
free( pAge );
free( pNumber );

Menu();
}



