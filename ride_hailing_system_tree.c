#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define NAME_LEN 100
static int booking_count=0;

typedef struct location_tag {
    int x; 
    int y;
} location;


typedef struct Driver_node_tag {
    int d_ID;
    char name[NAME_LEN];
    int vehicle_type;
    location current_location;
    int status;
    float total_earnings;
    int height;
    struct Driver_node_tag *left, *right;
} Driver;


typedef struct Passenger_tag {
    int p_ID;
    char name[NAME_LEN];
    char mobile_no[11];
    int frequency;
    int height;
    struct Passenger_tag *left;
    struct Passenger_tag *right;
} Passenger;


typedef struct Booking_tag {
    int booking_id;
    int d_ID;
    int p_ID;
    int vehicle_type;
    float distance_travelled;
    int fare;
    struct Booking_tag *left;
    struct Booking_tag *right;
    int height; 
} Booking;


int max(int a, int b) 
{ 
    return (a > b) ? a : b;
}

int getDHeight(Driver *n) 
{ 
    return n ? n->height : 0; 
}
int getPHeight(Passenger *n) 
{ 
    return n ? n->height : 0; 
}

int getDBalance(Driver *n) 
{ 
    return n ? getDHeight(n->left) - getDHeight(n->right) : 0; 
}
int getPBalance(Passenger *n) 
{ 
    return n ? getPHeight(n->left) - getPHeight(n->right) : 0; 
}

int getBHeight(Booking *n) 
{ 
    return n ? n->height : 0; 
}
int getBBalance(Booking *n) 
{ 
    if (n == NULL) {
        return 0;
    }
    return getBHeight(n->left) - getBHeight(n->right); 
}



Driver* leftRotateD(Driver *root) {
    Driver*temp;
    if((root==NULL)||(root->right==NULL))
    {
        return root;
    }
    else
    {
        temp=root->right;
        root->right=temp->left;
        temp->left=root;
    }
    root->height = 1 + max(getDHeight(root->left), getDHeight(root->right));
    temp->height = 1 + max(getDHeight(temp->left), getDHeight(temp->right));
    return temp;
}

Driver* rightRotateD(Driver *root) {
    Driver*temp;
    if((root==NULL)||(root->left==NULL))
    {
        return root;
    }
    else
    {
        temp=root->left;
        root->left=temp->right;
        temp->right=root;
    }
     root->height = 1 + max(getDHeight(root->left), getDHeight(root->right));
    temp->height = 1 + max(getDHeight(temp->left), getDHeight(temp->right));
    return temp;
}

Passenger* leftRotateP(Passenger *root) {
    Passenger *temp;
    if ((root == NULL) || (root->right == NULL)) {
        return root;
    } else {
        temp = root->right;
        root->right = temp->left;
        temp->left = root;
    }
    root->height = 1 + max(getPHeight(root->left), getPHeight(root->right));
    temp->height = 1 + max(getPHeight(temp->left), getPHeight(temp->right));
    return temp;
}

Passenger* rightRotateP(Passenger *root) {
    Passenger *temp;
    if ((root == NULL) || (root->left == NULL)) {
        return root;
    } else {
        temp = root->left;
        root->left = temp->right;
        temp->right = root;
    }

    root->height = 1 + max(getPHeight(root->left), getPHeight(root->right));
    temp->height = 1 + max(getPHeight(temp->left), getPHeight(temp->right));
    return temp;
}

Booking* leftRotateB(Booking *root) {
    Booking* temp;
    if((root == NULL) || (root->right == NULL))
    {
        return root;
    }
    else
    {
        temp = root->right;
        root->right = temp->left;
        temp->left = root;
    }
    root->height = 1 + max(getBHeight(root->left), getBHeight(root->right));
    temp->height = 1 + max(getBHeight(temp->left), getBHeight(temp->right));
    return temp;
}

