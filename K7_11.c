int nb_vertices(){
return 18;}

int is_adjacent(int u, int v){
 if(0< u && 0<v && u<19 && v<19){
  return (u<12 && v>11) || (u>11 && v<12);
 }
 else return 0;
}
