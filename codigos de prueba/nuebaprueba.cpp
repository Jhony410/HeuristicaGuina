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
    int totalOferta = 0;
    for (int i = 0; i < m; i++)
    {
        cout << "Oferta[" << i << "]: ";
        cin >> oferta[i];
        totalOferta += oferta[i];
    }
    
    cout << "\nIngrese el vector de demanda:\n";
    int totalDemanda = 0;
    for (int j = 0; j < n; j++)
    {
        cout << "Demanda[" << j << "]: ";
        cin >> demanda[j];
        totalDemanda += demanda[j];
    }
    
    // VALIDACION DE BALANCE
    cout << "\n========================================\n";
    cout << "VERIFICACION DE BALANCE:\n";
    cout << "Total Oferta  : " << totalOferta << "\n";
    cout << "Total Demanda : " << totalDemanda << "\n";
    cout << "========================================\n";
    
    if (totalOferta != totalDemanda)
    {
        cout << "\n*** ERROR: EL PROBLEMA NO ESTA BALANCEADO ***\n";
        cout << "Diferencia: " << abs(totalOferta - totalDemanda) << " unidades\n";
        
        if (totalOferta > totalDemanda)
        {
            cout << "\nHay EXCESO de oferta (sobran " << (totalOferta - totalDemanda) << " unidades)\n";
            cout << "Solucion: Aumente la demanda en " << (totalOferta - totalDemanda) << " unidades\n";
        }
        else
        {
            cout << "\nHay DEFICIT de oferta (faltan " << (totalDemanda - totalOferta) << " unidades)\n";
            cout << "Solucion: Aumente la oferta en " << (totalDemanda - totalOferta) << " unidades\n";
        }
        
        cout << "\nEl programa solo funciona con problemas balanceados.\n";
        cout << "Por favor, reingrese los datos con oferta = demanda.\n";
        return 1; // Termina el programa con código de error
    }
    
    cout << "\n✓ El problema esta BALANCEADO. Procediendo con la solucion...\n\n";
    
    // Copias de trabajo para el algoritmo
    int ofertaTrabajo[MAX_M];
    int demandaTrabajo[MAX_N];
    for (int i = 0; i < m; i++) ofertaTrabajo[i] = oferta[i];
    for (int j = 0; j < n; j++) demandaTrabajo[j] = demanda[j];
    
    double maxDemanda = demandaTrabajo[0];
    for (int j = 1; j < n; j++)
        if (demandaTrabajo[j] > maxDemanda)
            maxDemanda = demandaTrabajo[j];
    
    // ALGORITMO DE ASIGNACION
    while (true)
    {
        double mejor = 9999999;
        int mi = -1, mj = -1;
        
        for (int i = 0; i < m; i++)
        {
            if (ofertaTrabajo[i] <= 0)
                continue;
            for (int j = 0; j < n; j++)
            {
                if (demandaTrabajo[j] <= 0)
                    continue;
                
                double diferencia = ofertaTrabajo[i] - demandaTrabajo[j];
                if (diferencia < 0)
                    diferencia = -diferencia;
                
                double mayor;
                if (ofertaTrabajo[i] > demandaTrabajo[j])
                    mayor = ofertaTrabajo[i];
                else
                    mayor = demandaTrabajo[j];
                
                double equilibrio = 1.0 + diferencia / mayor;
                double prioridadDemanda = demandaTrabajo[j] / maxDemanda;
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
        if (ofertaTrabajo[mi] < demandaTrabajo[mj])
            asignar = ofertaTrabajo[mi];
        else
            asignar = demandaTrabajo[mj];
        
        asignacion[mi][mj] = asignar;
        ofertaTrabajo[mi] -= asignar;
        demandaTrabajo[mj] -= asignar;
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
    
    // VERIFICACION FINAL (opcional pero recomendado)
    cout << "\n========================================\n";
    cout << "VERIFICACION DE LA SOLUCION:\n";
    
    bool solucionCompleta = true;
    for (int i = 0; i < m; i++)
    {
        int asignado = 0;
        for (int j = 0; j < n; j++)
            asignado += asignacion[i][j];
        
        if (asignado != oferta[i])
        {
            cout << "✗ Origen " << i << ": asignado=" << asignado 
                 << ", oferta=" << oferta[i] << "\n";
            solucionCompleta = false;
        }
    }
    
    for (int j = 0; j < n; j++)
    {
        int recibido = 0;
        for (int i = 0; i < m; i++)
            recibido += asignacion[i][j];
        
        if (recibido != demanda[j])
        {
            cout << "✗ Destino " << j << ": recibido=" << recibido 
                 << ", demanda=" << demanda[j] << "\n";
            solucionCompleta = false;
        }
    }
    
    if (solucionCompleta)
        cout << "✓ Toda la oferta fue asignada\n";
        cout << "✓ Toda la demanda fue satisfecha\n";
    
    cout << "========================================\n";
    
    return 0;
}