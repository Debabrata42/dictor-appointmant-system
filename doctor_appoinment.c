#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int date, month, year, BPHigh, BPLow;
    float height, weight;
    char comment[99];
    struct Node *next;
};

struct Appointment
{
    int date, month, year;
    char name[99], gender[99];
    float height, weight;
} book[10];

int taken[10] = { 0 };

typedef struct Node node;

void clear()
{
#if 1
    system("cls");
#endif
#ifdef LINUX
    system("clear");
#endif
    printf("\033[H\033[J");
}

void insertNode(node **head, int date, int month, int year, float height, float weight, int BPHigh, int BPLow, char comment[])
{
    node *tempNode = (node *)malloc(sizeof(node));

    tempNode->date = date, tempNode->month = month, tempNode->year = year, tempNode->height = height, tempNode->weight = weight, tempNode->BPHigh = BPHigh, tempNode->BPLow = BPLow;
    strcpy(tempNode->comment, comment);
    tempNode->next = (*head);

    (*head) = tempNode;
}

void swapNode(node *tmp1, node *tmp2)
{
    char tmp[99];
    strcpy(tmp, tmp1->comment);
    strcpy(tmp1->comment, tmp2->comment);
    strcpy(tmp2->comment, tmp);
    int temp1;
    temp1 = tmp1->date;
    tmp1->date = tmp2->date;
    tmp2->date = temp1;
    temp1 = tmp1->month;
    tmp1->month = tmp2->month;
    tmp2->month = temp1;
    temp1 = tmp1->year;
    tmp1->year = tmp2->year;
    tmp2->year = temp1;
    float temp2;
    temp2 = tmp1->height;
    tmp1->height = tmp2->height;
    tmp2->height = temp2;
    temp2 = tmp1->weight;
    tmp1->weight = tmp2->weight;
    tmp2->weight = temp2;
    temp1 = tmp1->BPHigh;
    tmp1->BPHigh = tmp2->BPHigh;
    tmp2->BPHigh = temp1;
    temp1 = tmp1->BPLow;
    tmp1->BPLow = tmp2->BPLow;
    tmp2->BPLow = temp1;
}

void sortNodes(node *head)
{
    int swapped;
    node *A, *B = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        A = head;

        while (A->next != B)
        {
            if ((A->year > A->next->year) || (A->year == A->next->year && A->month > A->next->month) || (A->year == A->next->year && A->month == A->next->month && A->date > A->next->date))
            {
                swapNode(A, A->next);
                swapped = 1;
            }
            A = A->next;
        }
        B = A;
    } while (swapped);
}

void dailyWorkouts()
{
    clear();
    printf("Daily Workout & Fitness Challenges:\n\nWarm-Up:\n\n\t>> Jump rope: 2-3 minutes\n\t>> Jumping jacks: 25 reps\n\t>> Bodyweight squats: 20 reps\n\t>> Lunges: 5 reps each leg.\n\t>> Hip extensions: 10 reps each side\n\t>> Hip rotations: 5 each leg\n\t>> Forward leg swings: 10 each leg\n\t>> Side leg swings: 10 each leg\n\t>> Push-ups: 10-20 reps\n\t>> Spider-man steps: 10 reps\n\nPress enter to go to next page...\n\n");
    getchar();
    clear();
    printf("Daily Workout & Fitness Challenges:\n\nWorkout:\n\n\t>> Bodyweight squats: 20 reps\n\t>> Push-ups: 10 reps\n\t>> Walking lunges: 10 each leg\n\t>> Dumbbell rows (using a gallon milk jug or another weight): 10 each arm.\n\t>> Plank: 15 seconds\n\t>> Jumping Jacks: 30 reps\n\n\nPress enter to continue...\n\n");
    getchar();
}

void viewRecords(node *head)
{
    clear();
    node *current = head;
    printf("Daily Health Records (sorted by date):\n");
    int printed = 0;
    while (current != NULL)
    {
        char condition[99];
        float bmi = (current->weight / (current->height * current->height));
        if (bmi < 18.5)
            strcpy(condition, "Underweight");
        else if (bmi < 24.9)
            strcpy(condition, "Normal weight");
        else if (bmi < 29.9)
            strcpy(condition, "Over weight");
        else if (bmi < 34.9)
            strcpy(condition, "Obesity class I");
        else if (bmi < 39.9)
            strcpy(condition, "Obesity class II");
        else
            strcpy(condition, "Obesity class III");
        printf("\nDate: %02d/%02d/%02d\nHeight: %.2f meters(s)\nWeight: %.2f kilogram(s)\nBMI: %.1f (%s)\nBlood Pressure: %d - %d\nComment: %s\n", current->date, current->month, current->year, current->height, current->weight, bmi, condition, current->BPHigh, current->BPLow, current->comment);
        printed = 1;
        current = current->next;
    }
    if (!printed)
        printf("\nNo record have been saved yet!\n");
    printf("\n\nPress enter to continue...\n\n");
    getchar();
}

