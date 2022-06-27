#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<time.h>
#include <stdbool.h>
#include "map.h"
#include "list.h"
#define MAXLEN 100

typedef char cadena[MAXLEN];

typedef struct{
 char* mov1;
 char* mov2;
 char* mov3;
 char* mov4;
}Movs;

typedef struct{
 int hp;
 int atk;
 int def;
 int atk_esp;
 int def_esp;
 int vel;
}Stats;

typedef struct {
 Stats* stats;
 Movs* movs;
 char* nombre;
 char* tipo1;
 char* tipo2;
 int legendary;
}Pokemon;

typedef struct{
 char* nombre_tipo;
 float normal;
 float lucha;
 float volador;
 float veneno;
 float tierra;
 float roca;
 float bicho;
 float fantasma;
 float acero;
 float fuego;
 float agua;
 float planta;
 float electrico;
 float psiquico;
 float hielo;
 float dragon;
 float siniestro;
 float hada;
}Efectividad;

typedef struct{
 char* movimiento;
 char* tipo;
 int daño;
 int precision;
 char* efecto;
 char* tipo_daño;
}Movimiento;

//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES
//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES
const char *get_csv_field (char * tmp, int k);
int is_equal_string(void * key1, void * key2);
void singlePlayer(Map * mapaPokemon,List* listaEfectividad, Map * mapaMovimientos);
void multiplayer(Map * mapaPokemon,List* listaEfectividad, Map * mapaMovimientos);
void mostrarMapaPokemon (Map * mapaPokemon);
void mostrarListaEfectividad (List* listaEfectividad);
void mostrarMapaMovimientos (Map * mapaMovimientos);
float coincideTipo(char *tipo1,char *tipo2,char *tipo_mov);
float vsTipoRival1(List *listaEfectividad,char * movi_tipo,char* tipo_rival);
float vsTipoRival2(List * listaEfectividad,char * movi_tipo,char* tipo_rival);
float critico();

//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES
//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES//FUNCIONES

