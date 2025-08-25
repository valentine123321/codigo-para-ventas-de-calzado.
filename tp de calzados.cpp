#include<iostream>
#include<iomanip>

#define CANTCALZADOS 20
#define CANTTIPOS 4
#define CANTTALLES 6

using namespace std;

struct Calzado{
	int codCalzado;
	char tipoCalzado;
	float precioUnitario;
	int stockInicial[CANTTALLES];
	int stockActual[CANTTALLES];
	int ventasPorTalle[CANTTALLES];
};

//protipos
bool validarCodigo(int,Calzado[],int);
bool validarTalle(int);
void inicializarCalzados(Calzado[],int);
void cargarDatosCalzados(Calzado[],int);
void procesarVentas(Calzado[],int);
void informarStockInicial(Calzado[],int);
void informarStockActual(Calzado[],int);
void informarRecaudacion(Calzado[],int);
int sumaFila(int[],int);
int sumaColumna(Calzado[],int,int);
void maximoMinimoVentas(int[],int,int&,int&);
void tallesSinVender(Calzado[],int,int[]);

int main(){
	Calzado listaCalzado[CANTCALZADOS];
	int tallesSinVentas[CANTTALLES]={0};
	
	inicializarCalzados(listaCalzado, CANTCALZADOS);
	cargarDatosCalzados(listaCalzado,CANTCALZADOS);
	procesarVentas(listaCalzado,CANTCALZADOS);
	informarStockInicial(listaCalzado,CANTCALZADOS);
	informarStockActual(listaCalzado,CANTCALZADOS);
	informarRecaudacion(listaCalzado,CANTCALZADOS);
	
	tallesSinVender(listaCalzado,CANTCALZADOS,tallesSinVentas);
	
	cout<<"talles sin ventas ";
	for(int i=0; i<CANTTALLES;i++){
		if(tallesSinVentas[i] == 0){
			cout<< (i +37) << " ";
		}
	}
	
	int maxVentaTalle,minVentaTalle;
	int ventasPorTalle[CANTTALLES]={0};
	for(int i=0;i<CANTTALLES;i++){
		ventasPorTalle[i]=sumaColumna(listaCalzado,CANTCALZADOS,i);
	}
	maximoMinimoVentas(ventasPorTalle,CANTTALLES,maxVentaTalle,minVentaTalle);
	
	cout<<"talle con mas venta: "<<endl;
	cout<<"talle con menos ventas: "<<endl;
	
	return 0;
}

bool validarCodigo(int codigo,Calzado lista[],int cant){
	for(int i=0;i<cant;i++){
		if(lista[i].codCalzado == codigo){
			return true;
		}
	}
	return false;
}

bool validarTalle(int talle){
	return(talle>=37 && talle<=42);
}

void inicializarCalzados(Calzado lista[], int cant) {
    for (int i = 0; i < cant; i++) {
        lista[i].codCalzado = 0;
        lista[i].tipoCalzado = '0';
        lista[i].precioUnitario = 0.0;
        
        for (int j = 0; j < CANTTALLES; j++) {
            lista[i].stockInicial[j] = 0;
            lista[i].stockActual[j] = 0;
            lista[i].ventasPorTalle[j] = 0;
        }
    }
}

void cargarDatosCalzados(Calzado lista[],int cant){
	for(int i=0;i<cant;i++){
		cout<<"ingrese codigo del calzado (1000 - 2500): ";
		cin>>lista[i].codCalzado;
		while(lista[i].codCalzado<1000 || lista[i].codCalzado>2500){
			cout<<"codigo invalido vuelva ingresarlo ";
			cin >>lista[i].codCalzado;
		}		
		cout<<"ingrese tipo de calzado (R,T,N,C) ";
		cin>>lista[i].tipoCalzado;
		while (lista[i].tipoCalzado != 'R' && lista[i].tipoCalzado != 'T' && lista[i].tipoCalzado != 'N' && lista[i].tipoCalzado != 'C') {
            cout << "Tipo inválido. Reingrese: ";
            cin >> lista[i].tipoCalzado;
        }
		cout<<"ingrese precio unitario: ";
		cin>> lista[i].precioUnitario;
		while(lista[i].precioUnitario<= 0){
			cout<<"precio invalido ";
			cin>>lista[i].precioUnitario;
		}
		for(int j=0;j<CANTTALLES;j++){
			cout<<"ingrese stock inicial para talle ";
			cin>>lista[i].stockInicial[j];
			while(lista[i].stockInicial[j]<0){
				cout<<"stock invalido vuelva intetarlo ";
				cin>>lista[i].stockInicial[j];
			}
			lista[i].stockActual[j]=lista[i].stockInicial[j];
			lista[i].ventasPorTalle[j]=0;
		}
	}
}

