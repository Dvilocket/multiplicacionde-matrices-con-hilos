

import random

def multiplicacion(matriz1,matriz2):
    matriz_nueva = []
    for fila in matriz1:
        matriz_nueva.append(proceso(fila,matriz2))
    
    print(matriz_nueva)

    del matriz_nueva

def proceso(fila,matriz2):
    resultado = 0
    lista = []
    for columna in range(len(matriz2[0])):
        for n,i in enumerate(fila):
            resultado += (i*matriz2[n][columna])

        lista.append(resultado)
        resultado = 0

    return lista

def crear_matriz(fila,columna):
    matriz = []
    for i in range(fila):
        c = [random.randint(-50,50) for x in range(columna)]
        matriz.append(c)
    return matriz
    
if __name__ == '__main__':
    matriz_1 = [
        [5,3,-4,-2],
        [8,-1,0,-3]
    ]
    matriz_2 = [
        [1,4,0],
        [-5,3,7],
        [0,-9,5],
        [5,1,4]
    ]
    try:
        multiplicacion(matriz_1,matriz_2)
    except:
        print("Error!!")


    #Parametrizable

    try:
        fila_1,columna_1 = int(input("Fila(1):")), int(input("Columna(1):"))
        fila_2,columna_2 = int(input("Fila(2):")), int(input("Columna(2):"))

        matriz_1 = crear_matriz(fila_1,columna_1)

        matriz_2 = crear_matriz(fila_2,columna_2)

        print("Matrices Generadas:")
        print(matriz_1)
        print(matriz_2)

        multiplicacion(matriz_1,matriz_2)
    
    except:
        print("Error")