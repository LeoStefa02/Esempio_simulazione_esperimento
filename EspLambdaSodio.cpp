#include "./EspLambdaSodio.h"
#include <iostream>
#include <cmath>

using namespace std;

EspLambdaSodio::EspLambdaSodio()
	: m_rgen(1), m_d(20e-6), m_m(1), m_sigmatheta(1e-3)
{

	m_lambda_input = 589e-9;
	m_th_0_input = 0;
	m_th_m_input = asin((m_lambda_input / m_d) * m_m) + m_th_0_input;
}

EspLambdaSodio::EspLambdaSodio(double sigmatheta)
	: m_rgen(1), m_d(20e-6), m_m(1), m_sigmatheta(sigmatheta)
{

	m_lambda_input = 589e-9;
	m_th_0_input = 0;
	m_th_m_input = asin((m_lambda_input / m_d) * m_m) + m_th_0_input;
}

void EspLambdaSodio::set_m(unsigned int m)
{
	m_m = m;
	m_th_m_input = asin((m_lambda_input / m_d) * m) + m_th_0_input;
}

void EspLambdaSodio::esegui()
{
	m_th_0_misurato = m_rgen.gauss(m_th_0_input, m_sigmatheta);
	m_th_m_misurato = m_rgen.gauss(m_th_m_input, m_sigmatheta);
}

void EspLambdaSodio::analizza()
{
	m_lambda_misurato = (m_d / m_m) * sin(m_th_m_misurato - m_th_0_misurato);
}