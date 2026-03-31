#include "tema1.h"

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
// ------------ PRIORITY QUES ------------
// -------------------------------------------

PQueue Init_Queue(){
    PQueue q = malloc(sizeof(PriorityQue));
    if (!q){
        return NULL;
    }

    q->front = NULL;
    q->rear = NULL;
    return q;
}

void add_incident_to_queue(PQueue q, LIncident s){
    if (!q || !s){
        return;
    }

    PQNode new = malloc(sizeof(QNode));
        if (!new){
            return;
        }
    new->incident = s;
    new->next = NULL;

    if (q->rear == NULL){
        q->front = new;
        q->rear = new;
    } else {
        q->rear->next = new;
        q->rear = new;
    }
}

void Print_Priority_Queue(PQueue q){

      if (q == NULL || q->front == NULL) {
        printf("=============== Priority Queue ===============\n");
        printf("                   [EMPTY]                    \n");
        printf("==============================================\n\n");
        return;
    }

    char priority[7];
    strcpy(priority, q->front->incident->priority);

    PQNode p = q->front;

    printf("=============== Priority Que ===============\n\n");

       if (strcmp(priority, "high") == 0){
    printf("=================== HIGH ===================\n\n");
        } else if (strcmp(priority, "medium") == 0){
    printf("=================== MEDIUM ===================\n\n");
        } else if (strcmp(priority, "low") == 0){
    printf("=================== LOW ===================\n\n");

        } 
    
          while (p != NULL){

            printf("-------------------------------------\n");
        
            printf("ID:           | %d\n", p->incident->id);
            printf("Description:  | %s\n", p->incident->description);
            printf("Status:       | %s\n", p->incident->status);

            printf("-------------------------------------\n\n");

            p = p->next;
        }

    printf("==========================================\n\n");
}

void Free_Priority_Queue(PQueue *q_ptr) {
    if (q_ptr == NULL || *q_ptr == NULL) {
        return;
    }

    PQueue q = *q_ptr;
    PQNode current = q->front;
    PQNode aux;

    while (current != NULL) {
        aux = current;          
        current = current->next; 
        
        free(aux); 
    }

    free(q);

    *q_ptr = NULL;
}
// ----------- AVAILABLE UNITS QUE -----------
// -------------------------------------------

UQueue Init_Units_Queue(){
    UQueue q = malloc(sizeof(UnitsQue));
    if (!q){
        return NULL;
    }

    q->front = NULL;
    q->rear = NULL;
    return q;
}

void add_unit_to_queue(LUnit u, UQueue q){

    if ( !u || !q ){
        return;
    }

    AUNode new = malloc(sizeof(UNode));
        if (!new){
            return;
        }
    new->unit = u;
    new->next = NULL;

    if (q->rear == NULL){
        q->front = new;
        q->rear = new;
    } else {
        q->rear->next = new;
        q->rear = new;
    }

}

void Free_Units_Queue(UQueue *q_ptr){

    if (q_ptr == NULL || *q_ptr == NULL){
        return;
    }

    UQueue q = *q_ptr;
    AUNode current = q->front;
    AUNode aux;

    while (current != NULL){
        aux = current;
        current = current->next;

        free(aux);
    }
    free(q);

    *q_ptr = NULL;
}

// ------------ PROGRAM FUNCTIONS ------------
// -------------------------------------------

void add_incindent(FILE *fin, LIncident s_incident, PQueue high, 
                    PQueue medium, PQueue low){

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
    if (myPtr != NULL) {
        strcpy(priority, myPtr);
    }

    char *description = strtok(NULL, "\n");

    if (description != NULL){

        LIncident new = AlocateCell_Incident(id, priority, description, "queued");

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

        // add incident to priority queue
        if (strcmp(priority, "high") == 0){
            add_incident_to_queue(high, new);
        } else if (strcmp(priority, "medium") == 0){
            add_incident_to_queue(medium, new);
        } else if (strcmp(priority, "low") == 0){
            add_incident_to_queue(low, new);
        } 

    } else {
        printf("INVALID OPERATION! ERROR 404\n");
        return;
    }
    
}

int check_units_availability(UQueue q){

    int cnt = 0;

    if (q == NULL){
        return 0;
    }

    AUNode current = q->front;

    while(current != NULL){
        cnt++;
        current = current->next;
    }

    return cnt;

}

void show_incident(LIncident s, int id, FILE *fout){

    if (s->next == s){
        fprintf(fout, "No incident has been initiated\n");
        return;
    }

    LIncident current = s->next;
    int check = 0;

    while(current != s){
        if(current->id == id){
            fprintf(fout, "Incident %d has %s priority, the following description: %s and is %s\n", 
                    current->id, current->priority, current->description, current->status);
            check++;
            break;
        }
        current = current->next;
    }
    if (!check){
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
    }
}

void show_unit(LUnit s, int id, FILE *fout){

    if (s->next == s){
        fprintf(fout, "No unit has been initiated");
        return;
    }

    LUnit current = s->next;
    int check = 0;

    while(current != s){
        if(current->id == id){
            char availability[15];
            if (current->availability){
                strcpy(availability, "available");
            } else {
                strcpy(availability, "not available");
            }
            fprintf(fout, "Unit %d is type %c and is %s\n", 
                    current->id, current->type, availability);
            check++;
            break;
        }
        current = current->next;
    }
    if (!check){
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
    }
}

