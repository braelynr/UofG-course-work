#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueADT.h"

void addTime(Queue *queue, int time); /* increase time in queue */
/* move cars through intersection */
double moveCar(Queue *queue, List *departed);
void printStats(List *departed);

double timer;

int main(int argc, char *argv[]){

  Queue *north, *east, *south, *west;
  char *filename;
  int iscanned = 0;
  FILE *fp;
  car *newCar = NULL;
  List *temp = initializeList(NULL, NULL, &compare);
  Node *c;
  car *a;
  Node * node;
  car * car1, * car2, * car3, * car4;
  double add; /* time taken to clear intersection */
  List *departed = initializeList(NULL, NULL, NULL); /* cars passed through intersection */

  bool n = false, s = false, e = false, w = false; /* car ready to go true/false */

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

  while (1)
  {
    if (feof(fp))
    {
      break;
    }
    newCar = malloc(sizeof(car));
    iscanned = fscanf(fp, "%c %c %d\n", &newCar->direction, &newCar->turn, &newCar->arrivalTime);
    newCar->queueTime = 0;
  /*  printf("direction = %c\nturn = %c\ntime = %d\n\n", newCar->direction, newCar->turn, newCar->arrivalTime);
*/
    if (iscanned == 3)
    {
      insertSorted(temp, newCar); /* sort list by arrivalTime */
    }
  }
  fclose(fp);

/*  c = temp->head;
  printf("---------------------sorted-------------\n");
  while (c != NULL)
  {
    a = c->data;
    printf("direction = %c\nturn = %c\ntime = %d\n\n", a->direction, a->turn, a->arrivalTime);
    c= c->next;
  }*/

  /* SORT LIST INTO 4 QUEUES */
    north = create();
    east = create();
    south = create();
    west = create();

    for (c = temp->head ; c != NULL ; c = c->next)
    {
      a = c->data;

      if (a->direction == 'N')
      {
        enqueue(north, (void *)a);
      }
      else if (a->direction == 'E')
      {
        enqueue(east, (void *)a);
      }
      else if (a->direction == 'S')
      {
        enqueue(south, (void *)a);
      }
      else
      {
        enqueue(west, (void *)a);
      }
    }

  /* DELETE TEMPORARY LIST */
  while(temp->head != NULL)
  {
    c = temp->head;

    temp->head = temp->head->next;
    c->next = NULL;
    free(c);
  }
/* PRINT QUEUES
  printf("NORTH QUEUE:\n");
  for (c = north->front ; c != NULL ; c = c->next)
  {
    a = c->data;
    printf("direction = %c\nturn = %c\ntime = %d\n\n", a->direction, a->turn, a->arrivalTime);
  }
  printf("EAST QUEUE:\n");
  for (c = east->front ; c != NULL ; c = c->next)
  {
    a = c->data;
    printf("direction = %c\nturn = %c\ntime = %d\n\n", a->direction, a->turn, a->arrivalTime);
  }
  printf("SOUTH QUEUE:\n");
  for (c = south->front ; c != NULL ; c = c->next)
  {
    a = c->data;
    printf("direction = %c\nturn = %c\ntime = %d\n\n", a->direction, a->turn, a->arrivalTime);
  }
  printf("WEST QUEUE:\n");
  for (c = west->front ; c != NULL ; c = c->next)
  {
    a = c->data;
    printf("direction = %c\nturn = %c\ntime = %d\n\n", a->direction, a->turn, a->arrivalTime);
  }
*/

  /* SIMULATION START */
  timer = 0;
  /* while there are still cars waiting */
  while (isEmpty(north) == false || isEmpty(east) == false || isEmpty(south) == false || isEmpty(west) == false)
  {
    /* find which cars are ready to go */
    if (n == false && e == false && s == false && w == false)
    {
      if (north->front != NULL)
      {
        node = north->front;
        car1 = node->data;
        if (car1->arrivalTime <= timer)
        { /**********************PLUS TIME IN QUEUE???????????????????????????????????????????????????????????????????????????????????????????????*/
          n = true;
        }
      }
      if (east->front != NULL)
      {
        node = east->front;
        car2 = node->data;
        if (car2->arrivalTime <= timer)
        {
          e = true;
        }
      }
      if (south->front != NULL)
      {
        node = south->front;
        car3 = node->data;
        if (car3->arrivalTime <= timer)
        {
          s = true;
        }
      }
      if (west->front !=NULL)
      {
        node = west->front;
        car4 = node->data;
        if (car4->arrivalTime <= timer)
        {
          w = true;
        }
      }
    }
    /* move next car through intersection */
    if (n == true && s == false && w == false && e == false)
    {
      add = moveCar(north, departed);
      addTime(south, add);
      addTime(east, add);
      addTime(west, add);
      n = false;
    }
    else if (n == false && s == true && w == false && e == false)
    {
      add = moveCar(south, departed);
      addTime(north, add);
      addTime(east, add);
      addTime(west, add);
      s = false;
    }
    else if (n == false && s == false && w == true && e == false)
    {
      add = moveCar(west, departed);
      addTime(north, add);
      addTime(south, add);
      addTime(east, add);
      w = false;
    }
    else if (n == false && s == false && w == false && e == true)
    {
      add = moveCar(east, departed);
      addTime(north, add);
      addTime(south, add);
      addTime(west, add);
      e = false;
    }
    else if (n == true && s == false && w == true && e == false)
    {
      node = north->front;
      car1 = node->data;
      node = west->front;
      car4 = node->data;
      if ((car1->arrivalTime + car1->queueTime) >= (car4->arrivalTime + car4->queueTime))
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;

      }
      else
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(south, add);
        addTime(east, add);
        addTime(west, add);
        n = false;
      }
    }
    else if (n == true && s == false && w == false && e == true)
    {
      node = north->front;
      car1 = node->data;
      node = east->front;
      car2 = node->data;
      if ((car1->arrivalTime + car1->queueTime) > (car2->arrivalTime + car2->queueTime))
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(west, add);
        e = false;

      }
      else
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(south, add);
        addTime(east, add);
        addTime(west, add);
        n = false;
      }

    }
    else if (n == true && s == true && w == false && e == false)
    {
      node = north->front;
      car1 = node->data;
      node = south->front;
      car3 = node->data;
      if ((car1->arrivalTime + car1->queueTime) > (car3->arrivalTime + car3->queueTime))
      {
        /* south goes first */
        add = moveCar(south, departed);
        addTime(north, add);
        addTime(east, add);
        addTime(west, add);
        s = false;

      }
      else
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(south, add);
        addTime(east, add);
        addTime(west, add);
        n = false;
      }

    }
    else if (n == false && s == false && w == true && e == true)
    {
      node = west->front;
      car4 = node->data;
      node = east->front;
      car2 = node->data;
      if ((car4->arrivalTime + car4->queueTime) < (car2->arrivalTime + car2->queueTime))
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;

      }
      else
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(west, add);
        e = false;
      }

    }
    else if (n == false && s == true && w == true && e == false)
    {
      node = south->front;
      car3 = node->data;
      node = west->front;
      car4 = node->data;
      if ((car3->arrivalTime + car3->queueTime) > (car4->arrivalTime + car4->queueTime))
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;

      }
      else
      {
        /* south goes first */
        add = moveCar(south, departed);
        addTime(north, add);
        addTime(east, add);
        addTime(west, add);
        s = false;
      }

    }
    else if (n == false && s == true && w == false && e == true)
    {
      node = south->front;
      car3 = node->data;
      node = east->front;
      car2 = node->data;
      if ((car3->arrivalTime + car3->queueTime) >= (car2->arrivalTime + car2->queueTime))
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(west, add);
        e = false;

      }
      else
      {
        /* south goes first */
        add = moveCar(south, departed);
        addTime(north, add);
        addTime(east, add);
        addTime(west, add);
        s = false;
      }

    }
    else if (n == true && s == false && w == true && e == true)
    {
      node = north->front;
      car1 = node->data;
      node = west->front;
      car4 = node->data;
      node = east->front;
      car2 = node->data;
      if (((car1->arrivalTime + car1->queueTime) >= (car4->arrivalTime + car4->queueTime)) && ((car4->arrivalTime + car4->queueTime) <= (car2->arrivalTime + car2->queueTime)))
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;
      }
      else if (((car1->arrivalTime + car1->queueTime) < (car4->arrivalTime + car4->queueTime)) && ((car1->arrivalTime + car1->queueTime) <= (car2->arrivalTime + car2->queueTime)))
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(south, add);
        addTime(east, add);
        addTime(west, add);
        n = false;
      }
      else
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(west, add);
        e = false;
      }
    }
    else if (n == true && s == true && w == false && e == true)
    {
      node = north->front;
      car1 = node->data;
      node = south->front;
      car3 = node->data;
      node = east->front;
      car2 = node->data;
      if (((car1->arrivalTime + car1->queueTime) > (car3->arrivalTime + car3->queueTime)) && ((car3->arrivalTime + car3->queueTime) < (car2->arrivalTime + car2->queueTime)))
      {
        /* south goes first */
        add = moveCar(south, departed);
        addTime(north, add);
        addTime(east, add);
        addTime(west, add);
        s = false;
      }
      else if (((car2->arrivalTime + car2->queueTime) <= (car3->arrivalTime + car3->queueTime)) && ((car1->arrivalTime + car1->queueTime) > (car2->arrivalTime + car2->queueTime)))
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(south, add);
        addTime(north, add);
        addTime(west, add);
        e = false;
      }
      else
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(east, add);
        addTime(south, add);
        addTime(west, add);
        n = false;
      }
    }
    else if (n == true && s == true && w == true && e == false)
    {
      node = north->front;
      car1 = node->data;
      node = west->front;
      car4 = node->data;
      node = south->front;
      car3 = node->data;

      if (((car3->arrivalTime + car3->queueTime) <= (car4->arrivalTime + car4->queueTime)) && ((car1->arrivalTime + car1->queueTime) >= (car3->arrivalTime + car3->queueTime)))
      {
        /* south goes first */
        add = moveCar(south, departed);
        addTime(north, add);
        addTime(east, add);
        addTime(west, add);
        s = false;
      }
      else if (((car1->arrivalTime + car1->queueTime) > (car4->arrivalTime + car4->queueTime)) && ((car4->arrivalTime + car4->queueTime) < (car3->arrivalTime + car3->queueTime)))
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;
      }
      else
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(south, add);
        addTime(east, add);
        addTime(west, add);
        n = false;
      }
    }
    else if (n == false && s == true && w == true && e == true)
    {
      node = south->front;
      car3 = node->data;
      node = west->front;
      car4 = node->data;
      node = east->front;
      car2 = node->data;
      if (((car2->arrivalTime + car2->queueTime) <= (car4->arrivalTime + car4->queueTime)) && ((car3->arrivalTime + car3->queueTime) >= (car2->arrivalTime + car2->queueTime)))
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(west, add);
        e = false;
      }
      else if (((car3->arrivalTime + car3->queueTime) < (car4->arrivalTime + car4->queueTime)) && ((car3->arrivalTime + car3->queueTime) < (car2->arrivalTime + car2->queueTime)))
      {
        /* south goes first */
        add = moveCar(south, departed);
        addTime(north, add);
        addTime(east, add);
        addTime(west, add);
        s = false;
      }
      else
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;
      }

    }
    else if (n == true && s == true && w == true && e == true) /* if all arrive at same time: north goes first */
    {
      node = north->front;
      car1 = node->data;
      node = west->front;
      car4 = node->data;
      node = east->front;
      car2 = node->data;
      node = south->front;
      car3 = node->data;
      if (((car1->arrivalTime + car1->queueTime) <= (car4->arrivalTime + car4->queueTime)) && ((car1->arrivalTime + car1->queueTime) <= (car2->arrivalTime + car2->queueTime)) && ((car1->arrivalTime + car1->queueTime) <= (car3->arrivalTime + car3->queueTime)))
      {
        /* north goes first */
        add = moveCar(north, departed);
        addTime(south, add);
        addTime(east, add);
        addTime(west, add);
        n = false;
      }
      else if (((car1->arrivalTime + car1->queueTime) > (car4->arrivalTime + car4->queueTime)) && ((car4->arrivalTime + car4->queueTime) < (car2->arrivalTime + car2->queueTime)) && ((car4->arrivalTime + car4->queueTime) < (car3->arrivalTime + car3->queueTime)))
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;
      }
      else if (((car2->arrivalTime + car2->queueTime) < (car4->arrivalTime + car4->queueTime)) && ((car1->arrivalTime + car1->queueTime) > (car2->arrivalTime + car2->queueTime)) && ((car3->arrivalTime + car3->queueTime) > (car2->arrivalTime + car2->queueTime)))
      {
        /* east goes first */
        add = moveCar(east, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(west, add);
        e = false;
      }
      else
      {
        /* west goes first */
        add = moveCar(west, departed);
        addTime(north, add);
        addTime(south, add);
        addTime(east, add);
        w = false;
      }

    }
    else if (n == false && s == false && w == false && e == false)
    {
      timer = timer + 1;
    }

  }

  printStats(departed);

  return 0;
}

