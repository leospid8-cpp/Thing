#include <iostream>  // Includiamo la libreria per le operazioni di input/output
#include <cmath>     // Includiamo la libreria per le funzioni matematiche come sqrt(), pow(), sin(), etc.
#define M_PI 3.14159265358979323846  // Definizione manuale del valore di pi greco (per compatibilità con alcuni compilatori)

// Utilizziamo lo spazio dei nomi standard per evitare di scrivere 'std::' ogni volta
using namespace std;

int main() {
    double num1, num2, num3, delta;  // Dichiarazione delle variabili per i numeri e il discriminante
    int scelta; // Variabile per memorizzare la scelta dell'utente

    // Ciclo infinito che permette di eseguire diverse operazioni finché l'utente non esce
    while (true) {
        // Stampa il menu delle operazioni disponibili
        cout << "\nScegli un'operazione:" << endl;
        cout << "1. Somma" << endl;
        cout << "2. Sottrazione" << endl;
        cout << "3. Moltiplicazione" << endl;
        cout << "4. Divisione" << endl;
        cout << "5. Potenza" << endl;
        cout << "6. Radice quadrata" << endl;
        cout << "7. Logaritmo" << endl;
        cout << "8. Funzioni trigonometriche" << endl;
        cout << "9. Area e Perimetro del Cerchio" << endl;
        cout << "10. Area e Perimetro del Quadrato" << endl;
        cout << "11. Area e Perimetro del Triangolo" << endl;
        cout << "12. Equazione di primo grado" << endl;
        cout << "13. Disequazione di primo grado" << endl;
        cout << "14. Equazione di secondo grado" << endl;
        cout << "0. Uscita" << endl;

        // L'utente inserisce la sua scelta
        cin >> scelta;

        // Iniziamo il blocco switch per eseguire l'operazione in base alla scelta dell'utente
        switch (scelta) {
        case 1:  // Somma
            cout << "Inserisci due numeri: ";
            cin >> num1 >> num2;  // Leggiamo i due numeri da sommare
            cout << "Risultato: " << num1 + num2 << endl;  // Sommiamo i numeri e stampiamo il risultato
            break;

        case 2:  // Sottrazione
            cout << "Inserisci due numeri: ";
            cin >> num1 >> num2;  // Leggiamo i due numeri da sottrarre
            cout << "Risultato: " << num1 - num2 << endl;  // Sottrai i numeri e stampa il risultato
            break;

        case 3:  // Moltiplicazione
            cout << "Inserisci due numeri: ";
            cin >> num1 >> num2;  // Leggiamo i due numeri da moltiplicare
            cout << "Risultato: " << num1 * num2 << endl;  // Moltiplichiamo i numeri e stampiamo il risultato
            break;

        case 4:  // Divisione
            cout << "Inserisci due numeri: ";
            cin >> num1 >> num2;  // Leggiamo i due numeri per la divisione
            if (num2 != 0) {  // Verifica se il divisore non è zero
                cout << "Risultato: " << num1 / num2 << endl;  // Eseguiamo la divisione e stampiamo il risultato
            }
            else {
                cout << "Errore: Divisione per zero!" << endl;  // Se il divisore è zero, stampiamo un errore
            }
            break;

        case 5:  // Potenza
            cout << "Inserisci la base e l'esponente: ";
            cin >> num1 >> num2;  // Leggiamo la base e l'esponente
            cout << "Risultato: " << pow(num1, num2) << endl;  // Calcoliamo e stampiamo il risultato della potenza
            break;

        case 6:  // Radice quadrata
            cout << "Inserisci il numero: ";
            cin >> num1;  // Leggiamo il numero per calcolare la radice quadrata
            cout << "Risultato: " << sqrt(num1) << endl;  // Calcoliamo e stampiamo la radice quadrata
            break;

        case 7:  // Logaritmo naturale
            cout << "Inserisci il numero: ";
            cin >> num1;  // Leggiamo il numero per calcolare il logaritmo naturale
            cout << "Risultato: " << log(num1) << endl;  // Calcoliamo e stampiamo il logaritmo naturale
            break;

        case 8:  // Funzioni trigonometriche
            cout << "Inserisci l'angolo in radianti: ";
            cin >> num1;  // Leggiamo l'angolo in radianti
            // Calcoliamo e stampiamo seno, coseno e tangente dell'angolo
            cout << "Seno: " << sin(num1) << ", Coseno: " << cos(num1) << ", Tangente: " << tan(num1) << endl;
            break;

        case 9:  // Area e Perimetro del Cerchio
            cout << "Inserisci il raggio: ";
            cin >> num1;  // Leggiamo il raggio del cerchio
            // Calcoliamo e stampiamo l'area (π * r^2) e il perimetro (2 * π * r) del cerchio
            cout << "Area: " << M_PI * num1 * num1 << ", Perimetro: " << 2 * M_PI * num1 << endl;
            break;

        case 10:  // Area e Perimetro del Quadrato
            cout << "Inserisci il lato: ";
            cin >> num1;  // Leggiamo il lato del quadrato
            // Calcoliamo e stampiamo l'area (lato^2) e il perimetro (4 * lato) del quadrato
            cout << "Area: " << num1 * num1 << ", Perimetro: " << 4 * num1 << endl;
            break;

        case 11:  // Area e Perimetro del Triangolo
            cout << "Inserisci la base e l'altezza: ";
            cin >> num1 >> num2;  // Leggiamo la base e l'altezza del triangolo
            // Calcoliamo e stampiamo l'area (base * altezza / 2) del triangolo
            cout << "Area: " << 0.5 * num1 * num2 << endl;
            // Leggiamo i tre lati del triangolo per calcolare il perimetro
            cout << "Inserisci i 3 lati del triangolo: ";
            cin >> num1 >> num2 >> num3;
            // Calcoliamo e stampiamo il perimetro (somma dei 3 lati)
            cout << "Perimetro: " << num1 + num2 + num3 << endl;
            break;

        case 12:  // Equazione di primo grado (ax + b = 0)
            cout << "Inserisci i valori di a e b (ax + b = 0): ";
            cin >> num1 >> num2;  // Leggiamo i coefficienti a e b
            if (num1 != 0) {  // Verifica che 'a' non sia zero, altrimenti non è un'equazione di primo grado
                cout << "Soluzione: x = " << -num2 / num1 << endl;  // Risolviamo l'equazione: x = -b / a
            }
            else {
                cout << "Equazione impossibile!" << endl;  // Se a = 0, l'equazione non è valida
            }
            break;

        case 13:  // Disequazione di primo grado (ax + b > 0)
            cout << "Inserisci i valori di a e b (ax + b > 0): ";
            cin >> num1 >> num2;  // Leggiamo i coefficienti a e b
            if (num1 > 0) {
                cout << "La soluzione è x > " << -num2 / num1 << endl;  // Se a > 0, la soluzione è x > -b / a
            }
            else if (num1 < 0) {
                cout << "La soluzione è x < " << -num2 / num1 << endl;  // Se a < 0, la soluzione è x < -b / a
            }
            else {
                cout << "Disequazione impossibile!" << endl;  // Se a = 0, la disequazione non ha soluzioni
            }
            break;

        case 14:  // Equazione di secondo grado (ax^2 + bx + c = 0)
            cout << "Inserisci i valori di a, b e c (ax^2 + bx + c = 0): ";
            cin >> num1 >> num2 >> num3;  // Leggiamo i coefficienti a, b e c
            delta = num2 * num2 - 4 * num1 * num3;  // Calcoliamo il discriminante (delta)
            if (delta > 0) {  // Se delta è maggiore di 0, ci sono due soluzioni reali
                double x1 = (-num2 + sqrt(delta)) / (2 * num1);  // Prima soluzione
                double x2 = (-num2 - sqrt(delta)) / (2 * num1);  // Seconda soluzione
                cout << "Le soluzioni sono: x1 = " << x1 << " e x2 = " << x2 << endl;
            }
            else if (delta == 0) {  // Se delta è 0, c'è una sola soluzione reale
                double x = -num2 / (2 * num1);  // Soluzione unica
                cout << "Soluzione unica: x = " << x << endl;
            }
            else {  // Se delta è negativo, non ci sono soluzioni reali
                cout << "Nessuna soluzione reale." << endl;
            }
            break;

        case 0:  // Uscita
            cout << "Uscita dal programma." << endl;  // Messaggio di uscita
            return 0;  // Uscita dal programma

        default:  // Se la scelta non è valida
            cout << "Scelta non valida!" << endl;  // Messaggio di errore
        }
    }

    return 0;  // Termina il programma
}
