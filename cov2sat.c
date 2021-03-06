#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

/*
  Each integer +/- (i-1)*k+j+1 represents the variable :
  "is the vertex 'i' the 'j'th vertex of the cover ?"
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
  int step2 = (graph_size * (graph_size - 1)) * k;
  int step3 = nb_edges;
  int nb_clauses = step1 + step2 + step3;
  DEBUG("c nb_edges : %d\nc 1->%d, 2->%d, 3->%d", 
	nb_edges, step1, step2, step3);
  DEBUG("c Header :\n");
  printf("p cnf %d %d\n", nb_vars, nb_clauses);
}

/*
  There must be a positive variable for each j :
     X(1,1) \/ X(2,1) \/ ... \/ X(graph_size,1)
  /\ X(1,2) \/ X(2,2) \/ ... \/ X(graph_size,2)
  /\ ...
  /\ X(1,k) \/ X(2,k) \/ ... \/ X(graph_size,k)
*/
static void step1(void){
  #ifndef NO_DEBUG
  int cpt = 0;
  #endif  
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
  DEBUG("c %d\n", cpt); 
}

/*
  There must be at most one positive variable for each j :
     -X(1,1) \/ -X(2,1)
  /\ -X(2,1) \/ -X(3,1)
  /\ ...
  /\ -X(k-1,1) \/ -X(k,1)
  /\ -X(1,2) \/ -X(2,2)
  /\ ...
  /\ -X(graph_size-1,k) \/ -X(graph_size,k)    
*/
static void step2(void){
  #ifndef NO_DEBUG
  int cpt = 0;
  #endif
  DEBUG("c Step 2 :\n");
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
  DEBUG("c %d\n", cpt);
}

/*
  For each couple (XA, XB), if XA and XB are adjacent,
  then there must be one X(A|B, j) positive :
     X(A,1) \/ X(B,1) \/ X(A,2) \/ X(B,2) \/ ... \/ X(A,k) \/ X(B,k)
  /\ X(A',1) \/ X(B',1) \/ ...
  /\ ...
*/
static void step3(void){
  #ifndef NO_DEBUG
  int cpt = 0;
  #endif
  DEBUG("c Step 3 :\n");
  for(int i1 = 2; i1 <= graph_size; ++i1)
    for(int i2 = 1; i2 < i1; ++i2)
      if(is_adjacent(i1, i2)){
        for(int j = 0; j < k; ++j)
          printf("%d %d ", X(i1,j), X(i2,j));
	printf("0\n");
        #ifndef NO_DEBUG
	++cpt;
        #endif
      }
  DEBUG("c %d\n", cpt);
}

static void compute_cnf(void){
  step1();
  step2();
  step3();
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
