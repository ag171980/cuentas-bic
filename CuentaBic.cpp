#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
using namespace std;

struct Tarjeta {
	int  CuentaID;
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

void Menu(int opcion);
void LeerTarjetas();
void AgregarTarjetas();
void EliminarUsuario();
void BuscarUsuario();
void ListadoTarjetasAct();
void CargarMovimiento();
void LeerMovimientos();
int cantidad();
int CantidadMov();
void Actualizacion();
void SoloActivos();

int  main () {
	int opcion;
	Menu(opcion);
	return 0;
	}


void Menu(int opcion){

    cout<<"Menu"<<endl;
	cout<<"----------------------------------------------"<<endl;
	cout<<"Opcion 1: Ingresar una tarjeta"<< endl;
	cout<<"Opcion 2: Muestra las tarjetas ingresadas"<< endl;
	cout<<"Opcion 3: Eliminar una cuenta (por id) "<< endl;
	cout<<"Opcion 4: Buscar por id de la cuenta y mostrar "<< endl;
	cout<<"Opcion 5: Listado de las cuentas activas por saldo descendente"<< endl;
	cout<<"Opcion 6: Ingresar un movimiento"<<endl;
	cout<<"Opcion 7: Muestra los movimientos ingresados"<<endl;
	cout<<"Opcion 8: Actualizacion de las cuentas"<<endl;
	//cout<<" 6 - Salir y guardar cambios "<< endl;
    cout<<endl;
    cout<<" Elija una opcion: "<< endl;
	cin >>opcion;
	cout<<endl;




	switch (opcion){
		case 1:
			AgregarTarjetas();
			Menu(opcion);
			break;
		case 2:
			LeerTarjetas();
			Menu(opcion);
			break;
		case 3:
			EliminarUsuario();
			Menu(opcion);
			break;
		case 4:
		   BuscarUsuario();
           Menu(opcion);
			break;
		case 5:
		    ListadoTarjetasAct();
		    Menu(opcion);
			break;
		case 6:
        CargarMovimiento();
         Menu(opcion);
			break;
        case 7:
         LeerMovimientos();
            Menu(opcion);
            break;
        case 8:
            Actualizacion();
            Menu(opcion);
            break;
        case 9:
            SoloActivos();
            break;

}
}



void LeerTarjetas() {
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

void AgregarTarjetas(){
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

void EliminarUsuario(){
	FILE*archivo;
	archivo=fopen("Cuentas.BIC","rb");
	Tarjeta t;
	Tarjeta arr[cantidad()];
  int p=0;
 while(fread(&t,sizeof(Tarjeta),1,archivo)){
   arr[p].Activa=t.Activa;
   arr[p].FechaCreacion=t.FechaCreacion;
   arr[p].NroCliente=t.NroCliente;
   arr[p].Saldo=t.Saldo;
   arr[p].CuentaID=t.CuentaID;
   p++;
}
fclose(archivo);
FILE* otro;
otro=fopen("otro.dat","ab");
Tarjeta k;
int eliminar;

cout<<"Ingrese en numero de cuenta que desea eliminar"<<endl;
cin>>eliminar;

  for(int l=0;l<cantidad();l++){
        if(arr[l].CuentaID!=eliminar){

       k.Activa=arr[l].Activa;
       k.FechaCreacion=arr[l].FechaCreacion;
       k.NroCliente=arr[l].NroCliente;
       k.Saldo=arr[l].Saldo;
       k.CuentaID=arr[l].CuentaID;

    fwrite(&k,sizeof(Tarjeta),1,otro);
            }
            l++;
		}
    fclose(otro);
        remove("Cuentas.BIC");
        rename("otro.dat","Cuentas.BIC");

	}

void BuscarUsuario(){
	FILE*archivo;
	archivo = fopen("Cuentas.BIC","rb");
	Tarjeta t;
	int buscar;
	bool existe=false;
	cout<<"Ingrese el id de la cuenta a buscar:"<<endl;
	cin>>buscar;


		while(fread(&t,sizeof(Tarjeta),1,archivo)){
			if(t.CuentaID==buscar){
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
				existe=true;

			}
		}

        if(!existe){
            cout<<endl;
            cout<<"El usuario no existe"<<endl;
            cout<<endl;
        }

    fclose(archivo);
}



void ListadoTarjetasAct(){
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
array[c].CuentaID=t.CuentaID;
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
aux.CuentaID=array[j].CuentaID;
array[j].Saldo=array[j+1].Saldo;
array[j].FechaCreacion=array[j+1].FechaCreacion;
array[j].NroCliente=array[j+1].NroCliente;
array[j].Activa=array[j+1].Activa;
array[j].CuentaID=array[j+1].CuentaID;
array[j+1].Saldo=aux.Saldo;
array[j+1].Activa=aux.Activa;
array[j+1].FechaCreacion=aux.FechaCreacion;
array[j+1].NroCliente=aux.NroCliente;
array[j+1].CuentaID=aux.CuentaID;

}
}
}

for(int m=0;m<cantidad();m++){
if(array[m].Activa){
    cout<<"Numero de Cuenta: "<<array[m].CuentaID<<endl;
    cout<<"Fecha de creacion: "<<array[m].FechaCreacion<<endl;
	cout<<"Cuenta Activa: Si"<<endl;
    cout<<"El saldo de la tarjeta es: "<<array[m].Saldo<<endl;
    cout<<"El numero de cliente es: "<<array[m].NroCliente<<endl;
    cout<<"-------------------------------"<<endl;
    }
}

}

