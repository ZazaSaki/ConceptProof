#include "Evaluator.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[])
{   

//---------------------------------Needed Resources---------------------------------
    Resource_Map ress;

    ress[CORES] = 4;
    ress[CPU] = 4;
    ress[CPU_SPEED] = 4;
    ress[RAM] = 4;
    ress[iGPU] = 1;
    ress[GPU] = 1;


    Resource_Map ress2;

    ress2[CORES] = 1; // diference
    ress2[CPU] = 4;
    ress2[CPU_SPEED] = 4;
    ress2[RAM] = 4;
    ress2[iGPU] = 1;
    ress2[GPU] = 1;
    
    //ress2[0] = 1; // diference
    Evaluator ev(ress);

    //cout << "none existing ressource : " <<ress[TERMOMETER] << endl << endl;
    cout << "existing ressource cpu : " <<ress[CPU] << endl << endl;

    //create a vector of doubles from 3 to 9 in steps of 3
    vector<double> grades = {3, 6, 9};

    //call the procedural_weighted_average_test method
    cout << " Procedural weighted average test : " ;
    cout << ((ev.procedural_weighted_average_test(grades)==1)?"passed":"failed") << endl << endl;

    //has_ressources test
    cout << " Has own components : " << ((ev.has_ressources(ress) == 1) ? "passed":"failed") << endl << endl;
    cout << " Has own components with slight change : " << ((ev.has_ressources(ress2) == 0) ? "passed":"failed") << endl << endl;

    //ress2.size() != ress.size()
    ress2[TERMOMETER] = 1;
    cout << " Has diferent set components : " << ((ev.has_ressources(ress2) == 0) ? "passed":"failed") << endl << endl;

    // has own components
    cout << " Keeps having own components : " << ((ev.has_ressources(ress) == 1) ? "passed":"failed")<< endl << endl;

    // ress2 == ress;
    ress2.erase(TERMOMETER);
    ress2[CORES] = 4;
    cout << " Keeps having similar components : " << ((ev.has_ressources(ress2) == 1) ? "passed":"failed") << endl << endl;



//---------------------------------Proximity---------------------------------


    Network_Map ns;

    ns[HOPS] = 1;
    ns[RTT] = 4;
    ns[PVD] = 4;
    ns[MAX_PVD] = 4;
    ns[PVD_TOLERANCE] = 4;
    ns[PACKET_LOSS] = 4;
    ns[PACKET_LOSS_TRESHOLD] = 8;
    ns[PACKET_LOSS_MODE] = STEEP;

    cout << "Proximity criteria calculator consistensy test : " <<endl;
    
    for (int i = 0; i < 1000000; i++)
    {
        ns[HOPS] = rand() % 2 + 1;
        ns[RTT] = rand() % 200 + 1;
        ns[PVD] = rand() % 5 + 1;
        ns[PVD_TOLERANCE] = ((double)(rand() % 100))/100;
        ns[MAX_PVD] = ns[PVD]*1.1;
        ns[PACKET_LOSS] = rand() % 10 + 1;
        ns[PACKET_LOSS_TRESHOLD] = ns[PACKET_LOSS]*(((double)(rand() % 50))/100 + 1);
        ns[PACKET_LOSS_MODE] = rand() % 3 + 1;

        
        double CCC = ev.proximity_criteria_calculator_test(ns) ;
        //cout << "Proximity criteria calculator test : " << endl << ev.proximity_criteria_calculator_test(ns) << endl << endl;

        if (CCC>1)
        {
            // print ns values
            for (auto i = ns.begin(); i != ns.end(); i++)
            {
                cout << i->first << " : " << i->second << endl; 
            }

            

            cout << "FAILED" << endl;

            break;
        }
        
    

    }

    cout << "passed" << endl << endl;
    


    cout << "BID criteria calculator consistensy test : " <<endl;
    for (int i = 0; i < 1000000; i++)
    {
        ns[HOPS] = rand() % 2 + 1;
        ns[RTT] = rand() % 200 + 1;
        ns[PVD] = rand() % 5 + 1;
        ns[PVD_TOLERANCE] = ((double)(rand() % 100))/100;
        ns[MAX_PVD] = ns[PVD]*1.1;
        ns[PACKET_LOSS] = rand() % 10 + 1;
        ns[PACKET_LOSS_TRESHOLD] = ns[PACKET_LOSS]*(((double)(rand() % 50))/100 + 1);
        ns[PACKET_LOSS_MODE] = rand() % 3 + 1;

        
        double CCC = ev.bid_value(ress, ns, 3);
        //cout << "bid : " << endl << ev.bid_value(ress,ns,3) << endl << endl;

        if (CCC>1)
        {
            // print ns values
            for (auto i = ns.begin(); i != ns.end(); i++)
            {
                cout << i->first << " : " << i->second << endl; 
            }

            

            cout << "FAILED" << endl;

            break;
        }
        
    

    }

    cout << "passed" << endl << endl;


    // history_criteria_calculator_test
    // cout << "History criteria calculator test : " << ev.history_criteria_calculator_test() << endl << endl;
    for (int i = 0; i < 10; i++)
    {
        ev.history_criteria_calculator_test();          
    }
    
    // // print ns values
    // for (auto i = ns.begin(); i != ns.end(); i++)
    // {
    //     cout << i->first << " : " << i->second << endl; 
    // }
    
    
    // // print proximity_criteria_calculator_test
    // cout << "Proximity criteria calculator test : " << ev.proximity_criteria_calculator_test(ns) << endl << endl;
    

    return 0;
}
