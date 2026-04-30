#include <stdio.h>
#include <string.h>

#define MAX_CAPACITY 10   // أقصى عدد عناصر ممكن نخزنها

// بنية ال Buffer
typedef struct
{
    char ArrData[MAX_CAPACITY]; 
    int WritePos;               
    int ReadPos;               
    int ActiveElement;        
} RingBuffer;


//تهيئة لل Buffer
void PrepareBuffer(RingBuffer* rb)
{
    rb->WritePos = 0;     
    rb->ReadPos = 0;
    rb->ActiveElement = 0; 
}

// تحقق إذا Buffer مليان
int BufferFull(RingBuffer* rb)
{
    return rb->ActiveElement == MAX_CAPACITY;
}

// تحقق إذا Buffer فاضي
int BufferEmpty(RingBuffer* rb) 
{
    return rb->ActiveElement == 0;
}

// إضافة عنصر جديد
void PushData(RingBuffer* rb, char val)
{

    if (BufferFull(rb)) 
    {
        printf("\n[Warning] Capacity Reached! Overflow At: %c", val);
        return;
    }

    rb->ArrData[rb->WritePos] = val;

    rb->WritePos = (rb->WritePos + 1) % MAX_CAPACITY;

    rb->ActiveElement++;
}

// سحب عنصر من البفر
char PopData(RingBuffer* rb) 
{

    if (BufferEmpty(rb))
    {
        printf("\n[Warning] No Data Available (Underflow).");
        return '\0';
    }

    char OutputValue = rb->ArrData[rb->ReadPos];

    rb->ReadPos = (rb->ReadPos + 1) % MAX_CAPACITY;

    rb->ActiveElement--;

    return OutputValue;
}

int main()
{

    RingBuffer MyRing;

    // تهيئة البفر قبل الاستخدام
    PrepareBuffer(&MyRing);

    char InputText[64];

    printf("Enter Student Name: ");
    scanf("%63s", InputText); // حطيت limit لحتى ما يصير overflow

    // إضافة suffix للنص
    strcat(InputText, "-CE-ESY");

    printf("\nProcessing String: %s\n", InputText);
    printf("Storing to Ring Buffer...\n");

    int len = strlen(InputText);

    // تخزين كل حرف بال Buffer
    for (int j = 0; j < len; j++)
    {
        PushData(&MyRing, InputText[j]);
    }

    printf("\n\nRetrieving Data...\n");

    // سحب وطباعة كل البيانات
    while (!BufferEmpty(&MyRing))
    {
        printf("%c",PopData(&MyRing));
    }

    printf("\n\nTask Complete.\n");

    return 0;
}