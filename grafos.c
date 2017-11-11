#include"stdio.h"
#include"stdlib.h"
struct cola
{
	struct elementos *frente;
	struct elementos *final;
};

struct elementos{
	struct elementos *sig;
	int id;
	char nombre[20];
};

struct cola2{
	struct camino *frente;
	struct camino *fin;
};

struct camino{
	struct camino *siguiente;
	float peso;
	int id;
};

struct elementos *crea_nodo(struct cola **nodo,int id){
	struct elementos *nuevo=(struct elementos *)malloc(sizeof(struct elementos));
	if(!nuevo){
		return NULL;
	}
	printf("Ciudad %d:",id);
	fflush(stdin);
	scanf("%[^\n]",nuevo->nombre);
	nuevo->id=id;
	nuevo->sig=NULL;
	if((*nodo)->final==NULL){
		(*nodo)->frente=nuevo;
	}else{
		(*nodo)->final->sig=nuevo;
	}
	(*nodo)->final=nuevo;
	return (*nodo)->final;
}

void mostrar_ciudades(struct elementos *frente){
	if(frente){
		printf("\nCiudad:%s",frente->nombre);
		mostrar_ciudades(frente->sig);
	}
	return ;
}

int crea_cola(struct cola **nodo){
	struct cola *nuevo=(struct cola *)malloc(sizeof(struct cola));
	if(!nuevo){
		return 0;
	}
	nuevo->frente=NULL;
	nuevo->final=NULL;
	*nodo=nuevo;
	return 1;
}

int main(){
	struct cola *nodo=NULL;
	int cant,i=1,opc;
	
	crea_cola(&nodo);
	printf("\nCuanas ciudades insertara: ");
	scanf("%d",&cant);
	do{
		crea_nodo(&nodo,i);
		cant=cant-1;
		i=i+1;
	}while(cant>0);
	
	do{
		printf("\n1.Mostrar ciudades\n2.Salir\nOpcion:");
		scanf("%d",&opc);
		switch(opc){
			case 1: mostrar_ciudades(nodo->frente); break;
		}
	printf("\n");
	system("pause");
	system("cls");
	}while(opc!=2);
	return 0;
}
