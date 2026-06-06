#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define NAME_LEN 100
static int count=0;
typedef struct location_tag
{
    int x;
    int y;
}location;

typedef struct Driver_node_tag
{
    int d_ID;
    char name[NAME_LEN];
    int vehicle_type;
    location current_location;
    int status;
    float total_earnings;
    struct Driver_node_tag*next;
}Driver;

Driver*create_driver(int id, char name[], int type, int x, int y)
{
    Driver*node=(Driver*)malloc(sizeof(Driver));
    if(node==NULL) return NULL;
    node->d_ID=id;
    strcpy(node->name, name);
    node->vehicle_type=type;
    node->current_location.x=x;
    node->current_location.y=y;
    node->status=0;
    node->total_earnings=0;
    node->next=NULL;
    return node;
}

typedef struct Passenger_tag
{
    int p_ID;
    char name[NAME_LEN];
    char mobile_no[10];
    int frequency;
    struct Passenger_tag*next;
}Passenger;

Passenger*create_passenger(int id, char name[], char mob[])
{
    Passenger*node=(Passenger*)malloc(sizeof(Passenger));
    if(node==NULL) return NULL;
    else
    {
        node->p_ID=id;
        strcpy(node->name, name);
        strcpy(node->mobile_no, mob);
        node->frequency=0;
        node->next=NULL;
    }
    return node;
}

typedef struct Booking_tag
{
    int booking_id;
    int d_ID;
    int p_ID;
    int vehicle_type;
    float distance_travelled; 
    int fare; 
    struct Booking_tag*next;
}Booking;

Booking*create_Booking(int did, int pid, int type )
{
    Booking*node=(Booking*)malloc(sizeof(Booking));
    if(node!=NULL)
    {
        count++;
        node->booking_id=count;
        node->d_ID=did;
        node->p_ID=pid;
        node->vehicle_type=type;
        node->distance_travelled=0;
        node->fare=0;
        node->next=NULL;
    }
    return node;
}

Driver* find_driver(Driver* dHead, int id) {
    Driver* dptr = dHead;
    while (dptr != NULL) {
        if (dptr->d_ID == id) return dptr;
        dptr = dptr->next;
    }
    return NULL;
}

Passenger*find_passenger(Passenger*pHead, int id)
{
    Passenger* dptr = pHead;
    while (dptr != NULL) {
        if (dptr->p_ID == id) return dptr;
        dptr = dptr->next;
    }
    return NULL;
}

Booking*find_Booking(Booking*dHead, int id)
{
    Booking* dptr = dHead;
    while (dptr != NULL) {
        if (dptr->booking_id == id) return dptr;
        dptr = dptr->next;
    }
    return NULL;
}

bool valid_vehicle(int n)
{
    if(n<-1 || n>1) return false;
    return true;
}
bool valid_status(int s)
{
    if(s != 0 && s != 1) return false;
    return true;
}

int distance(int x1, int x2, int y1, int y2)
{
    int t1=(x1-x2)*(x1-x2);
    int t2=(y1-y2)*(y1-y2);
    return sqrt(t1+t2);
}
Driver* divide(Driver* lptr)
{
    Driver *slow, *fast, *nptr;

    slow = lptr;
    fast = lptr->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    nptr = slow->next;
    slow->next = NULL;

    return nptr;
}
void mergeArray(Driver* arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Driver* L[n1];
    Driver* R[n2];

    for (int i = 0; i < n1; i++) 
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) 
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->total_earnings >= R[j]->total_earnings) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        k++;
        i++;
    }
    while (j < n2) 
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}
void sortDriverArray(Driver* arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        sortDriverArray(arr, left, mid);
        sortDriverArray(arr, mid + 1, right);

        mergeArray(arr, left, mid, right);
    }
}

void addDriver(Driver **head, int id, char name[], int type, int x, int y)
{
    if(id>0 && valid_vehicle(type))
    {
        Driver*ptr=*head;
        if(ptr==NULL) *head=create_driver(id,name,type,x,y);
        else{
            int dup=0;
            Driver*prev=NULL;
            while(ptr!=NULL && dup==0)
            {
                if(id!=ptr->d_ID) 
                {
                    prev=ptr;
                    ptr=ptr->next;
                }
                else dup=1;
            }
            if(dup==0)prev->next=create_driver(id,name,type,x,y);
            else printf("Duplicate found, could not add");
        }
    }
    else printf("Invalid ID or Vehicle type");
}