void CargarMovimiento(){
FILE* mov;
FILE* sol;
sol=fopen("sol.dat","ab"),
mov=fopen("procesados.BIC","ab");
Movimiento m;
Movimiento s;
cout<<"Ingrese el numero de movimiento:"<<endl;
cin>>m.MovimientoID;
cout<<"Ingrese la Fecha y Hora : (AAAAMMDDHH:MM)"<<endl;
cin>>m.FechaHora;
cout<<"Ingrese el monto:"<<endl;
cin>>m.Monto;
s.Monto=m.Monto;
cout<<"Ingrese el numero de cuenta:"<<endl;
cin>>m.CuentaID;
s.CuentaID=m.CuentaID;

fwrite(&s,sizeof(Movimiento),1,sol);
fwrite(&m,sizeof(Movimiento),1,mov);
fclose(mov);
fclose(sol);
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

int CantidadMov(){
FILE* mov;
mov=fopen("procesados.BIC","rb");
Movimiento m;
int cont=0;
while(fread(&m,sizeof(Movimiento),1,mov)){
cont++;
}
fclose(mov);
return cont;
}


void Actualizacion(){

FILE* sol;
sol=fopen("sol.dat","rb");

Movimiento s;
Movimiento cp[CantidadMov()];
int h=0;

while(fread(&s,sizeof(Movimiento),1,sol)){
cp[h].CuentaID=s.CuentaID;
cp[h].Monto=s.Monto;
h++;
}
fclose(sol);
FILE* archivo;
archivo=fopen("Cuentas.BIC","rb");
Tarjeta t;

int suma[cantidad()];
int suna;
int g=0;
while(fread(&t,sizeof(Tarjeta),1,archivo)){

suna=t.Saldo;
for(int a=0;a<CantidadMov();a++){
    if(t.CuentaID==cp[a].CuentaID){
    suna=suna+cp[a].Monto;
   }
}
suma[g]=suna;
g++;
}
fclose(archivo);
FILE* luna;
luna=fopen("luna.dat","ab");
archivo=fopen("Cuentas.BIC","rb");
Tarjeta c;
int x=0;
while(fread(&t,sizeof(Tarjeta),1,archivo)){
c.Activa=t.Activa;
c.CuentaID=t.CuentaID;
c.FechaCreacion=t.FechaCreacion;
c.NroCliente=t.NroCliente;

for(int e=0;e<CantidadMov();e++){
if(t.CuentaID==cp[e].CuentaID){
c.Saldo=suma[x];
}else{
c.Saldo=t.Saldo;
}
}
fwrite(&c,sizeof(Tarjeta),1,luna);
x++;
}
fclose(archivo);
fclose(luna);

remove("Cuentas.BIC");
rename("luna.dat","Cuentas.BIC");

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
areglo[u].CuentaID=t.CuentaID;
u++;
}
fclose(archivo);
FILE* copia;
copia=fopen("copia.dat","ab");

Tarjeta v;

for(int r=0;r<cantidad();r++){
if(areglo[r].Activa){
v.Activa=areglo[r].Activa;
v.FechaCreacion=areglo[r].FechaCreacion;
v.NroCliente=areglo[r].NroCliente;
v.Saldo=areglo[r].Saldo;
v.CuentaID=areglo[r].CuentaID;
fwrite(&v,sizeof(Tarjeta),1,copia);
}
}
fclose(copia);

remove("Cuentas.BIC");
rename("copia.dat","Cuentas.BIC");

}
