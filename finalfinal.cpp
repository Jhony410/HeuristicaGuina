#include <iostream>
using namespace std;

const int MAX_M = 50;
const int MAX_N = 50;

int main()
{
    int m, n;

    cout << "Ingrese numero de origenes (m): ";
    cin >> m;
    cout << "Ingrese numero de destinos (n): ";
    cin >> n;

    int costo[MAX_M][MAX_N];
    int asignacion[MAX_M][MAX_N] = {0};
    int oferta[MAX_M];
    int demanda[MAX_N];

    cout << "\nIngrese la matriz de costos:\n";
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            cout << "Costo[" << i << "][" << j << "]: ";
            cin >> costo[i][j];
        }

    cout << "\nIngrese el vector de oferta:\n";
    for (int i = 0; i < m; i++)
    {
        cout << "Oferta[" << i << "]: ";
        cin >> oferta[i];
    }

    cout << "\nIngrese el vector de demanda:\n";
    for (int j = 0; j < n; j++)
    {
        cout << "Demanda[" << j << "]: ";
        cin >> demanda[j];
    }

    int suma_oferta = 0;
    int suma_demanda = 0;

    for (int i = 0; i < m; i++)
        suma_oferta += oferta[i];
    for (int j = 0; j < n; j++)
        suma_demanda += demanda[j];

    if (suma_oferta != suma_demanda)
    {
        int diferencia;
        if (suma_oferta > suma_demanda)
            diferencia = suma_oferta - suma_demanda;
        else
            diferencia = suma_demanda - suma_oferta;

        cout << "\nEl problema no esta balanceado.\n";
        cout << "Suma de oferta: " << suma_oferta << endl;
        cout << "Suma de demanda: " << suma_demanda << endl;
        cout << "Diferencia entre oferta y demanda: " << diferencia << endl;
        cout << "Por favor balancee el problema e intente de nuevo.\n";
        return 0;
    }

    double maxDemanda = demanda[0];
    for (int j = 1; j < n; j++)
        if (demanda[j] > maxDemanda)
            maxDemanda = demanda[j];

    while (true)
    {
        double mejor = 9999999;
        int mi = -1, mj = -1;

        for (int i = 0; i < m; i++)
        {
            if (oferta[i] <= 0)
                continue;

            for (int j = 0; j < n; j++)
            {
                if (demanda[j] <= 0)
                    continue;

                double diferencia;
                if (oferta[i] > demanda[j])
                    diferencia = oferta[i] - demanda[j];
                else
                    diferencia = demanda[j] - oferta[i];

                double mayor;
                if (oferta[i] > demanda[j])
                    mayor = oferta[i];
                else
                    mayor = demanda[j];

                double equilibrio = 1.0 + diferencia / mayor;
                double prioridadDemanda = demanda[j] / maxDemanda;
                double hcbe_d = costo[i][j] * equilibrio * prioridadDemanda;

                if (hcbe_d < mejor)
                {
                    mejor = hcbe_d;
                    mi = i;
                    mj = j;
                }
            }
        }

        if (mi == -1)
            break;

        int asignar;
        if (oferta[mi] < demanda[mj])
            asignar = oferta[mi];
        else
            asignar = demanda[mj];

        asignacion[mi][mj] = asignar;
        oferta[mi] -= asignar;
        demanda[mj] -= asignar;
    }

    cout << "\nMatriz de asignacion final:\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cout << asignacion[i][j] << " ";
        cout << endl;
    }

    int z = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            z += asignacion[i][j] * costo[i][j];

    cout << "\nValor de Z: " << z << endl;

    for (int i = 0; i < m; i++)
        cout << "Origen " << i << " tiene oferta no asignada de: " << oferta[i] << endl;

    for (int j = 0; j < n; j++)
        cout << "Destino " << j << " tiene demanda no satisfecha de: " << demanda[j] << endl;

    return 0;
}