void addPassenger(Passenger **head, int id, char name[], char mobile[])
{
    if(id>0)
    {
        Passenger*node=create_passenger(id,name, mobile);
        if(node!=NULL)
        {
            Passenger*ptr=*head;
            if(ptr==NULL) *head=node;
            else
            {
                int dup=0;
                while(ptr->next!=NULL && dup==0)
                {
                    if(ptr->p_ID!=id) ptr=ptr->next;
                    else dup=1;
                }
                if(dup==1) printf("Duplicate found, could not add");
                else ptr->next=node;
            }
        }
    }
    else printf("Invalid ID\n");
}

Driver* findNearestVehicle(Driver *dHead, int p_x, int p_y, int prefType)
{
    Driver*ptr=dHead;
    int found=0;
    Driver*match=NULL;
    int minDist=6;
    while(ptr!=NULL)
    {
        if(ptr->status==0 && ptr->vehicle_type==prefType)
        {
            int dist=distance(p_x, ptr->current_location.x, p_y, ptr->current_location.y);
            if(dist<=5 && dist<minDist)
            {
                match=ptr;
                minDist=dist;
            } 
        }
        ptr=ptr->next;
    }
    return match;
}

int requestRide(Driver *dHead, Passenger *pHead, Booking **bHead, int p_id, int p_x, int p_y,
int prefType)
{
    Passenger *ptr=pHead;
    while(ptr!=NULL && ptr->p_ID!=p_id)
    {
        ptr=ptr->next;
    }
    if(ptr==NULL)
    {
        printf("Passenger not found");
        return -1;
    }
    else
    {
        Driver*available_driver=NULL;
        if(prefType == -1) 
        {
            Driver* cab = findNearestVehicle(dHead, p_x, p_y, 0);
            Driver* bike = findNearestVehicle(dHead, p_x, p_y, 1);
            
            if (cab && bike) {
                int dCab = distance(p_x, cab->current_location.x, p_y, cab->current_location.y);
                int dBike = distance(p_x, bike->current_location.x, p_y, bike->current_location.y);
                available_driver = (dCab <= dBike) ? cab : bike;
            } else {
                available_driver = cab ? cab : bike;
            }
        }
        else available_driver=findNearestVehicle(dHead,p_x, p_y, prefType);
        if(available_driver!=NULL)
        {
            Booking*b_node=create_Booking(available_driver->d_ID, ptr->p_ID, prefType);
            available_driver->status=1;
            Booking*bptr=*bHead;
            if(bptr==NULL)
            {
                *bHead=b_node;
            }
            else
            {
                while(bptr->next!=NULL)
                {
                    bptr=bptr->next;
                }
                bptr->next=b_node;
            }
            printf("Name of driver:%s", available_driver->name);
            printf("Distance from you:%d\n", distance(available_driver->current_location.x, p_x, available_driver->current_location.y, p_y));
            return b_node->booking_id;
        }
        else return -1;
    }
}

void completeRide(Driver *dHead, Passenger *pHead, Booking *bHead, int booking_id, float
distance)
{
    Booking*bptr=find_Booking(bHead,booking_id);
    if(bptr==NULL || bptr->fare!=0) printf("Booking id not found or the ride is already completed.");
    else
    {
        bptr->distance_travelled=distance;
        int fare;
        if(bptr->vehicle_type==0) fare=10*distance;
        else fare=5*distance;
        bptr->fare=fare;

        Driver*dptr=find_driver(dHead, bptr->d_ID);
        dptr->total_earnings=dptr->total_earnings+fare;
        dptr->status=0;

        Passenger*ptr=find_passenger(pHead, bptr->p_ID);
        ptr->frequency+=1;
        printf("Ride Completed.\n");
    }
}

float calculateDriverEarnings(Driver *dHead, int d_id)
{
    /*Booking*bptr=&BookingList;
    int sum=0;
    while(bptr!=NULL)
    {
        if(bptr->d_ID==d_id) sum=sum+bptr->fare;
        bptr=bptr->next;
    }
    return sum;*/
    Driver*node=find_driver(dHead, d_id);
    if(node!=NULL) return node->total_earnings;
    else
    {
        printf("Not found");
        return 0;
    }
}

