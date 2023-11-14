#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <stdio.h>

using namespace std;

void separatium_v0(  vector<vector<double>> &p,
              vector<double> &CX,
              vector<double> &CY,
              vector<vector<double>> &D,
              vector<double> X,
              vector<double> Y,
			  int iteracao
			  )
{
  int i = 0;
  while(i < iteracao)
  {
    std::cout << " ------------------------------------------------\n";
    std::cout << " X []\t";
    for (int i = 0; i < X.size(); i++)
      std::cout << X[i] << "|";
    std::cout << endl;
    std::cout << " ------------------------------------------------\n";
    std::cout << " Y []\t";
    for (int i = 0; i < Y.size(); i++)
      std::cout << Y[i] << "|";
    std::cout << endl;

    std::cout << " ------------------------------------------------\n";
    for (int i = 0; i < p.size(); i++) {
      std::cout << " AMO [" << i << "]\t";
      for (int j = 0; j < p[i].size(); j++)
        std::cout << p[i][j] << "|";
      std::cout << endl;
    }

    std::cout << " ------------------------------------------------\n";
    std::cout << " CALCULANDO CX E CY\n";
    for (int i = 0; i < p.size(); i++) 
    {
      double upper = 0.0;
      for (int j = 0; j < p[i].size(); j++)
      {
        upper += pow(p[i][j], 2.0) * X[j];
      }

      double lower = 0.0;
      for (int j = 0; j < p[i].size(); j++)
        lower += pow(p[i][j], 2.0);

      CX[i] = upper / lower;
      printf("CX[%d] = %f\n", i, CX[i]);

      upper = 0.0;
      for (int j = 0; j < p[i].size(); j++)
        upper += pow(p[i][j], 2.0) * Y[j];

      CY[i] = upper / lower;
      printf("CY[%d] = %f\n", i, CY[i]);
    }

    std::cout << " ------------------------------------------------\n";
    std::cout << " CALCULANDO D11 D12 D21 D22 \n";

    D[0][0] = sqrt(pow(X[0] - CX[0], 2.0) + pow(Y[0] - CY[0], 2.0));
    D[0][1] = sqrt(pow(X[0] - CX[1], 2.0) + pow(Y[0] - CY[1], 2.0));
    D[1][0] = sqrt(pow(X[1] - CX[0], 2.0) + pow(Y[1] - CY[0], 2.0));
    D[1][1] = sqrt(pow(X[1] - CX[1], 2.0) + pow(Y[1] - CY[1], 2.0));

    printf("D[0][0] = %f\n", D[0][0]);
    printf("D[0][1] = %f\n", D[0][1]);
    printf("D[1][0] = %f\n", D[1][0]);
    printf("D[1][1] = %f\n", D[1][1]);

    std::cout << " ------------------------------------------------\n";
    std::cout << " CALCULANDO p11 p12 p21 p22 \n";

    p[0][0] = 1.0 / ( pow(D[0][0]/D[0][0],2.0)  + pow(D[0][0]/D[0][1],2.0));
    p[0][1] = 1.0 / ( pow(D[0][1]/D[0][1],2.0)  + pow(D[0][1]/D[0][0],2.0));

    p[1][0] = 1.0 / ( pow(D[1][0]/D[1][0],2.0)  + pow(D[1][0]/D[1][1],2.0));
    p[1][1] = 1.0 / ( pow(D[1][1]/D[1][1],2.0)  + pow(D[1][1]/D[1][0],2.0));


    printf("p[0][0] = %f\n", p[0][0]);
    printf("p[0][1] = %f\n", p[0][1]);
    printf("p[1][0] = %f\n", p[1][0]);
    printf("p[1][1] = %f\n", p[1][1]);

    std::cout << " ------------------------------------------------\n";
    i++;
  }
}