// T
// void show_interventions(LIntervention s, int id, FILE *fout){

// }

// in case there's a string and not the wanted id, ex: SHOW_UNIT miau bla bla bla
void empty_buffer(FILE *fin, FILE *fout){

    fprintf(fout, "INVALID OPERATION! ERROR 404\n");
    int c;
            while ((c = fgetc(fin)) != '\n' && c != EOF) {
            }
}

void dispatch(LIncident s_incident, LUnit s_unit, LIntervention s_intervention,
                PQueue high, PQueue medium, PQueue low, UQueue units){

    int emergency = 0;

    if (s_incident->next == s_incident || s_unit->next == s_unit){
        return;
    }

    if (units->front == NULL){
        return;
    }

    PQNode current = NULL;

    if (high->front != NULL){
        current = high->front;
        high->front = high->front->next;
            if (high->front == NULL) 
                high->rear = NULL;

    } else if (medium->front != NULL){
        current = high->front;
        medium->front = medium->front->next;
            if (medium->front == NULL)
                 medium->rear = NULL;
        
    } else if (low->front != NULL){
        current = low->front;
        low->front = low->front->next;
            if (low->front == NULL) 
                low->rear = NULL;

    } else if (current == NULL){
        return;
    }

    
    AUNode c_unit = units->front;
    units->front = units->front->next;
    if (units->front == NULL) units->rear = NULL;

    if (current && c_unit){
        LIntervention new = AlocateCell_Intervention(current->incident, c_unit->unit);

        strcpy(new->incident->status, "intervened");
        new->unit->availability = 0;

        if (s_intervention->next == s_intervention){
            s_intervention->next = new;
            new->prev = s_intervention;
            new->next = s_intervention;
            s_intervention->prev = new;
        }

        else {
            new->prev = s_intervention->prev;
            s_intervention->prev->next = new;
            s_intervention->prev = new;
            new->next = s_intervention;
        }

        free(current);
        free(c_unit);
    }

}

void solved_incident(LIntervention s_intervention, UQueue units, int id, FILE *fout) {
    
    if (s_intervention->next == s_intervention){
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }

    LIntervention current = s_intervention->next;
    int check = 0;

    while (current != s_intervention) {
        
        if (current->incident->id == id) {
            
            strcpy(current->incident->status, "solved");

            current->unit->availability = 1;

            add_unit_to_queue(current->unit, units);

            check++;
            break; 
        }
        current = current->next;
    }

    if (!check) {
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
    }
}

void command_manager(char command[], FILE *fin, FILE *fout, LIncident s_incident,
                    LUnit s_unit, LIntervention s_intervention,
                    PQueue high, PQueue medium, PQueue low, UQueue units){
    if (strcmp(command, "ADD_INCIDENT") == 0){
    add_incindent(fin, s_incident, high, medium, low);

    } 
    else if (strcmp(command, "CHECK_UNITS_AVAILABILITY") == 0){
        fprintf(fout, "Number of available units: %d\n", check_units_availability(units));

    } 
    else if (strcmp(command, "ADD_INCIDENT") == 0){

    } 
    else if (strcmp(command, "DISPATCH") == 0){
        dispatch(s_incident, s_unit, s_intervention, high,  medium, low, units);

    } 
    else if (strcmp(command, "UNDO_LAST_DISPATCH") == 0){

    } 
    else if (strcmp(command, "SOLVED_INCIDENT") == 0){
        int id;
        if (fscanf(fin, "%d", &id) == 1){
            solved_incident(s_intervention, units, id, fout) ;
        } else {
           empty_buffer(fin, fout);
        }
    } 
    else if (strcmp(command, "SHOW_UNIT") == 0){
        int id;
        if (fscanf(fin, "%d", &id) == 1){
            show_unit(s_unit, id, fout);
        } else {
           empty_buffer(fin, fout);
        }
    } 
    else if (strcmp(command, "SHOW_INCIDENT") == 0){
        int id;
        if (fscanf(fin, "%d", &id) == 1){
            show_incident(s_incident, id, fout);
        } else {
            empty_buffer(fin, fout);
        }
    } 
    else if (strcmp(command, "SHOW_INTERVENTIONS") == 0){
        // int id;
        // if (fscanf(fin, "%d", &id) == 1){
        //     show_intervention(s_intervention, id, fout);
        // } else {
        //     empty_buffer(fin, fout);
        // }
    } 
    else printf("Invalid command");
}

void scan_input_file(FILE *fin, FILE *fout, int *total_units,
                    int *total_commands, LUnit s_unit, LIncident s_incident, LIntervention s_intervention,
                    PQueue high, PQueue medium, PQueue low, UQueue units){

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
            add_unit_to_queue(new, units);
        
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
            command_manager(command, fin, fout, s_incident,s_unit,
                            s_intervention, high, medium, low, units);
        }
        else return;
    }
}