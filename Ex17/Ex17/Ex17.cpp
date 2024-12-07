#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

double randomWalk2D(int numSteps) {
    int x = 0, y = 0;
    for (int i = 0; i < numSteps; i++) {
        int direction = rand() % 4;
        switch (direction) {
        case 0: y++; break;
        case 1: x++; break;
        case 2: y--; break;
        case 3: x--; break;
        }
    }
    return sqrt(x * x + y * y);
}

int main() {
    srand(time(0));
    int maxSteps = 50, numSimulations = 10000;
    vector<double> meanDistances(maxSteps, 0.0), evenStepDistances, oddStepDistances;

    for (int steps = 1; steps <= maxSteps; steps++) {
        double totalDistance = 0.0;
        for (int sim = 0; sim < numSimulations; sim++) {
            totalDistance += randomWalk2D(steps);
        }
        meanDistances[steps - 1] = totalDistance / numSimulations;
        if (steps % 2 == 0) {
            evenStepDistances.push_back(meanDistances[steps - 1]);
        }
        else {
            oddStepDistances.push_back(meanDistances[steps - 1]);
        }
    }

    int maxAllowedSteps = 0;
    for (int steps = 1; steps <= maxSteps; steps++) {
        if (meanDistances[steps - 1] <= 5.0) {
            maxAllowedSteps = steps;
        }
    }

    double evenMean = 0.0, oddMean = 0.0;
    for (double dist : evenStepDistances) {
        evenMean += dist;
    }
    for (double dist : oddStepDistances) {
        oddMean += dist;
    }
    evenMean /= evenStepDistances.size();
    oddMean /= oddStepDistances.size();

    cout << "Numarul maxim de pasi pentru care distanta medie este <= 5: " << maxAllowedSteps << endl;
    cout << "Distanta medie pentru pasi pari: " << evenMean << endl;
    cout << "Distanta medie pentru pasi impari: " << oddMean << endl;

    if (evenMean < oddMean) {
        cout << "Rezultat conform teoriei: pasi pari conduc la distante mai mici in medie." << endl;
    }
    else {
        cout << "Rezultat diferit fata de teorie: pasi impari conduc la distante mai mici in medie." << endl;
    }

    for (int steps = 1; steps <= maxSteps; steps++) {
        cout << "Pasi: " << steps << " - Distanta medie: " << meanDistances[steps - 1] << endl;
    }

    for (int steps = 1; steps <= maxSteps; steps++) {
        double theoreticalDistance = sqrt(steps);  
        cout << "Pasi: " << steps << " - Distanta teoretica: " << theoreticalDistance << endl;
        cout << "Pasi: " << steps << " - Distanta medie simulata: " << meanDistances[steps - 1] << endl;
        cout << "Diferenta: " << abs(theoreticalDistance - meanDistances[steps - 1]) << endl;
    }

    if (evenMean < oddMean) {
        cout << "Conform teoriei din Exercitiul 14, pasi pari ar trebui sa conduca la o distanta mai mica." << endl;
        cout << "Distanta medie pentru pasi pari este " << evenMean << " iar pentru pasi impari este " << oddMean << "." << endl;
    }
    else {
        cout << "Conform teoriei din Exercitiul 14, pasi impari ar trebui sa conduca la o distanta mai mica." << endl;
        cout << "Distanta medie pentru pasi impari este " << oddMean << " iar pentru pasi pari este " << evenMean << "." << endl;
    }

    return 0;
}
