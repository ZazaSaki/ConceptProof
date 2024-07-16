#include "./Evaluator.h"
#include <iostream>
using namespace std;
// instantiate the object
Evaluator::Evaluator(Resource_Map& my_ressources) : _my_ressources(my_ressources) {
    
    // extract the existing components list
    _ressources_list = extractKeys(my_ressources);
    
}

// bid_value
double Evaluator::bid_value(Resource_Map& Needed_resources, Network_Map& network_data, int priority){
    double c1_ressources = has_ressources(Needed_resources)
    , c2_proximity = proximity_criteria_calculator(network_data)
    , c3_historic = 0   
    , c4_curent_ressources = 0
    , c5_fairness = fairness_bid(priority);
    

    
    return c1_ressources * ((c2_proximity + c3_historic)/2) * c4_curent_ressources * c5_fairness;
};




//------------------------------------------------------------
// ----------------Existing ressources checker----------------
//Ressources checker
double Evaluator::has_ressources(Resource_Map& list){
    //extract the keys from the list
    std::vector<Hadware_Resources> keys = extractKeys(list);

    /* Verbose : double Evaluator::has_ressources(RessourceMap& list){
        //print both sizes
            cout << endl;
            cout << "list size : " << list.size() << endl;
            cout << "_my_ressources size : " << _my_ressources.size() << endl;
    //*/


    // Checking Number of Components required
    if (list.size() > get_my_ressources_size())
    {   

        /* Verbose : double Evaluator::has_ressources(RessourceMap& list){
 
        //print not the same size
        cout << "given list is bigger than own components' list" << endl;
        //*/

        return 0;
    }

    // Checking if the components are available
    for (int packet_loss_mode = 0; packet_loss_mode < keys.size(); packet_loss_mode++)
    {
        if(get_my_ressource(keys[packet_loss_mode]) != list[keys[packet_loss_mode]]) return 0;
    }
    
    return 1;
}


//------------------------Measuring ressources aviability------------------------
    
    // C4 Criteria calculator
    double Evaluator::procedural_weighted_average(std::vector<double> grades, int divisor, int bigger_weight){
        
        //starting from the end of the vector
        double sum = grades.back();
        

        /* Verbose : procedural_weighted_average 
        cout << sum << endl;
        //*/
        
        
        //loop through the vector starting from the second to last element
        //applying the formula P(pi) = (1/3)pi-1 + (2/3)pi
        for (int packet_loss_mode = grades.size()-2; packet_loss_mode > -1; packet_loss_mode--){
            
            /* Verbose : procedural_weighted_average 
            cout << "formula" << sum << " = " << sum << " * (" << divisor - bigger_weight << ") / " << divisor << " + (" << bigger_weight << " / " << divisor << ") * " << grades[packet_loss_mode] << endl;
            //*/
            sum = sum * (divisor-bigger_weight)/divisor;
            
            sum += (bigger_weight/divisor) * grades[packet_loss_mode];
            

            /* Verbose : procedural_weighted_average 
            cout << "irteration : "<< packet_loss_mode ;
            cout << " sum(" << sum << ")" << endl;
            //*/
            
            
        }
        return sum;
    };



