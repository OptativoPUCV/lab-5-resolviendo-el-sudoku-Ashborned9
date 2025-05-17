#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
  
  if (n == NULL) {
      printf("No solution found.\n");
      return;
    }
  int i,j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      printf("%d ", n->sudo[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
// TENIA ERRORES DE SEGMENTACION CON EL SUDOKU.C 
// POR ESO TENGO TAN POCO TIEMPO CON EL TEST.SH
// 
int is_valid(Node* n){

  for (int i = 0; i < 9; i++)
  {
    int col[10] = {0};
    int fil[10] = {0};

    for (int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] != 0)
      {
        if (fil[n->sudo[i][j]] == 1)
        {
          return 0;
        }
        fil[n->sudo[i][j]] = 1;
      }
      if (n->sudo[j][i] != 0)
      {
        if (col[n->sudo[j][i]] == 1)
        {
          return 0;
        }
        col[n->sudo[j][i]] = 1;
      }
    }
  }

  for (int i = 0; i < 9; i +=3)
  {
    for (int j = 0; j < 9; j += 3)
    {
      int fila_sub[10] = {0};
      int colum_sub[10] = {0};
      for (int p = 0; p < 3; p++)
      {
        for (int q = 0; q < 3; q++)
        {
          if (n->sudo[i + p][j + q] != 0)
          {
            if (fila_sub[n->sudo[i + p][j + q]] == 1)
            {
              return 0;
            }
            fila_sub[n->sudo[i + p][j + q]] = 1;
          }
          if (n->sudo[j + p][i + q] != 0)
          {
            if (colum_sub[n->sudo[j + p][i + q]] == 1)
            {
              return 0;
            }
            colum_sub[n->sudo[j + p][i + q]] = 1;
          }
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list = createList();
  for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
      {
        if (n->sudo[i][j] == 0)
        {
          for (int m = 1; m <= 9; m++)
          {
            Node* act = copy(n);
            act->sudo[i][j] = m;
            if (is_valid(act))
            {
              pushBack(list, act);
            }
            
          }
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pl = createStack();
  push(pl, initial);
  while (!is_empty(pl)){
    Node* n = top(pl);
    pop(pl);
    (*cont)++;
    
    if (is_final(n))
    {
      return n;
    }
    
    List* adj_nod = get_adj_nodes(n);
    Node* aux = first(adj_nod);
    while (aux != NULL){
      push(pl, aux);
      aux = next(adj_nod);
    }
    free(adj_nod);
    free(n);
  }
  free(pl);
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
} */




