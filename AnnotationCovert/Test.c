#include<stdio.h>
#include"AnnotationConvert.h"

int main()
{
	ConvertState ret=AnnotationConvert("input.c", "output.c");
	if (ret == FILE_ERROR)
	{
		printf("打开文件错误\n");
	}
	else if (ret == SUCCESS)
	{
		printf("转换成功\n");
	}
	else if (ret == NO_MATCH)
	{
		printf("不匹配\n");
	}
	return 0;
}