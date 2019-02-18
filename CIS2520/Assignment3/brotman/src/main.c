/*//////////////////////////
Assignment 2
CIS 2520
Braelyn Rotman
ID: 1006740
brotman@uoguelph.ca
July 16th, 2018
main.c
//////////////////////////*/

#include "heap.h"
#include "heapADT.h"
#include "QueueADT.h"
#include "hospital.h"
void printArray (Heap *heap);

int main(int argc, char *argv[]){

  FILE *fp;
  char *filename; /* command line arguement */
  client *newClient;
  char *idBuf;
  int priBuf;
  char *codeBuf;
  bool GP1 = false, GP2 = false, CVs = false, RCs = false, SKs = false;
  int busytimer1 = 0, busytimer2 = 0, addtime = 0, CVbusy = 0, RCbusy = 0, SKbusy = 0;
  int timer1 = 0; /* regular simulation timer */
  float timer2 = 0; /* specialists simulation timer */
  int i = 0; /* number of elements */
  Node *current = NULL;
  Node *temp = NULL;
  client *pclient;
  client *tclient;
  Heap *heap = createHeap(15, 0, &destroyData, NULL, &compare);
  Queue *queue = create();
  Queue *treated = create();

  if (argc != 2)
  {
    return 0;
  }

  filename = argv[1];

  fp = fopen (filename, "r");
  if (fp == NULL)
  {
    printf("Error while opening file\n");
    return -1;
  }

  /* INSERT INTO HEAP */
  while (!feof(fp))
  {
    newClient = malloc(sizeof(client));
    idBuf = calloc(25, sizeof(char));
    codeBuf = calloc(3, sizeof(char));
    fscanf(fp, "%s %d %s\n", idBuf, &priBuf, codeBuf);
    newClient->ID = idBuf;
    newClient->priority = priBuf;
    newClient->code = codeBuf;
  /*  printf("%s %d %s\n", newClient->ID, newClient->priority, newClient->code);
    */insertHeapNode(heap, (void *)(newClient));
    i++;
  }
  fclose(fp);

  printArray(heap);

  /* INSERT INTO QUEUE */
  for (int d = 0; d < i ; d++)
  {
    enqueue(queue, heap->arr[d]->data);
  }

  for (int d = 0; d < i ; d++)
  {
    free(heap->arr[i]);
  }
  free(heap->arr);
  free(heap);
  printList(queue);

  /* NO SPECIALISTS SIMULATION */
  current = queue->front;
  while (current != NULL)
  {
    pclient = (client *)(current->data);
    if (strcmp(pclient->code, "CV") == 0)
    {
      addtime = 15;
    }
    else if (strcmp(pclient->code, "HN") == 0)
    {
      addtime = 3;
    }
    else if (strcmp(pclient->code, "EV") == 0)
    {
      addtime = 4;
    }
    else if (strcmp(pclient->code, "GI") == 0)
    {
      addtime = 20;
    }
    else if (strcmp(pclient->code, "MH") == 0)
    {
      addtime = 10;
    }
    else if (strcmp(pclient->code, "NC") == 0)
    {
      addtime = 20;
    }
    else if (strcmp(pclient->code, "EC") == 0)
    {
      addtime = 7;
    }
    else if (strcmp(pclient->code, "RC") == 0)
    {
      addtime = 8;
    }
    else if (strcmp(pclient->code, "SK") == 0)
    {
      addtime = 5;
    }
    else if (strcmp(pclient->code, "SA") == 0)
    {
      addtime = 10;
    }
    else if (strcmp(pclient->code, "TR") == 0)
    {
      addtime = 14;
    }
    /* assign to free doctor */
    if (GP1 == false)
    {
      busytimer1 = timer1 + addtime;
      GP1 = true;
    }
    else if (GP2 == false)
    {
      busytimer2 = timer1 + addtime;
      GP2 = true;
    }
    while (true)
    {
      timer1++; /* increase timer */

      if (busytimer2 == timer1)
      {
        GP2 = false;
      }
      if (busytimer1 == timer1)
      {
        GP1 = false;
      }

      if (GP2 == false || GP1 == false) /* when a doctor is free */
      {
        break;
      }
    }
    current = current->next; /* next client */
  }

  /* add last client time to timer */
  if (timer1 < busytimer1)
  {
    timer1 = busytimer1;
  }
  if (timer1 < busytimer2)
  {
    timer1 = busytimer2;
  }

  GP1 = false;
  GP2 = false;
  busytimer2 = 0;
  busytimer1 = 0;
  addtime = 0;

  /* SPECIALISTS SIMULATION */
  current = queue->front;
  while (queue->front != NULL)
  {
    pclient = (client *)(queue->front->data);

    if (strcmp(pclient->code, "CV") == 0)
    {
      addtime = 15;
    }
    else if (strcmp(pclient->code, "HN") == 0)
    {
      addtime = 3;
    }
    else if (strcmp(pclient->code, "EV") == 0)
    {
      addtime = 4;
    }
    else if (strcmp(pclient->code, "GI") == 0)
    {
      addtime = 20;
    }
    else if (strcmp(pclient->code, "MH") == 0)
    {
      addtime = 10;
    }
    else if (strcmp(pclient->code, "NC") == 0)
    {
      addtime = 20;
    }
    else if (strcmp(pclient->code, "EC") == 0)
    {
      addtime = 7;
    }
    else if (strcmp(pclient->code, "RC") == 0)
    {
      addtime = 8;
    }
    else if (strcmp(pclient->code, "SK") == 0)
    {
      addtime = 5;
    }
    else if (strcmp(pclient->code, "SA") == 0)
    {
      addtime = 10;
    }
    else if (strcmp(pclient->code, "TR") == 0)
    {
      addtime = 14;
    }
    enqueue(treated, (void *)(pclient));
    dequeue(queue);
    /* assign to free doctor or specialist */
    if (CVs == false && strcmp(pclient->code, "CV")==0)
    {
      CVbusy = timer2 + (addtime*1.1);
      CVs = true;
    }
    else if (RCs == false && strcmp(pclient->code, "RC")==0)
    {
      RCbusy = timer2 + (addtime*1.1);
      RCs = true;
    }
    else if (SKs == false && strcmp(pclient->code, "SK")==0)
    {
      SKbusy = timer2 + (addtime*1.1);
      SKs = true;
    }
    else if (GP1 == false)
    {
      busytimer1 = timer2 + addtime;
      GP1 = true;
    }
    else if (GP2 == false)
    {
      busytimer2 = timer2 + addtime;
      GP2 = true;
    }

    while (true)
    {
      timer2++; /* increase timer */

      if (busytimer2 == timer2)
      {
        GP2 = false;
      }
      if (busytimer1 == timer2)
      {
        GP1 = false;
      }
      if (CVbusy == timer2)
      {
        CVs = false;
      }
      if (RCbusy == timer2)
      {
        RCs = false;
      }
      if (SKbusy == timer2)
      {
        SKs = false;
      }


      if (GP2 == false || GP1 == false) /* when a doctor is free */
      {
        break;
      }
      if (CVs == false)
      {
        temp = queue->front;
        while (temp != NULL)
        {

          tclient = (client *)(temp->data);
          if (strcmp(tclient->code, "CV") == 0)
          {
            CVbusy = timer2 + (15*1.1);
            CVs = true;
            enqueue(treated, (void *)(tclient));

            deleteDataFromList(queue->list, (void *)(tclient));
            queue->back = queue->list->tail;
            queue->front = queue->list->head;
            queue->length = queue->length - 1;

            break;
          }
          temp = temp->next;
        }
      }
      if (RCs == false)
      {

        temp = queue->front;
        while (temp != NULL)
        {

          tclient = (client *)(temp->data);
          if (strcmp(tclient->code, "RC") == 0)
          {

            RCbusy = timer2 + (15*1.1);
            RCs = true;
            enqueue(treated, (void *)(tclient));

            deleteDataFromList(queue->list, (void *)(tclient));
            queue->back = queue->list->tail;
            queue->front = queue->list->head;
            queue->length = queue->length - 1;

            break;
          }
          temp = temp->next;
        }
      }
      if (SKs == false)
      {
        temp = queue->front;
        while (temp != NULL)
        {
          tclient = (client *)(temp->data);
          if (strcmp(tclient->code, "SK") == 0)
          {
            SKbusy = timer2 + (15*1.1);
            SKs = true;
            enqueue(treated, (void *)(tclient));

            deleteDataFromList(queue->list, (void *)(tclient));
            queue->back = queue->list->tail;
            queue->front = queue->list->head;
            queue->length = queue->length - 1;

            break;
          }
          temp = temp->next;
        }

      }
    }


  /*  enqueue(treated, (void *)(pclient));
    dequeue(queue);
*/
    printList(treated);

    current = current->next; /* next client */
  }



  /* add last client time to timer */
  if (timer2 < busytimer1)
  {
    timer2 = busytimer1;
  }
  if (timer2 < busytimer2)
  {
    timer2 = busytimer2;
  }
  if (timer2 < CVbusy)
  {
    timer2 = CVbusy;
  }
  if (timer2 < RCbusy)
  {
    timer2 = RCbusy;
  }
  if (timer2 < SKbusy)
  {
    timer2 = SKbusy;
  }

  if (timer1 < 3) /* NO CLIENTS */
  {
    timer1 = 0;
    timer2 = 0;
  }
  free(queue->list);
  free(queue);
  printf("\nSIMULATIONS:\nTIMER 1 = %d minutes\nTIMER 2 = %.2f minutes\n\n", timer1, timer2);

  printList(treated);

  printReport(treated, timer1, timer2);

  destroy(treated);

  return 0;
}

