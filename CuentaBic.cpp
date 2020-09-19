#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
using namespace std;

struct Tarjeta {
	char CuentaID[10];
	int FechaCreacion;
	bool Activa;
	int Saldo;
	int NroCliente;
};
struct Movimiento {
	int MovimientoID;
	int FechaHora;
	int Monto;
	int CuentaID;
};

void ListarUsuarios(); 
void AgregarUsuario();
int EliminarUsuario(char Cuenta[]);
int BuscarUsuario(char Cuenta[]);
int  main () {
	FILE*archivo;
	int opcion = 0;
	while(opcion!=6) {
	cout<<" 1 - Listado de usuarios "<< endl;
	cout<<" 2 - Agregar un nuevo usuario "<< endl;
	cout<<" 3 - Eliminar una cuenta (por id) "<< endl;
	cout<<" 4 - Buscar por id de la cuenta y mostrar "<< endl;
	cout<<" 5 - Listar cuentas activas por saldo descendente "<< endl;
	cout<<" 6 - Salir y guardar cambios "<< endl;
	cout<<" Elija una opcion: "<< endl;
	cin >>opcion;
	char cuentaBuscada[10];
	switch (opcion){
		case 1:
			 ListarUsuarios();
			break;
		case 2:	
			AgregarUsuario();
			break;
		case 3:
			cout<<"Ingrese el numero de Cuenta que desea borrar: "<<endl;
			cin>>cuentaBuscada;
			EliminarUsuario(cuentaBuscada);
			break;
		case 4:
			cout<<"Ingrese el numero de Cuenta que desea buscar: "<<endl;
			cin>>cuentaBuscada;
			BuscarUsuario(cuentaBuscada);
			break;
		case 5:	
			break;
		case 6:
			break;
		default:
			break;		
	}
	cout <<" ----------- "<< endl;
	}
	fclose (archivo);
	return 0;
}
int cantidad(){
FILE* archivo; 
archivo=fopen("Cuentas.BIC","rb");
Tarjeta t;
int cant=0;
while(fread(&t,sizeof(Tarjeta),1,archivo)){
cant++;
}
fclose(archivo);
return cant;
}

void ordenar(){
FILE* archivo;
archivo=fopen("Cuentas.BIC","rb");
Tarjeta t;
Tarjeta array[cantidad()];
int c=0;
while(fread(&t,sizeof(Tarjeta),1,archivo)){
array[c].Activa=t.Activa;
array[c].FechaCreacion=t.FechaCreacion;
array[c].NroCliente=t.NroCliente;
array[c].Saldo=t.Saldo;
array[c].TarjetaID=t.TarjetaID;
c++;
}

fclose(archivo);

Tarjeta aux;

for(int i=0;i<cantidad();i++){
for(int j=0;j<cantidad()-1;j++){
if(array[j].Saldo>array[j+1].Saldo){
aux.Saldo=array[j].Saldo;
aux.Activa=array[j].Activa;
aux.FechaCreacion=array[j].FechaCreacion;
aux.NroCliente=array[j].NroCliente;
aux.TarjetaID=array[j].TarjetaID;
array[j].Saldo=array[j+1].Saldo;
array[j].FechaCreacion=array[j+1].FechaCreacion;
array[j].NroCliente=array[j+1].NroCliente;
array[j].Activa=array[j+1].Activa;
array[j].TarjetaID=array[j+1].TarjetaID;
array[j+1].Saldo=aux.Saldo;
array[j+1].Activa=aux.Activa;
array[j+1].FechaCreacion=aux.FechaCreacion;
array[j+1].NroCliente=aux.NroCliente;
array[j+1].TarjetaID=aux.TarjetaID;

}
}
}

FILE* arch;
arch=fopen("a.dat","ab");
Tarjeta au;
for(int f=0;f<cantidad();f++){
        au.Activa=array[f].Activa;
        au.FechaCreacion=array[f].FechaCreacion;
        au.NroCliente=array[f].NroCliente;
        au.Saldo=array[f].Saldo;
        au.TarjetaID=array[f].TarjetaID;
    fwrite(&au,sizeof(Tarjeta),1,arch);
}
fclose(arch);
remove("Cuentas.BIC");
rename("a.dat","Cuentas.BIC");
}

void ListarUsuarios () {
        ordenar();
	FILE*archivo;
	archivo=fopen("Cuentas.BIC","rb");
	Tarjeta t;

	while(fread(&t,sizeof(Tarjeta),1,archivo)){
		cout<<"Numero de Cuenta: "<<t.CuentaID<<endl;
		cout<<"Fecha de creacion: "<<t.FechaCreacion<<endl;
	if(t.Activa){
		 cout<<"Cuenta Activa: Si"<<endl;
	}else{
		cout<<"Cuenta Activa: No"<<endl;
	}
		cout<<"El saldo de la tarjeta es: "<<t.Saldo<<endl;
		cout<<"El numero de cliente es: "<<t.NroCliente<<endl;
		cout<<"-------------------------------"<<endl;
	}
		fclose(archivo);
	} 

