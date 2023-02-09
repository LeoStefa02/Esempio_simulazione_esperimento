#include "FunzioniUtili/funzioni.h"
#include "EspLambdaSodio.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH1.h"
#include <vector>
#include "TAxis.h"
#include <iomanip>
#include "FunzioniUtili/RandomGen.h"

#define NUMERO_MASSIMI 5
#define N_SIMULAZIONI 10000

using namespace std;

int main() {

    TApplication app("", 0, 0);

    TH1D ld1("lambda dist 1", "lambda dist 1", 100, 0., 0.);
    TH1D ld2("lambda dist 2", "lambda dist 2", 100, 0., 0.);
    TH1D ld3("lambda dist 3", "lambda dist 3", 100, 0., 0.);
    TH1D ld4("lambda dist 4", "lambda dist 4", 100, 0., 0.);
    TH1D ld5("lambda dist 5", "lambda dist 5", 100, 0., 0.);

    EspLambdaSodio esp;
    vector<TH1D> dists_lambda {ld1, ld2, ld3, ld4, ld5};
    vector<double> media_lambda;
    vector<double> RMS_lambda;

    TCanvas canvas1, canvas2;
    canvas1.Divide(3, 2);

    TGraph error_graph;

    for(int i = 0; i < NUMERO_MASSIMI; i++) {
        dists_lambda[i].GetXaxis()->SetTitle("Lambda");
        dists_lambda[i].GetYaxis()->SetTitle("N Lambda");
        dists_lambda[i].StatOverflows(kTRUE);
    }

    for(int k= 0; k < NUMERO_MASSIMI; k++) {
        esp.set_m(k + 1);
        vector<double> v;

        for(int i = 0; i < N_SIMULAZIONI; i++) {
            esp.esegui();
            esp.analizza();
            v.push_back(esp.get_lambda_mis());
            dists_lambda[k].Fill(esp.get_lambda_mis());
        }

        error_graph.AddPoint(k + 1, pow(varianza<double>(v.begin(), v.end()), 0.5));

        canvas1.cd(k + 1);
        dists_lambda[k].Draw();

        media_lambda.push_back(media<double>(v.begin(), v.end()));
        RMS_lambda.push_back(dists_lambda[k].GetRMS());
    }

    canvas2.cd();
    error_graph.GetXaxis()->SetTitle("N massimo");
    error_graph.GetYaxis()->SetTitle("std dev");
    error_graph.SetMarkerStyle(20);
    error_graph.Draw("AP");

    cout << endl<< setw(5) << "massimo" << setw(10) << "media" << setw(10) << "RMS" << endl << endl;

    for(int i = 0; i < NUMERO_MASSIMI; i++) {
        cout << setw(4) << setprecision(4) << i + 1;
        cout << setw(15) << setprecision(4) << media_lambda[i];
        cout << setw(12) << setprecision(4) << RMS_lambda[i];
        cout << endl << endl;
    }

    app.Run();

}