int main(void) { 
printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
	printf("oooooooooo.            oooo                                                      \n");
	printf("`888   `Y88.          `888                                                      \n");
	printf(" 888   .d88' .ooooo.   888  oooo   .ooooo.  ooo..oo. .oo.    .ooooo.  ooo. .oo. \n");
	printf(" 888ooo88P' d88' `88b  888 .8P'   d88' `88b `888PY88bPY88b  d88' `88b `888P'Y88b\n");
	printf(" 888        888   888  888888.    888ooo888  888  888  888  888   888  888   888\n");
	printf(" 888        888   888  888 `88b.  888    .o  888  888  888  888   888  888   888\n");
	printf("o888o       `Y8bod8P' o888o o888o `Y8bod8P' o888  888o 888o `Y8bod8P' o888o o888\n"); 
printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n\n"); 
  srand(time(NULL));
  //Aqui se almacena todo lo relacionado a los pokemon
  Map * mapaPokemon =createMap(is_equal_string);
  FILE *pokecsv = fopen("pokemon.csv","r");
  char datos[1024]; int totalPokemon = 0;
  while(fgets(datos,1024,pokecsv)!=NULL){
    Pokemon *poke = (Pokemon *) malloc(sizeof(Pokemon));
    poke->stats=(Stats*) malloc (sizeof(Stats));
    poke->movs=(Movs*) malloc (sizeof(Movs));
    poke->nombre = (get_csv_field(datos,0));
    poke->tipo1 = get_csv_field(datos,1);
    poke->tipo2 = get_csv_field(datos,2);
    poke->stats->hp = atoi(get_csv_field(datos,3));
    poke->stats->atk = atoi(get_csv_field(datos,4));
    poke->stats->def = atoi(get_csv_field(datos,5));
    poke->stats->atk_esp = atoi(get_csv_field(datos,6));
    poke->stats->def_esp = atoi(get_csv_field(datos,7));
    poke->stats->vel = atoi(get_csv_field(datos,8));
    poke->legendary = atoi(get_csv_field(datos,9));
    poke->movs->mov1= (get_csv_field(datos,10));
    poke->movs->mov2= (get_csv_field(datos,11));
    poke->movs->mov3= (get_csv_field(datos,12));
    poke->movs->mov4= (get_csv_field(datos,13));
    insertMap(mapaPokemon,poke->nombre,poke);
    totalPokemon++;
    if (totalPokemon==110) break;
  } 
  
  //Aqui se almacena todo lo relacionado a efectividad
  List * listaEfectividad =createList();
  FILE *efcsv = fopen("efectividad.csv","r");
  char datosef[1024]; int totalEfectividad = 0;
   while(fgets(datosef,1024,efcsv)!=NULL){
     Efectividad * ef = (Efectividad*) malloc (sizeof(Efectividad));
     ef->nombre_tipo= get_csv_field(datosef,0);
     ef->normal = atof(get_csv_field(datosef,1));
     ef->lucha = atof(get_csv_field(datosef,2)); 
     ef->volador = atof(get_csv_field(datosef,3)); 
     ef->veneno = atof(get_csv_field(datosef,4));
     ef->tierra = atof(get_csv_field(datosef,5)); 
     ef->roca = atof(get_csv_field(datosef,6));
     ef->bicho = atof(get_csv_field(datosef,7));
     ef->fantasma = atof(get_csv_field(datosef,8));
     ef->acero = atof(get_csv_field(datosef,9));
     ef->fuego = atof(get_csv_field(datosef,10));
     ef->agua = atof(get_csv_field(datosef,11));
     ef->planta = atof(get_csv_field(datosef,12));
     ef->electrico= atof(get_csv_field(datosef,13));
     ef->psiquico = atof(get_csv_field(datosef,14));
     ef->hielo = atof(get_csv_field(datosef,15));
     ef->dragon = atof(get_csv_field(datosef,16));
     ef->siniestro = atof(get_csv_field(datosef,17));
     ef->hada = atof(get_csv_field(datosef,18));
     pushBack(listaEfectividad,ef);
     totalEfectividad++;
    if (totalEfectividad==19) break;
  } 
  
  //Aqui se almacena todo lo relacionado a los movimientos
  Map * mapaMovimientos =createMap(is_equal_string);
  FILE *movcsv = fopen("movimientos.csv","r");
  char datosmov[1024]; int totalMovs = 0;
  while(fgets(datosmov,1024,movcsv)!=NULL){
     Movimiento * mov = (Movimiento*) malloc (sizeof(Movimiento));
      mov->movimiento= get_csv_field(datosmov,0);
      mov->tipo= get_csv_field(datosmov,1);
      mov->daño= atoi(get_csv_field(datosmov,2));
      mov->precision= atoi(get_csv_field(datosmov,3));
      mov->efecto= get_csv_field(datosmov,4);
      mov->tipo_daño= get_csv_field(datosmov,5);
    
     insertMap(mapaMovimientos,mov->movimiento,mov);
     totalMovs++;
    if (totalMovs==80) break;
  } 
  
  printf("1- Modo Singleplayer\n");
  printf("2- Modo Multijugador\n");
  printf("3- Listado de Pokémons\n");
  printf("4- Movimientos disponibles\n");
  printf("5- Tipos elementales\n");
  printf("6- Finalizar simulador\n");
  
  int opcion;
  scanf("%d",&opcion);
    switch(opcion) {
      case 1: singlePlayer(mapaPokemon,listaEfectividad,mapaMovimientos); return 0;
      case 2: multiplayer(mapaPokemon,listaEfectividad,mapaMovimientos); return 0;
      case 3: mostrarMapaPokemon(mapaPokemon); return 0;
      case 4: mostrarMapaMovimientos(mapaMovimientos); return 0;
      case 5: mostrarListaEfectividad(listaEfectividad); return 0;
      case 6: return 0;
  }
}//Cierre main

//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO

