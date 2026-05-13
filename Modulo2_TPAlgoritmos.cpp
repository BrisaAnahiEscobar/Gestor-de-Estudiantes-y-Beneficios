//Grupo 8 - Gestor de Beneficios

#include <iostream>
#include <cstring>
using namespace std;

void seleccionDeOperacion();
void mostrarBeneficios();
void modificarCosto();
void agregarMasBeneficios();
void eliminarBeneficio();

struct beneficio    //Definimos el struct, solo necesitamos nombre y creditos
{
    char nombre[50];
    float creditos;
};

int main()
{
    seleccionDeOperacion();
    return 0;
}

void seleccionDeOperacion()
{
    int selector;
    while(selector!=5)  //Se repite hasta que el usuario decida finalizar el programa
    {
        cout<<"Seleccione la tarea a realizar:"<<endl<<"(1)Mostrar la lista de beneficios"<<endl;
        cout<<"(2)Modificar costo de un beneficio"<<endl<<"(3)Agregar mas beneficios"<<endl;
        cout<<"(4)Eliminar un beneficio"<<endl<<"(5)Finalizar el programa"<<endl;
        cin>>selector;
        system("cls");
        switch(selector)    //Elegimos entre las 5 opciones, si no es valida se muestra por pantalla
        {
            case 1:
                cout<<"Selecciono <Mostrar la lista de beneficios>"<<endl;
                mostrarBeneficios();    //Llamamos a la funcion que muestra los beneficios
                break;
            case 2:
                cout<<"Selecciono <Modificar costo de un beneficio>"<<endl;
                modificarCosto();   //Llamamos a la funcion para modificar el nombre de un beneficio
                break;
            case 3:
                cout<<"Selecciono <Agregar mas beneficios>"<<endl;
                agregarMasBeneficios(); //Llamamos a la funcion para agregar un beneficio
                break;
            case 4:
                cout<<"Selecciono <Eliminar un beneficio>"<<endl;
                eliminarBeneficio();    //Llamamos a la funcion que elimina un beneficio
                break;
            case 5:
                cout<<"Selecciono <Final del programa>"<<endl;
                break;
            default:
                cout<<"Seleccion no valida";
                break; 
        }
        cout<<endl<<endl;
    }
}

void mostrarBeneficios()
{
    int i=1;
    beneficio b;
    FILE* archivo = fopen("Beneficios.dat", "rb");   //Abrimos el archivo solo para lectura, si no existe no se lee nada
    if (archivo != NULL)
    {
        while (fread(&b, sizeof(b), 1, archivo) == 1)   //Leemos hasta el final mostrando el nombre de cada beneficio y su costo
        {
            cout<<endl<<"Beneficio numero "<<i<<":"<<endl;
            cout<<"Nombre: "<< b.nombre<<endl;
            cout<<"Costo: "<< b.creditos<<" creditos"<<endl;
            i++;
        }
        fclose(archivo);
    }
    else
    {
        cout<<"No se encuentra el archivo / no se puede abrir";
    }
}

void modificarCosto()
{
    char buscar[50];
    int encontrado=0;
    beneficio b;
    FILE *archivo = fopen("Beneficios.dat","rb+");   //Abrimos el archivo para leer y escribir, solo si existe
     if(archivo != NULL)
    {
        cout<<"Ingrese el nombre del beneficio a modificar: "; 
        cin>>buscar;
        while(!encontrado && fread(&b,sizeof(b),1,archivo)==1)  //Leemos hasta el final o hasta encontrarlo
        {
            if(strcmp(buscar,b.nombre)==0)  //Si un beneficio coincide con el buscado, lo marcamos como encontrado
            {
                encontrado=1;
                cout<<"Ingrese el nuevo precio: ";
                cin>>b.creditos;
                fseek(archivo,-sizeof(b),SEEK_CUR); //Debemos volver hacia adelante para sobreescribir el precio
                fwrite(&b,sizeof(b),1,archivo);
                cout<<"El nuevo costo de "<<b.nombre<<" es "<<b.creditos<<" creditos"<<endl;
            }
        }
        if(!encontrado)
        {
            cout<<"El beneficio no fue encontrado"<<endl;
        }
        fclose(archivo);
    }
    else
    {
        cout<<"No se encuentra el archivo / no se puede abrir";
    }
}

void agregarMasBeneficios()
{
    FILE *archivo = fopen("Beneficios.dat","ab+");   //Abrimos el archivo, y si no existe se lo crea
    if(archivo != NULL)
    {
        beneficio b;    //Rellenamos ambos campos y lo subimos al archivo
        cout<<"Ingrese el nuevo beneficio: ";
        cin>>b.nombre;
        cout<<"Ingrese la cantidad de creditos: ";
        cin>>b.creditos;
        fwrite(&b, sizeof(b), 1, archivo);
        fclose(archivo);
        cout<<"Se agrego el beneficio "<<b.nombre<<" con un costo de "<<b.creditos<<" creditos"<<endl;
    }
    else
    {
        cout<<"No se encuentra el archivo / no se puede abrir";
    }
}

void eliminarBeneficio()
{
    int encontrado=0;
    FILE *aux = fopen("Auxiliar.dat","wb+");    //Creamos un archivo auxiliar para guardar los archivos que NO se eliminan
    FILE *archivo = fopen("Beneficios.dat","rb+");   //Abrimos el archivo para lectura y escritura, si no existe no se hace nada
     if(archivo != NULL)
    {
        if(aux != NULL)
        {
            char eliminar[50];
            cout<<"Ingrese el nombre del beneficio a eliminar: ";   //Ingresamos el archivo que buscamos eliminar
            cin>>eliminar;
            beneficio b;
            while (fread(&b, sizeof(b), 1, archivo) == 1)   //Se lee todo el archivo
            {
                if(strcmp(b.nombre,eliminar)!=0)    //Todos los archivos que no sean el buscado se transcriben en el auxiliar
                {
                    fwrite(&b,sizeof(b),1,aux);
                }
                else    //Si se encuentra lo marcamos como tal
                {
                    encontrado=1;
                }
            }
            fclose(archivo);
            if (encontrado==1)  //Si se encontro el beneficio, debemos reescribir nuestro archivo
            {
                fseek(aux,0,SEEK_SET);  //Volvemos al principio del auxiliar
                archivo = fopen("Beneficios.dat","wb+"); //Sobreescribimos el archivo ya existente para transcribir
                while(fread(&b,sizeof(b),1,aux)==1) //Leemos el auxiliar hasta el final y escribimos todo en nuestro archivo principal
                {
                    fwrite(&b,sizeof(b),1,archivo);
                }
                fclose(aux);
                fclose(archivo);
                cout<<"El beneficio "<<eliminar<<" fue eliminado"<<endl;
            }
            else    //Si no se encontro, solo se avisa por pantalla que no se encontro
            {
                cout<<"Ese beneficio no existe"<<endl;
            }
        }
        else
        {
            cout<<"No se pudo realizar la tarea"<<endl;
        }
    }
    else
    {
        cout<<"No se encuentra el archivo / no se puede abrir";
    }
}