void AgregarUsuario(){

	FILE*archivo;
	archivo=fopen("Cuentas.BIC","ab");
	Tarjeta t;
	cout<<"Ingrese el numero de la tarjeta:"<<endl;
	cin>>t.CuentaID;
	cout<<"Ingrese su Fecha de Creacion:"<<endl;
	cin>>t.FechaCreacion;
	cout<<"Ingrese estado de la tarjeta: (True=Activa o 1 o False=Desactivada o 0)"<<endl;
	cin>>t.Activa;
	cout<<"Ingrese el saldo de la cuenta:"<<endl;
	cin>>t.Saldo;
	cout<<"Ingrese el numero de cliente:"<<endl;
	cin>>t.NroCliente;
	fwrite(&t,sizeof(Tarjeta),1,archivo);
	fclose(archivo);
}

int EliminarUsuario(char Cuenta[]){
	FILE*archivo;
	int encontrado = 0;
	Tarjeta t;
	if(archivo = fopen("Cuentas.BIC","rb+")){
		while(!encontrado && fread(&t,sizeof(Tarjeta),1,archivo)){
			if(strcmp(Cuenta,t.CuentaID)==0){
				encontrado=1;
				t.Activa=false;
				fseek(archivo,sizeof(Tarjeta),SEEK_CUR);
				fwrite(&t,sizeof(Tarjeta),1,archivo);
			}
		}
		if(!encontrado){
			cout << "No se encontro la persona a borrar." << endl;
		}
		fclose(archivo);
    	return 1;
	}
	return 0;
}

int BuscarUsuario(char Cuenta[]){
	FILE*archivo;
	int encontrado = 0;
	Tarjeta t;
	if(archivo = fopen("Cuentas.BIC","rb+")){
		while(!encontrado && fread(&t,sizeof(Tarjeta),1,archivo)){
			if(strcmp(Cuenta,t.CuentaID)==0){
				encontrado = 1;
                cout << "****** Datos de la cuenta *******" << endl;
                cout << "CuentaID: " << t.CuentaID << endl;
                cout << "Fecha de Creacion: " << t.FechaCreacion << endl;
                cout << "Saldo: " << t.Saldo << endl;
                cout << "Nro de Cliente: " << t.NroCliente << endl;
                if(t.Activa){
                	cout << "Activa: Si"<< endl;
				}else{
					cout << "Activa: No"<< endl;
				}
				fwrite(&t,sizeof(Tarjeta),1,archivo);
			}
		}
		if(!encontrado){
			cout << "No se encontro la persona a borrar." << endl;
		}
		fclose(archivo);
    	return 1;
	}
	return 0;
}

void SoloActivos(){
FILE* archivo;
archivo=fopen("Cuentas.BIC","rb");
Tarjeta t;
Tarjeta areglo[cantidad()];
int u=0;
while(fread(&t,sizeof(Tarjeta),1,archivo)){
areglo[u].Activa=t.Activa;
areglo[u].FechaCreacion=t.FechaCreacion;
areglo[u].NroCliente=t.NroCliente;
areglo[u].Saldo=t.Saldo;
areglo[u].TarjetaID=t.TarjetaID;
u++;
}
fclose(archivo);
FILE* copia;
copia=fopen("copia.dat","ab");

Tarjeta c;

for(int r=0;r<cantidad();r++){
if(areglo[r].Activa){
c.Activa=areglo[r].Activa;
c.FechaCreacion=areglo[r].FechaCreacion;
c.NroCliente=areglo[r].NroCliente;
c.Saldo=areglo[r].Saldo;
c.TarjetaID=areglo[r].TarjetaID;
fwrite(&c,sizeof(Tarjeta),1,copia);
}
}
fclose(copia);

remove("Cuentas.BIC");
rename("copia.dat","Cuentas.BIC");



}


void CargarMovimiento(){
FILE* mov;
mov=fopen("procesados.BIC","ab");
Movimiento m;
cout<<"Ingrese el numero de movimiento:"<<endl;
cin>>m.MovimientoID;
cout<<"Ingrese la Fecha y Hora : (AAAAMMDDHH:MM)"<<endl;
cin>>m.FechaHora;
cout<<"Ingrese el monto:"<<endl;
cin>>m.Monto;
cout<<"Ingrese el numero de cuenta:"<<endl;
cin>>m.CuentaID;

fwrite(&m,sizeof(Movimiento),1,mov);
fclose(mov);
}


void LeerMovimientos(){
FILE* mov;
mov=fopen("procesados.BIC","rb");
Movimiento m;
 while(fread(&m,sizeof(Movimiento),1,mov)){
cout<<"-------------------------------"<<endl;
cout<<"El ID del movimiento es:"<<endl;
cout<<m.MovimientoID<<endl;
cout<<"La fecha y hora es:"<<endl;
cout<<m.FechaHora<<endl;
cout<<"El monto es:"<<endl;
cout<<m.Monto<<endl;
cout<<"El ID de la cuenta es:"<<endl;
cout<<m.CuentaID<<endl;
cout<<"-------------------------------"<<endl;
}
fclose(mov);
}