void singlePlayer(Map * mapaPokemon,List* listaEfectividad, Map * mapaMovimientos){
  printf("Cargando modo Singleplayer....\n");
  cadena equipoJugador[10]; //arreglo que guarda el equipo pokémon del jugador
  cadena equipoEnemigo[10]; //arreglo que guarda el equipo pokémon del rival
  char nombre_pokemon[20];//variable para almacenar el nombre del pokemon
  
  printf("Ingrese los nombres de los 3 pokémon aliados a elegir\n"); 
  //POKEMON NUMERO 1
  while(1){
    printf("Pokemon 1 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Arcanine");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador[0],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 2 
  while(1){
    printf("Pokemon 2 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Blastoise");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador[1],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 3
  while(1){
    printf("Pokemon 3 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Archeops");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador[2],nombre_pokemon); break;
     }
  }
  
  //Ingresamos el equipo enemigo
  printf("Ingrese los nombres de los 3 pokémon enemigos a elegir\n"); 
  //POKEMON NUMERO 1 ENEMIGO
  while(1){
    printf("Pokemon 1 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Arcanine");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoEnemigo[0],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 2 ENEMIGO
  while(1){
    printf("Pokemon 2 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Blastoise");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoEnemigo[1],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 3 ENEMIGO
  while(1){
    printf("Pokemon 3 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Archeops");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoEnemigo[2],nombre_pokemon); break;
     }
  }
  printf("\nEquipo Jugador-> %s | ",equipoJugador[0]); printf("%s | ",equipoJugador[1]); printf("%s",equipoJugador[2]);
  printf("\nEquipo Enemigo-> %s | ",equipoEnemigo[0]); printf("%s | ",equipoEnemigo[1]); printf("%s \n\n",equipoEnemigo[2]);

  //Equipo pokémon enemigo
  /*strcpy(equipoEnemigo[0],"Decidueye");
  strcpy(equipoEnemigo[1],"Charizard");
  strcpy(equipoEnemigo[2],"Crobat");*/

  //Comienza el duelo 
  int i_jug=0; int i_ene=0;//Contadores para el equipo, cuando llegue a 3, se acaba el combate
  Pokemon * pokeJugador; Pokemon * pokeEnemigo; Movimiento * movi;//iniciar tipos de datos struct
  int dano_total; int mov_seleccionado;//variables del daño(formula) y el movimiento que seleccionara el usuario
 while(1){
  Pokemon * pokeJugador = searchMap(mapaPokemon,equipoJugador[i_jug]);//nos paramos con la info del pokemon
  Pokemon * pokeEnemigo =searchMap(mapaPokemon,equipoEnemigo[i_ene]);//nos paramos con la info del pokemon
  //Ciclo donde comienza el combate con los pokemons que estan en el campo
    while(1){
      //Cuando la vida de uno de los 2 pokemons termina, se acaba ese combate
      while(pokeJugador->stats->hp > 0 && pokeEnemigo->stats->hp >0 ){
      //Comparamos velocidades para ver quien ataca primero
      if ((pokeJugador->stats->vel > pokeEnemigo->stats->vel)){
        //ATACA EL JUGADOR
        printf("Ataca Jugador... Seleccione un movimiento\n");
        printf("»1- %s / 2- %s \n»3- %s / 4- %s \n",pokeJugador->movs->mov1,pokeJugador->movs->mov2,pokeJugador->movs->mov3,pokeJugador->movs->mov4);
        scanf("%d",&mov_seleccionado);
        //Segun el movimiento elegido, se buscara en el mapa para tenerlo a mano
        if (mov_seleccionado==1){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov4);
        }
        
        //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador->stats->atk_esp * movi->daño/pokeEnemigo->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        }

        //Se ve cuanto daño le hicimos al enemigo
        printf("%s aliado usa %s.\nLa salud de %s enemigo pasa de %d a ",pokeJugador->nombre,movi->movimiento,pokeEnemigo->nombre,pokeEnemigo->stats->hp);
        pokeEnemigo->stats->hp=(pokeEnemigo->stats->hp)-dano_total;
        //Si la vida es 0, el pokemon enemigo debe salir del combate
        //Si no, printea la vida con la que quedo el enemigo
        if (pokeEnemigo->stats->hp<=0){
        pokeEnemigo->stats->hp =0;
        printf("%d\n\n",pokeEnemigo->stats->hp);
        break;
        }else printf("%d\n\n",pokeEnemigo->stats->hp);
        
        //ATACA LA MAQUINA
        printf("Ataca %s enemigo.\n",pokeEnemigo->nombre);
        mov_seleccionado=((rand()%4)+1);//Movimiento random de la maquina
        if (mov_seleccionado==1){
           movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov4);
        }
        
        //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador->stats->atk_esp * movi->daño/pokeEnemigo->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        }

        //Se ve cuanto daño nos hicieron
        printf("%s enemigo usa %s.\nLa salud de %s aliado pasa de %d a ",pokeEnemigo->nombre,movi->movimiento,pokeJugador->nombre,pokeJugador->stats->hp);
        pokeJugador->stats->hp=(pokeJugador->stats->hp)-dano_total;

        //Si nos dejaron el pokemon con 0 de vida, sale de combate
        //Si no, printea la vida con la que quedo nuestro pokemon
       if (pokeJugador->stats->hp<=0){
        pokeJugador->stats->hp =0;
        printf("%d\n\n",pokeJugador->stats->hp);
        break;
        }else printf("%d\n\n",pokeJugador->stats->hp);
  
        
      } else{
        //else, En caso de que sea mas rapido el enemigo, parte atacando él
        
        //ATACA EL ENEMIGO
        printf("Ataca %s enemigo.\n",pokeEnemigo->nombre);
        //movimiento random para el enemigo
        mov_seleccionado=((rand()%4)+1);
        if (mov_seleccionado==1){
           movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeEnemigo->movs->mov4);
        }

       //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador->stats->atk_esp * movi->daño/pokeEnemigo->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        }
        
        //Daño que nos hacen
        printf("%s enemigo usa %s.\nLa salud de %s aliado pasa de %d a ",pokeEnemigo->nombre,movi->movimiento,pokeJugador->nombre,pokeJugador->stats->hp);
        pokeJugador->stats->hp=(pokeJugador->stats->hp)-dano_total;

        //Si nos quedamos en 0 de vida, cambiamos pokemon
        //Si no, muestra con cuanto quedamos
       if (pokeJugador->stats->hp<=0){
        pokeJugador->stats->hp =0;
        printf("%d\n\n",pokeJugador->stats->hp);
        break;
        }else printf("%d\n\n",pokeJugador->stats->hp);
  
         //ATACA EL JUGADOR
        printf("Ataca Jugador... Seleccione un movimiento\n");
        printf("»1- %s / 2- %s \n»3- %s / 4- %s \n",pokeJugador->movs->mov1,pokeJugador->movs->mov2,pokeJugador->movs->mov3,pokeJugador->movs->mov4);
        scanf("%d",&mov_seleccionado);
        if (mov_seleccionado==1){
           movi =searchMap(mapaMovimientos,pokeJugador->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeJugador->movs->mov4);
        }
        
       //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador->stats->atk_esp * movi->daño/pokeEnemigo->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador->stats->atk * movi->daño/pokeEnemigo->stats->def)/50) + 2)*coincideTipo(pokeJugador->tipo1,pokeJugador->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeEnemigo->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeEnemigo->tipo2)*((rand()%15)+85)/100)*critico();
        }
        
        //Cuanto daño hicimos
        printf("%s aliado usa %s.\nLa salud de %s enemigo pasa de %d a ",pokeJugador->nombre,movi->movimiento,pokeEnemigo->nombre,pokeEnemigo->stats->hp);
        pokeEnemigo->stats->hp=(pokeEnemigo->stats->hp)-dano_total;
        
        //si el enemigo quedo en 0, tiene que cambiar al siguiente pokemon
        //si no, se muestra por pantalla la vida con la que quedo
        if (pokeEnemigo->stats->hp<=0){
        pokeEnemigo->stats->hp =0;
        printf("%d\n\n",pokeEnemigo->stats->hp);
        break;
        }else printf("%d\n\n",pokeEnemigo->stats->hp);
  
      }//Cierre else
     }
      break;
    }

    //Aqui se ven los cambios de los pokemon cuando uno queda en 0 de vida (nosotros)
    if (pokeJugador->stats->hp == 0){
    i_jug++;
      if (i_jug>2){
        printf("====COMBATE FINALIZADO====");
        break;
      }else {
        printf("====CAMBIO DE POKEMON====\n");
        printf("Entra %s aliado al combate.\n",equipoJugador[i_jug]);
        }
    }
    //Aqui se ven los cambios de los pokemon para el enemigo
    if (pokeEnemigo->stats->hp == 0){
    i_ene++;
      if (i_ene>2){
        printf("====COMBATE FINALIZADO====");
        break;
      }else {
        printf("====CAMBIO DE POKEMON====\n");
        printf("Entra %s enemigo al combate.\n",equipoEnemigo[i_ene]);
        }
    }
  }
}//Cierra la funcion

