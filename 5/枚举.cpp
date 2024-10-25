#include <stdio.h>
#include <malloc.h>
/*
	题目：
		枚举
*/
/*
	算法思想：

*/
typedef enum workday
{
	Mon = 1,
	Tue,//Tue=2,
	Wed,
	Thu,
	Fir
} workday;

int main()
{
	workday day;
	day = Wed;
	printf("day:%d ", day);
}
