import pdb

def cholesky(matriz):
    #calculamos la len de la matriz
    alto = len(matriz[0])
    ancho = len(matriz)
    if ancho!=alto:
        return None
    #definimos las variables necearias
    l = [None] * alto
    d = [None] * alto
    u = [None] * alto
    for i in range(ancho):
        l[i] = [None] * ancho
        u[i] = [None] * ancho
        
    l[0][0] = 0
    u[0][0] = 0
    d[0] = matriz[0][0]
    #bucle grande
    for k in range(ancho):
        if k == 0:
            continue
        #pdb.set_trace()

        #buble u
        for i in range(k):
            suma = 0
            for j in range(i):
                suma += l[i][j] * u[j][k]
            u[i][k] = (matriz[i][k] - suma)/ d[i]
            print("u[{}][{}] = {}".format(i,k,u[i][k]))

        #buble l
        for i in range(k):
            suma = 0
            for j in range(i):
                suma += u[j][i] * l[k][j]
            l[k][i] = (matriz[k][i] - suma)/ d[i]
            print("l[{}][{}] = {}".format(k,i,l[k][i]))

        #siguiente elementos
        l[k][k] = 1
        u[k][k] = 1
        suma = 0
        for j in range(k):
            suma += l[k][j] * d[j] * u[j][k]
        d[k] = matriz[k][k] - suma
        print ('d[{}]->{}'.format(k, d[k]))

    #return una nueva matriz
    newMatriz = [None] * alto
    for i in range(alto):
        newMatriz[i] = [None] * ancho
    #copiamos los valors en la nueva matriz
    print("L----------")
    impMatrix(l)
    for i in range(alto):
        for j in range(ancho):
            if i < j:
                newMatriz[i][j] = u[i][j]
            elif i == j:
                newMatriz[i][j] = d[i]
            else:
                newMatriz[i][j] = l[i][j]

    return newMatriz

def impMatrix(matriz):
    s = [[str(e) for e in row] for row in matriz]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = '\t'.join('{{:{}}}'.format(x) for x in lens)
    table = [fmt.format(*row) for row in s]
    print ('\n'.join(table))


def main():
    #creamos la matriz de testeo
    matriz = [None] * 3
    for i in range(3):
        matriz[i] = [None] * 3

    #guardamos valores de prueba en la matriz
    matriz[0][0] = 1
    matriz[0][1] = -0.6875
    matriz[0][2] = 0
    matriz[1][0] = -0.3125
    matriz[1][1] = 1
    matriz[1][2] = -0.6875
    matriz[2][0] = 0
    matriz[2][1] = -0.3125
    matriz[2][2] = 1

    #imprimimos la matriz
    impMatrix(matriz)
    #factorizamos
    newMatriz = cholesky(matriz)
    #imprimimos resultados
    print('')
    impMatrix(newMatriz)

if __name__ == "__main__":
    main()
