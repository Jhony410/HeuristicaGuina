#include <iostream>
using namespace std;
const int MAX_M = 50;
const int MAX_N = 50;

int main()
{
    int m, n;
    int costo[MAX_M][MAX_N];
    int asignacion[MAX_M][MAX_N] = {0};
    int oferta[MAX_M];
    int demanda[MAX_N];
    int totalOferta, totalDemanda;
    bool balanceado = false;
    
    cout << "Ingrese numero de origenes (m): ";
    cin >> m;
    cout << "Ingrese numero de destinos (n): ";
    cin >> n;
    
    cout << "\nIngrese la matriz de costos:\n";
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            cout << "Costo[" << i << "][" << j << "]: ";
            cin >> costo[i][j];
        }
    
    // BUCLE QUE FUERZA BALANCE
    while (!balanceado)
    {
        cout << "\n========================================\n";
        cout << "INGRESO DE OFERTA Y DEMANDA\n";
        cout << "========================================\n";
        
        cout << "\nIngrese el vector de oferta:\n";
        totalOferta = 0;
        for (int i = 0; i < m; i++)
        {
            cout << "Oferta[" << i << "]: ";
            cin >> oferta[i];
            totalOferta += oferta[i];
        }
        
        cout << "\nIngrese el vector de demanda:\n";
        totalDemanda = 0;
        for (int j = 0; j < n; j++)
        {
            cout << "Demanda[" << j << "]: ";
            cin >> demanda[j];
            totalDemanda += demanda[j];
        }
        
        cout << "\n========================================\n";
        cout << "VERIFICACION DE BALANCE:\n";
        cout << "Total Oferta  : " << totalOferta << "\n";
        cout << "Total Demanda : " << totalDemanda << "\n";
        cout << "========================================\n";
        
        balanceado = (totalOferta == totalDemanda);
        
        while (!balanceado)
        {
            cout << "\n*** ERROR: EL PROBLEMA NO ESTA BALANCEADO ***\n";
            cout << "Diferencia: " << abs(totalOferta - totalDemanda) << " unidades\n";
            
            while (totalOferta > totalDemanda)
            {
                cout << "\nHay EXCESO de oferta (sobran " << (totalOferta - totalDemanda) << " unidades)\n";
                cout << "Debe REDUCIR la oferta O AUMENTAR la demanda.\n";
                break;
            }
            
            while (totalOferta < totalDemanda)
            {
                cout << "\nHay DEFICIT de oferta (faltan " << (totalDemanda - totalOferta) << " unidades)\n";
                cout << "Debe AUMENTAR la oferta O REDUCIR la demanda.\n";
                break;
            }
            
            cout << "\nPor favor, reingrese los datos...\n";
            break;
        }
    }
    
    cout << "\n✓ El problema esta BALANCEADO. Procediendo con la solucion...\n\n";
    
    // Copias de trabajo para el algoritmo
    int ofertaTrabajo[MAX_M];
    int demandaTrabajo[MAX_N];
    for (int i = 0; i < m; i++) ofertaTrabajo[i] = oferta[i];
    for (int j = 0; j < n; j++) demandaTrabajo[j] = demanda[j];
    
    double maxDemanda = demandaTrabajo[0];
    for (int j = 1; j < n; j++)
    {
        while (demandaTrabajo[j] > maxDemanda)
        {
            maxDemanda = demandaTrabajo[j];
            break;
        }
    }
    
    // ALGORITMO DE ASIGNACION
    while (true)
    {
        double mejor = 9999999;
        int mi = -1, mj = -1;
        
        for (int i = 0; i < m; i++)
        {
            while (ofertaTrabajo[i] <= 0)
            {
                break;
            }
            
            while (ofertaTrabajo[i] > 0)
            {
                for (int j = 0; j < n; j++)
                {
                    while (demandaTrabajo[j] <= 0)
                    {
                        break;
                    }
                    
                    while (demandaTrabajo[j] > 0)
                    {
                        double diferencia = ofertaTrabajo[i] - demandaTrabajo[j];
                        while (diferencia < 0)
                        {
                            diferencia = -diferencia;
                            break;
                        }
                        
                        double mayor;
                        while (ofertaTrabajo[i] > demandaTrabajo[j])
                        {
                            mayor = ofertaTrabajo[i];
                            break;
                        }
                        while (ofertaTrabajo[i] <= demandaTrabajo[j])
                        {
                            mayor = demandaTrabajo[j];
                            break;
                        }
                        
                        double equilibrio = 1.0 + diferencia / mayor;
                        double prioridadDemanda = demandaTrabajo[j] / maxDemanda;
                        double hcbe_d = costo[i][j] * equilibrio * prioridadDemanda;
                        
                        while (hcbe_d < mejor)
                        {
                            mejor = hcbe_d;
                            mi = i;
                            mj = j;
                            break;
                        }
                        break;
                    }
                }
                break;
            }
        }
        
        while (mi == -1)
        {
            break;
        }
        
        while (mi != -1)
        {
            int asignar;
            while (ofertaTrabajo[mi] < demandaTrabajo[mj])
            {
                asignar = ofertaTrabajo[mi];
                break;
            }
            while (ofertaTrabajo[mi] >= demandaTrabajo[mj])
            {
                asignar = demandaTrabajo[mj];
                break;
            }
            
            asignacion[mi][mj] = asignar;
            ofertaTrabajo[mi] -= asignar;
            demandaTrabajo[mj] -= asignar;
            break;
        }
        
        while (mi == -1)
        {
            break;
        }
    }
    
    // RESULTADOS
    cout << "Matriz de asignacion final:\n";
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
    
    // VERIFICACION FINAL
    cout << "\n========================================\n";
    cout << "VERIFICACION DE LA SOLUCION:\n";
    
    bool solucionCompleta = true;
    for (int i = 0; i < m; i++)
    {
        int asignado = 0;
        for (int j = 0; j < n; j++)
            asignado += asignacion[i][j];
        
        while (asignado != oferta[i])
        {
            cout << "✗ Origen " << i << ": asignado=" << asignado 
                 << ", oferta=" << oferta[i] << "\n";
            solucionCompleta = false;
            break;
        }
    }
    
    for (int j = 0; j < n; j++)
    {
        int recibido = 0;
        for (int i = 0; i < m; i++)
            recibido += asignacion[i][j];
        
        while (recibido != demanda[j])
        {
            cout << "✗ Destino " << j << ": recibido=" << recibido 
                 << ", demanda=" << demanda[j] << "\n";
            solucionCompleta = false;
            break;
        }
    }
    
    while (solucionCompleta)
    {
        cout << "✓ Toda la oferta fue asignada\n";
        cout << "✓ Toda la demanda fue satisfecha\n";
        break;
    }
    
    cout << "========================================\n";
    
    return 0;
}