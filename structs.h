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
void add_incindent(FILE *fin, LIncident s_incident);
void command_manager (char command[], FILE *fin, LIncident s_incident);
void scan_input_file(FILE *fin, int *total_units,
                    int *total_commands, LUnit s_unit, LIncident s_incident);