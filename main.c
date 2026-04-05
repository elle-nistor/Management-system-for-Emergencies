#include "tema1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char command[25];
    int total_units, total_commands;

    System *sys = malloc(sizeof(System));
        if (sys == NULL){
            return 1;
        }

    // initiate lists & sentinels
    sys->units = Init_Unit();
    sys->incidents = Init_Incident();
    sys->interventions = Init_Intervention();

    //initiate queues - interventions & units availability
    PQueue queue_high = Init_Queue();
    PQueue queue_medium = Init_Queue();
    PQueue queue_low = Init_Queue();
    UQueue queue_units = Init_Units_Queue();
    IStack s = Init_Stack();

    if ( sys->units == NULL || sys->incidents == NULL || sys->interventions == NULL){
        free(sys);
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
    scan_input_file(fin, fout, &total_units, &total_commands, sys,
                    queue_high, queue_medium, queue_low, queue_units, s);
  

    // free memory
    Free_Units(&(sys->units));
    Free_Incidents(&(sys->incidents));
    Free_Interventions(&(sys->interventions));
    
    free(sys);

    Free_Priority_Queue(&queue_high);
    Free_Priority_Queue(&queue_medium);
    Free_Priority_Queue(&queue_low);

    Free_Units_Queue(&queue_units);
    Free_Interventions_Stack(&s);

    fclose(fin);
    fclose(fout);

    return 0;
}