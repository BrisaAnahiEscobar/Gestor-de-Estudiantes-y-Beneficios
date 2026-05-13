//Grupo 8 - Gestor de Estudiantes

#include <iostream>
#include <cstring>
using namespace std;

struct usuario  //Definimos el struct, necesitamos el mail, la clave y los creditos
{
    char mail[100];
    char clave[100];
    int creditos;
};

void login();
void mostrarUsuarios();

int main()
{
    int eleccion;
    while(eleccion!=3)  //Se repite hasta que el usuario decida finalizar el programa
    {
        cout<<"Seleccione la tarea a realizar: "<<endl<<"(1)Registrar un nuevo usuario"<<endl<<"(2)Mostrar los usuarios registrados"<<endl;
        cout<<"(3)Finalizar programa"<<endl;
        cin>>eleccion;
        system("cls");
        switch(eleccion)    //Elegimos entre las 3 opciones, si no es valida se muestra por pantalla
        {
            case 1:
                cout<<"Selecciono <Registrar un nuevo usuario>"<<endl;
                login();    //Se llama a la funcion para registrar otro usuario
                break;
            case 2:
                cout<<"Selecciono <Mostrar usuarios registrados>"<<endl;
                mostrarUsuarios();  //Se llama a la funcion para mostrar los usuarios
                break;
            case 3:
                cout<<"Selecciono <Finalizar programa>"<<endl;
                break;
            default:
                cout<<"Seleccion no valida"<<endl;
                break;
        }
        cout<<endl<<endl;
    }
    return 0;
}

void login()
{
    usuario user;
    int flag=0;
    char correo[50];
    FILE *archivo = fopen("Registro.dat","ab+");    //Se abre el archivo, y si no existe se crea
    if(archivo!=NULL)
    {
        cout<<"Ingrese el mail: ";
        cin>>correo;
        while(fread(&user,sizeof(user),1,archivo)==1)   //Se lee hasta el final
        {
            if(strcmp(correo,user.mail)==0) //Si el mail ya esta en uso le avisamos al usuario
            {
                cout<<"El mail ya esta en uso"<<endl;
                flag=1; //Si encontramos el mail entonces no hay que registrarlo de nuevo
            }
        }
        if(flag==0) //Si no se encontro el mail, lo registramos
        {
            strcpy(user.mail,correo);   //Escribimos el correo en el struct, le pedimos la clave
            cout<<"Ingrese la clave: ";
            cin>>user.clave;
            user.creditos=1000; //Le adjudicamos 1000 creditos (por consigna)
            fwrite(&user,sizeof(user),1,archivo);
            
        }
        fclose(archivo);
    }
    else
    {
        cout<<"No se encuentra el archivo / no se puede abrir";
    }
}

void mostrarUsuarios()
{
    int i=1;
    usuario user;
    FILE* archivo = fopen("Registro.dat", "rb");    //Se abre solo para lectura, de no existir no se lee nada
    if (archivo != NULL)
    {
        while (fread(&user, sizeof(user), 1, archivo) == 1) //Se lee hasta el final
        {
            cout<<endl<<"Mail numero "<<i<<": "<<user.mail; //Se muestra solo los mails registrados (las claves no)
            i++;
        }
        fclose(archivo);
    }
    else
    {
        cout<<"No se encuentra el archivo / no se puede abrir";
    }
}