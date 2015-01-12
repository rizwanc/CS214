
//Structure to hold a user's order
struct Order
{
	char title[300];  //Array for holding the title of the book
	float price; //Price of the book
	int customerID; //Id of the customer
	float remainingCredit; //Remaining assets of the customer
	char category[50]; //Category the book belongs too
	
	struct Order *next; //Pointer to the next customer order
};
typedef struct Order Order;

//Create a new order for a user
void *createNewOrder(void *orderFile);

//Process the order for a user
void *processOrder(void *o);

//Destory user order
void destroyOrder(Order *);
