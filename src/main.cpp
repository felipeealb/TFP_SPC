#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <string>

#include "graph.h"

#include "reader.h"
#include "TFP_SCP.h"
#include "matching.h"
#include "TFP_SCP_simp.h"
using namespace std;

double get_cpu_time(){
    struct timeval time;
    if(gettimeofday(&time,nullptr)){
        // HANDLE ERROR
        return 0;
    }else{
        return static_cast<double>(time.tv_sec) + static_cast<double>(time.tv_usec*0.000001); //microsegundos
    }
}

int main(int argc, char** argv){


    cout << "You have entered " << argc << " arguments:"
         << "\n";
 
    // for (int i = 0; i < argc; ++i)                                   
    //     cout << argv[i] << "\n";


    string prob;
    int gclass,ctype;
    const char* SEC; const char* METHOD; char* instType; char* gtype;
    int n;
    // Parameters parsing
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-prob") == 0) {
                prob = argv[i + 1];
            } else if (strcmp(argv[i], "-n") == 0) {
                n = stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-gclass") == 0) {
                gclass = stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-ctype") == 0) {
                ctype = stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-itype") == 0) {
                instType = argv[i + 1];
            } else if (strcmp(argv[i], "-sec") == 0) {
                SEC = argv[i + 1];
            } else if (strcmp(argv[i], "-method") == 0) {
                METHOD = argv[i + 1];
            } else if (strcmp(argv[i], "-gtype") == 0) {
                gtype = argv[i + 1];
            } else {
                cerr << "Unknown parameter: " << argv[i] << endl;
                exit(1);
            }
        }
    }

    // Parameters check
    if (prob.empty()) {
        cerr << "[ERROR] No problem defined\n";
        exit(1);
    }else if (n == 0){
        cerr << "[ERROR] No number of vertices\n";
        exit(1);
    }
    // } else if (dist_matrix_filename.empty()) {
    //     cerr << "Distance matrix -dm not given.\n";
    //     exit(1);
    // } else if (labeled_weights_filename.empty()) {
    //     cerr << "Customer weights -w not given.\n";
    //     exit(1);
    // } else if (capacities_filename.empty()) {
    //     cerr << "Location capacities -c not given.\n";
    //     exit(1);
    // }



    // cout << "Instance: " << endl;
    // cout << "Problem: " << prob << endl;
    // cout << "No. vertices: " << n << endl;
    // cout << "Graph class: " << gclass << endl;
    // cout << "Class type: " << ctype << endl;
    // cout << "Graph instance type: " << instType << endl;
    // cout << "Graph type: " << gtype << endl;
    // cout << "SEC:" << SEC << endl;
    // cout << "Method: " << METHOD << endl;



    // time
    double cpu_start, cpu_final;

    // instance
    // Reader rd(false,n, gclass,ctype, instType);

    Reader rd(false,n, gclass,ctype, instType,"directed");
    rd.show();
    exit(-1);
    // Reader rd(false,14, 1,1, "random");
    // rd.show();
    Graph GRAPH = Graph(rd.G, rd.num_vertices, rd.G_type);

    if (GRAPH.isConnected()){

        
        // TFP_SCP
        if(prob == "TFP_SCP"){
            cout << prob << endl;
        
            cpu_start = get_cpu_time();

            TFP_SCP prob = TFP_SCP(&rd,SEC); 
            prob.solveILP();

            cpu_final = get_cpu_time(); 

            prob.saveResults((cpu_final-cpu_start));

        }

        // TFP_SCP_simplified
        if(prob == "TFP_SCP_simp"){
            
        
            cpu_start = get_cpu_time();
            
            // Graph GRAPH = Graph(rd.G, rd.num_vertices, rd.G_type);
            TFP_SCP_SIMP prob_simp = TFP_SCP_SIMP(&rd,GRAPH,METHOD);

            
            prob_simp.solveILP();
            
            cpu_final = get_cpu_time(); 

            prob_simp.saveResults((cpu_final-cpu_start));

        }

    }else{
        cout << "[ERROR] Graph is not connected" << endl;
    }

    return 0;
}