void printReport(Queue *treated, int timer1, float timer2){
  FILE *fp;
  client *pclient;
  Node *current = NULL;

  fp = fopen("report.txt", "w");
  fprintf(fp, "ER Hospital Report\n");
  fprintf(fp, "Braelyn Rotman\nID:1006740\n\n");

  fprintf(fp, "Clients Treated (in order of treatment start time):\n");
  fprintf(fp, "**Client priorities may have changed in starvation algorithm**\n\n");

  if (timer1 > 0)
  {
    current = treated->front;
    while (current != NULL)
    {
      pclient = (client *)current->data;
      fprintf(fp, "%s %d %s\n", pclient->ID, pclient->priority, pclient->code);
      current = current->next;
    }
  }
  else
  {
    fprintf(fp, "There were no clients\n");
  }
  fprintf(fp, "\nNumber of General Practitioners: 2\n");
  fprintf(fp, "Specialist Doctor Codes: CV, RC, SK\n\n");

  fprintf(fp, "Simulation Time With 0 Specialists: %d.00 minutes\n", timer1);
  fprintf(fp, "Simulation Time With 3 Specialists: %.2f minutes\n\n", timer2);

  fprintf(fp, "NOTES:\n");
  fprintf(fp, "Although specialists take longer to treat clients, they shorten the overall time taken.\n");
  fprintf(fp, "Specialists only take certain clients which shortens the waiting list\n");
  fprintf(fp, "********************************************************************************************\n");

  fclose(fp);
}

void destroyData(void *data){
  HeapNode *delete = (HeapNode *)(data);
  client *cdelete = (client *)(delete->data);
  delete->parent = NULL;
  delete->left = NULL;
  delete->right = NULL;
  free(cdelete->ID);
  free(cdelete->code);
  free(delete->data);
}

int compare(const void *first, const void *second){
  client *one = (client *)first;
  client *two = (client *)second;

  if (one->priority > two->priority)
  {
    return 1;
  }
  else if (one->priority < two->priority)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

void printArray (Heap *heap){
  int i = 0;
  client * pclient;

  printf("HEAP ARRAY:\n");
  while (heap->arr[i] != NULL)
  {
    pclient = (client *)(heap->arr[i]->data);
    printf("%s %d %s\n", pclient->ID, pclient->priority, pclient->code);
    i++;
  }
  printf("\n");
}

void printList (Queue *queue){
  client * pclient = NULL;
  Node * current = queue->front;

  printf("QUEUE:\n");
  while (current != NULL)
  {
    pclient = (client *)(current->data);
    printf("%s %d %s\n", pclient->ID, pclient->priority, pclient->code);
    current = current->next;
  }
}
