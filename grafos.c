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

int dkjistra(struct vertices **inicio){
	if(!*inicio){
		return 0;
	}
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
