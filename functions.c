#include "structs.h"

// ----------------UNIT LIST------------------
// -------------------------------------------

LUnit AlocateCell_Unit (int id, char type, 
                        int availability){
    LUnit aux = malloc(sizeof(Unit));
    if (!aux){
        return NULL;
    }

    aux->id = id;
    aux->type = type;
    aux->availability = availability;

    aux->prev = aux->next = NULL;

    return aux;
}

// create sentinel
LUnit Init_Unit(){

    LUnit aux = malloc(sizeof(Unit));
    if (!aux) {
        return NULL;
    }

    aux->id = 0;
    aux->type = 'T';
    aux->availability = 0;

    aux->prev = aux;
    aux->next = aux;

    return aux;
}

void Print_Units(LUnit s){

    LUnit p = s->next;
    printf("================== UNITS ==================\n\n");

        while (p != s){

            printf("-------------------------------------\n");
            printf("ID:           | %d\n", p->id);
            printf("Type:         | %c\n", p->type);
            printf("Availability: | %d\n", p->availability);
            printf("-------------------------------------\n\n");

            p = p->next;
        }

    printf("==========================================\n\n");

}

void Free_Units (LUnit *s){
    LUnit p = (*s)->next, aux;

    while( p != *s){
        aux = p;
        p = p->next;
        free(aux);
    }

    free(*s);
    *s = NULL;
}

// --------------INCIDENT LIST----------------
// -------------------------------------------

LIncident AlocateCell_Incident (int id, char priority[], 
                                char *description, char status[])
{

    LIncident aux = malloc(sizeof(Incident));
    if (!aux){
        return NULL;
    }

    aux->id = id;

    strncpy(aux->priority, priority, sizeof(aux->priority) - 1);
    aux->priority[sizeof(aux->priority) - 1] = '\0';

    strncpy(aux->status, status, sizeof(aux->status) - 1);
    aux->status[sizeof(aux->status) - 1] = '\0';

    size_t len = strlen(description);

    aux->description = malloc(len + 1);
    if (aux->description != NULL){
        strncpy(aux->description, description, len);
        aux->description[len] = '\0';

    }

    aux->prev = aux->next = NULL;

    return aux;
}

// create sentinel - Test Incident
LIncident Init_Incident(){

    LIncident aux = malloc (sizeof(Incident));
    if (!aux) {
        return NULL;
    }

    aux->id = 0;
    strcpy(aux->priority, "low");
    aux->description = malloc(14);
    strcpy(aux->description, "test incident");
    strcpy(aux->status, "solved");

    aux->prev = aux;
    aux->next = aux;

    return aux;
}

void Print_Incidents(LIncident s){

    LIncident p = s->next;
    printf("=============== INCIDENTS ===============\n\n");

        while (p != s){

            printf("-------------------------------------\n");
        
            printf("ID:           | %d\n", p->id);
            printf("Priority:     | %s\n", p->priority);
            printf("Description:  | %s\n", p->description);
            printf("Status:       | %s\n", p->status);

            printf("-------------------------------------\n\n");

            p = p->next;
        }

    printf("==========================================\n\n");
}

void Free_Incidents (LIncident *s){
    LIncident p = (*s)->next, aux;

    while( p != *s){
        aux = p;
        p = p->next;
        free(aux->description);
        free(aux);
    }
    free((*s)->description);
    free(*s);
    *s = NULL;
}

// --------------INCIDENT LIST----------------
// -------------------------------------------

LIntervention AlocateCell_Intervention (LIncident incident,
                                        LUnit unit){

    LIntervention aux = malloc (sizeof(Intervention));
    if (!aux){
        return NULL;
    }

    aux->incident = incident;
    aux->unit = unit;

    aux->prev = aux->next = NULL;

    return aux;
}

// create sentinel
LIntervention Init_Intervention(){

    LIntervention aux = malloc (sizeof(Intervention));
    if (!aux) {
        return NULL;
    }

    aux->incident = NULL;
    aux->unit = NULL;

    aux->prev = aux;
    aux->next = aux;

    return aux;
}