Booking* rightRotateB(Booking *root) {
    Booking* temp;
    if((root == NULL) || (root->left == NULL))
    {
        return root;
    }
    else
    {
        temp = root->left;
        root->left = temp->right;
        temp->right = root;
    }

    root->height = 1 + max(getBHeight(root->left), getBHeight(root->right));
    temp->height = 1 + max(getBHeight(temp->left), getBHeight(temp->right));
    return temp;
}

Driver* find_driver(Driver* root, int id) {
    if (root == NULL || root->d_ID == id) return root;
    if (id < root->d_ID) return find_driver(root->left, id);
    return find_driver(root->right, id);
}

Passenger* find_passenger(Passenger* root, int id) {
    if (root == NULL || root->p_ID == id) return root;
    if (id < root->p_ID) return find_passenger(root->left, id);
    return find_passenger(root->right, id);
}
Booking* find_booking(Booking* root, int id) {
    if (root == NULL || root->booking_id == id) return root;
    if (id < root->booking_id) return find_booking(root->left, id);
    return find_booking(root->right, id);
}

Driver* create_driver(int id, char name[], int type, int x, int y) {
    Driver* node = (Driver*)malloc(sizeof(Driver));
    if (!node) return NULL;
    node->d_ID = id;
    strcpy(node->name, name);
    node->vehicle_type = type;
    node->current_location.x = x;
    node->current_location.y = y;
    node->status = 0;
    node->total_earnings = 0;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

Passenger* create_passenger(int id, char name[], char mobile[]) {
    Passenger* node = (Passenger*)malloc(sizeof(Passenger));
    if (!node) return NULL;
    node->p_ID = id;
    strcpy(node->name, name);
    strcpy(node->mobile_no, mobile);
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

Booking* createNode(int b_id, int d_id, int p_id, int v_type) {
    Booking* newNode = (Booking*)malloc(sizeof(Booking));
    
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->booking_id = b_id;
    newNode->d_ID = d_id;
    newNode->p_ID = p_id;
    newNode->vehicle_type = v_type;
    newNode->distance_travelled = 0;
    newNode->fare = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

Driver* addDriverAVL(Driver* node, int id, char name[], int type, int x, int y) {
    if (node == NULL) return create_driver(id, name, type, x, y);
    if(node->d_ID==id) printf("Id exists");
    if (id < node->d_ID) node->left = addDriverAVL(node->left, id, name, type, x, y);
    else if (id > node->d_ID) node->right = addDriverAVL(node->right, id, name, type, x, y);
    else return node; 

    node->height = 1 + max(getDHeight(node->left), getDHeight(node->right));
    int balance = getDBalance(node);
    if (balance > 1 && id < node->left->d_ID) return leftRotateD(node);
    if (balance < -1 && id > node->right->d_ID) return rightRotateD(node);
    if (balance > 1 && id > node->left->d_ID) {
        node->left = rightRotateD(node->left);
        return leftRotateD(node);
    }
    if (balance < -1 && id < node->right->d_ID) {
        node->right = leftRotateD(node->right);
        return rightRotateD(node);
    }
    return node;
}

Passenger* addPassengerAVL(Passenger* node, int id, char name[], char mobile[]) {
    if (node == NULL) return create_passenger(id, name, mobile);
    if(node->p_ID==id) printf("Id exists");
    if (id < node->p_ID) node->left = addPassengerAVL(node->left, id, name, mobile);
    else if (id > node->p_ID) node->right = addPassengerAVL(node->right, id, name, mobile);
    else return node; 
    node->height = 1 + max(getPHeight(node->left), getPHeight(node->right));
    int balance = getPBalance(node);
    if (balance > 1 && id < node->left->p_ID) return rightRotateP(node);
    if (balance < -1 && id > node->right->p_ID) return leftRotateP(node);
    if (balance > 1 && id > node->left->p_ID) {
        node->left = leftRotateP(node->left);
        return rightRotateP(node);
    }
    if (balance < -1 && id < node->right->p_ID) {
        node->right = rightRotateP(node->right);
        return leftRotateP(node);
    }
    return node;
}

Booking* insertBooking(Booking* node, int b_id, int d_id, int p_id, int v_type) {
    if (node == NULL) {
        return createNode(b_id, d_id, p_id, v_type);
    }

    if (b_id < node->booking_id) {
        node->left = insertBooking(node->left, b_id, d_id, p_id, v_type);
    } else if (b_id > node->booking_id) {
        node->right = insertBooking(node->right, b_id, d_id, p_id, v_type);
    } else {
        return node;
    }

    node->height = 1 + max(getBHeight(node->left), getBHeight(node->right));

    int balance = getBBalance(node);

    if (balance > 1 && b_id < node->left->booking_id) {
        return leftRotateB(node);
    }

    if (balance < -1 && b_id > node->right->booking_id) {
        return rightRotateB(node);
    }

    if (balance > 1 && b_id > node->left->booking_id) {
        node->left = rightRotateB(node->left);
        return leftRotateB(node);
    }

    if (balance < -1 && b_id < node->right->booking_id) {
        node->right = leftRotateB(node->right);
        return rightRotateB(node);
    }

    return node;
}

int distance(int x1, int x2, int y1, int y2)
{
    int t1=(x1-x2)*(x1-x2);
    int t2=(y1-y2)*(y1-y2);
    return sqrt(t1+t2);
}



void searchNearest(Driver* root, int px, int py, int type, Driver** best, int* minDist) 
{
    if (!root) return;
    if(type!=-1)
    {
        if(root->status == 0 && root->vehicle_type == type) 
        {
            int d = distance(px, root->current_location.x, py,root->current_location.y);
            if (d <= 5 && d < *minDist) 
            {
                *minDist = d;
                *best = root;
            }
        }
    }
    else
    {
        if(root->status==0)
        {
            int d = distance(px, root->current_location.x, py,root->current_location.y);
            if (d <= 5 && d < *minDist) 
            {
                *minDist = d;
                *best = root;
            }       
        }
    }
    searchNearest(root->left, px, py, type, best, minDist);
    searchNearest(root->right, px, py, type, best, minDist);
}
Driver* findNearestVehicle(Driver *dHead, int p_x, int p_y, int prefType)
{
    Driver*ptr=NULL;
    int min=6;
    searchNearest(dHead,p_x,p_y,prefType,&ptr,&min);
    return ptr;
}

int requestRide(Driver *dHead, Passenger *pHead, Booking **bHead, int p_id, int p_x, int p_y,
int prefType)
{
    Passenger*pptr=find_passenger(pHead,p_id);
    if(pptr==NULL) return -1;
    Driver*dptr=findNearestVehicle(dHead,p_x, p_y, prefType);
    if(dptr!=NULL)
    {
        booking_count++;
        *bHead=insertBooking(*bHead,booking_count,dptr->d_ID,p_id, prefType);
        dptr->status=1;
    }
    return booking_count;
}


void completeRide(Driver *dHead, Passenger *pHead, Booking *bHead, int booking_id, float
dist)
{
    Booking*bptr=find_booking(bHead,booking_id);
    if(bptr!=NULL)
    {
        bptr->distance_travelled=dist;
        Driver*dptr=find_driver(dHead,bptr->d_ID);
        int fare;
        if(dptr->vehicle_type==0) fare=10*dist;
        else fare=5*dist;
        bptr->fare=fare;
        dptr->total_earnings+=fare;
        dptr->status=0;
        Passenger*ptr=find_passenger(pHead,bptr->p_ID);
        if(ptr!=NULL) ptr->frequency+=1;
    }
    else
    {
        printf("Booking id not found\n");
    }
}


float calculateDriverEarnings(Driver *dHead, int d_id)
{
    Driver*dptr=find_driver(dHead, d_id);
    if(dptr!=NULL) return dptr->total_earnings;
    else 
    {
        printf("driver not found\n");
        return 0.0;
    }
}

typedef struct {
    Driver* ptr;
    int earnings;
} Leaderboard;

void updateTopThree(Leaderboard top[], Driver* dptr) {
    int earnings=dptr->total_earnings;

    if (earnings > top[0].earnings) {
        top[2] = top[1];
        top[1] = top[0];
        top[0].earnings=earnings;
        top[0].ptr=dptr;
    } 
    else if (earnings>top[1].earnings) 
    {
        top[2] = top[1];
        top[1].earnings = earnings;
        top[1].ptr =dptr;
    } 
    else if (earnings > top[2].earnings) 
    {
        top[2].earnings = earnings;
        top[2].ptr = dptr;
    }
}

void traverse(Driver* root, Leaderboard top[]) {
    if (root == NULL) return;
    traverse(root->left, top);
    updateTopThree(top, root);
    traverse(root->right, top);
}

void displayTopDrivers(Driver *dHead)
{
    Leaderboard top[3]={ {NULL, -1}, {NULL, -1}, {NULL, -1} };
    traverse(dHead,top);
    printf("top drivers:\n");
    for(int i=0; i<3; i++)
    {
        if(top[i].ptr!=NULL)
        {
            printf("Name:%s \n",top[i].ptr->name);
        }
    }
}

typedef struct Pairs
{
    int pid;
    int did;
    int count;
    struct Pairs *left, *right;
}PairCount;

PairCount* newNode(int did, int pid) 
{
    PairCount* temp = (PairCount*)malloc(sizeof(PairCount));
    temp->did = did;
    temp->pid = pid;
    temp->count = 1;
    temp->left = temp->right = NULL;
    return temp;
}

PairCount* insertpaircount(PairCount* root, int did, int pid) {
    if (root == NULL) return newNode(did, pid);
    if (did < root->did || (did == root->did && pid < root->pid))
        root->left = insertpaircount(root->left, did, pid);
    else if (did > root->did || (did == root->did && pid > root->pid))
        root->right = insertpaircount(root->right, did, pid);
    else
        root->count++; 
    return root;
}

void inorderpaircount(PairCount*pHead, PairCount**max)
{
    if(pHead==NULL) return;
    inorderpaircount(pHead->left, max);
    if(*max==NULL|| pHead->count>(*max)->count) *max=pHead;
    inorderpaircount(pHead->right,max);
}

void inorderbooking(Booking*bHead, PairCount**unique)
{
    if(bHead==NULL) return;
    inorderbooking(bHead->left, unique);
    *unique=insertpaircount(*unique, bHead->d_ID, bHead->p_ID);
    inorderbooking(bHead->right, unique);
}

void displayFrequentPairs(Driver *dHead, Passenger *pHead, Booking *bHead)
{
    if (bHead == NULL) {
        printf("No bookings found.\n");
        return;
    }
    else
    {
        PairCount*unique=NULL;
        inorderbooking(bHead, &unique);
        PairCount*frq=NULL;
        inorderpaircount(unique,&frq);
        if(frq!=NULL)
        {
            Driver*dptr=find_driver(dHead, frq->did);
            Passenger*ptr=find_passenger(pHead, frq->pid);
            printf("Driver:%s \n", dptr->name);
            printf("Passenger:%s \n", ptr->name);
            printf("Frequency:%d\n", frq->count);
        }
    }
    
}


void displayAvailableVehicles(Driver* root) {
    if (!root) return;
    displayAvailableVehicles(root->left);
    if (root->status == 0) {
        printf("ID:%d \n", root->d_ID);
        printf("Name: %s \n", root->name);
        printf("Vehicle:");
        if(root->vehicle_type==0) printf("Cab\n");
        else printf("Bike\n");
        printf("Current Location:\n");
        printf("X-coordinate:%d\n", root->current_location.x);
        printf("Y-coordinate:%d\n", root->current_location.y);
    }
    displayAvailableVehicles(root->right);
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

void displayBookingHistory(Booking *bHead)
{
    if (bHead == NULL) {
        return;
    }
    displayBookingHistory(bHead->left);
    printf("Booking ID: %d\n", bHead->booking_id);
    printf("Driver ID: %d\n", bHead->d_ID);
    printf("Passenger ID: %d\n", bHead->p_ID);
    printf("Vehicle Type: %d\n", bHead->vehicle_type);
    printf("Distance: %f km\n", bHead->distance_travelled);
    printf("Fare: %d\n", bHead->fare);
    displayBookingHistory(bHead->right);
    
}


void range_search(Passenger*pHead, int id1, int id2)
{
    if(pHead==NULL) return;
    if (pHead->p_ID > id1) range_search(pHead->left, id1, id2);
    if(pHead->p_ID >= id1 && pHead->p_ID <= id2)
    {
        range_search(pHead->left, id1, id2);
        printf("Passenger ID : %d\n", pHead->p_ID);
        printf("Name: %s\n", pHead->name);
        printf("Mobile No: %s\n", pHead->mobile_no);
        printf("Ride Freq: %d\n", pHead->frequency);
        printf("Node Height: %d\n", pHead->height);
    }
    if (pHead->p_ID < id2) range_search(pHead->right, id1, id2);

}


Driver*delete(Driver*root, int v)
{
    if(root==NULL) return root;
    if(v<root->d_ID) root->left=delete(root->left,v);
    else if(v>root->d_ID) root->right=delete(root->right,v);
    else
    {
        if(root->left==NULL) 
        {
            Driver*temp=root->right;
            free(root);
            return temp;
        }
        if(root->right==NULL)
        {
            Driver*temp=root->left;
            free(root);
            return temp;
        }
        else
        {
            Driver*p, *q;
            p=root;
            q=root->left;
            while(q->right!=NULL)
            {
                p=q;
                q=q->right;
            }
            if(p==root)
            {
                q->right=root->right;
            }
            else
            {
                p->right=q->left;
                q->left=root->left;
                q->right=root->right;
            }
            free(root);
            root=q;

        }
    }
    root->height = 1 + max(getDHeight(root->left), getDHeight(root->right));
    int balance = getDBalance(root);
    if (balance < -1 && getDBalance(root->left) >= 0) return rightRotateD(root);
    if (balance < -1 && getDBalance(root->left) < 0) 
    {
        root->left = leftRotateD(root->left);
        return rightRotateD(root);
    }
    if (balance > 1 && getDBalance(root->right) <= 0) return leftRotateD(root);

    if (balance >1 && getDBalance(root->right) > 0) 
    {
        root->right = rightRotateD(root->right);
        return leftRotateD(root);
    }

    return root;

}


void saveDrivers(Driver* root, FILE* fp) {
    if (root == NULL) return;
    saveDrivers(root->left, fp);
    fprintf(fp, "%d %s %d %d %d %d %f\n", root->d_ID, root->name, root->vehicle_type, 
            root->current_location.x, root->current_location.y, root->status, root->total_earnings);
    saveDrivers(root->right, fp);
}

Driver* loadDrivers(Driver* root) {
    FILE* fp = fopen("drivers.txt", "r");
    if (!fp) return root;
    int id, type, x, y, status;
    char name[NAME_LEN];
    float earnings;
    while (fscanf(fp, "%d %s %d %d %d %d %f", &id, name, &type, &x, &y, &status, &earnings) != EOF) {
        root = addDriverAVL(root, id, name, type, x, y);
        Driver* d = find_driver(root, id);
        if (d) {
            d->status = status;
            d->total_earnings = earnings;
        }
    }
    fclose(fp);
    return root;
}


void savePassengers(Passenger* root, FILE* fp) {
    if (root == NULL) return;
    savePassengers(root->left, fp);
    fprintf(fp, "%d %s %s %d\n", root->p_ID, root->name, root->mobile_no, root->frequency);
    savePassengers(root->right, fp);
}

Passenger* loadPassengers(Passenger* root) {
    FILE* fp = fopen("passengers.txt", "r");
    if (!fp) return root;
    int id, freq;
    char name[NAME_LEN], mobile[11];
    while (fscanf(fp, "%d %s %s %d", &id, name, mobile, &freq) != EOF) {
        root = addPassengerAVL(root, id, name, mobile);
        Passenger* p = find_passenger(root, id);
        if (p) p->frequency = freq;
    }
    fclose(fp);
    return root;
}

int main() 
{
    Driver *driverDatabase = NULL;
    Passenger *passengerDatabase = NULL;
    Booking *bookingHistoryDatabase = NULL;

    driverDatabase = loadDrivers(driverDatabase);
    passengerDatabase = loadPassengers(passengerDatabase);

    int choice, id, type, x, y, id2;
    char name[NAME_LEN], mobile[11];
    float dist;

    while (1) {
        printf("\nRIDE-HAILING SYSTEM MENU");
        printf("\n1. Add Driver\n2. Add Passenger\n3. Request Ride\n4. Complete Ride\n");
        printf("5. Top Drivers\n6. Frequent Pairs\n7. Available Vehicles\n8. Update Location\n");
        printf("9. Delete Driver\n10. Range search\n11. History\n12. Exit\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
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
                driverDatabase = addDriverAVL(driverDatabase, id, name, type, x, y);
                break;
            case 2:
                printf("Enter Passenger ID: "); 
                scanf("%d", &id);
                printf("Enter Name: "); 
                scanf("%s", name);
                printf("Enter Mobile: "); 
                scanf("%s", mobile);
                if(strlen(mobile)==10)
                {
                    passengerDatabase = addPassengerAVL(passengerDatabase, id, name, mobile);
                }
                else printf("Invalid mobile number \n");
                
                break;
            case 3:
                int pid;
                printf("Enter Passenger ID: "); 
                scanf("%d", &pid);
                printf("Enter Pickup X: "); 
                scanf("%d", &x);
                printf("Enter Pickup Y: "); 
                scanf("%d", &y);
                printf("Enter Preferred Type (0:Cab, 1:Bike, -1:Any): "); 
                scanf("%d", &type);
                
                int b_id = requestRide(driverDatabase, passengerDatabase, &bookingHistoryDatabase, id, x, y, type);
                if (b_id != -1) printf("Ride Booked! Booking ID: %d\n", b_id);
                else printf("Ride Request Failed.\n");
                break;
            case 4:
                int bid;
                printf("Enter Booking ID: "); scanf("%d", &bid);
                printf("Enter Distance Travelled (km): "); scanf("%f", &dist);
                completeRide(driverDatabase, passengerDatabase, bookingHistoryDatabase, bid, dist);
                printf("Ride Completed!\n");
                break;
            case 5:
                displayTopDrivers(driverDatabase);
                break;
            case 6:
                displayFrequentPairs(driverDatabase,passengerDatabase,bookingHistoryDatabase);
                break;
            case 7:
                displayAvailableVehicles(driverDatabase);
                break;
            case 8:
                printf("Enter Driver ID: "); scanf("%d", &id);
                printf("Enter New X: "); scanf("%d", &x);
                printf("Enter New Y: "); scanf("%d", &y);
                updateDriverLocation(driverDatabase, id, x, y);
                break;
            case 9:
                printf("Enter Driver ID to delete: "); 
                scanf("%d", &id);
                driverDatabase=delete(driverDatabase, id);
                break;
            case 10:
                int l, r;
                printf("Enter range(l,r):");
                scanf("%d%d", &l, &r);
                range_search(passengerDatabase, l, r);
                break;
            case 11:
                displayBookingHistory(bookingHistoryDatabase);
                break;
            case 12:
                FILE *fd = fopen("drivers.txt", "w");
                saveDrivers(driverDatabase, fd);
                fclose(fd);
                FILE *fp = fopen("passengers.txt", "w");
                savePassengers(passengerDatabase, fp);
                fclose(fp);
                printf("Data Saved\n");
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }
    return 0;
}