#pragma once
#include<assert.h>
#include<errno.h>

typedef enum ConvertState
{
	SUCCESS,
	FILE_ERROR,
	NO_MATCH,
}ConvertState;

typedef enum State
{
	C_BEING,
	C_END,
}State;
ConvertState Convert(FILE *fIn, FILE *fOut)
{
	ConvertState ret= SUCCESS;
	char first, second;
	State tag = C_END;
	assert(fIn);
	assert(fOut);
	do{
		first = fgetc(fIn);
		switch (first)
		{
		case'/':
			second = fgetc(fIn);
			if (second == '*')
			{
				//ƥ������
				if (tag == C_END)
				{
					fputc('/', fOut);
					fputc('/', fOut);
					tag = C_BEING;
				}
				else
				{
					fputc('/', fOut);
					fputc('*', fOut);
				}
			}
			//C++
			else if (second == '/')
			{
				char next;
				fputc('/', fOut);
				fputc('/', fOut);
				do
				{
					next = fgetc(fIn);
					fputc(next,fOut);
					if (next == EOF)
						return ret;
				} while (next != '\n');
			}
			else
			{
				fputc(first, fOut);
				fputc(second, fOut);
			}
			break;
		case'\n'://����ע��
			fputc('\n', fOut);
			if (tag == C_BEING)
			{
				fputc('/', fOut);
				fputc('/', fOut);
			}
			break;
		case'*':
			second = fgetc(fIn);
			if (second == '/')
			{
				//����ע������
				char next = fgetc(fIn);
				if (next == '/')
				{
					fputc('\n', fOut);
					fseek(fIn,-1,SEEK_CUR);
				}
				//��������
				else if (next != '\n'&&next != EOF)
				{
					fputc('\n',fOut);
					fputc(next,fOut);
				}
				else
				{
					fputc('\n', fOut);
				}
				tag = C_END;
			}
			//������*/����
			else if (second == '*')
			{
				fputc(first, fOut);
				fseek(fIn,-1,SEEK_CUR);
			}
			else
			{
				fputc(first, fOut);
				fputc(second, fOut);
			}
			break;
		default:
			if (first!=EOF)
				fputc(first, fOut);
			break;
		}
	} while (first != EOF);
	if (tag != C_END)
	{
		ret = NO_MATCH;
	}
	return ret;
}
ConvertState AnnotationConvert(const char* inputFile, const char* outputFile)
{
	ConvertState ret;
	FILE *fIn, *fOut;
	fIn = fopen(inputFile,"r");
	if (fIn == NULL)
	{
		printf("���ļ�%sʧ��",inputFile);
		return FILE_ERROR;
	}
	fOut = fopen(outputFile,"w");
	if (fOut == NULL)
	{
		fclose(fIn);
		printf("���ļ�%sʧ��", outputFile);
		return FILE_ERROR;
	}
	ret=Convert(fIn,fOut);
	
	fclose(fIn);
	fclose(fOut);
	return ret;
}
