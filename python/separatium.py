import math

def separatium (p, H, Ce, D, X, iteracoes):
  it = 0;
  i = 0
  while i < len(X):
    print(" X[" , i , "]\t", end="");
    j = 0
    while j < len(X[i]):
      print(X[i][j], "|", end="")
      j = j + 1
    print("\n", end="")
    i = i + 1

  print(" ------------------------------------------------");
  i = 0
  while i < len(p):
    print(" p [" , i , "]\t", end="")
    j = 0
    while j < len(p[i]):
      print(p[i][j], "|", end="")
      j = j + 1
    print("\n", end="")
    i = i + 1

  while(it < iteracoes):
    print(" ------------------------------------------------");
    print("         ITERACAO [", it ,"] \n");
    print(" ------------------------------------------------");

    #print(" ------------------------------------------------");
    #i = 0
    #while i < len(H):
    #  print(" H [", i, "]\t", end="")
    #  j = 0
    #  while j < len(H[i]):
    #    print(H[i][j],"|", end="")
    #    j = j + 1
    #  print("\n", end="");
    #  i = i + 1

    print(" ------------------------------------------------");
    print(" CALCULANDO Ce ")
    Probabilidades = len(p)
    Dimensoes = len(X)
    Pontos = 0;
    if(Dimensoes > 0):
      Pontos = len(X[0])
  
    i = 0
    while i < Probabilidades:
      j = 0
      while j < Dimensoes:
        upper = 0.0;
        lower = 0.0;
        k = 0
        while k < Pontos:
          upper += pow(p[i][k], 2.0) * X[j][k];
          lower += pow(p[i][k], 2.0);
          k = k +1
        Ce[j][i] = upper / lower;
        print("Ce[",j,"][",i,"] = ",Ce[j][i]);
        j = j + 1
      i = i + 1 

    print(" ------------------------------------------------");
    print(" CALCULANDO D11 D12 D21 D22 ");

    i = 0
    while i < Probabilidades:
      k = 0
      while k < Pontos:
        soma = 0.0;
        j = 0
        while j < Dimensoes:
          soma += pow(X[j][k] - Ce[j][i], 2.0);
          j = j + 1 

        D[i][k] = math.sqrt(soma);
        print("D[",i,"][",k,"] = ",D[i][k])
        k = k + 1 
      i = i + 1 

    print(" ------------------------------------------------");
    print(" CALCULANDO H11 H12 H21 H22 ");

    i = 0
    while i < Probabilidades:
      k = 0
      while k < Pontos: 
        soma = 0.0;
        i2 = 0
        while i2 < Probabilidades:
          soma += pow(D[i][k] / D[i2][k], 2.0);
          i2 += 1
        H[i][k] = 1.0 / soma;
        print("H[",i,"][",k,"] = ",H[i][k])
        k += 1
      i += 1

    print(" ------------------------------------------------");
    print(" ATUALIZANDO p11 p12 p21 p22 \n")

    i = 0
    while i < Probabilidades:
      k = 0
      while k < Pontos:
        p[i][k] = H[i][k]
        k += 1
      i += 1

    print(" ------------------------------------------------");

    i = 0
    while i < len(p):
      print(" p [" , i , "]\t", end="")
      j = 0
      while j < len(p[i]):
        print(p[i][j], "|", end="")
        j = j + 1
      print("\n", end="")
      i = i + 1

    print(" ------------------------------------------------");

    it += 1;