void multiplayer(Map * mapaPokemon,List* listaEfectividad, Map * mapaMovimientos){
printf("Cargando modo Multiplayer....\n");
  cadena equipoJugador1[10]; //arreglo que guarda el equipo pokémon del jugador 1
  cadena equipoJugador2[10]; //arreglo que guarda el equipo pokémon del jugador 2 
  char nombre_pokemon[20];//variable para almacenar el nombre del pokemon
  
  printf("Jugador 1, ingrese los nombres de los 3 pokémon aliados a elegir\n"); 
  //POKEMON NUMERO 1
  while(1){
    printf("Pokemon 1 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Arcanine");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador1[0],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 2 
  while(1){
    printf("Pokemon 2 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Blastoise");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador1[1],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 3
  while(1){
    printf("Pokemon 3 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Archeops");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador1[2],nombre_pokemon); break;
     }
  }
  
  //Ingresamos el equipo del jugador 2
  printf("Jugador, ingrese los nombres de los 3 pokémon aliados a elegir\n"); 
  //POKEMON NUMERO 1 
  while(1){
    printf("Pokemon 1 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Arcanine");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador2[0],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 2 
  while(1){
    printf("Pokemon 2 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Blastoise");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador2[1],nombre_pokemon); break;
     }
  }
  //POKEMON NUMERO 3 
  while(1){
    printf("Pokemon 3 : "); scanf("%s",nombre_pokemon); 
    //strcpy(nombre_pokemon,"Archeops");
    if (searchMap(mapaPokemon,nombre_pokemon)==NULL){
      printf("Pokemon no existe\n");
    } else {
      strcpy(equipoJugador2[2],nombre_pokemon); break;
     }
  }
  //Mostramos equipos por pantalla
  printf("\nEquipo Jugador-> %s | ",equipoJugador1[0]); printf("%s | ",equipoJugador1[1]); printf("%s",equipoJugador1[2]);
  printf("\nEquipo Enemigo-> %s | ",equipoJugador2[0]); printf("%s | ",equipoJugador2[1]); printf("%s \n\n",equipoJugador2[2]);

  //Comienza el duelo 
  int i_jug1=0; int i_jug2=0;//Contadores para el equipo, cuando llegue a 3, se acaba el combate
  Pokemon * pokeJugador1; Pokemon * pokeJugador2; Movimiento * movi;//iniciar tipos de datos struct
  int dano_total; int mov_seleccionado;//variables del daño(formula) y el movimiento que seleccionara el usuario
 while(1){
  Pokemon * pokeJugador1 = searchMap(mapaPokemon,equipoJugador1[i_jug1]);//nos paramos con la info del pokemon
  Pokemon * pokeJugador2 =searchMap(mapaPokemon,equipoJugador2[i_jug2]);//nos paramos con la info del pokemon
  //Ciclo donde comienza el combate con los pokemons que estan en el campo
    while(1){
      //Cuando la vida de uno de los 2 pokemons termina, se acaba ese combate
      while(pokeJugador1->stats->hp > 0 && pokeJugador2->stats->hp >0 ){
      //Comparamos velocidades para ver quien ataca primero
      if ((pokeJugador1->stats->vel > pokeJugador2->stats->vel)){
        //ATACA EL JUGADOR 1
        printf("Ataca Jugador 1... Seleccione un movimiento\n");
        printf("»1- %s / 2- %s \n»3- %s / 4- %s \n",pokeJugador1->movs->mov1,pokeJugador1->movs->mov2,pokeJugador1->movs->mov3,pokeJugador1->movs->mov4);
        scanf("%d",&mov_seleccionado);
        //Segun el movimiento elegido, se buscara en el mapa para tenerlo a mano
        if (mov_seleccionado==1){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov4);
        }
        
        //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk_esp * movi->daño/pokeJugador2->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        }

        //Se ve cuanto daño le hicimos al jugador 2
        printf("%s aliado usa %s.\nLa salud de %s enemigo pasa de %d a ",pokeJugador1->nombre,movi->movimiento,pokeJugador2->nombre,pokeJugador2->stats->hp);
        pokeJugador2->stats->hp=(pokeJugador2->stats->hp)-dano_total;
        //Si la vida es 0, el pokemon enemigo debe salir del combate
        //Si no, printea la vida con la que quedo el enemigo
        if (pokeJugador2->stats->hp<=0){
        pokeJugador2->stats->hp =0;
        printf("%d\n\n",pokeJugador2->stats->hp);
        break;
        }else printf("%d\n\n",pokeJugador2->stats->hp);
        
        //ATACA JUGADOR 2
        printf("Ataca Jugador 2... Seleccione un movimiento\n");
        printf("»1- %s / 2- %s \n»3- %s / 4- %s \n",pokeJugador2->movs->mov1,pokeJugador2->movs->mov2,pokeJugador2->movs->mov3,pokeJugador2->movs->mov4);
        scanf("%d",&mov_seleccionado);
        //Segun el movimiento elegido, se buscara en el mapa para tenerlo a mano
        if (mov_seleccionado==1){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov4);
        }
        
        //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk_esp * movi->daño/pokeJugador2->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        }

        //Se ve cuanto daño recibe Jugador 1 
        printf("%s enemigo usa %s.\nLa salud de %s aliado pasa de %d a ",pokeJugador2->nombre,movi->movimiento,pokeJugador1->nombre,pokeJugador1->stats->hp);
        pokeJugador1->stats->hp=(pokeJugador1->stats->hp)-dano_total;

        //Si dejan al jugador 1 con 0 de vida, sale de combate
        //Si no, printea la vida con la que quedo el pokemon de jugador 1 
       if (pokeJugador1->stats->hp<=0){
        pokeJugador1->stats->hp =0;
        printf("%d\n\n",pokeJugador1->stats->hp);
        break;
        }else printf("%d\n\n",pokeJugador1->stats->hp);
  
        
      } else{
        //else, En caso de que sea mas rapido el Jugador 2, parte atacando él
        
        //ATACA JUGADOR 2
        printf("Ataca Jugador 2... Seleccione un movimiento\n");
        printf("»1- %s / 2- %s \n»3- %s / 4- %s \n",pokeJugador2->movs->mov1,pokeJugador2->movs->mov2,pokeJugador2->movs->mov3,pokeJugador2->movs->mov4);
        scanf("%d",&mov_seleccionado);
        //Segun el movimiento elegido, se buscara en el mapa para tenerlo a mano
        if (mov_seleccionado==1){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov4);
        }

       //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk_esp * movi->daño/pokeJugador2->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        }
        
        //Daño que recibe Jugador 1
        printf("%s enemigo usa %s.\nLa salud de %s aliado pasa de %d a ",pokeJugador2->nombre,movi->movimiento,pokeJugador1->nombre,pokeJugador1->stats->hp);
        pokeJugador1->stats->hp=(pokeJugador1->stats->hp)-dano_total;

        //Si queda en 0 de vida el Jugador 1, cambiamos pokemon
        //Si no, muestra con cuanto quedo Jugador 1
       if (pokeJugador1->stats->hp<=0){
        pokeJugador1->stats->hp =0;
        printf("%d\n\n",pokeJugador1->stats->hp);
        break;
        }else printf("%d\n\n",pokeJugador1->stats->hp);
  
         //ATACA EL JUGADOR 1
        printf("Ataca Jugador... Seleccione un movimiento\n");
        printf("»1- %s / 2- %s \n»3- %s / 4- %s \n",pokeJugador1->movs->mov1,pokeJugador1->movs->mov2,pokeJugador1->movs->mov3,pokeJugador1->movs->mov4);
        scanf("%d",&mov_seleccionado);
        if (mov_seleccionado==1){
           movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov1);
        }else if (mov_seleccionado==2){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov2);
        }else if (mov_seleccionado==3){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov3);
        }else if (mov_seleccionado==4){
          movi =searchMap(mapaMovimientos,pokeJugador1->movs->mov4);
        }
        
       //Formula de daño "dano_total", F para daño Fisico, E para daño Especial, X para no_type
        if (strcmp(movi->tipo_daño,"F")==0){//Fisico
        dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"E")==0){ //Especial
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk_esp * movi->daño/pokeJugador2->stats->def_esp)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        } else if (strcmp(movi->tipo_daño,"X")==0){ //no_type
          dano_total=(((((2*100/7)*pokeJugador1->stats->atk * movi->daño/pokeJugador2->stats->def)/50) + 2)*coincideTipo(pokeJugador1->tipo1,pokeJugador1->tipo2,movi->tipo)*vsTipoRival1(listaEfectividad,movi->tipo,pokeJugador2->tipo1)*vsTipoRival2(listaEfectividad,movi->tipo,pokeJugador2->tipo2)*((rand()%15)+85)/100)*critico();
        }
        
        //Cuanto daño recibe Jugador 2
        printf("%s aliado usa %s.\nLa salud de %s enemigo pasa de %d a ",pokeJugador1->nombre,movi->movimiento,pokeJugador2->nombre,pokeJugador2->stats->hp);
        pokeJugador2->stats->hp=(pokeJugador2->stats->hp)-dano_total;
        
        //si el Jugador 2 quedo en 0, tiene que cambiar al siguiente pokemon
        //si no, se muestra por pantalla la vida con la que quedo
        if (pokeJugador2->stats->hp<=0){
        pokeJugador2->stats->hp =0;
        printf("%d\n\n",pokeJugador2->stats->hp);
        break;
        }else printf("%d\n\n",pokeJugador2->stats->hp);
  
      }//Cierre else
     }
      break;
    }

    //Aqui se ven los cambios de los pokemon cuando el Jugador 1 queda con 0 de vida
    if (pokeJugador1->stats->hp == 0){
    i_jug1++;
      if (i_jug1>2){
        printf("====COMBATE FINALIZADO====");
        break;
      }else {
        printf("====CAMBIO DE POKEMON====\n");
        printf("Entra %s aliado al combate.\n",equipoJugador1[i_jug1]);
        }
    }
    //Aqui se ven los cambios de los pokemon cuando el Jugador 2 queda con 0 de vida
    if (pokeJugador2->stats->hp == 0){
    i_jug2++;
      if (i_jug2>2){
        printf("====COMBATE FINALIZADO====");
        break;
      }else {
        printf("====CAMBIO DE POKEMON====\n");
        printf("Entra %s enemigo al combate.\n",equipoJugador2[i_jug2]);
        }
    }
  }
}//Cierra funcion


