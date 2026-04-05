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
// ------------ INTERVENTIONS STACK ----------
// -------------------------------------------

IStack Init_Stack(){
    IStack s = malloc(sizeof(InterventionStack));
    if (!s){
        return NULL;
    }

    s->top = NULL;
    return s;
}

void add_intervention_to_stack(IStack s, LIntervention s_intervention) {
    if (!s || !s_intervention) return;
    
    INode new = malloc(sizeof(InterventionNode));
    if (!new) return;
    
    new->intervention = s_intervention;
    
    new->next = s->top; 
    s->top = new;
}

void Free_Interventions_Stack(IStack *s_ptr){
      if (s_ptr == NULL || *s_ptr == NULL) {
        return;
    }

    IStack s = *s_ptr;
    INode current = s->top;
    INode aux;

    while (current != NULL) {
        aux = current;          
        current = current->next; 
        
        free(aux); 
    }

    free(s);

    *s_ptr = NULL;
}



// ------------ PROGRAM FUNCTIONS ------------
// -------------------------------------------

void add_incindent(FILE *fin, FILE *fout, System *sys, PQueue high,
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

        LIncident s = sys->incidents;

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
        fprintf(fout,"INVALID OPERATION! ERROR 404\n");
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

void show_incident(System *sys, int id, FILE *fout){

    LIncident s = sys->incidents;

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

void show_unit(System *sys, int id, FILE *fout){

    LUnit s = sys->units;

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
                strcpy(availability, "unavailable");
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


void show_interventions(System *sys, FILE *fout){

    LIntervention s_intervention = sys->interventions;

    if (s_intervention->next == s_intervention){
        fprintf(fout,"No intervention has been initiated\n");
        return;
    }

    LIntervention current = s_intervention->next;

    while (current != s_intervention){
        fprintf(fout,"Incident %d was assigned to unit %d, and has the following status: \"%s\"\n",
                current->incident->id, current->unit->id, current->incident->status);
        current = current->next;
    }
}

void dispatch(System *sys, PQueue high, PQueue medium, 
                PQueue low, UQueue units, IStack s, FILE *fout){

    if ((high->front == NULL && medium->front == NULL && low->front == NULL) || units->front == NULL){
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }

    PQNode current = NULL;

    if (high->front != NULL){
        current = high->front;
        high->front = high->front->next;
            if (high->front == NULL) 
                high->rear = NULL;

    } else if (medium->front != NULL){
        current = medium->front; 
        medium->front = medium->front->next;
            if (medium->front == NULL)
                 medium->rear = NULL;
        
    } else if (low->front != NULL){
        current = low->front;
        low->front = low->front->next;
            if (low->front == NULL) 
                low->rear = NULL;
    }

    AUNode c_unit = units->front;
    units->front = units->front->next;
    if (units->front == NULL) units->rear = NULL;

    if (current && c_unit){
        LIntervention new = AlocateCell_Intervention(current->incident, c_unit->unit);

        strcpy(new->incident->status, "intervened");
        new->unit->availability = 0;
        
        LIntervention s_intervention = sys->interventions;

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

        add_intervention_to_stack(s, new);
    }
}
void add_incident_to_front_of_queue(PQueue q, LIncident incident) {

    PQNode new = malloc(sizeof(QNode));

    if (!new){ 
        return;
    }

    new->incident = incident;
    new->next = q->front;
    q->front = new;

    if (q->rear == NULL) {
        q->rear = new;
    }
}

void undo_last_dispatch(System *sys, PQueue high, PQueue medium,
                        PQueue low, UQueue units, IStack s, FILE *fout) {
    if (!s || !s->top ) {
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }

    INode current = NULL;
    LIntervention problem = NULL;

    while (s->top != NULL) {
        current = s->top;
        problem = current->intervention;
        
        if (strcmp(problem->incident->status, "intervened") != 0) {
            s->top = s->top->next;
            free(current);
            problem = NULL;
        } else {

            s->top = s->top->next;
            free(current);
            break;
        }
    }

    // No problematic intervention found
    if (problem == NULL) {
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }

    // Add incident back to its priority que
    strcpy(problem->incident->status, "queued");
    if (strcmp(problem->incident->priority, "high") == 0)
        add_incident_to_front_of_queue(high, problem->incident);
    else if (strcmp(problem->incident->priority, "medium") == 0)
        add_incident_to_front_of_queue(medium, problem->incident);
    else
        add_incident_to_front_of_queue(low, problem->incident);

    // The unit should now be available
    problem->unit->availability = 1;
    add_unit_to_queue(problem->unit, units);

    // Remove the problematic intervention from the interventions list
    problem->prev->next = problem->next;
    problem->next->prev = problem->prev;
    
    free(problem);
}

void solved_incident(System *sys, UQueue units, int id, FILE *fout, IStack s) {
    
    LIntervention s_intervention = sys->interventions;

    if (s_intervention->next == s_intervention){
        fprintf(fout, "INVALID OPERATION! ERROR 404\n");
        return;
    }

    LIntervention current = s_intervention->next;
    int check = 0;

    while (current != s_intervention) {
        
        if (current->incident->id == id && (strcmp(current->incident->status, "solved"))!=0) {
            
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

void command_manager(char command[], FILE *fin, FILE *fout, System *sys,
                    PQueue high, PQueue medium, PQueue low, UQueue units, IStack s){
    if (strcmp(command, "ADD_INCIDENT") == 0){
    add_incindent(fin, fout, sys, high, medium, low);

    } 
    else if (strcmp(command, "CHECK_UNITS_AVAILABILITY") == 0){
        fprintf(fout, "Number of available units: %d\n", check_units_availability(units));

    } 
    else if (strcmp(command, "ADD_INCIDENT") == 0){

    } 
    else if (strcmp(command, "DISPATCH") == 0){
        dispatch(sys, high,  medium, low, units, s, fout);

    } 
    else if (strcmp(command, "UNDO_LAST_DISPATCH") == 0){
        undo_last_dispatch(sys, high, medium, low, units, s, fout);
    } 
    else if (strcmp(command, "SOLVED_INCIDENT") == 0){
        int id;
        if (fscanf(fin, "%d", &id) == 1){
            solved_incident(sys, units, id, fout, s);
        }
    } 
    else if (strcmp(command, "SHOW_UNIT") == 0){
        int id;
        if (fscanf(fin, "%d", &id) == 1){
            show_unit(sys, id, fout);
        }
    } 
    else if (strcmp(command, "SHOW_INCIDENT") == 0){
        int id;
        if (fscanf(fin, "%d", &id) == 1){
            show_incident(sys, id, fout);
        }
    } 
    else if (strcmp(command, "SHOW_INTERVENTIONS") == 0){
            show_interventions(sys, fout);
    } 
    else fprintf(fout,"Invalid command");
}

void scan_input_file(FILE *fin, FILE *fout, int *total_units,
                    int *total_commands, System *sys,
                    PQueue high, PQueue medium, PQueue low, UQueue units, IStack s){

    char command[25];
    if (!fin || !(sys->units)) return;

    if (fscanf(fin, "%d",total_units) != 1) 
                        return;

    LUnit s_unit = sys->units;
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
            command_manager(command, fin, fout, sys, high, medium, low, units, s);
        }
        else return;
    }
}