void displayTopDrivers(Driver *dHead, Booking *bHead)
{
    if(dHead!=NULL)
    {   
        int count = 0;
        Driver *temp = dHead;
        while (temp) 
        { 
            count++; 
            temp = temp->next; 
        } 
        Driver** ptrArray = (Driver**)malloc(count * sizeof(Driver*));
        temp = dHead;
        for (int i = 0; i < count; i++) {
            ptrArray[i] = temp;
            temp = temp->next;
        }
        sortDriverArray(ptrArray, 0, count - 1);
        for(int i=0; i<3 && i<count; i++)
        {
            printf("Name:%s \n", ptrArray[i]->name);
            printf("Total Earning: %f \n", ptrArray[i]->total_earnings);
        }
    }
    else printf("No Drivers found\n");
}

typedef struct Pairs
{
    int pid;
    int did;
    int count;
    struct Pairs*next;
}Pairs;

Pairs*get_pair(Pairs**pHead, int d, int p)
{
    Pairs*ptr=*pHead;
    while(ptr!=NULL)
    {
        if(ptr->did==d && ptr->pid==p)
        {
            return ptr;
        }
        ptr=ptr->next;
    }
    Pairs*node=(Pairs*)malloc(sizeof(Pairs));
    node->did=d;
    node->pid=p;
    node->count=0;
    node->next=*pHead;
    *pHead=node;
    return node;

}

void displayFrequentPairs(Driver *dHead, Passenger *pHead, Booking *bHead)
{
    if (bHead == NULL) 
    { printf("No bookings found.\n"); 
        return;
    }
    Pairs*pairList=NULL;
    Booking*bptr=bHead;
    while(bptr!=NULL)
    {
        Pairs*p=get_pair(&pairList, bptr->d_ID, bptr->p_ID);
        p->count++;
        bptr=bptr->next;
    }
    int maxCount=0;
    Pairs*p=pairList;
    while(p!=NULL)
    {
        if(p->count>maxCount) maxCount=p->count;
        p=p->next;
    }
    p=pairList;
    while(maxCount!=0 && p!=NULL)
    {
        if(p->count==maxCount)
        {
            Driver*dptr=find_driver(dHead, p->did);
            Passenger*ptr=find_passenger(pHead, p->pid);
            printf("Driver:%s \n", dptr->name);
            printf("Passenger:%s \n", ptr->name);
            printf("Frequency:%d\n", maxCount);
        }
        p=p->next;
    }

    p = pairList;
    while (p != NULL) {
        Pairs* temp = p;
        p = p->next;
        free(temp);
    }

}

void displayAvailableVehicles(Driver *dHead)
{
    Driver *dptr=dHead;
    while(dptr!=NULL)
    {
        if(dptr->status==0)
        {
            printf("ID:%d \n", dptr->d_ID);
            printf("Name: %s \n", dptr->name);
            printf("Vehicle:");
            if(dptr->vehicle_type==0) printf("Cab\n");
            else printf("Bike\n");
            printf("Current Location:\n");
            printf("X-coordinate:%d\n", dptr->current_location.x);
            printf("Y-coordinate:%d\n", dptr->current_location.y);
        }
        dptr=dptr->next;
    }
}

void updateDriverLocation(Driver *dHead, int d_id, int new_x, int new_y)
{
    Driver*dptr=find_driver(dHead, d_id);
    if(dptr!= NULL)
    {    if(dptr->status==1)
        {
            printf("Booked right now\n");
        }
        else
        {
            dptr->current_location.x=new_x;
            dptr->current_location.y=new_y;
        }
    }
    else printf("Driver not found!\n");
}

void deleteDriver(Driver **dHead, int d_id)
{
    Driver*prev=NULL;
    Driver*curr=*dHead;
    if(curr==NULL) printf("No drivers currently");
    else
    {
        
        while(curr!=NULL && curr->d_ID!=d_id)
        {
            prev=curr;
            curr=curr->next;
        }
        if(curr!=NULL)
        {
            if(curr->status==0)
            {
                if(prev!=NULL)
                {
                    prev->next=curr->next;
                    free(curr);
                }
                else
                {
                    *dHead=curr->next;
                }
            }
            else
            {
                printf("Error, driver is booked");
            }
        }
        
        
    }
}

