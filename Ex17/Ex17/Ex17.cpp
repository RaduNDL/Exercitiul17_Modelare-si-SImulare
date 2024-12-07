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
    srand(static_cast<unsigned>(time(0))); 
    const int maxSteps = 50;          
    const int numSimulations = 10000;     
    vector<double> meanDistances(maxSteps, 0.0); 
    vector<double> evenDistances, oddDistances;

    for (int steps = 1; steps <= maxSteps; steps++) {
        double totalDistance = 0.0;
        for (int sim = 0; sim < numSimulations; sim++) {
            totalDistance += randomWalk2D(steps);
        }
        meanDistances[steps - 1] = totalDistance / numSimulations;

        if (steps % 2 == 0) {
            evenDistances.push_back(meanDistances[steps - 1]);
        }
        else {
            oddDistances.push_back(meanDistances[steps - 1]);
        }
    }

    int maxAllowedSteps = 0;
    for (int steps = 1; steps <= maxSteps; steps++) {
        if (meanDistances[steps - 1] <= 5.0) {
            maxAllowedSteps = steps;
        }
    }

    double evenMean = 0.0, oddMean = 0.0;
    for (double dist : evenDistances) evenMean += dist;
    for (double dist : oddDistances) oddMean += dist;
    evenMean /= evenDistances.size();
    oddMean /= oddDistances.size();

    cout << "Exercitiul 13:" << endl;
    cout << "Numarul maxim de pasi pentru care distanta medie este <= 5: " << maxAllowedSteps << endl;
    cout << "\nExercitiul 14:" << endl;
    cout << "Distanta medie pentru pasi pari: " << evenMean << endl;
    cout << "Distanta medie pentru pasi impari: " << oddMean << endl;

    if (evenMean < oddMean) {
        cout << "Concluzie: Pasi pari conduc la distante mai mici, in medie." << endl;
    }
    else {
        cout << "Concluzie: Pasi impari conduc la distante mai mici, in medie." << endl;
    }

    cout << "\nComparatie intre distanta teoretica si simulata:" << endl;
    for (int steps = 1; steps <= maxSteps; steps++) {
        double theoreticalDistance = sqrt(steps);
        cout << "Pasi: " << steps
            << " | Distanta teoretica: " << theoreticalDistance
            << " | Distanta simulata: " << meanDistances[steps - 1]
            << " | Diferenta: " << fabs(theoreticalDistance - meanDistances[steps - 1]) << endl;
    }

    return 0;
}