float coincideTipo(char *tipo1,char *tipo2,char *tipo_mov){
  int igual_tipo1; int igual_tipo2;
  igual_tipo1 =strcmp(tipo1,tipo_mov); igual_tipo2=strcmp(tipo2,tipo_mov);
  //Si coincide devuelve 1.5, si no, 1 
  if (( igual_tipo1==0 || igual_tipo2==0)) return 1.5;
  else return 1;
}

float vsTipoRival1(List * listaEfectividad,char * movi_tipo,char* tipo_rival){
  Efectividad * efe =firstList(listaEfectividad);
  while(efe !=NULL){
    if(strcmp(efe->nombre_tipo,movi_tipo)==0){
      if (strcmp(tipo_rival,"Normal")==0) return efe->normal;
        else if (strcmp(tipo_rival,"")==0) return 1;
        else if (strcmp(tipo_rival,"Lucha")==0) return efe->lucha;
        else if (strcmp(tipo_rival,"Volador")==0) return efe->volador;
        else if (strcmp(tipo_rival,"Veneno")==0) return efe->veneno;
        else if (strcmp(tipo_rival,"Tierra")==0) return efe->tierra;
        else if (strcmp(tipo_rival,"Roca")==0) return efe->roca;
        else if (strcmp(tipo_rival,"Bicho")==0) return efe->bicho;
        else if (strcmp(tipo_rival,"Fantasma")==0) return efe->fantasma;
        else if (strcmp(tipo_rival,"Acero")==0) return efe->acero;
        else if (strcmp(tipo_rival,"Fuego")==0) return efe->fuego;
        else if (strcmp(tipo_rival,"Agua")==0) return efe->agua;
        else if (strcmp(tipo_rival,"Planta")==0) return efe->planta; 
        else if (strcmp(tipo_rival,"Electrico")==0) return efe->electrico;
        else if (strcmp(tipo_rival,"Psiquico")==0) return efe->psiquico;
        else if (strcmp(tipo_rival,"Hielo")==0) return efe->hielo;
        else if (strcmp(tipo_rival,"Dragon")==0) return efe->dragon;
        else if (strcmp(tipo_rival,"Siniestro")==0) return efe->siniestro;
        else if (strcmp(tipo_rival,"Hada")==0) return efe->hada;
    }else efe=nextList(listaEfectividad);
  }
}