void addTime(Queue *queue, int timeAdd){
  Node * temp = queue->front;
  car * current;
  while (temp != NULL)
  {
      current = temp->data;
      if (current->arrivalTime <= timer)
      {
        current->queueTime = current->queueTime + timeAdd;
      }

      temp = temp->next;
  }
}

double moveCar(Queue *queue, List *departed){
  Node *temp;
  car *pCar;
  car *departedCar = malloc (sizeof(struct car));

  temp = queue->front;
  pCar = temp->data;
  memcpy(departedCar, pCar, sizeof(car));
  if (pCar->turn == 'L')
  {
    timer = timer + 3.5;
    insertBack(departed, departedCar);
    dequeue(queue);
    addTime(queue, 4.5);
    return 3.5;
  }
  else if (pCar->turn == 'F')
  {
    timer = timer + 2;
    insertBack(departed, departedCar);
    dequeue(queue);
    addTime(queue, 3);
    return 2;
  }
  else
  {
    timer = timer + 1.5;
    insertBack(departed, departedCar);
    dequeue(queue);
    addTime(queue, 2.5);
    return 1.5;
  }
}

void printStats(List *departed){
  Node *temp;
  car *data;
  double northWait = 0, eastWait = 0, southWait = 0, westWait = 0, overallWait = 0, maxWait = 0;
  int n = 0, e = 0, s = 0, w = 0; /* number of cars from each direction */

  printf("***********************************\nOrder of Cars Through Intersection\n***********************************\n");
  for (temp = departed->head ; temp != NULL ; temp = temp->next)
  {
    data = temp->data;
    printf("%c %c %d\n", data->direction, data->turn, data->arrivalTime);

    if (data->direction == 'N')
    {
      n++;
      northWait = northWait + data->queueTime;
    }
    else if (data->direction == 'E')
    {
      e++;
      eastWait = eastWait + data->queueTime;
    }
    else if (data->direction == 'S')
    {
      s++;
      southWait = southWait + data->queueTime;
    }
    else
    {
      w++;
      westWait = westWait + data->queueTime;
    }
    overallWait = overallWait + data->queueTime;

    if (maxWait < data->queueTime)
    {
      maxWait = data->queueTime;
    }
  }

  northWait = northWait / n;
  eastWait = eastWait / e;
  southWait = southWait / s;
  westWait = westWait / w;
  overallWait = overallWait / (n + e + s + w);

  printf("\n***********************************\nAverage Wait Times\n***********************************\n");
  printf("North Queue: %.3lf seconds\n", northWait);
  printf("East Queue: %.3lf seconds\n", eastWait);
  printf("South Queue: %.3lf seconds\n", southWait);
  printf("West Queue: %.3lf seconds\n\n", westWait);
  printf("Overall Average Wait Time: %.3lf seconds\n", overallWait);
  printf("\n***********************************\n");
  printf("Maximum Wait Time to Cross Intersection: %.3lf seconds\n\n", maxWait);

  deleteList(departed);

}
