int nb_vertices(){
return 21;}

int is_adjacent(int u, int v){
if(0< u && 0<v && u<nb_vertices()+1 && v<nb_vertices()+1){
  if(u==21)
   return (v%2==0);
  else if(v==21)
   return (u%2==0);
  else
  return (((20+u-v)%20==1)||((20+v-u)%20==1));
 }	
 else return 0;
}