//-------------------------------------------------------------------------------
//-----------------------------------Proximity-----------------------------------
    //proximity_bid
    double Evaluator::proximity_bid(){
        proximity_data_manager();

        //proximity_criteria_calculator();
        
        return 0;
    };

    //proximity_data_manager
    void Evaluator::proximity_data_manager(){
        
    };

    double Evaluator::proximity_criteria_calculator_test(Network_Map& data){
        return proximity_criteria_calculator(data);
    }

    //proximity_criteria_calculator
    double Evaluator::proximity_criteria_calculator(Network_Map& map){

    /* Verbose :Evaluator::proximity_criteria_calculator_test
        //print rtt
        cout << "RTT : " << rtt(map[HOPS],map[RTT])<< endl;

        //print hops
        cout << "Hops : " << hops(map[HOPS])<< endl;

        //print pdvEvaluator
        cout << "PVD : " << pvdEvaluator(map[PVD],map[MAX_PVD],map[PVD_TOLERANCE])<< endl;

        //print packetLoss
        cout << "Packet Loss : " << packetLoss(map[PACKET_LOSS],map[PACKET_LOSS_TRESHOLD], map[PACKET_LOSS_MODE])<< endl;
    //*/
        //int hops, double rtt, double pvd, double max_pvd, double tolerance, double package_loss_treshold, double package_loss_treshold, int packet_loss_mode
        return (rtt(map[HOPS],map[RTT]) + hops(map[HOPS]) + pvdEvaluator(map[PVD],map[MAX_PVD],map[PVD_TOLERANCE]) + packetLoss(map[PACKET_LOSS],map[PACKET_LOSS_TRESHOLD], map[PACKET_LOSS_MODE]))/4;
    };

    //RTT and Hops
    double Evaluator::rtt(double hops,double rtt){
        if(hops<=rtt)return 1;
        else return pow(2,-((hops-rtt)/rtt));
    };

    //Hops
    double Evaluator::hops(double hops){
        return pow(2,-((int)hops));
    };

    //PVD
    double Evaluator::pvdEvaluator(double pvd,double max_pvd, double tolerance){
        if (pvd <= max_pvd)return 1;
        else if (pvd > max_pvd && pvd <= max_pvd*tolerance)return (pvd-max_pvd)/(tolerance*max_pvd) + 1;
        else return 0;
    };

    //Packet Loss
    double Evaluator::packetLoss(double packet_loss,double package_loss_treshold, int packet_loss_mode){
        if(packet_loss<=package_loss_treshold)return fii(packet_loss,package_loss_treshold, packet_loss_mode);
        else return 0;
    };

    //fii
    double Evaluator::fii(double packet_loss, double package_loss_treshold, int packet_loss_mode){
        switch (packet_loss_mode)
        {   
            //step
            case 1:
                return (0.75/(package_loss_treshold*package_loss_treshold))*(packet_loss-package_loss_treshold)*(packet_loss-package_loss_treshold)+0.25;
                break;
            //linear
            case 2:
                return (-0.75*pow(package_loss_treshold,-1)*packet_loss)+1;
                break;  
            //smooth
            case 3:
                return -(0.75/(package_loss_treshold*package_loss_treshold))*(packet_loss*packet_loss)+1;
                break;
        }

        throw "Invalid packet_loss_mode value";
    };

//------------------------------------History------------------------------------

    //history_criteria_calculator
    double Evaluator::history_criteria_calculator(){
            //A1 = requirements req/total req * 100
            //A2 = non used reservations %
            //A3 = avg duration last admition/avg general allowed admition duration 
            //A4 = resource reservation/all admitions * 100
            return 0;
    };


//------------------------------------Fairness------------------------------------
int Evaluator::fairness_bid(int priority){
    return double(priority)/MAX_PRIORITY;
};

//-------------------------------------------------------------------
//------------------------getters and setters------------------------
    double Evaluator::get_my_ressources(){
        return 0;
    };

    double Evaluator::get_my_ressource(Hadware_Resources ressource){
        
        //check if the ressource exists
        if (_my_ressources.count(ressource)==0)return 0;
        
        else return _my_ressources[ressource];
    };

    int Evaluator::get_my_ressources_size(){
        return _my_ressources.size();
    };

    void Evaluator::set_my_ressource(Hadware_Resources ressource, double value){
        if(value == 0) _my_ressources.erase(ressource);
        else _my_ressources[ressource] = value;
    };

    void Evaluator::set_my_ressources(Resource_Map ressources){
        //iterate the ressources
        for (const auto& pair : ressources) {
            //set the ressource
            set_my_ressource(pair.first, pair.second);
        }
        
    };


//-------------------------------------------------------------------
//------------------Auxiliar functions------------------
// procedural_weighted_average_test
    double Evaluator::procedural_weighted_average_test(std::vector<double> grades, int divisor, int bigger_weight){
        return procedural_weighted_average(grades, divisor, bigger_weight);
    };

// Function to extract keys from the map
    std::vector<Hadware_Resources> Evaluator::extractKeys(const Resource_Map& myMap) {
        std::vector<Hadware_Resources> keys;
        for (const auto& pair : myMap) {
            keys.push_back(pair.first);
        }
        return keys;
    }

