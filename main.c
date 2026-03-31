#include "tema1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char command[25];
    int total_units, total_commands;

    // initiate lists & sentinels
    LUnit s_unit = NULL;
    LIncident s_incident = NULL;
    LIntervention s_intervention = NULL;
    s_unit = Init_Unit();
    s_incident = Init_Incident();
    s_intervention = Init_Intervention();

    //initiate queues - interventions & units availability
    PQueue queue_high = Init_Queue();
    PQueue queue_medium = Init_Queue();
    PQueue queue_low = Init_Queue();
    UQueue queue_units = Init_Units_Queue();

    if (s_unit == NULL || s_incident == NULL || s_intervention == NULL){
        return 1;
    }

    // input output file management
    FILE *fin, *fout;

    fin = fopen("tema1.in", "r");

    if (fin == NULL){
        printf("Could not open input file");
        return 2;
    }

    fout = fopen("tema1.out", "w");

    if (fout == NULL){
        printf("Could not create output file");
    }
    scan_input_file(fin, fout, &total_units, &total_commands, s_unit, s_incident, s_intervention,
                    queue_high, queue_medium, queue_low, queue_units);
  
    Print_Units(s_unit);
    Print_Incidents(s_incident);
    Print_Priority_Queue(queue_high);
    Print_Priority_Queue(queue_medium);
    Print_Priority_Queue(queue_low);

    // free memory
    Free_Units(&s_unit);
    Free_Incidents(&s_incident);
    Free_Interventions(&s_intervention);

    Free_Priority_Queue(&queue_high);
    Free_Priority_Queue(&queue_medium);
    Free_Priority_Queue(&queue_low);

    Free_Units_Queue(&queue_units);

    fclose(fin);
    fclose(fout);

    return 0;
}