#include <map>

// ressouces enumerator
enum Hadware_Resources {
    OS,
    CORES,
    CPU,
    CPU_SPEED,
    RAM,
    STORAGE,
    iGPU,
    GPU,
    GPU_SPEED,
    CUDA,
    VRAM,
    NPU,
    BANDWITH,
    SENSORS,
    CAMERA,
    MICROPHONE,
    LDR,
    TERMOMETER
};

enum Network_Status {
    HOPS,
    RTT, 
    PVD,
    MAX_PVD,
    PVD_TOLERANCE,
    PACKET_LOSS,
    PACKET_LOSS_TRESHOLD,
    PACKET_LOSS_MODE,
};

enum Packet_Loss_Mode{
    STEEP = 1,
    LINEAR = 2,
    SMOOTH = 3
};

class Evaluator;
typedef std::map<Hadware_Resources, double> Resource_Map;
typedef std::map<Network_Status, double> Network_Map;
