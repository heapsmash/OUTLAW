#ifndef VBL_H
#define VBL_H

void do_VBL_ISR(void);
void MyVsync(void);
long MyVblank(void);
int GetSeconds(void);
void ResetSeconds(void);
void ResetTicks(void);
void ResetVblankFlag(void);
#endif /* VBL_H */