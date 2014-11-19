#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

/*
  Each integer +/- (i-1)*k+j+1 represents the variable :
  is the vertex 'i' the 'j'th vertex of the cover ?
  With 1 <= i <= graph_size
  And  0 <= j < k
 */
#define X(i, j) ((i-1)*k+j+1)

#ifdef NO_DEBUG
#define DEBUG(format,...) do{}while(0)
#else
#define DEBUG(format,...) printf(format, ##__VA_ARGS__)
#endif

static int graph_size = 0;
static int k = 0;

static void compute_header(void){
  int nb_vars = k*graph_size;
  int nb_edges = 0;
  for(int u = 1; u <= graph_size; ++u)
    for(int v = 1; v <= graph_size; ++v)
      if(u != v && is_adjacent(u,v))
	++nb_edges;
  nb_edges /= 2;
  int step1 = k;
  int step2 = (k * (k-1) * graph_size);
  int step3 = (graph_size * (graph_size - 1)) * k;
  int step4 = nb_edges*2;
  int nb_clauses = step1 + step2 + step3 + step4;
  DEBUG("c nb_edges : %d\nc 1->%d, 2->%d, 3->%d, 4->%d", nb_edges, step1, step2, step3, step4);
  DEBUG("c Header :\n");
  printf("p cnf %d %d\n", nb_vars, nb_clauses);
}

static void compute_cnf(void){
#ifndef NO_DEBUG
  int cpt = 0;
#endif
  /*
    There must be a positive variable for each j.
   */
  DEBUG("c Step 1 :\n");
  for(int j = 0; j < k; ++j){
    for(int i = 1; i <= graph_size; ++i){
      printf("%d ", X(i, j));
    }
    printf("0\n");
#ifndef NO_DEBUG
      ++cpt;
#endif
  }
  DEBUG("c%d\n", cpt);
  
  /*
    There must be at most one positive variable for each i
   */
#ifndef NO_DEBUG
  cpt = 0;
#endif
  DEBUG("c Step 2 :\n");
  for(int i = 1; i <= graph_size; ++i){
    for(int j1 = 0; j1 < k; ++j1)
      for(int j2 = 0; j2 < k; ++j2)
	if(j1 != j2){
    	  printf("%d %d 0\n", -X(i,j1), -X(i,j2));
#ifndef NO_DEBUG
	  ++cpt;
#endif
        }
  }
  DEBUG("c%d\n", cpt);
  
  /*
    There must be at most one positive variable for each j
   */
#ifndef NO_DEBUG
  cpt = 0;
#endif
  DEBUG("c Step 3 :\n");
  for(int j = 0; j < k; ++j){
    for(int i1 = 1; i1 <= graph_size; ++i1)
      for(int i2 = 1; i2 <= graph_size; ++i2)
	if(i1 != i2){
	  printf("%d %d 0\n", -X(i1,j), -X(i2,j));
#ifndef NO_DEBUG
	  ++cpt;
#endif
	}
  }
  DEBUG("c%d\n", cpt);
  
  /*
    For each couple (XA, XB), if XA and XB are adjacent,
    then there must be one X(A|B, j) positive.
   */
#ifndef NO_DEBUG
  cpt = 0;
#endif
  DEBUG("c Step 4 :\n");
  for(int i1 = 1; i1 <= graph_size; ++i1)
    for(int i2 = 1; i2 <= graph_size; ++i2)
      if(i1 != i2 && is_adjacent(i1, i2)){
        for(int j = 0; j < k; ++j)
          printf("%d %d ", X(i1,j), X(i2,j));
	printf("0\n");
#ifndef NO_DEBUG
	++cpt;
#endif
      }
  DEBUG("c%d\n", cpt);
}
  
  static void usage(char *name){
  fprintf(stderr, "Usage : %s k\nWith k >= 1\n", name);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
  if(argc != 2 || (k = atoi(argv[1])) < 1)
    usage(argv[0]);
  graph_size = nb_vertices();
  compute_header();
  compute_cnf();
  return EXIT_SUCCESS;
}
