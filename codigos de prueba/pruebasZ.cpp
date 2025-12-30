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

                double diferencia = oferta[i] - demanda[j];
                if (diferencia < 0)
                    diferencia = -diferencia;

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
    {
        for (int j = 0; j < n; j++)
        {
            z += asignacion[i][j] * costo[i][j];
        }
    }

    cout << "\nValor de Z: " << z << endl;

    return 0;
}