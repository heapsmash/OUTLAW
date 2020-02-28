#include <stdio.h>

#define NUM_CODES 7

int g_ikbd_buffer[NUM_CODES];
int g_front = -1;
int g_rear = -1;

int isFull(void)
{
    if ((g_front == g_rear + 1) || (g_front == 0 && g_rear == NUM_CODES - 1))
        return 1;
    return 0;
}

int isEmpty(void)
{
    if (g_front == -1)
        return 1;
    return 0;
}

void enQueue(int element)
{
    if (isFull())
        printf("\n Queue is full!! \n");
    else
    {
        if (g_front == -1)
            g_front = 0;
        g_rear = (g_rear + 1) % NUM_CODES;
        g_ikbd_buffer[g_rear] = element;
        printf("\n Inserted -> %d", element);
    }
}

int deQueue(void)
{
    int element;
    if (isEmpty())
    {
        printf("\n Queue is empty !! \n");
        return (-1);
    }
    else
    {
        element = g_ikbd_buffer[g_front];
        if (g_front == g_rear)
        {
            g_front = -1;
            g_rear = -1;
        } /* Q has only one element, so we reset the queue after dequeing it. ? */
        else
        {
            g_front = (g_front + 1) % NUM_CODES;
        }
        printf("\n Deleted element -> %d \n", element);
        return (element);
    }
}

void display(void)
{
    int i;
    if (isEmpty())
        printf(" \n Empty Queue\n");
    else
    {
        printf("\n g_Front -> %d ", g_front);
        printf("\n g_ikbd_buffer -> ");
        for (i = g_front; i != g_rear; i = (i + 1) % NUM_CODES)
        {
            printf("%d ", g_ikbd_buffer[i]);
        }
        printf("%d ", g_ikbd_buffer[i]);
        printf("\n g_Rear -> %d \n", g_rear);
    }
}

int main(int argc, char *argv[])
{
    g_front = -1; 
    g_rear = -1; 

    /* Fails because g_front = -1 */
    deQueue();

    enQueue(1);
    enQueue(2);
    enQueue(3);
    enQueue(4);
    enQueue(5);

    /* Fails to enqueue because g_front == 0 && g_rear == NUM_CODES - 1 */
    enQueue(6);

    display();
    deQueue();

    display();

    enQueue(7);
    display();

    /* Fails to enqueue because g_front == g_rear + 1 */
    enQueue(8);

    return 0;
}
