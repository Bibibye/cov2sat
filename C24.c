int nb_vertices(){
return 24;}

int is_adjacent(int u, int v){
 if(0< u && 0<v && u<25 && v<25){
  return (((24+u-v)%24==1)||((24+v-u)%24==1));
 }	
 else return 0;
}

