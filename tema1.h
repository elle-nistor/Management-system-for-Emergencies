#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max 50 units
typedef struct Unit {
    
    //info
    int id;
    char type; // A - Police, B - Firefighters, C - Ambulance
    int availability; // 0 - 1
    //-----------------------------------
    struct Unit *prev, *next;

} Unit, *LUnit;

typedef struct Incident{

    // info 
    int id;
    char priority[7]; // low - medium - high
    char *description;
    char status[11]; // queued - intervened - solved
    //-----------------------------------
    struct Incident *prev, *next;

} Incident, *LIncident ;

typedef struct Intervention{

    //info
    struct Incident *incident;
    struct Unit *unit;
    //-----------------------------------
    struct Intervention *prev, *next;

} Intervention, *LIntervention;

//-------------------------

typedef struct QNode{
    struct Incident *incident;
    struct QNode *next;
} QNode, *PQNode;

typedef struct PriorityQue{
    PQNode front;
    PQNode rear;
} PriorityQue, *PQueue;

//-------------------------

typedef struct UNode{
    struct Unit *unit;
    struct UNode *next;
} UNode, *AUNode;

typedef struct UnitsQue{
    AUNode front;
    AUNode rear;
} UnitsQue, *UQueue;

//-------------------------

// typedef struct system{
//     LUnit units;
//     LIncident incidents;
//     LIntervention interventions;
// } Tsystem;

LUnit AlocateCell_Unit (int id, char type, 
                        int availability);
LUnit Init_Unit();
void Print_Units(LUnit s);
void Free_Units (LUnit *s);
LIncident AlocateCell_Incident (int id, char priority[], 
                                char *description, char status[]);
LIncident Init_Incident();
void Print_Incidents(LIncident s);
void Free_Incidents (LIncident *s);
LIntervention AlocateCell_Intervention (LIncident incident,
                                        LUnit unit);
LIntervention Init_Intervention();
void Print_Intervention(LIntervention s);
void Free_Interventions (LIntervention *s);
void add_incindent(FILE *fin, LIncident s_incident, PQueue high, 
                    PQueue medium, PQueue low);
void command_manager(char command[], FILE *fin, FILE *fout, LIncident s_incident,
                    PQueue high, PQueue medium, PQueue low, UQueue units);
void scan_input_file(FILE *fin, FILE *fout, int *total_units,
                    int *total_commands, LUnit s_unit, LIncident s_incident, 
                    PQueue high, PQueue medium, PQueue low, UQueue units);

PQueue Init_Queue();
void add_incident_to_queue(PQueue q, LIncident s);
void Print_Priority_Queue(PQueue q);
void Free_Priority_Queue(PQueue *q_ptr);

UQueue Init_Units_Queue();
void add_unit_to_queue(LUnit u, UQueue units);
void Free_Units_Queue(UQueue *q_ptr);
int check_units_availability(UQueue q);