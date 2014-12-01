int nb_vertices(){
return 10;}

int is_adjacent(int u, int v){
 if(0< u && 0<v && u<11 && v<11){
  return (u<6 && v>5) || (u>5 && v<6);
 }	
 else return 0;
}