void separatium(   vector<vector<double>> &p,
                  vector<vector<double>> &H,
                  vector<vector<double>> &Ce,
                  vector<vector<double>> &D,
                  vector<vector<double>> &X,
                  int iteracoes)
{
  int i = 0;
  while(i < iteracoes)
  {
    
    std::cout << " ------------------------------------------------\n";
    std::cout << "         ITERACAO ["<< i << "] \n";
    std::cout << " ------------------------------------------------\n";
    for (int i = 0; i < X.size(); i++) {
      std::cout << " X[" << i << "]\t";
      for (int j = 0; j < X[i].size(); j++)
        printf("%f|", X[i][j]);
      std::cout << endl;
    }

    std::cout << " ------------------------------------------------\n";
    for (int i = 0; i < p.size(); i++) {
      std::cout << " p [" << i << "]\t";
      for (int j = 0; j < p[i].size(); j++)
        printf("%f|", p[i][j]);
      std::cout << endl;
    }
  std::cout << " ------------------------------------------------\n";
  for (int i = 0; i < H.size(); i++) {
    std::cout << " H [" << i << "]\t";
    for (int j = 0; j < H[i].size(); j++)
      printf("%f|", H[i][j]);
    std::cout << endl;
  }

    std::cout << " ------------------------------------------------\n";
    std::cout << " CALCULANDO Ce \n";
    int Probabilidades = p.size();
    int Dimensoes = X.size();
    int Pontos = 0;
    if(Dimensoes > 0)
      Pontos = X[0].size();
  
    for (int i = 0; i < Probabilidades; i++) 
    {
      for (int j = 0; j < Dimensoes; j++) 
      {
        double upper = 0.0;
        double lower = 0.0;
        for (int k = 0; k < Pontos; k++) 
        {
          upper += pow(p[i][k], 2.0) * X[j][k];
          lower += pow(p[i][k], 2.0);
        }
        Ce[j][i] = upper / lower;
        printf("Ce[%d][%d] = %f\n",j, i, Ce[j][i]);
      }
    }

    std::cout << " ------------------------------------------------\n";
    std::cout << " CALCULANDO D11 D12 D21 D22 \n";

  for (int i = 0; i < Probabilidades; i++) 
  {
    for (int k = 0; k < Pontos; k++) 
    {
      double soma = 0.0;
      for (int j = 0; j < Dimensoes; j++) 
      {
        soma += pow(X[j][k] - Ce[j][i], 2.0);
      }
      D[i][k] = sqrt(soma);
      printf("D[%d][%d] = %f\n",i, k, D[i][k]);
    }
  }

  std::cout << " ------------------------------------------------\n";
  std::cout << " CALCULANDO H11 H12 H21 H22 \n";

  for (int i = 0; i < Probabilidades; i++) 
  {
    for (int k = 0; k < Pontos; k++) 
    {
      double soma = 0.0;
      for (int i2 = 0; i2 < Probabilidades; i2++) 
      {
        soma += pow(D[i][k] / D[i2][k], 2.0);
      }
      H[i][k] = 1.0 / soma;
      printf("H[%d][%d] = %f\n",i, k, H[i][k]);
    }
  }

  std::cout << " ------------------------------------------------\n";
  std::cout << " ATUALIZANDO p11 p12 p21 p22 \n";

  for (int i = 0; i < Probabilidades; i++) 
  {
    for (int k = 0; k < Pontos; k++) 
    {
      p[i][k] = H[i][k];
    }
  }

    std::cout << " ------------------------------------------------\n";
    i++;
  }
}
int main() 
{
	int exemplo = 3;
	
	if(exemplo == 1 )
	{
			
		vector<vector<double>>p;
		vector<double> CX;
		vector<double> CY;
		vector<vector<double>> D;
		//vector<vector<double>> &H = p;
		vector<double> X;
		vector<double> Y;
		
		vector<double> vecTemp;
		vector<double> amo1({0.70, 0.20});
		vector<double> amo2({0.30, 0.80});
		p.push_back(amo1);
		p.push_back(amo2);
		
		D.push_back(amo1);
		D.push_back(amo2);
		
		double aX[] = {2.0, 4.0};
		X.insert(X.begin(), aX, aX + 2);
		double aY[] = {3.0, 6.0};
		Y.insert(Y.begin(), aY, aY + 2);
		
		double Zero[] = {0.0, 0.0};
		CX.insert(CX.begin(), Zero, Zero + 2);
		CY.insert(CY.begin(), Zero, Zero + 2);
		
		separatium_v0(p,CX,CY,D,X,Y, 2);
	
	}
	if(exemplo == 2 )
	{
		int qtd_dimensoes = -1;
		int qtd_pontos = -1;
		int qtd_probab = 2;
		int qtd_iteracoes = 4;

		vector<vector<double>> p;
		vector<vector<double>> Ce;
		vector<vector<double>> D;
		vector<vector<double>> X;
		
		// ------------------------
		// DEFINIÇÃO DOS PONTOS ...
		// ------------------------


		// ------------------------
		//  f(x) = Himmelblau's ...
		// ------------------------
		X.resize(2);

		 X[0].push_back(1.0);
		 X[0].push_back(3.0);
		 X[0].push_back(6.0);
		 X[0].push_back(8.0);
	 
		 X[1].push_back(2.0);
		 X[1].push_back(4.0);
		 X[1].push_back(7.0);
		 X[1].push_back(9.0);
		 
		qtd_dimensoes = X.size();
		
		if ( X.size() > 0)
			qtd_pontos = X[0].size();

		p.resize(qtd_probab);		

		p[0].push_back(0.7);
		p[0].push_back(0.8);
		p[0].push_back(0.1);
		p[0].push_back(0.3);

		p[1].push_back(0.3);
		p[1].push_back(0.2);
		p[1].push_back(0.9);
		p[1].push_back(0.7);

		vector<vector<double>> H (p);

		for (int i=0; i < qtd_probab; i++)
			D.push_back(p[i]);

		for(int i=0; i< qtd_dimensoes; i++)
		{
		  vector<double> Temp (qtd_probab, 0.0);
		  Ce.push_back(Temp);
		}
		
		separatium(p, H, Ce, D, X, qtd_iteracoes);
		
		
		std::cout << " ------------------------------------------------\n";
		
		int Probabilidades = p.size();
		int Pontos = 0;
		if (Probabilidades > 0)
			Pontos = p[0].size();
		vector<int> PontoEscolhido(Pontos,0);
		for (int j = 0; j < Pontos; j++) 
		{
			double maior = 0.0;
			for (int ip = 0; ip < Probabilidades; ip++) 
			{
				if (p[ip][j] >= maior)
				{
					maior = p[ip][j];
					PontoEscolhido[j] = ip;				
				}
			}
		}
		
		std::cout << " Ponto|Probab\n";
		for (int k = 0; k < Pontos; k++) 
			printf("[%2d] - [%2d]\n", k, PontoEscolhido[k]);
		std::cout << " ------------------------------------------------\n";			
		
	
	}
	if(exemplo == 3 )
	{
		int qtd_dimensoes = -1;
		int qtd_pontos = -1;
		int qtd_probab = 2;
		int qtd_iteracoes = 6;

		vector<vector<double>> p;
		vector<vector<double>> Ce;
		vector<vector<double>> D;
		vector<vector<double>> X;
		
		// ------------------------
		// DEFINIÇÃO DOS PONTOS ...
		// ------------------------


		// ------------------------
		//  f(x) = Himmelblau's ...
		// ------------------------
		X.resize(2);

		 X[0].push_back(3.0);
		 X[0].push_back(0.0);
		 X[0].push_back(7.0);
		 X[0].push_back(8.0);
		 X[0].push_back(9.0);
		 X[0].push_back(1.0);
		 X[0].push_back(2.0);
		 X[0].push_back(6.0);
	 
		 X[1].push_back(2.0);
		 X[1].push_back(3.0);
		 X[1].push_back(6.0);
		 X[1].push_back(7.0);
		 X[1].push_back(8.0);
		 X[1].push_back(1.0);
		 X[1].push_back(1.0);
		 X[1].push_back(9.0);
		 
		qtd_dimensoes = X.size();
		
		if ( X.size() > 0)
			qtd_pontos = X[0].size();

		p.resize(qtd_probab);		

		p[0].push_back(0.8);
		p[0].push_back(0.7);
		p[0].push_back(0.2);
		p[0].push_back(0.1);
		p[0].push_back(0.3);
		p[0].push_back(0.7);
		p[0].push_back(0.65);
		p[0].push_back(0.4);

		p[1].push_back(0.2);
		p[1].push_back(0.3);
		p[1].push_back(0.8);
		p[1].push_back(0.9);
		p[1].push_back(0.8);
		p[1].push_back(0.3);
		p[1].push_back(0.35);
		p[1].push_back(0.6);

		vector<vector<double>> H (p);

		for (int i=0; i < qtd_probab; i++)
			D.push_back(p[i]);

		for(int i=0; i< qtd_dimensoes; i++)
		{
		  vector<double> Temp (qtd_probab, 0.0);
		  Ce.push_back(Temp);
		}
		
		separatium(p, H, Ce, D, X, qtd_iteracoes);
		
		
		std::cout << " ------------------------------------------------\n";
		
		int Probabilidades = p.size();
		int Pontos = 0;
		if (Probabilidades > 0)
			Pontos = p[0].size();
		vector<int> PontoEscolhido(Pontos,0);
		for (int j = 0; j < Pontos; j++) 
		{
			double maior = 0.0;
			for (int ip = 0; ip < Probabilidades; ip++) 
			{
				if (p[ip][j] >= maior)
				{
					maior = p[ip][j];
					PontoEscolhido[j] = ip;				
				}
			}
		}
		
		std::cout << " Ponto|Probab\n";
		for (int k = 0; k < Pontos; k++) 
			printf("[%2d] - [%2d]\n", k, PontoEscolhido[k]);
		std::cout << " ------------------------------------------------\n";			
		
	
	}
	else
	{
		int qtd_dimensoes = -1;
		int qtd_probab = 4;
		int qtd_pontos = -1;
		int qtd_iteracoes = 20;

		vector<vector<double>> p;
		vector<vector<double>> Ce;
		vector<vector<double>> D;
		vector<vector<double>> X;
		
		// ------------------------
		// DEFINIÇÃO DOS PONTOS ...
		// ------------------------


		// ------------------------
		//  f(x) = Himmelblau's ...
		// ------------------------
		X.resize(3);

		 X[0].push_back(-4);
		 X[0].push_back(-3.5);
		 X[0].push_back(-3);
		 X[0].push_back(3);
		 X[0].push_back(3.5);
		 X[0].push_back(4);
		 X[0].push_back(3);
		 X[0].push_back(3.5);
		 X[0].push_back(4);
		 X[0].push_back(2.5);
		 X[0].push_back(3);
		 X[0].push_back(3.5);
		 X[0].push_back(-3);
		 X[0].push_back(-2.5);
		 X[0].push_back(-2);

	 
		 X[1].push_back(-3.5);
		 X[1].push_back(-3.5);
		 X[1].push_back(-3.5);
		 X[1].push_back(-2);
		 X[1].push_back(-2);
		 X[1].push_back(-2);
		 X[1].push_back(-1.5);
		 X[1].push_back(-1.5);
		 X[1].push_back(-1.5);
		 X[1].push_back(2);
		 X[1].push_back(2);
		 X[1].push_back(2);
		 X[1].push_back(3);
		 X[1].push_back(3);
		 X[1].push_back(3);

		 X[2].push_back(0.69);
		 X[2].push_back(0.24);
		 X[2].push_back(0.00);
		 X[2].push_back(0.07);
		 X[2].push_back(0.38);
		 X[2].push_back(0.92);
		 X[2].push_back(0.13);
		 X[2].push_back(0.45);
		 X[2].push_back(1.00);
		 X[2].push_back(0.17);
		 X[2].push_back(0.47);
		 X[2].push_back(0.96);
		 X[2].push_back(0.61);
		 X[2].push_back(0.27);
		 X[2].push_back(0.07);
		 
		 
		 
		// ---------------------
		//  ff(x) = sin(x)/x ...
		// ---------------------
		/*X.resize(2);

		 X[0].push_back(0.000);
		 X[0].push_back(0.025);
		 X[0].push_back(0.050);
		 X[0].push_back(0.075);
		 X[0].push_back(0.100);
		 X[0].push_back(0.125);
		 X[0].push_back(0.150);
		 X[0].push_back(0.175);
		 X[0].push_back(0.200);
		 X[0].push_back(0.225);
		 X[0].push_back(0.250);
		 X[0].push_back(0.275);
		 X[0].push_back(0.300);
		 X[0].push_back(0.325);
		 X[0].push_back(0.350);
		 X[0].push_back(0.375);
		 X[0].push_back(0.400);
		 X[0].push_back(0.425);
		 X[0].push_back(0.450);
		 X[0].push_back(0.475);
		 X[0].push_back(0.500);
		 X[0].push_back(0.525);
		 X[0].push_back(0.550);
		 X[0].push_back(0.575);
		 X[0].push_back(0.600);
		 X[0].push_back(0.625);
		 X[0].push_back(0.650);
		 X[0].push_back(0.675);
		 X[0].push_back(0.700);
		 X[0].push_back(0.725);
		 X[0].push_back(0.750);
		 X[0].push_back(0.775);
		 X[0].push_back(0.800);
		 X[0].push_back(0.825);
		 X[0].push_back(0.850);
		 X[0].push_back(0.875);
		 X[0].push_back(0.900);
		 X[0].push_back(0.925);
		 X[0].push_back(0.950);
		 X[0].push_back(0.975);
		 X[0].push_back(1.000);
							 
		 X[1].push_back(0.046);
		 X[1].push_back(0.008);
		 X[1].push_back(-0.042);
		 X[1].push_back(-0.057);
		 X[1].push_back(-0.018);
		 X[1].push_back(0.043);
		 X[1].push_back(0.071);
		 X[1].push_back(0.032);
		 X[1].push_back(-0.045);
		 X[1].push_back(-0.091);
		 X[1].push_back(-0.054);
		 X[1].push_back(0.046);
		 X[1].push_back(0.124);
		 X[1].push_back(0.094);
		 X[1].push_back(-0.047);
		 X[1].push_back(-0.192);
		 X[1].push_back(-0.189);
		 X[1].push_back(0.047);
		 X[1].push_back(0.455);
		 X[1].push_back(0.841);
		 X[1].push_back(1.000);
		 X[1].push_back(0.841);
		 X[1].push_back(0.455);
		 X[1].push_back(0.047);
		 X[1].push_back(-0.189);
		 X[1].push_back(-0.192);
		 X[1].push_back(-0.047);
		 X[1].push_back(0.094);
		 X[1].push_back(0.124);
		 X[1].push_back(0.046);
		 X[1].push_back(-0.054);
		 X[1].push_back(-0.091);
		 X[1].push_back(-0.045);
		 X[1].push_back(0.032);
		 X[1].push_back(0.071);
		 X[1].push_back(0.043);
		 X[1].push_back(-0.018);
		 X[1].push_back(-0.057);
		 X[1].push_back(-0.042);
		 X[1].push_back(0.008);
		 X[1].push_back(0.046);*/
		 
		 
		 
		qtd_dimensoes = X.size();
		
		if ( X.size() > 0)
			qtd_pontos = X[0].size();	

	/*
		p[0].push_back(0.8);
		p[0].push_back(0.7);
		p[0].push_back(0.2);
		p[0].push_back(0.1);
		p[0].push_back(0.3);
		p[0].push_back(0.7);
		p[0].push_back(0.65);
		p[0].push_back(0.4);

		p[1].push_back(0.2);
		p[1].push_back(0.3);
		p[1].push_back(0.8);
		p[1].push_back(0.9);
		p[1].push_back(0.8);
		p[1].push_back(0.3);
		p[1].push_back(0.35);
		p[1].push_back(0.6);
	*/
		// -------------------------------------------------
		// DEFINIÇÃO DA PROBABILIDADE INICIAL, ALEATORIA ...
		// -------------------------------------------------
		p.resize(qtd_probab);
		srand (time(NULL));
		for (int i=0; i < qtd_probab; i++)
		{
			p[i].reserve(qtd_pontos);
			for (int j=0; j < qtd_pontos; j++)
			{
				p[i].push_back(((double) rand() / (RAND_MAX)));
			}
		}
	  /*
		p[0].push_back(0.1);
		p[0].push_back(0.2);
		p[0].push_back(0.3);

		p[1].push_back(0.6);
		p[1].push_back(0.2);
		p[1].push_back(0.6);
	*/
	  
		vector<vector<double>> H (p);

		for (int i=0; i < qtd_probab; i++)
			D.push_back(p[i]);


		X.resize(qtd_dimensoes);
		/*X[0].push_back(3.0);
		X[0].push_back(0.0);
		X[0].push_back(7.0);
		X[0].push_back(8.0);
		X[0].push_back(9.0);
		X[0].push_back(1.0);
		X[0].push_back(2.0);
		X[0].push_back(6.0);

		X[1].push_back(2.0);
		X[1].push_back(3.0);
		X[1].push_back(6.0);
		X[1].push_back(7.0);
		X[1].push_back(8.0);
		X[1].push_back(1.0);
		X[1].push_back(1.0);
		X[1].push_back(9.0);*/

		
		//double Zero[] = {0.0, 0.0};
		//CX.insert(CX.begin(), Zero, Zero + 2);
		//CY.insert(CY.begin(), Zero, Zero + 2);
		for(int i=0; i< qtd_dimensoes; i++)
		{
		  vector<double> Temp (qtd_probab, 0.0);
		  Ce.push_back(Temp);
		}
		
		separatium(p, H, Ce, D, X, qtd_iteracoes);
		
		
		std::cout << " ------------------------------------------------\n";
		
		int Probabilidades = p.size();
		int Pontos = 0;
		if (Probabilidades > 0)
			Pontos = p[0].size();
		vector<int> PontoEscolhido(Pontos,0);
		for (int j = 0; j < Pontos; j++) 
		{
			double maior = 0.0;
			for (int ip = 0; ip < Probabilidades; ip++) 
			{
				if (p[ip][j] >= maior)
				{
					maior = p[ip][j];
					PontoEscolhido[j] = ip;				
				}
			}
		}
		
		std::cout << " Ponto|Probab\n";
		for (int k = 0; k < Pontos; k++) 
			printf("[%2d] - [%2d]\n", k, PontoEscolhido[k]);
		std::cout << " ------------------------------------------------\n";			
	}
}
