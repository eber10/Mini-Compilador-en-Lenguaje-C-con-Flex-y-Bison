#include <stdio.h>
#include <stdlib.h>
#include "temp.h"


int main() {

list = insertElement(list);
list = insertElement(list);
addVar("a", &list->table);
setVarList("a", 2, list);
addVar("b", &list->table);
setVarList("b", 5, list);
addVar("i", &list->table);
setVarList("i", 0, list);
addVar("j", &list->table);
t0 = getVarList("a", list);
t1 = 1;
t2 = t0 > t1;
if (t2) goto L0;
goto L1;
L0:
list = insertElement(list);
t3 = 0;
setVarList("j", t3, list);
L3:
t4 = getVarList("j", list);
t5 = 10;
t6 = t4 < t5;
if (t6) goto L4;
goto L5;
L4:
list = insertElement(list);
t7 = getVarList("a", list);
t8 = getVarList("b", list);
t9 = t7 + t8;
setVarList("a", t9, list);
t10 = getVarList("j", list);
t11 = 1;
t12 = t10 + t11;
setVarList("j", t12, list);
t13 = getVarList("a", list);
t14 = 10;
t15 = t13 > t14;
if (t15) goto L6;
goto L7;
L6:
list = insertElement(list);
printf("%s: %d\n", "a", getVarList("a", list));
list = removeElement(list);
goto L8;
L7:
list = insertElement(list);
printf("%s: %d\n", "b", getVarList("b", list));
list = removeElement(list);
goto L8;
L8:
list = removeElement(list);
goto L3;
L5:
list = removeElement(list);
goto L2;
L1:
list = insertElement(list);
L9:
t16 = getVarList("i", list);
t17 = 5;
t18 = t16 < t17;
if (t18) goto L10;
goto L11;
L10:
list = insertElement(list);
addVar("c", &list->table);
t19 = getVarList("a", list);
t20 = getVarList("i", list);
t21 = t19 + t20;
setVarList("c", t21, list);
t22 = getVarList("i", list);
t23 = 1;
t24 = t22 + t23;
setVarList("i", t24, list);
printf("%s: %d\n", "c", getVarList("c", list));
list = removeElement(list);
goto L9;
L11:
list = removeElement(list);
goto L2;
L2:
printf("%s: %d\n", "a", getVarList("a", list));
printf("%s: %d\n", "b", getVarList("b", list));
list = removeElement(list);
list = removeElement(list);

return 0;
}