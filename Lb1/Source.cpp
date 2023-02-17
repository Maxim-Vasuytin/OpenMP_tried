#include <windows.h> 
#include <iostream>
#include <math.h>
#include <thread>
#include <time.h>
using namespace std;


// функция, интеграл
double f(double x)
{
    return sin(x);
}

void main()
{
    clock_t start = clock();

    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    int cpuCount = siSysInfo.dwNumberOfProcessors;

    int i; // счётчик
    double Integral; // здесь будет интеграл
    double a = 1.0, b = 100.0; // задаём отрезок интегрирования
    double h = 0.000001;// задаём шаг интегрирования

    double n; // задаём число разбиений n

    n = (b - a) / h;
    // вычисляем интеграл по формуле трапеций
    Integral = h * (f(a) + f(b)) / 2.0;
        
            //for (i = 1; i <= n - 1; i++)
            //{
            //    Integral = Integral + h * f(a + h * i);
            //    //cout << Integral << " ";
            //}
        
       
    
        long long totalSum = 0;
        int threadsN = 0;
#pragma omp parallel
        {
            int threadId = -1;
#pragma omp critical 
            {
                threadId = threadsN;
                cout << "Thread # " << threadId << " started..." << endl;
                ++threadsN;
            }
            long long threadSum = 0;
#pragma omp for 
            for (int i = 1; i < (int)n; ++i)
            {
                Integral = Integral + h * f(a + h * i);
            }
#pragma omp critical
            {
                totalSum += Integral;
                cout << "Thread #" << threadId << " finished!" << endl;
            }
        }
        cout << "I2 = " << Integral << "\n";

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
}