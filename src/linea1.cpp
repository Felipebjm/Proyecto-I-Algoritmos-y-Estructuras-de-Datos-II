#include <iostream>

void bucleStack(int contador) {
    if (contador == 6)
    {
        return;
    }
    int array[5] = {1,2,3,4,5};
    std::cout << "Stack: Posicion array " << contador << ": " << &array[0] << '\n';
    contador++;
    bucleStack(contador);
    return;
}

void bucleHeap (int contador) {
        if (contador == 6)
    {
        return;
    }
    int* array = new int[5];
    for (int i = 0; i<5; i++)
    {
        array[i] = i;
    }
    std::cout << "Heap: Posicion array " << contador << ": " << &array[0] << '\n';
    contador++;
    bucleHeap(contador);
    delete[] array;
    return;
}


int main() {
    bucleStack(1);
    bucleHeap(1);
    return 0;
}
