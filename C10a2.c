int nb_vertices(){
return 10;}

int is_adjacent(int u, int v){
 if(0< u && 0<v && u<11 && v<11){
  return (((10+u-v)%10==1)||((10+v-u)%10==1)||((10+u-v)%10==2)||((10+v-u)%10==2));
 }	
 else return 0;
}

