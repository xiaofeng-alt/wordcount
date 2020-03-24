#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void CharCount(char file[]);
void WordCount(char file[]);
void LineCount(char file[]);
void aCount(char file[]);

//������
int main()
{
  char order;
  char file_name[100];
  while(1)
    {
       printf("����c�������ļ����ַ���\n");
       printf("����w�������ļ��Ĵʵ���Ŀ\n");
       printf("����l�������ļ�������\n");
       printf("����a�����ظ����ӵ����ݣ������� / ���� / ע����)\n");
       printf("����o���˳�\n\n\n");
       printf("���������wc.exe-");
       scanf("%c",&order);
       getchar();
       if(order!='c'&&order!='w'&&order!='l'&&order!='a'&&order!='o')  //�ж������Ƿ����Ҫ��
         {
           printf("�����������������\n");
           continue;
         }
       if(order=='o')
         {
           break;
         }
       printf("�������ļ�����");
       scanf("%s",&file_name);
       getchar();
       switch(order)
         {
           case 'c':
                    CharCount(file_name);
                    break;
           case 'w':
                    WordCount(file_name);
                    break;
           case 'l':
                    LineCount(file_name);
                    break;
           case 'a':
                    aCount(file_name);
                    break;
         }
    }
  return 0;
}

//�ַ�ͳ��
void CharCount(char file[])
{
  FILE *pf=NULL;
  int count=0;
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("���ļ�ʧ��\n");
      exit(1);
    }
  char getc;
  while(!feof(pf))
    {
       getc=fgetc(pf);
       if(getc=='\n')
         continue;
       if(getc!=EOF)
         count++;
    }
  rewind(pf);
  fclose(pf);
  printf("�ļ����ַ������У�%d\n\n",count);
}

//������ͳ��
void WordCount(char file[])
{
  FILE *pf=NULL;
  int count=0;
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("���ļ�ʧ��\n");
      exit(1);
    }
  char getc;
  int flag=0;
  while(!feof(pf))
  {
    getc=fgetc(pf);
    if((getc>='a'&&getc<='z')||(getc>='A'&&getc<='Z')||(getc>='0'&&getc<='9')||(getc=='_'))
       {
           if(flag==0)
             flag=1;
           continue;
       }
    else if(getc=='.')
    {
        continue;
    }
    else if(flag==1)
    {
        count++;
        flag=0;
    }
  }
  rewind(pf);
  fclose(pf);
  printf("�ļ��ĵ��������У�%d\n\n",count);
}

//�ļ�����ͳ��
void LineCount(char file[])
{
  FILE *pf=NULL;
  int count=0;
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("���ļ�ʧ��\n");
      exit(1);
    }
  char getc;
  while(!feof(pf))
  {
      getc=fgetc(pf);
      if(getc=='\n')
        count++;
  }
  rewind(pf);
  fclose(pf);
  printf("�ļ����������У�%d\n\n",count);
}

void aCount(char file[])
{
  FILE *pf=NULL;
  int blank=0,code=0,tag=0;//�ֱ�����ͳ�ƿ��У������У�ע����
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("���ļ�ʧ��\n");
      exit(1);
    }
  char getc;
  int flag=0; //��flagΪ0���У�Ϊ1�����ض��ַ��Ŀ��У�Ϊ2��ע���У�Ϊ3�Ǵ�����
  while(!feof(pf))
  {
      getc=fgetc(pf);
      if(flag==0||flag==1)//���е��ж�
      {
          if(getc=='\n')
          {
              blank++;
              flag=0;
              continue;
          }
          else if(flag==0&&(getc=='{'||getc=='}'))
          {
                flag==1;
                continue;
          }
          else if(getc==' ')
          {
              continue;
          }
          else
          {
              if(getc=='/')
                flag=2;
              else flag=3;
          }
      }
      if(flag==2)//ע���е��ж�
      {
          int tagflag=0;
          while(!feof(pf))
          {
              getc=fgetc(pf);
              if(getc=='/'&&tagflag==0)
                tagflag=1;
              if(getc=='*'&&tagflag==0)
                tagflag=2;
              if(getc=='*'&&tagflag==2)
                tagflag=3;
              else if(tagflag==0)
              {
                  while(!feof(pf)&&getc!='\n')
                    getc=fgetc(pf);
                  code++;
                  flag=0;
                  tagflag=0;
                  break;
              }
              if(tagflag=1)
              {
                  while(!feof(pf)&&getc!='\n')
                    getc=fgetc(pf);
                  tag++;
                  flag=0;
                  tagflag=0;
                  break;
              }
              if(tagflag==2)
              {
                  while(!feof(pf)&&getc!='\n'&&getc!='*')
                    getc=fgetc(pf);
                  if(getc=='*')
                  {
                      tagflag=3;  //���Ƿ�Ϊע�ͽ�����־
                      continue;
                  }
                  tag++;
              }
              if(tagflag==3&&getc=='/')
              {
                  while(!feof(pf)&&getc!='\n')
                    getc=fgetc(pf);
                  tag++;
                  flag=0;
                  tagflag=0;
                  break;
              }
              else if(tagflag==3&&getc!='/') //��'*'���ǽ���ע���е�ʱ������Ϊ2
              {
                  tagflag=2;
              }
          }
      }
      else if(flag==3)
      {
          while(!feof(pf)&&getc!='\n')
            getc=fgetc(pf);
          code++;
          flag=0;
          continue;
      }
  }
  printf("�ļ��Ŀ���������%d,������������%d,ע����������%d\n\n",blank,code,tag);

}
