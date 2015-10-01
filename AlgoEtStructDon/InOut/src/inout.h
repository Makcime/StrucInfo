#if !defined(INOUT_H)
#define INOUT_H
//---------------------------------------------------------------------------
#include <limits>
//---------------------------------------------------------------------------
const int LINE_LENGTH = 80;
//---------------------------------------------------------------------------
void Purge(void);
int Stop(void);
void Pause(void);
void ShowTitle(const char* titre, char s, int lineLength=LINE_LENGTH);
void Center(const char* message, int lineLength=LINE_LENGTH);
int ReadInt(const char* message, int min=std::numeric_limits< int >::min(), int max=std::numeric_limits< int >::max());
double ReadDouble(const char* message, double min=-std::numeric_limits< double >::max(),
                  double max=std::numeric_limits< double >::max());
char ReadChar(const char* message, const char* chars);
void Suspend(unsigned long d);
char* ReadString(const char* message, int longMax=80);
char* ReadStringUp(const char* message, int longMax=80);
//---------------------------------------------------------------------------
#endif
