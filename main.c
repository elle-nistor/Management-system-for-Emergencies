#include "structs.h"

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

    if (s_unit == NULL || s_incident == NULL || s_intervention == NULL){
        return 1;
    }

    // input output file management
    FILE *fin;

    fin = fopen("tema1.in", "r");

    if (fin == NULL){
        printf("Could not open input file");
        return 2;
    }

    // fout = fopen("tema1.out", "w");

    // if (fout == NULL){
    //     printf("Could not create output file");
    // }
    scan_input_file(fin, &total_units, &total_commands, s_unit, s_incident);
    // printf("Total units: %d\nTotal commands: %d\n", 
    //         total_units, total_commands);

    Print_Units(s_unit);
    Print_Incidents(s_incident);

    // free memory
    Free_Units(&s_unit);
    Free_Incidents(&s_incident);
    Free_Interventions(&s_intervention);

    fclose(fin);
    // fin = NULL;
    // fclose(fout);

    return 0;
}