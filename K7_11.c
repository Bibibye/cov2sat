int nb_sommet(){
return 18;}

int est_adjacent(int u, int v){
 if(0< u && 0<v && u<18 && v<18){
  return (u<12 && v>11);
 }	
 else return 0;
}