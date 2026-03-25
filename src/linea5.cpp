#include <iostream>
using namespace std;

int* funcionHeap()
{
    int* p = new int(50);
    cout << "En el Heap el valor " << *p
         << " tiene la direccion " << p << endl;
    return p;
}

int* funcionStack()
{
    int x = 50;
    cout << "En el Stack, x = " << x
         << " con direccion " << &x << endl;
    return &x;
}

void otraFuncion()
{
    int y = 66;
    cout << "En otra funcion, y = " << y
         << " (tambien en el stack) con direccion " << &y << endl;
}

int main()
{
    int* pHeap = funcionHeap();
    cout << "En main, el puntero Heap apunta a " << pHeap << endl;
    cout << "En main, al leer el puntero Heap sale " << *pHeap << endl;
    otraFuncion();
    cout << "Despues de ejecutar la otra funcion, al leer el puntero Heap sale " << *pHeap << endl;

    delete pHeap;
    cout << "Despues de liberar el Heap, el puntero Heap apunta a " << pHeap << endl;
    cout << "Despues de liberar el Heap, al leer el puntero Heap sale " << *pHeap << endl;

    pHeap = NULL;
    cout << "Despues de poner el puntero Heap en NULL, queda en " << pHeap << endl;

    cout << endl;

    int* pStack = funcionStack();
    cout << "En main, el puntero Stack apunta a " << pStack << endl;

    otraFuncion();

    if (pStack != NULL)
    {
        cout << "Se intenta leer el puntero Stack: "
             << *pStack << endl;
    }
    else
    {
        cout << "En esta ejecucion, el puntero Stack llega en NULL porque la variable local ya no existe fuera de la funcion" << endl;
    }

    return 0;
}