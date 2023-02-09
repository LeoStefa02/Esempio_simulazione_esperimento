#ifndef _Esp_LambdaSodio_h_
#define _Esp_LambdaSodio_h_

#include "./FunzioniUtili/RandomGen.h"
using namespace std;

class EspLambdaSodio
{

public:
    EspLambdaSodio();
    EspLambdaSodio(double sigmatheta);
    ~EspLambdaSodio() { ; };

    void esegui();
    void analizza();

    double get_lambda_mis() { return m_lambda_misurato; }
    double get_th_0_mis() { return m_th_0_misurato; }
    double get_th_m_mis() { return m_th_m_misurato; }

    void set_sigma_theta(double sigmatheta)
    {
        m_sigmatheta = sigmatheta;
    }

    void set_m(unsigned int m);

private:
    // generatore di numeri casuali

    RandomGen m_rgen;

    // parametri dell'apparato sperimentale
    double m_sigmatheta;
    unsigned int m_m;
    double m_d;

    // valori delle quantita' misurabili :
    // input    : valori assunti come ipotesi nella simulazione
    // misurato : valore dopo la simulazione di misura
    double m_lambda_input, m_lambda_misurato;
    double m_th_0_input, m_th_0_misurato;
    double m_th_m_input, m_th_m_misurato;
};

#endif