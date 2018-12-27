#define MAXCOUNT 100

typedef struct {
	double Key;
	char Name[11];
}PQItem;

typedef PQItem PQArray[MAXCOUNT +1];

typedef struct {
		int Count;
		PQArray ItemArray;
}PriorityQueue;
