int nb_vertices(){
return 17;}

int is_adjacent(int u, int v){
if(0< u && 0<v && u<nb_vertices()+1 && v<nb_vertices()+1){
  if(u==17)
   return (v!=17);
  else if(v==17)
   return (u!=17);
  else
  return (((16+u-v)%16==1)||((16+v-u)%16==1));
 }	
 else return 0;
}