void Print_Intervention(LIntervention s){

    LIntervention p = s->next;
    printf("============== INTERVENTIONS ==============\n\n");

        while (p != s){
            
            printf("-------------------------------------\n");
            printf("------------- Incident: -------------\n");
        
            printf("ID:           | %d\n", p->incident->id);
            printf("Priority:     | %s\n", p->incident->priority);
            printf("Description:  | %s\n", p->incident->description);
            printf("Status:       | %s\n", p->incident->status);

            printf("-------------- Unit: ---------------\n");
            printf("ID:           | %d\n", p->unit->id);
            printf("Type:         | %c\n", p->unit->type);
            printf("Availability: | %d\n", p->unit->availability);

            printf("-------------------------------------\n\n");

            p = p->next;
        }

    printf("==========================================\n\n");
}

void Free_Interventions (LIntervention *s){
    LIntervention p = (*s)->next, aux;

    while( p != *s){
        aux = p;
        p = p->next;
        free(aux);
    }

    free(*s);
    *s = NULL;
}

// ------------ PROGRAM FUNCTIONS ------------
// -------------------------------------------

void add_incindent(FILE *fin, LIncident s_incident){

    char line[1001];

    if (fgets(line, sizeof(line), fin) == NULL)
        return;

    int id;
    char *myPtr = strtok(line, " ");
    
    if (myPtr != NULL){
        id = atoi(myPtr);
    }

    char priority[7];

    myPtr = strtok(NULL, " ");
    strcpy(priority, myPtr);

    myPtr = strtok(NULL, "\n");

    char *description = NULL;

    if (myPtr != NULL){
        description = malloc(sizeof(myPtr));

        if (description != NULL){
            strcpy(description, myPtr);
        }
    }

    if ( description != NULL ){
        LIncident new = AlocateCell_Incident(id, priority, description, "qued");

        LIncident s = s_incident;

        if (s->next == s){

            s->next = new;
            s->prev = new;
            new->next = s;
            new->prev = s;

        } else {
        
            s->prev->next = new;
            new->prev = s->prev;
            s->prev = new;
            new->next = s;

        }

    } else {

        printf("INVALID OPERATION! ERROR 404");
        return;
    }

    free(description);
    // free(myPtr);

}

void command_manager(char command[], FILE *fin, LIncident s_incident){
    if (strcmp(command, "ADD_INCIDENT") == 0){
    add_incindent(fin, s_incident);

    } 
    else if (strcmp(command, "CHECK_UNITS_AVAILABILITY") == 0){

    } 
    else if (strcmp(command, "ADD_INCIDENT") == 0){

    } 
    else if (strcmp(command, "DISPATCH") == 0){

    } 
    else if (strcmp(command, "UNDO_LAST_DISPATCH") == 0){

    } 
    else if (strcmp(command, "SOLVED_INCIDENT") == 0){

    } 
    else if (strcmp(command, "SHOW_UNIT") == 0){

    } 
    else if (strcmp(command, "SHOW_INCIDENT") == 0){

    } 
    else if (strcmp(command, "SHOW_INTERVENTIONS") == 0){

    } 
    else printf("Invalid command");
}

void scan_input_file(FILE *fin, int *total_units,
                    int *total_commands, LUnit s_unit, LIncident s_incident){

    char command[25];
    if (!fin || !s_unit) return;

    if (fscanf(fin, "%d",total_units) != 1) 
                        return;

    LUnit p = s_unit;

    for (int i = 0; i < *(total_units); i++){
        int id;
        char type; 

        if (fscanf(fin, "%d %c", &id, &type) == 2){
            LUnit new = AlocateCell_Unit(id, type, 1);
        
        if (new){
        
        p->next = new;
        new->prev = p;
        s_unit->prev = new;
        new->next = s_unit;

        p = new;
        }
    }
}

    fscanf(fin, "%d", total_commands);

    for (int i = 0; i < *(total_commands); i++){
        if (fscanf(fin, "%s", command) == 1){
            command_manager(command, fin, s_incident);
        }
        else return;
    }
}