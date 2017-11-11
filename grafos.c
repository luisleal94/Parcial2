#include"stdio.h"
#include"stdlib.h"
#include "string.h"
struct cola{
	struct cola *sig;
	float peso;
	char ciudad[20];
	int id;
};


struct lista{
	int id;
	char ciudad[20];
	struct cola *frente;
	struct cola *final;
	struct lista *siguiente;
};

int inserta_lista(struct lista **inicio,int id){
	struct lista *nuevo=(struct lista*)malloc(sizeof(struct lista));
	if(!nuevo){
		return 0;
	}
	printf("Inserte ciudad: ");
	fflush(stdin);
	scanf("%[^\n]",nuevo->ciudad);
	nuevo->id=id;
	nuevo->frente=NULL;
	nuevo->final=NULL;
	nuevo->siguiente=*inicio;
	*inicio=nuevo;
}

void mostrar_ciudad(struct lista *inicio){
	if(inicio){
		printf("%s\n",inicio->ciudad);
		mostrar_ciudad(inicio->siguiente);
	}
	return ;
}

int crea_camino(struct cola **frente,struct cola **final,struct lista *inicio,struct lista *origen){
	if(inicio==NULL){
		return 0;
	}
	struct cola *nuevo=(struct cola*)malloc(sizeof(struct cola));
	if(!nuevo){
		return 0;
	}
	//printf("\nOrigen:%s",origen->ciudad);  //Necesitamos saber si es la misma ciudad para asignarle un peso de 0 o si tiene distancia
	strcpy(nuevo->ciudad,inicio->ciudad); 
	if(strcmp(nuevo->ciudad,origen->ciudad)==0){
		//Son iguales
		nuevo->peso=0;
	}else{
		printf("\nDistancia de %s a %s: ",origen->ciudad,nuevo->ciudad);
		scanf("%f",&nuevo->peso);
	}
	nuevo->sig=NULL;
	if(*final==NULL){
		*frente=nuevo;
	}else{
		(*final)->sig=nuevo;
	}
	*final=nuevo;
	crea_camino(frente,final,inicio->siguiente,origen);
}

int llena_grafo(struct lista **inicio,struct lista *aux){
	if(!*inicio){
		return 0;
	}
	crea_camino(&(*inicio)->frente,&(*inicio)->final,aux,*inicio);
	llena_grafo(&(*inicio)->siguiente,aux);
}

void mostrar_grafo2(struct cola *frente){
	if(frente){
		printf("\t|%s ->Distancia: %0.2f|",frente->ciudad,frente->peso);
		mostrar_grafo2(frente->sig);	
	}
	return ;
}

void mostrar_grafo(struct lista *inicio){
	if(inicio){
		printf("\nCiudidad:%s \n",inicio->ciudad);
		mostrar_grafo2(inicio->frente);
		mostrar_grafo(inicio->siguiente);
	}
	return ;
}
int main(){
	struct lista *inicio=NULL;
	int cant,i=1,opc;
	printf("Cuantas ciudades que insertara: ");
	scanf("%d",&cant);
	do{
		inserta_lista(&inicio,i);	
		cant=cant-1;
		i=i+1;
	}while(cant>0);
	llena_grafo(&inicio,inicio);
	mostrar_grafo(inicio);
	return 0;
}
