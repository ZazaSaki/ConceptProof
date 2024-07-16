#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include "Ressources.h"
#include <cmath>
#define MAX_PRIORITY 8

// Include any necessary headers here

class Evaluator {
public:
    //object contructor
        Evaluator(Resource_Map&);

    //methods
        double has_ressources(Resource_Map&);
        double bid_value(Resource_Map&, Network_Map&, int=1);
    
    

    //getters and setters
        double get_my_ressources();
        double get_my_ressource(Hadware_Resources);

        int get_my_ressources_size();

        void set_my_ressource(Hadware_Resources, double);
        void set_my_ressources(Resource_Map);

    //tests
    double procedural_weighted_average_test(std::vector<double>, int=3, int=2);
    double proximity_criteria_calculator_test(Network_Map&);

private:
    // Add any private members or helper methods here
    double procedural_weighted_average(std::vector<double>, int=3, int=2);
    std::vector<Hadware_Resources> extractKeys(const Resource_Map&);
    //double ;
    Resource_Map _my_ressources;
    std::vector<Hadware_Resources> _ressources_list = {};

    //proximity
    double rtt(double,double);
    double hops(double);
    double pvdEvaluator(double,double, double);
    double packetLoss(double,double, int);
    double fii(double, double, int);
    double proximity_criteria_calculator(Network_Map&);
    double history_criteria_calculator();
    double proximity_bid();
    void proximity_data_manager();

    //fairness
    int fairness_bid(int);

};

#endif // EVALUATOR_H