float vsTipoRival2(List * listaEfectividad,char * movi_tipo,char* tipo_rival){
    Efectividad * efe =firstList(listaEfectividad);
  while(efe !=NULL){
    if(strcmp(efe->nombre_tipo,movi_tipo)==0){
      if (strcmp(tipo_rival,"Normal")==0) return efe->normal;
        else if (strcmp(tipo_rival,"")==0) return 1;
        else if (strcmp(tipo_rival,"Lucha")==0) return efe->lucha;
        else if (strcmp(tipo_rival,"Volador")==0) return efe->volador;
        else if (strcmp(tipo_rival,"Veneno")==0) return efe->veneno;
        else if (strcmp(tipo_rival,"Tierra")==0) return efe->tierra;
        else if (strcmp(tipo_rival,"Roca")==0) return efe->roca;
        else if (strcmp(tipo_rival,"Bicho")==0) return efe->bicho;
        else if (strcmp(tipo_rival,"Fantasma")==0) return efe->fantasma;
        else if (strcmp(tipo_rival,"Acero")==0) return efe->acero;
        else if (strcmp(tipo_rival,"Fuego")==0) return efe->fuego;
        else if (strcmp(tipo_rival,"Agua")==0) return efe->agua;
        else if (strcmp(tipo_rival,"Planta")==0) return efe->planta; 
        else if (strcmp(tipo_rival,"Electrico")==0) return efe->electrico;
        else if (strcmp(tipo_rival,"Psiquico")==0) return efe->psiquico;
        else if (strcmp(tipo_rival,"Hielo")==0) return efe->hielo;
        else if (strcmp(tipo_rival,"Dragon")==0) return efe->dragon;
        else if (strcmp(tipo_rival,"Siniestro")==0) return efe->siniestro;
        else if (strcmp(tipo_rival,"Hada")==0) return efe->hada;
    }else efe=nextList(listaEfectividad);
  }
}