void bookAppointment()
{
    first:
    clear();
    printf("Book an Appointment:\n\nAppointment Available for Following Hours:\n\n");
    int hour1, hour2;
    for (int i=0; i<10; i++)
    {
        hour1 = 9+i, hour2 = 10+i;
        if (hour1 > 12)
            hour1 -= 12;
        if (hour2 > 12)
            hour2 -= 12;
        printf("%c. %02d:00 - %02d:00 -> %s\n", (char)(97+i), hour1, hour2, (taken[i]==1) ? "Booked" : "Available");
    }
    printf("k. Back\n\nEnter Value: ");
    char y;
    scanf("%c%*c", &y);
    int index = (y-'a');
    if (index < 0 || index > 10)
    {
        printf("\nInvalid option. Press enter to try again.\n\n");
        getchar();
        goto first;
    }
    else
    {
        if (index == 10)
            return;
        else
        {
            if (taken[index])
            {
                printf("\nSorry! The following hour is already booked.\n\nPress enter to try again.\n\n");
                getchar();
                goto first;
            }
            else
            {
                taken[index] = 1;
                clear();
                printf("Book an Appointment:\n\nName: ");
                scanf("%[^\n]%*c", book[index].name);
                printf("Date of Birth (format date/month/year): ");
                scanf("%d/%d/%d%*c", &book[index].date, &book[index].month, &book[index].year);
                printf("Gender: ");
                scanf("%s%*c", book[index].gender);
                printf("Height (meters): ");
                scanf("%f%*c", &book[index].height);
                printf("Weight (kilograms): ");
                scanf("%f%*c", &book[index].weight);
                printf("\n\nDone!\nPress any key to continue...\n\n");
                getchar();
            }
        }
    }
}

void viewAppointment()
{
    clear();
    printf("Book an Appointment:\n\nAppointment Available for Following Hours:\n\n");
    int hour1, hour2;
    for (int i=0; i<10; i++)
    {
        hour1 = 9+i, hour2 = 10+i;
        if (hour1 > 12)
            hour1 -= 12;
        if (hour2 > 12)
            hour2 -= 12;
        printf("%c. %02d:00 - %02d:00 -> %s %s\n", (char)(97+i), hour1, hour2, (taken[i]==1) ? "Booked by" : "Available", (taken[i]==1) ? book[i].name : "");
    }
    printf("\nPress enter to continue...\n\n");
    getchar();
}

void contactDoctors()
{
    clear();
    printf("Contact Health Consultants:\n\nName: Dr XYZ (Consultant Physician)\nSpecialities: General medicine\nWorks at: The ABC Hospital\nEmail: xxxxxxxxxxxxx@gmail.com\nPhone: +880xxxxxxxxxx\n\nName: Dr XYZ (Consultant Physician)\nSpecialities: General medicine\nWorks at: The ABC Hospital\nEmail: xxxxxxxxxxxxx@gmail.com\nPhone: +880xxxxxxxxxx\n\nName: Dr XYZ (Consultant Physician)\nSpecialities: General medicine\nWorks at: The ABC Hospital\nEmail: xxxxxxxxxxxxx@gmail.com\nPhone: +880xxxxxxxxxx\n\n\nPress enter to go to next page...\n\n");
    getchar();
    clear();
    printf("Contact Health Consultants:\n\nName: Dr XYZ (Consultant Surgeon)\nSpecialities: General surgery\nWorks at: The ABC Medical Centre\nEmail: xxxxxxxxxxxxx@yahoo.com\nPhone: +880xxxxxxxxxx\n\nName: Dr XYZ (Consultant Surgeon)\nSpecialities: General surgery\nWorks at: The ABC Medical Centre\nEmail: xxxxxxxxxxxxx@yahoo.com\nPhone: +880xxxxxxxxxx\n\nName: Dr XYZ (Consultant Surgeon)\nSpecialities: General surgery\nWorks at: The ABC Medical Centre\nEmail: xxxxxxxxxxxxx@yahoo.com\nPhone: +880xxxxxxxxxx\n\n\nPress enter to continue...\n\n");
    getchar();
}

