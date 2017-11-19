#include"stdio.h"
#include"stdlib.h"
#include"string.h"
struct vertices
{
	char ciudad[20];
	int marca;
	struct arista *unir;
	struct vertices *siguiente;
};

struct arista
{
	char nodo[20];
	float peso;
	float suma;
	struct vertices *conecta;
	struct arista *siguiente;

};

int crea_camino(struct vertices **camino,char nodo[]){
	struct vertices *nuevo=(struct vertices*)malloc(sizeof(struct vertices));
	if(!nuevo){
		return 0;
	}
	strcpy(nuevo->ciudad,nodo);
	nuevo->siguiente=*camino;
	*camino=nuevo;
	return 1;
}

struct vertices *crea_vertice(struct vertices **inicio){
	struct vertices *nuevo=(struct vertices*)malloc(sizeof(struct vertices));
	if(!nuevo){
		return NULL;
	}
	printf("Nombre de la ciudad:");
	fflush(stdin);
	scanf("%[^\n]",&nuevo->ciudad);
	nuevo->marca=0;
	nuevo->unir=NULL;
	nuevo->siguiente=*inicio;
	*inicio=nuevo;
	return nuevo;
}

struct arista *crea_arista(struct arista **inicio,char nodo[],float peso){
	struct arista *nuevo=(struct arista*)malloc(sizeof(struct arista));
	if(!nuevo){
		return NULL;
	}
	nuevo->conecta=NULL;
	nuevo->peso=peso;
	nuevo->suma=0;
	strcpy(nuevo->nodo,nodo);
	nuevo->siguiente=*inicio;
	*inicio=nuevo;
	return nuevo;
}

void mostrar_arista(struct arista *aris){
	if(aris){
		printf(" %s - ",aris->nodo);
		mostrar_arista(aris->siguiente);
	}
	return ;
}

void mostrar_vertices(struct vertices *inicio){
	if(inicio){
		printf("\n %s -> ",inicio->ciudad);
		mostrar_arista(inicio->unir);
		mostrar_vertices(inicio->siguiente);
	}
	return ;
}

struct vertices *busca_nodo(struct vertices *ciudad,char nodo[]){
	if(!ciudad){
		return NULL;
	}
	if(strcmp(nodo,ciudad->ciudad)==0){
		return ciudad;
	}
	busca_nodo(ciudad->siguiente,nodo);
}

int enlazar(struct vertices **inicio){
	if(!*inicio){
		printf("\nNo existe ningun nodo"); 
		return 0;
	}
	printf("Ciudades posibles\n");
	mostrar_vertices(*inicio);
	char nodo[20],nodo2[20];
	float peso;
	printf("\nCiudad de partida: ");
	fflush(stdin);
	scanf("%[^\n]",nodo);
	struct vertices *aux,*aux2;
	while((aux=busca_nodo(*inicio,nodo))==NULL){
		printf("Error\nInserte nueva mente el nodo: ");
		fflush(stdin);
		scanf("%[^\n]",nodo);
	}
	printf("\nnodo correcto\nInserte el nodo destino: ");
	fflush(stdin);
	scanf("%[^\n]",nodo2);
	while((aux2=busca_nodo(*inicio,nodo2))==NULL){
		printf("Error\nInserte nueva mente el nodo: ");
		fflush(stdin);
		scanf("%[^\n]",nodo2);
	}
	printf("Nodos conectados correctamente");
	printf("\nDistancia entre los nodos: ");
	scanf("%f",&peso);
	crea_arista(&aux->unir,nodo2,peso);
	crea_arista(&aux2->unir,nodo,peso);
	return 0;
}

struct arista *busca_menor(struct arista *origen,struct arista *menor,struct vertices *inicio){
	if(origen==NULL){
		return menor;
	}
	struct vertices *aux=busca_nodo(inicio,origen->nodo);
	if(aux->marca==0){
		if(menor->peso > origen->peso){
			menor=origen;
		}	
	}
	busca_menor(origen->siguiente,menor,inicio);
	
}

int marcar(struct vertices **nodo){  //Funcion que podria ser necesaria
	(*nodo)->marca=1;
}

int algortimo(struct vertices **origen,struct vertices **destino,struct vertices **inicio,struct vertices **camino){
	
	crea_camino(camino,(*origen)->ciudad);
	if(strcmp((*origen)->ciudad,(*destino)->ciudad)==0){
		return printf("Ciudad encontrada\nRecorrido -> ");
		mostrar_vertices(*camino);
		return 1;
	}
	struct arista *aux=(*origen)->unir;
	struct arista *aux2=busca_menor((*origen)->unir->siguiente,aux,*inicio);
	printf("\nCamino con menor costo: %s   Distancia: %0.1f",aux2->nodo,aux2->peso);
	(*origen)->marca=1;
	struct vertices *nod=busca_nodo(*inicio,aux2->nodo);
	marcar(&nod);
	algortimo(&nod,destino,inicio,camino);
	return 1;	
}

int dkjistra(struct vertices **inicio){
	if(!*inicio){
		return 0;
	}
	struct vertices *camino=NULL; //lista que contendra el camino del recorrido
	char nodo[20],nodo2[20];
	printf("\nCiudad de partida: ");
	fflush(stdin);
	scanf("%[^\n]",nodo);
	struct vertices *aux,*aux2;
	while((aux=busca_nodo(*inicio,nodo))==NULL){
		printf("Error\nInserte nueva mente el nodo: ");
		fflush(stdin);
		scanf("%[^\n]",nodo);
	}
	printf("\nInserte el nodo destino: ");
	fflush(stdin);
	scanf("%[^\n]",nodo2);
	while((aux2=busca_nodo(*inicio,nodo2))==NULL){
		printf("Error\nInserte nueva mente el nodo: ");
		fflush(stdin);
		scanf("%[^\n]",nodo2);
	}
	algortimo(&aux,&aux2,inicio,&camino);
	return 1;
}

void menu(struct vertices **inicio){
	int opc;
	do{
		printf("1.Crear vertice\n2.Mostrar vertices\n3.Enlazar vertices\n4.Algoritmo\n5.Salir\nOpcion: ");
		scanf("%d",&opc);
		switch(opc){
			case 1: crea_vertice(inicio); break;
			case 2: mostrar_vertices(*inicio); break;
			case 3: enlazar(inicio); break;
			case 4: dkjistra(inicio); break;
		}	
	printf("\n");	
	system("pause");
	system("cls");
	}while(opc!=5);
}


int main(){
	struct vertices *inicio=NULL;
	menu(&inicio);
	return 0;
}
