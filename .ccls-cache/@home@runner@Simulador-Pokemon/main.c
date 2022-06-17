#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include "map.h"
#include "list.h"

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

const char *get_csv_field (char * tmp, int k);
int is_equal_string(void * key1, void * key2);
void mostrarMapaPokemon (Map * mapaPokemon);
void mostrarMapaEfectividad (Map * mapaEfectividad);

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
  
  Map * mapaPokemon =createMap(is_equal_string);
  FILE *fp = fopen("pokemon.csv","r");
  char datos[1024]; int totalPokemon = 0;
  //Aqui se almacena todo lo relacionado a los pokemon
  while(fgets(datos,1024,fp)!=NULL){
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
    if (totalPokemon==15) break;
  } 
  //Aqui se almacena todo lo relacionado a efectividad
  Map * mapaEfectividad =createMap(is_equal_string);
  FILE *fp1 = fopen("efectividad.csv","r");
  char datos1[1024]; int totalEfectividad = 0;
   while(fgets(datos1,1024,fp1)!=NULL){
     Efectividad * ef = (Efectividad*) malloc (sizeof(Efectividad));
     ef->nombre_tipo= get_csv_field(datos,0);
     ef->normal = atof(get_csv_field(datos,1));
     ef->lucha = atof(get_csv_field(datos,2)); 
     ef->volador = atof(get_csv_field(datos,3)); 
     ef->veneno = atof(get_csv_field(datos,4));
     ef->tierra = atof(get_csv_field(datos,5)); 
     ef->roca = atof(get_csv_field(datos,6));
     ef->bicho = atof(get_csv_field(datos,7));
     ef->fantasma = atof(get_csv_field(datos,8));
     ef->acero = atof(get_csv_field(datos,9));
     ef->fuego = atof(get_csv_field(datos,10));
     ef->agua = atof(get_csv_field(datos,11));
     ef->planta = atof(get_csv_field(datos,12));
     ef->electrico= atof(get_csv_field(datos,13));
     ef->psiquico = atof(get_csv_field(datos,14));
     ef->hielo = atof(get_csv_field(datos,15));
     ef->dragon = atof(get_csv_field(datos,16));
     ef->siniestro = atof(get_csv_field(datos,17));
     ef->hada = atof(get_csv_field(datos,18));
     insertMap(mapaEfectividad,ef->nombre_tipo,ef);
     totalEfectividad++;
    if (totalEfectividad==18) break;
  } 
  
  printf("1- Modo Singleplayer\n");
  printf("2- Modo Multijugador\n");
  printf("3- Listado de Pokémons\n");
  printf("\n\n\n");
  int select;
  printf("pokemons (1) ; efectividad (2)");
  if (select==1){
     mostrarMapaPokemon(mapaPokemon);
  } else if (select ==2){
     mostrarMapaEfectividad(mapaEfectividad);
  }
  return 0;
}

void mostrarMapaPokemon (Map * mapaPokemon){
  Pokemon * poke = firstMap(mapaPokemon);
  while (poke!=NULL){
    printf("»%s,%s,%s,%i,%i,%i,%i,%i,%i,%s,%s,%s,%s\n",poke->nombre,poke->tipo1,poke->tipo2,poke->stats->hp,poke->stats->atk,poke->stats->def,poke->stats->atk_esp,poke->stats->def_esp,poke->stats->vel,poke->movs->mov1,poke->movs->mov2,poke->movs->mov3,poke->movs->mov4);
    poke=nextMap(mapaPokemon);
  }
}

void mostrarMapaEfectividad(Map * mapaEfectividad){
  Efectividad * ef = firstMap(mapaEfectividad);
  while (ef!=NULL){
    printf("»%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",ef->nombre_tipo,ef->normal,ef->lucha,ef->volador,ef->veneno,ef->tierra,ef->roca,ef->bicho,ef->fantasma,ef->acero,ef->fuego,ef->agua,ef->planta,ef->electrico,ef->psiquico,ef->hielo,ef->dragon,ef->siniestro,ef->hada);
    ef=nextMap(mapaEfectividad);
  }
}





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
