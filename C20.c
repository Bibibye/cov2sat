int nb_vertices(){
return 20;}

int is_adjacent(int u, int v){
 if(0< u && 0<v && u<21 && v<21){
  return (((20+u-v)%20==1)||((20+v-u)%20==1));
 }	
 else return 0;
}