void procesarVentas(Calzado lista[],int cant){
	int masVentas;
	do{
		int codigo,talle;
		cout<<"ingrese codigo del calzado vendido: ";
		cin>>codigo;
		while(!validarCodigo(codigo,lista,cant)){
			cout<<"codigo invalido intentelo nuemente";
			cin>>codigo;
		}
		cout<<"ingrese talle vendido: ";
		cin >> talle;
		while(!validarTalle(talle)){
			cout<<"talle invalido intentelo nuevaente";
			cin>>talle;
		}
		for(int i=0;i<cant;i++){
			if(lista[i].codCalzado == codigo){
				int iTalle=talle - 37;
				if(lista[i].stockActual[iTalle]>0){
					lista[i].stockActual[iTalle]--;
					lista[i].ventasPorTalle[iTalle]++;
				}else{
					cout<<"no hay stock disponible para este talle ";
				}
				break;
			}	
		}
		cout<<"hay mas ventas para cargar? (si:1 / no:0 ";
		cin>>masVentas;	
	}while(masVentas == 1);	
}

void informarStockInicial(Calzado lista[],int cant){
	cout<<"stock inicial de cada calzado ;";
	for(int i=0;i<cant;i++){
		cout<<"codigo: " << lista[i].codCalzado << " tipo "<<lista[i].tipoCalzado <<"precio "<<lista[i].precioUnitario<<endl;
		for(int j=0;j<CANTTALLES;j++){
			cout<<"talle "<< j << " :" << lista[i].stockInicial[j]<<endl;
		}
	}
}

void informarStockActual(Calzado lista[],int cant){
	cout<<"stock actual de cada calzado; ";
	for(int i=0;i<cant;i++){
		cout<<"codigo " << lista[i].codCalzado<<" tipo "<<lista[i].tipoCalzado<<endl;
		for(int j=0;j<CANTTALLES;j++){
			cout<<" talle " << j << " : " << lista[i].stockActual[j]<<endl;
		}
	}	
}

void informarRecaudacion(Calzado lista[],int cant){
	cout<<"recaudacion por calzado ";
	for(int i=0;i<cant;i++){
		float total=0;
		for(int j=0;j<CANTTALLES;j++){
			total += lista[i].ventasPorTalle[j] * lista[i].precioUnitario;
		}
		cout<<"codigo " <<lista[i].codCalzado << " Recaudacion: " << total << endl;
	}
}

int sumaFila(int fila[],int tam){
	int suma=0;
	for(int i=0;i<tam;i++){
		suma += fila[i];
	}
	return suma;
}

int sumaColumna(Calzado lista[],int cant,int columna){
	int suma=0;
	for(int i=0;i<cant;i++){
		suma += lista[i].ventasPorTalle[columna]; 
	}
	return suma;
}

void maximoMinimoVentas(int ventas[],int tam, int &max,int &min){
	max=0;
	min=0;
	for(int i=1;i<tam;i++){
		if(ventas[i] > ventas[max]){
		max=i;	
		} 
		if(ventas[i] < ventas[min]){
		min=i;	
		} 
	}	
}

void tallesSinVender(Calzado lista[],int cant, int resultado[]){
	for(int j=0;j<CANTTALLES;j++){
		resultado[j]=0;
		for(int i=0; i<cant;i++){
			if(lista[i].ventasPorTalle[j]>0){
				resultado[j]=1;
				break;
			}
		}
	}
}