void displayBookingHistory(Booking *bHead)
{
    if (bHead == NULL) {
        printf("No bookings available\n");
        return;
    }

    Booking *temp = bHead;

    while (temp) {
        printf("Booking ID: %d\n", temp->booking_id);
        printf("Driver ID: %d\n", temp->d_ID);
        printf("Passenger ID: %d\n", temp->p_ID);
        printf("Vehicle Type: %d\n", temp->vehicle_type);
        printf("Distance: %f km\n", temp->distance_travelled);
        printf("Fare: %d\n", temp->fare);
        temp = temp->next;
    }
}

int main() {
    Driver *DriverList = NULL;
    Passenger *PassengerList = NULL;
    Booking *BookingList = NULL;

    addDriver(&DriverList, 101, "Arjun", 0, 2, 3);   
    addDriver(&DriverList, 102, "Sita", 1, 10, 10);  
    addDriver(&DriverList, 103, "Kabir", 1, 1, 1);   
    addDriver(&DriverList, 104, "Neha_D", 0, 4, 4); 

    addPassenger(&PassengerList, 1, "Neha", "9876543210");
    addPassenger(&PassengerList, 2, "Rahul", "8888877777");
    addPassenger(&PassengerList, 3, "Amit", "7776665554");

    int op = -1;
    while (op != 0) {
        printf("\n--- RIDE-HAILING-SYSTEM ---\n");
        printf("1. Add Driver\n2. Add Passenger\n3. Request Ride\n4. Complete Ride\n");
        printf("5. Top Drivers\n6. Frequent Pairs\n7. Available Vehicles\n8. Update Location\n");
        printf("9. Delete Driver\n10. History\n0. Exit\n");
        printf("Choice: ");
        scanf("%d", &op);

        if (op == 1) {
            int id, type, x, y;
            char name[NAME_LEN];
            printf("Enter Driver ID: "); 
            scanf("%d", &id);
            printf("Enter Name: "); 
            scanf("%s", name);
            printf("Enter Type (0:Cab, 1:Bike): "); 
            scanf("%d", &type);
            printf("Enter X Coordinate: "); 
            scanf("%d", &x);
            printf("Enter Y Coordinate: "); 
            scanf("%d", &y);
            addDriver(&DriverList, id, name, type, x, y);
        } 
        else if (op == 2) {
            int id;
            char name[NAME_LEN], mob[10];
            printf("Enter Passenger ID: "); 
            scanf("%d", &id);
            printf("Enter Name: "); 
            scanf("%s", name);
            printf("Enter Mobile: "); 
            scanf("%s", mob);
            if(strlen(mob)==10)
            {
                addPassenger(&PassengerList, id, name, mob);
            }
            else printf("Invalid mobile number \n");
        } 
        else if (op == 3) {
            int pid, x, y, type;
            printf("Enter Passenger ID: "); 
            scanf("%d", &pid);
            printf("Enter Pickup X: "); 
            scanf("%d", &x);
            printf("Enter Pickup Y: "); 
            scanf("%d", &y);
            printf("Enter Preferred Type (0:Cab, 1:Bike, -1:Any): "); 
            scanf("%d", &type);
            if(valid_vehicle(type))
            { 
                int bid = requestRide(DriverList, PassengerList, &BookingList, pid, x, y, type);
                if (bid != -1) printf("Ride Booked!\n");
                else printf("No nearby driver found.\n");
            }
            else printf("Invalid Vehicle\n");
        } 
        else if (op == 4) {
            int bid;
            float dist;
            printf("Enter Booking ID: "); scanf("%d", &bid);
            printf("Enter Distance Travelled (km): "); scanf("%f", &dist);
            completeRide(DriverList, PassengerList, BookingList, bid, dist);
            
        } 
        else if (op == 5) {
            displayTopDrivers(DriverList, BookingList);
        } 
        else if (op == 6) {
            displayFrequentPairs(DriverList, PassengerList, BookingList);
        } 
        else if (op == 7) {
            displayAvailableVehicles(DriverList);
        } 
        else if (op == 8) {
            int id, x, y;
            printf("Enter Driver ID: "); scanf("%d", &id);
            printf("Enter New X: "); scanf("%d", &x);
            printf("Enter New Y: "); scanf("%d", &y);
            updateDriverLocation(DriverList, id, x, y);
        } 
        else if (op == 9) {
            int id;
            printf("Enter Driver ID to delete: "); 
            scanf("%d", &id);
            deleteDriver(&DriverList, id);
        } 
        else if (op == 10) {
            displayBookingHistory(BookingList);
        }
    }
    return 0;
}
