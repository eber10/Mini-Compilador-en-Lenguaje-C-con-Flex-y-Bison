#include <stdio.h>
#include <stdlib.h>
#include "temp.h"


int main() {

list = insertElement(list);
list = insertElement(list);
addVar("x", &list->table);
setVarList("x", 0, list);
addVar("i", &list->table);
setVarList("i", 1, list);
addVar("j", &list->table);
L0:
t0 = getVarList("i", list);
t1 = 50;
t2 = t0 <= t1;
if (t2) goto L1;
goto L2;
L1:
list = insertElement(list);
t3 = 1;
t4 = 1;
t5 = t3 <= t4;
t6 = getVarList("i", list);
t7 = 17;
t8 = t6 <= t7;
t9 = t5 && t8;
t10 = 29;
t11 = getVarList("i", list);
t12 = t10 <= t11;
t13 = getVarList("i", list);
t14 = 33;
t15 = t13 <= t14;
t16 = t12 && t15;
t17 = t9 || t16;
if (t17) goto L3;
goto L4;
L3:
list = insertElement(list);
t18 = 1;
setVarList("j", t18, list);
L6:
t19 = getVarList("j", list);
t20 = 13;
t21 = t19 <= t20;
if (t21) goto L7;
goto L8;
L7:
list = insertElement(list);
t22 = getVarList("x", list);
t23 = 7;
t24 = t22 + t23;
setVarList("x", t24, list);
t25 = getVarList("j", list);
t26 = 1;
t27 = t25 + t26;
setVarList("j", t27, list);
list = removeElement(list);
goto L6;
L8:
list = removeElement(list);
goto L5;
L4:
list = insertElement(list);
t28 = 1;
setVarList("j", t28, list);
L9:
t29 = getVarList("j", list);
t30 = 17;
t31 = t29 <= t30;
if (t31) goto L10;
goto L11;
L10:
list = insertElement(list);
t32 = getVarList("x", list);
t33 = 13;
t34 = t32 + t33;
setVarList("x", t34, list);
t35 = getVarList("j", list);
t36 = 1;
t37 = t35 + t36;
setVarList("j", t37, list);
list = removeElement(list);
goto L9;
L11:
list = removeElement(list);
goto L5;
L5:
t38 = getVarList("i", list);
t39 = 1;
t40 = t38 + t39;
setVarList("i", t40, list);
list = removeElement(list);
goto L0;
L2:
printf("%s: %d\n", "x", getVarList("x", list));
printf("%s: %d\n", "i", getVarList("i", list));
printf("%s: %d\n", "j", getVarList("j", list));
list = removeElement(list);
list = removeElement(list);

return 0;
}