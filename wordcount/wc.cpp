#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void CharCount(char file[]);
void WordCount(char file[]);
void LineCount(char file[]);
void aCount(char file[]);

//主函数
int main()
{
  char order;
  char file_name[100];
  while(1)
    {
       printf("命令c：返回文件的字符数\n");
       printf("命令w：返回文件的词的数目\n");
       printf("命令l：返回文件的行数\n");
       printf("命令a：返回更复杂的数据（代码行 / 空行 / 注释行)\n");
       printf("命令o：退出\n\n\n");
       printf("请输入命令：wc.exe-");
       scanf("%c",&order);
       getchar();
       if(order!='c'&&order!='w'&&order!='l'&&order!='a'&&order!='o')  //判断输入是否符合要求
         {
           printf("输入错误，请重新输入\n");
           continue;
         }
       if(order=='o')
         {
           break;
         }
       printf("请输入文件名：");
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

//字符统计
void CharCount(char file[])
{
  FILE *pf=NULL;
  int count=0;
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("打开文件失败\n");
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
  printf("文件的字符数共有：%d\n\n",count);
}

//单词数统计
void WordCount(char file[])
{
  FILE *pf=NULL;
  int count=0;
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("打开文件失败\n");
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
  printf("文件的单词数共有：%d\n\n",count);
}

//文件行数统计
void LineCount(char file[])
{
  FILE *pf=NULL;
  int count=0;
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("打开文件失败\n");
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
  printf("文件的行数共有：%d\n\n",count);
}

void aCount(char file[])
{
  FILE *pf=NULL;
  int blank=0,code=0,tag=0;//分别用于统计空行，代码行，注释行
  pf=fopen(file,"r");
  if(!pf)
    {
      printf("打开文件失败\n");
      exit(1);
    }
  char getc;
  int flag=0; //当flag为0空行，为1是有特定字符的空行，为2是注释行，为3是代码行
  while(!feof(pf))
  {
      getc=fgetc(pf);
      if(flag==0||flag==1)//空行的判定
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
      if(flag==2)//注释行的判定
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
                      tagflag=3;  //看是否为注释结束标志
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
              else if(tagflag==3&&getc!='/') //当'*'不是结束注释行的时候，令标记为2
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
  printf("文件的空行数共有%d,代码行数共有%d,注释行数共有%d\n\n",blank,code,tag);

}
