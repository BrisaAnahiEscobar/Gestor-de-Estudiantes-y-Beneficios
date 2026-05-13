//Grupo 8 - Consumidor de Beneficios

#include <iostream>
#include <cstring>
using namespace std;

struct Estudiante //Definimos ambos struct usados en los otros dos modulos
{
    char mail[100];
    char clave[100];
    int creditos;
};

struct Beneficio 
{
    char nombre[50];
    float creditos;
};

int elegirEstudiante(const char* clave, const char* mail);
int mostrarBeneficios(int creditos);
int restarBeneficio(const char* beneficioelegido);
void editarPuntosEstudiante(int puntosParaRestar, const char* estudiantebuscado);

int main() {
    Estudiante estudiante;
    char beneficioelegido[50];

    cout << "Ingrese su mail: " << endl;    //Le pedimos al usuario que ingrese su mail y su clave
    cin >> estudiante.mail;

    cout << "Ingrese su clave: " << endl;
    cin >> estudiante.clave;

    int cantidaddepuntos = elegirEstudiante(estudiante.clave, estudiante.mail); //Llamamos a la funcion para obtener la cantidad de puntos (si existe el usuario)

    if (cantidaddepuntos<0) //Si la funcion devuelve un -1, significa que no se encontro el usuario
    {
        cout<<"Los datos de inicio de sesion no son validos"<<endl;
    }
    else    //Si obtenemos el usuario y los puntos, mostramos por pantalla los puntos y los benefecios disponibles
    {
        mostrarBeneficios(cantidaddepuntos);

        cout << "Elija un beneficio disponible: " << endl;  //Le pedimos al usuario que ingrese el beneficio deseado
        cin >> beneficioelegido;

        int puntosgastados = restarBeneficio(beneficioelegido); //Obtenemos los puntos restantes
        editarPuntosEstudiante(puntosgastados, estudiante.mail);
    }

    return 0;
}

int elegirEstudiante(const char* clave, const char* mail) {
    FILE* archivo = fopen("Registro.dat", "rb");    //Abrimos el archivo para lectura
    if (archivo != NULL) 
    {
        Estudiante estudiante;
        while (fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1) //Leemos todo el archivo
        {
            if (strcmp(estudiante.mail, mail) == 0 && strcmp(estudiante.clave, clave) == 0) //Si coincide el mail y la clave, mostramos los puntos
            {
                cout << "Estudiante encontrado:" << endl;
                cout << "Cantidad de puntos: " << estudiante.creditos << endl;
                int cantidaddepuntos = estudiante.creditos;
                fclose(archivo);
                return cantidaddepuntos;    //Retornamos los puntos del estudiantes
            }
        }
        fclose(archivo);
    } 
    else
    {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    return -1;  //Si no encontramos el usuario, devolvemos un -1 para indicarlo
}

int mostrarBeneficios(int creditos) 
{
    FILE* archivo = fopen("Beneficios.dat", "rb");  //Abrimos el archivo para lectura
    if (archivo != NULL) 
    {
        cout << "Beneficios disponibles: " << endl;
        Beneficio beneficio;
        while (fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1)   //Recorremos todo el archivo
        {
            if (creditos >= beneficio.creditos) //Mostramos solo los beneficios que el usuario puede pagar
            {
                cout << beneficio.nombre << " - Costo: " << beneficio.creditos << endl;
            }
        }
        fclose(archivo);
    } 
    else 
    {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    return 0;
}

int restarBeneficio(const char* beneficioelegido) 
{
    int puntosgastados = 0;
    FILE* archivo = fopen("Beneficios.dat", "rb");  //Abrimos el archivo para lectura
    if (archivo != NULL) 
    {
        Beneficio beneficio;
        bool encontrado = false;
        while (fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1)   //Leemos todo el archivo hasta encontrar el archivo buscado
        {
            if (strcmp(beneficioelegido, beneficio.nombre) == 0)    //Si coincide, lo mostramos por pantalla y guardamos los puntos gastados en una variable
            {
                puntosgastados = beneficio.creditos;
                cout << "Beneficio elegido correctamente" << endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) 
        {
            cout << "Beneficio no encontrado" << endl;
        }
        fclose(archivo);
    }
    else 
    {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    return puntosgastados;  //Retornamos los puntos gastados
}

void editarPuntosEstudiante(int puntosParaRestar, const char* estudiantebuscado) {
    FILE* archivo = fopen("Registro.dat", "rb+");   //Abrimos el archivo para lectura y escritura
    if (archivo != NULL) {
        Estudiante estudiante;
        bool encontrado = false;
        while (!encontrado && fread(&estudiante, sizeof(Estudiante), 1, archivo) == 1)  //Leemos todo el archivo hasta encontrar el mail
        { //Cuando encontramos el estudiante, lo marcamos como tal y restamos los puntos
            if (strcmp(estudiante.mail, estudiantebuscado) == 0 && estudiante.creditos >= puntosParaRestar)
            {
                encontrado = true;
                estudiante.creditos -= puntosParaRestar;
                fseek(archivo, -sizeof(Estudiante), SEEK_CUR);  //Debemos volver hacia adelante para sobreescribir los puntos
                fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
                cout << "Puntos actualizados exitosamente (" << (estudiante.creditos)<< ")" << endl;
            }
        }
        if (!encontrado) 
        {
            cout << "No se encontro un estudiante con ese correo / no se pudo pagar el beneficio" << endl;
        }
        fclose(archivo);
    }
    else 
    {
        cout << "No se pudo abrir el archivo para lectura y escritura." << endl;
    }
}