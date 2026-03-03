#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Structură pentru stocarea rezultatelor
struct ResultatMetoda {
    string nume;
    double radacina;
    double valoare_functie;
    int iteratii;
    int eval_f;
    int eval_df;
};

// Funcțiile pentru ambele probleme
double f_a(double x) {
    return sqrt(x + 1) - 1.0 / x;
}

double df_a(double x) {
    return 1.0 / (2.0 * sqrt(x + 1)) + 1.0 / (x * x);
}

double f_b(double x) {
    return x * x * x + 34 * x + 23;
}

double df_b(double x) {
    return 3 * x * x + 34;
}

// Metoda înjumătățirii intervalului (bisecție)
double bisection(double (*f)(double), double a, double b, double eps, int& iterations) {
    iterations = 0;
    double c;

    while ((b - a) / 2.0 > eps) {
        c = (a + b) / 2.0;
        iterations++;

        if (fabs(f(c)) < eps) {
            return c;
        }

        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    return (a + b) / 2.0;
}

// Metoda aproximațiilor succesive
double fixedPoint(double (*f)(double), double (*phi)(double), double x0, double eps, int& iterations, int& f_evals) {
    iterations = 0;
    f_evals = 0;
    double x = x0;
    double x_new;

    do {
        x_new = phi(x);
        iterations++;
        f_evals++;

        if (iterations > 10000) {
            cout << "Metoda nu converge!" << endl;
            return x_new;
        }
    } while (fabs(x_new - x) > eps && (x = x_new, true));

    return x_new;
}

// Metoda Newton (tangentelor)
double newton(double (*f)(double), double (*df)(double), double x0, double eps, int& iterations, int& f_evals, int& df_evals) {
    iterations = 0;
    f_evals = 0;
    df_evals = 0;
    double x = x0;
    double x_new;

    do {
        double fx = f(x);
        double dfx = df(x);
        f_evals++;
        df_evals++;

        if (fabs(dfx) < 1e-10) {
            cout << "Derivata este prea mică!" << endl;
            return x;
        }

        x_new = x - fx / dfx;
        iterations++;

        if (iterations > 10000) {
            cout << "Metoda nu converge!" << endl;
            return x_new;
        }
    } while (fabs(x_new - x) > eps && (x = x_new, true));

    return x_new;
}

// Metoda secantelor
double secant(double (*f)(double), double x0, double x1, double eps, int& iterations, int& f_evals) {
    iterations = 0;
    f_evals = 0;
    double x_prev = x0;
    double x_curr = x1;
    double x_new;

    do {
        double f_prev = f(x_prev);
        double f_curr = f(x_curr);
        f_evals += 2;

        if (fabs(f_curr - f_prev) < 1e-10) {
            cout << "Diviziune la zero în metoda secantelor!" << endl;
            return x_curr;
        }

        x_new = x_curr - f_curr * (x_curr - x_prev) / (f_curr - f_prev);
        iterations++;

        x_prev = x_curr;
        x_curr = x_new;

        if (iterations > 10000) {
            cout << "Metoda nu converge!" << endl;
            return x_new;
        }
    } while (fabs(x_curr - x_prev) > eps);

    return x_new;
}

// Funcții phi pentru metoda aproximațiilor succesive
double phi_a(double x) {
    return 1.0 / sqrt(x + 1);
}

double phi_b(double x) {
    return -(x * x * x + 23) / 34.0;
}

void separareRadacini(double (*f)(double), double a, double b, double pas) {
    cout << "\n=== SEPARAREA RĂDĂCINILOR ===" << endl;
    cout << "Interval: [" << a << ", " << b << "]" << endl;
    cout << "\nIntervale unde există rădăcini:" << endl;

    int nr_intervale = 0;
    for (double x = a; x < b; x += pas) {
        if (f(x) * f(x + pas) < 0) {
            cout << "[" << fixed << setprecision(2) << x << ", " << x + pas << "]";
            cout << " - f(" << x << ") = " << f(x) << ", f(" << x + pas << ") = " << f(x + pas) << endl;
            nr_intervale++;
        }
    }

    if (nr_intervale == 0) {
        cout << "Nu s-au găsit schimbări de semn în intervalul dat." << endl;
    }
}

void afiseazaTabelComparativ(vector<ResultatMetoda>& rezultate, string titlu) {
    cout << "\n\n╔═══════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  " << left << setw(71) << titlu << "  ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════════════════════╝" << endl;

    cout << "\n┌──────────────────┬─────────────────────┬─────────────────┬──────────┐" << endl;
    cout << "│ Metoda           │ Radacina aproximata │ F(rad)          │ Iteratii │" << endl;
    cout << "├──────────────────┼─────────────────────┼─────────────────┼──────────┤" << endl;

    for (const auto& rez : rezultate) {
        cout << "│ " << left << setw(16) << rez.nume << " │ ";
        cout << right << fixed << setprecision(10) << setw(19) << rez.radacina << " │ ";
        cout << scientific << setprecision(6) << setw(15) << rez.valoare_functie << " │ ";
        cout << setw(8) << rez.iteratii << " │" << endl;
    }

    cout << "└──────────────────┴─────────────────────┴─────────────────┴──────────┘" << endl;
}

void rezolvaProblema(string nume, string prefix, double (*f)(double), double (*df)(double), double (*phi)(double), double a, double b) {
    cout << "\n\n╔═══════════════════════════════════════════════════════╗" << endl;
    cout << "║        PROBLEMA: " << left << setw(35) << nume << "║" << endl;
    cout << "╚═══════════════════════════════════════════════════════╝" << endl;

    vector<ResultatMetoda> rezultate;

    // 1. Separarea rădăcinilor
    separareRadacini(f, a, b, 0.5);

    // 2. Metoda bisecției cu ε = 10^-2
    int iter_bis;
    double x_bisect = bisection(f, a, b, 1e-2, iter_bis);
    cout << "\n=== BISECȚIE (ε = 10^-2) ===" << endl;
    cout << "Rădăcina: x = " << fixed << setprecision(4) << x_bisect << endl;
    cout << "Iterații: " << iter_bis << endl;
    cout << "f(x) = " << scientific << setprecision(6) << f(x_bisect) << endl;

    ResultatMetoda rez_bisect;
    rez_bisect.nume = prefix + "-bisect";
    rez_bisect.radacina = x_bisect;
    rez_bisect.valoare_functie = f(x_bisect);
    rez_bisect.iteratii = iter_bis;
    rez_bisect.eval_f = iter_bis * 2;
    rez_bisect.eval_df = 0;
    rezultate.push_back(rez_bisect);

    double x0 = x_bisect;

    cout << "\n=== METODE CU PRECIZIE ε = 10^-6 ===" << endl;
    cout << "Punct initial: x0 = " << fixed << setprecision(6) << x0 << endl;

    // 3a. Metoda aproximațiilor succesive (ε = 10^-6)
    int iter_fp, f_evals_fp;
    double x_fp = fixedPoint(f, phi, x0, 1e-6, iter_fp, f_evals_fp);

    ResultatMetoda rez_fp;
    rez_fp.nume = prefix + "-fp";
    rez_fp.radacina = x_fp;
    rez_fp.valoare_functie = f(x_fp);
    rez_fp.iteratii = iter_fp;
    rez_fp.eval_f = f_evals_fp;
    rez_fp.eval_df = 0;
    rezultate.push_back(rez_fp);

    // 3b. Metoda Newton (ε = 10^-6)
    int iter_newton, f_evals_newton, df_evals_newton;
    double x_newton = newton(f, df, x0, 1e-6, iter_newton, f_evals_newton, df_evals_newton);

    ResultatMetoda rez_newton;
    rez_newton.nume = prefix + "-newton";
    rez_newton.radacina = x_newton;
    rez_newton.valoare_functie = f(x_newton);
    rez_newton.iteratii = iter_newton;
    rez_newton.eval_f = f_evals_newton;
    rez_newton.eval_df = df_evals_newton;
    rezultate.push_back(rez_newton);

    // 3c. Metoda secantelor (ε = 10^-6)
    int iter_secant, f_evals_secant;
    double x_secant = secant(f, x0 - 0.1, x0 + 0.1, 1e-6, iter_secant, f_evals_secant);

    ResultatMetoda rez_secant;
    rez_secant.nume = prefix + "-secantei";
    rez_secant.radacina = x_secant;
    rez_secant.valoare_functie = f(x_secant);
    rez_secant.iteratii = iter_secant;
    rez_secant.eval_f = f_evals_secant;
    rez_secant.eval_df = 0;
    rezultate.push_back(rez_secant);

    // Afișează tabelul comparativ
    afiseazaTabelComparativ(rezultate, "TABEL COMPARATIV - " + nume);
}

int main() {
    cout << fixed << setprecision(6);

    cout << "╔════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              LUCRAREA DE LABORATOR NR.1                                        ║" << endl;
    cout << "║   REZOLVAREA NUMERICĂ A ECUAȚIILOR ALGEBRICE ȘI TRANSCENDENTE                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════╝" << endl;

    // Problema a) sqrt(x+1) - 1/x = 0
    rezolvaProblema("a) sqrt(x+1) - 1/x = 0", "f1", f_a, df_a, phi_a, 0.1, 5.0);

    // Problema b) x^3 + 34x + 23 = 0
    rezolvaProblema("b) x^3 + 34x + 23 = 0", "f2", f_b, df_b, phi_b, -5.0, 5.0);

    return 0;
}