#include<stdio.h>
#include"AnnotationConvert.h"

int main()
{
	ConvertState ret=AnnotationConvert("input.c", "output.c");
	if (ret == FILE_ERROR)
	{
		printf("���ļ�����\n");
	}
	else if (ret == SUCCESS)
	{
		printf("ת���ɹ�\n");
	}
	else if (ret == NO_MATCH)
	{
		printf("��ƥ��\n");
	}
	return 0;
}