float critico(){
  //Only probabilty
  int probabilidad = ((rand()%100)+1);
  if (probabilidad<=13){
    printf("GOLPE CRITICO\n");
    return 1.5; 
  } 
  return 1;
}

void mostrarMapaPokemon (Map * mapaPokemon){
  Pokemon * poke = firstMap(mapaPokemon);
  while (poke!=NULL){
    printf("»%s,%s,%s,%i,%i,%i,%i,%i,%i,%i,%s,%s,%s,%s\n",poke->nombre,poke->tipo1,poke->tipo2,poke->stats->hp,poke->stats->atk,poke->stats->def,poke->stats->atk_esp,poke->stats->def_esp,poke->stats->vel,poke->legendary,poke->movs->mov1,poke->movs->mov2,poke->movs->mov3,poke->movs->mov4);
    poke=nextMap(mapaPokemon);
  }
}

void mostrarListaEfectividad (List* listaEfectividad){
  Efectividad * ef = firstList(listaEfectividad);
  while (ef!=NULL){ printf("»%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\n",ef->nombre_tipo,ef->normal,ef->lucha,ef->volador,ef->veneno,ef->tierra,ef->roca,ef->bicho,ef->fantasma,ef->acero,ef->fuego,ef->agua,ef->planta,ef->electrico,ef->psiquico,ef->hielo,ef->dragon,ef->siniestro,ef->hada);
    ef=nextList(listaEfectividad);
  }
}

