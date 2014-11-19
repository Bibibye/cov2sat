cov2sat
=======

cov2sat is a vertex cover problem to SAT reductor.

You will need gcc, make, bash and minisat in order to compile and execute this project.

A graph must be implemented with 2 functions :

 - `int nb_vertices(void)` which returns the number of vertices in the graph.
 - `int is_adjacent(int u, int v)` which returns 1 if u and v are adjacent, 0 if not.

Then, you must link it with cov2sat.o.

You can try cov2sat with :

```
$ make
$ ./Petersen.out 6 > P6.sat
$ minisat P6.sat P6.result
```

You can also try the vertex cover solver with every graph :

```
$ make run
```

Or just one :

```
$ ./solver.sh Petersen.out
```

