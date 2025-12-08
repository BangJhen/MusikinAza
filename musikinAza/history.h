#ifndef history_h
#define history_h

#include "song.h"

typedef struct elmHistory* addressHistory;

struct elmHistory {
    Song info;
    addressHistory next;
};

struct History {
    addressHistory top;
};

void createHistory(History &H);
void pushHistory(History &H, Song s);
void popHistory(History &H, Song &s);
void showHistory(History H);
bool isHistoryEmpty(History H);

#endif