void mostrarMapaMovimientos (Map * mapaMovimientos){
  Movimiento * mov = firstMap(mapaMovimientos);
  while (mov!=NULL){
    printf("»%s, %s, %d, %d, %s, %s \n",mov->movimiento,mov->tipo,mov->daño,mov->precision,mov->efecto,mov->tipo_daño);
    mov=nextMap(mapaMovimientos);
  }
}

  
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO
//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO//ESPACIO DE TRABAJO


/*
  funcion para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

// Funcion para leer el k-esimo elemento de un string (separado por comas)
const char *get_csv_field (char * tmp, int k) {
  int open_mark = 0;
  char* ret=(char*) malloc (100*sizeof(char));
  int ini_i=0, i=0;
  int j=0;
  while(tmp[i+1]!='\0'){
      if(tmp[i]== '\"'){
        open_mark = 1-open_mark;
        if(open_mark) ini_i = i+1;
        i++;
        continue;
      }
      if(open_mark || tmp[i]!= ','){
        if(k==j) ret[i-ini_i] = tmp[i];
        i++;
        continue;
      }
      if(tmp[i]== ','){
          if(k==j) {
          ret[i-ini_i] = 0;
          return ret;
        }
          j++; ini_i = i+1;
      }
      i++;
  }
  if(k==j) {
    ret[i-ini_i] = 0;
    return ret;
  }
  return NULL;
}    