void aboutProject()
{
    clear();
    printf("About This Project:\n\nExpected Outcome:\n\n1. User can easily get best instruction for their according diseases.\n2. Easy doctor's appointment technology.\n3. Easy ambulance service.\n4.Easy user experience.\n\nMotivation:\n\nMany people in our country live in village. They can not get proper treatment for the lake of Doctor. I also live in village there are many problem in village such as lack of vehicles, lack of money etc. When some one is suddenly infected with a dangerous disease, It is not possible to provide immediate medical care. So, To get rid of all these problems, I make this website. By using this application people can get best guideline for their disease. From this website they can get emergency ambulance.\n\nObjective:\n\nThe \"Health guide\" provides function on identify medication usages instruction. Meet your wellness goals with the health guide that's right for you. Get complete tips for weight loss, managing diabetes etc. Users will easily find health trainers and proper nursing. If users need a best doctor in their area, they can easily make a doctor appointment.\n\nPress enter to continue...\n\n");
    getchar();
}

int main()
{
    node *head = NULL;
    int x = 0;
    while (x != 7)
    {
        clear();
        printf("## HEALTH GUIDE AND SERVICE ##\n==============================\n");
        printf("\nChoose an option:\n\n1. Workout & Health Records\n2. Doctor's Appointment\n3. Contact Health Consultants\n4. About This Project\n5. Exit\n\nEnter Value: ");
        scanf("%d%*c", &x);
        if (x < 1 || x > 5)
        {
            printf("\nInvalid option. Press enter to try again.\n\n");
            getchar();
        }
        else
        {
            if (x == 1)
            {
                char y = 'a';
                while (y != 'c')
                {
                    clear();
                    printf("Workout & Health Records:\n\nChoose an option:\n\na. Daily Workouts\nb. Daily Health Records\nc. Back\n\nEnter Value: ");
                    scanf("%c%*c", &y);
                    if (y < 'a' || y > 'c')
                    {
                        printf("\nInvalid option. Press enter to try again.\n\n");
                        getchar();
                    }
                    else
                    {
                        if (y == 'a')
                            dailyWorkouts();
                        else if (y == 'b')
                        {
                            char z = 'a';
                            while (z != 'c')
                            {
                                clear();
                                printf("Daily Health Records:\n\nChoose an option:\n\na. Save New Health Records\nb. View Previously Saved Records\nc. Back\n\nEnter Value: ");
                                scanf("%c%*c", &z);
                                if (z < 'a' || z > 'c')
                                {
                                    printf("\nInvalid option. Press enter to try again.\n\n");
                                    getchar();
                                }
                                else
                                {
                                    if (z == 'a')
                                    {
                                        int n;
                                        clear();
                                        printf("Save New Health Records:\n\nHow many records do you want to save?\n\nEnter value: ");
                                        scanf("%d%*c", &n);
                                        int date, month, year, BPHigh, BPLow;
                                        float height, weight;
                                        char comment[99];
                                        for (int i = 0; i < n; i++)
                                        {
                                            printf("\nDate (date/month/year): ");
                                            scanf("%d/%d/%d%*c", &date, &month, &year);
                                            printf("Height (meters): ");
                                            scanf("%f%*c", &height);
                                            printf("Weight (kilograms): ");
                                            scanf("%f%*c", &weight);
                                            printf("Blood Pressure (eg. 130 80): ");
                                            scanf("%d %d%*c", &BPHigh, &BPLow);
                                            printf("Comment: ");
                                            scanf("%[^\n]%*c", comment);
                                            insertNode(&head, date, month, year, height, weight, BPHigh, BPLow, comment);
                                        }
                                        sortNodes(head);
                                        printf("\n\nDone!\nPress any key to continue...\n\n");
                                        getchar();
                                    }
                                    else if (z == 'b')
                                        viewRecords(head);
                                    else
                                        continue;
                                }
                            }
                        }
                        else
                            continue;
                    }
                }
            }
            else if (x == 2)
            {
                char y = 'a';
                while (y != 'c')
                {
                    clear();
                    printf("Doctor's Appointment:\n\nChoose an option:\n\na. Book an Appointment\nb. View Existing Appointment\nc. Back\n\nEnter Value: ");
                    scanf("%c%*c", &y);
                    if (y < 'a' || y > 'c')
                    {
                        printf("\nInvalid option. Press enter to try again.\n\n");
                        getchar();
                    }
                    else
                    {
                        if (y == 'a')
                            bookAppointment();
                        else if (y == 'b')
                            viewAppointment();
                        else if (y == 'c')
                            continue;
                    }
                }
            }
            else if (x == 3)
                contactDoctors();
            else if (x == 4)
                aboutProject();
            else if (x == 5)
            {
                printf("\nThank you for using my project.\n\n");
                return 0;
            }
        }
    }
    return 0;
}
