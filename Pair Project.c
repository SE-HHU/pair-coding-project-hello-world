//测试数据：100 1 100 1 100 1 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int SetPositionByLine(FILE *fp, int nLine);    //大概是定位函数，copy下来的 
void sort(int *a);	//对数组进行排序，便于验重,a为数组指针
int check(int this_item,int result,int all_ch,FILE *Checks,int *num);	//check函数为验重函数，参数名称与主函数保持一致 
int gys(int x, int y);	//求最大公约数，copy来的 

int main(void)
{
	int num_items,n_number_range_down,n_number_range_up,t_number_range_down,t_number_range_up,brackets;	
	//num_items为题目个数,n_number_range为自然数范围,t_number_range为真分数分母范围,brackets为是否带括号（0否1是）， 
	int num_M[4],num_S[4],ch[3],i,j,k,num_sign,all_ch,count1 = 0,count2 = 0;
	//num_M[4]为分母列表(整数分母为1),num_S=[4]为分子列表,ch[3]为符号列表,num_sign存放符号个数,all_cl计算符号和便于验证,count用于计数
	//ch参数详解:+-*/:0,1,2,3,空符号:3,另：空数为0 
	int YN,result_M = 1,result_S = 0,this_item = 0;  
	//YN用于存放布尔数,result_M为分母答案,result_S为分母答案,this_item为计数当前为第几题
	FILE *Exercises,*Answers,*Checks;
	//Exercises放题目,Answers放答案,Check以(数子1 数母1 符1 …… 结果子 结果母)的顺序,+-*/分别为0123,空符号:-1,空数为-1,每13行放一个对应题目 
	//若无符2和数3则以10(符2)和0(数3)对应;
	
	printf("欢迎使用计算题生成软件！\n请输入参数控制题目生成个数：");
	while(scanf("%d",&num_items) != 1 || num_items <= 0) 
		printf("输入错误，请重新输入一个大于0的整数:"); 
	printf("请依次输入参数控制题目中自然数的下限和上限：");
	while(scanf("%d %d",&n_number_range_down,&n_number_range_up) != 2 || n_number_range_down < 0 || n_number_range_down >= n_number_range_up) 
		printf("输入错误，请严格按照自然数定义依次输入题目中自然数的下限和上限："); 
	printf("请依次输入自然数参数控制题目中真分数分母的下限和上限：");
	while(scanf("%d %d",&t_number_range_down,&t_number_range_up) != 2 || t_number_range_down <= 0 || t_number_range_down >= t_number_range_up) 
		printf("输入错误，请严格按照自然数定义依次输入题目中真分数分母的下限和上限："); 
	printf("请输入题目在是否带括号（1为是，0为否）：");
	while(1)
	{
		if(scanf("%d",&brackets) == 1)
		{
			if(brackets == 1 || brackets == 0)
				break;
		}
		printf("输入错误，请重新输入1或0（1为带括号，0为不带括号）："); 
	}
	Exercises = fopen("Exercises.txt","w+");
	Answers = fopen("Answers.txt","w+");
	Checks = fopen("Checks.txt","w+");
	srand((unsigned)time(NULL));	//产生依赖于时间的随机种子，[a,b]随机数为int(rand()%(b-a+1)+a)
	for(k = 0;k < num_items;k++) //每次循环生成一个题目 
	{
		num_sign = rand()%(3)+1;	//确定符号生成个数(1或2或3) 
		for(i = 0;i < 4;i++)	//添加数字 
		{
			if(i < num_sign)	//此处为有定义数添加
			{
				YN =  rand()%3 + 10;
				if(YN % 3 != 0)		//YN判断为整数
				{
					num_S[i] = rand()%(n_number_range_up - n_number_range_down + 1) + n_number_range_down;		//添加整数
					num_M[i] = 1; 
					if(i < 3)
						ch[i] = rand()%(4);		//添加符号
				} 
				else
				{
					num_S[i] = rand()%(t_number_range_up - t_number_range_down - 1) + t_number_range_down;		//添加分子
					num_M[i] = rand()%(t_number_range_up - num_S[i]) + num_S[i] +1;		//添加分母 
					if(i < 3)
						ch[i] = rand()%(4);		//添加符号
				}
			}
			if(i == num_sign)	//此处添加尾数,不再添加符号 
			{
				YN = (rand()%(3))+10;
				if(YN % 3 != 0)		//YN判断为整数
				{
					num_S[i] = rand()%(n_number_range_up - n_number_range_down + 1) + n_number_range_down;		//添加整数
					num_M[i] = 1; 
				} 
				else
				{
					num_S[i] = rand()%(t_number_range_up - t_number_range_down - 1) + t_number_range_down;		//添加分子
					num_M[i] = rand()%(t_number_range_up - num_S[i]) + num_S[i] + 1;		//添加分母  
				} 
			}
			if(i > num_sign)
			{
				if(i-1 < 3)
					ch[i-1] = -1;		//添加空符号
				num_S[i] = -1;
				num_M[i] = -1;	//添加空数
			}
		}   
		for(i = 0;i < 4;i++)	//输出题目
		{
			if(num_S[i] == -1)
				break;
			if(num_M[i] == 1 && num_S != 0)
			{
				fprintf(Exercises,"%d  ",num_S[i]);
				fprintf(Checks,"%d\n1\n",num_S[i]);
			}
			else
			{
				fprintf(Exercises,"%d/%d  ",num_S[i],num_M[i]);
				fprintf(Checks,"%d\n%d\n",num_S[i],num_M[i]);
			} 
			if(i < 3)
			{
				switch(ch[i])
				{
				case 0:
					fprintf(Exercises,"+  ");
					fprintf(Checks,"0\n");
					break;
				case 1:
					fprintf(Exercises,"-  ");
					fprintf(Checks,"1\n");
					break;
				case 2:
					fprintf(Exercises,"×  ");
					fprintf(Checks,"2\n");
					break;
				case 3:
					fprintf(Exercises,"÷  ");
					fprintf(Checks,"3\n");
					break;
				case -1:
					break;
				}
			} 
		} 
		fprintf(Exercises,"=\n");
		for(i = 0;i < 3;i++)	//预处理,便于计算 
		{
			if(ch[i] == -1)
				break;
			if(ch[i] == 2)	//第i个符号为* 
			{
				num_S[i+1] *= num_S[i];
				num_M[i+1] *= num_M[i];
				num_S[i] = 0;
				num_M[i] = 1;
				ch[i] = 0;
				//将乘法a/b * c/d变为1/1 * (a*c / b*d),再改为0/1 + (a*c / b*d),使得最后计算时全为加减法 
			}
			if(ch[i] == 3)	//第i个符号为/,改为*,循环退一步 
			{
				count1 = num_S[i+1];
				num_S[i+1] = num_M[i+1];
				num_M[i+1] = count1;
				ch[i] = 2; 
				i--;
				count1 = 0;
			}
		}
		for(i = 0;i < 4;i++)	//计算原始分母
		{
			if(num_M != 0)
				result_M *= num_M[i];
		}
		result_S = num_S[0] * result_M / num_M[0];
		for(i = 0;i < 3;i++)	//计算原始分子
		{
			if(ch[i] == -1)
				break;
			if(ch[i] == 0)
				result_S += num_S[i+1] * result_M / num_M[i+1];
			else
				result_S -= num_S[i+1] * result_M / num_M[i+1];
		}
		count1 = gys(result_M,result_S);	//存放最大公约数
		result_M /= count1; 
		result_S /= count1;		//求得最简结果的分子和分母 
		if(result_M == 1)	//输出结果
				fprintf(Answers,"%d\n",result_S);
		else
		{
			if(result_M < 0)
				fprintf(Answers,"-%d/%d\n",abs(result_S),result_M);  	
			else
				fprintf(Answers,"%d/%d\n",result_S,result_M);  
		}
		fprintf(Checks,"%d\n%d\n",result_S,result_M);
		count1 = 0;
		/*if(this_item > 0)  //判断是否重复
		{
			count = check(this_item,result,all_ch,Checks,num);
			if(count == 3)
			{
				k--;
				continue;
			}
		}*/
		result_M = 1;
		result_S = 0;		//初始化答案
		all_ch = 0;		//初始化符号和 
		this_item++; 	//计算+1 
	}
	fclose(Exercises);
	fclose(Answers); 
	fclose(Checks);
	printf("生成完成！");
	remove("Checks.txt");	//删除检查文件 

	return 0; 
}

int SetPositionByLine(FILE *fp, int nLine)
{
	int i = 0;
	char buffer[7];
	fpos_t pos;
 
	rewind(fp);
	for (; i < nLine; i++)
		fgets(buffer, 6, fp);
	fgetpos(fp, &pos);
	return 0;
}

void sort(int *a)
{
    int i,j,v;
    for(i = 0; i < 2; i++)
    {
    	for(j = i + 1;j < 3;j++)
        {
            if(a[i] > a[j])//如前面的比后面的大，则交换。
            {
                v = a[i];
                a[i] = a[j];
                a[j] = v;
            }
        }
	}  
} 

int check(int this_item,int result,int all_ch,FILE *Checks,int *num)  
{
	char buffer[7];		//临时存放读取文件的字符串
	int history[3],temporary[3],count = 0,i,j;		//temporary临时储存num[3],history[3]为每次循环中每道历史题目的参数
	
	for(i = 0;i < this_item;i++)	//先读取每个历史答案，若有答案相同则读取两个符号之和，若相同则比较每个数，若相同，则题目重复 
	{
		SetPositionByLine(Checks, 5+i*6);	//46~48行读取第i组答案并比较 
		fgets(buffer, 6, Checks); 
		if(atoi(buffer) == result);
		{
			SetPositionByLine(Checks, 1+i*6);	//50~55行读取第i组1、2个符号，计算和并比较 
			fgets(buffer, 6, Checks);
			history[0] = atoi(buffer); 
			SetPositionByLine(Checks, 3+i*6);
			history[0] += atoi(buffer);
			if(history[0] == all_ch);
			{
				SetPositionByLine(Checks, 0+i*6);	//57~81行读取第i组1、2、3个数，进行比较，每一个相同则j+1，j=3时题目重复
				fgets(buffer, 6, Checks);
				history[0] = atoi(buffer);
				SetPositionByLine(Checks, 2+i*6);	
				fgets(buffer, 6, Checks);
				history[1] = atoi(buffer);
				SetPositionByLine(Checks, 4+i*6);	
				fgets(buffer, 6, Checks);
				history[2] = atoi(buffer);
				sort(history);
				for(j = 0;j < 3;j++)
				{
					temporary[j] = num[j];
				}
				sort(temporary);
				for(j = 0;j < 3;j++)
				{
				if(temporary[j] == history[j])
						count++;
				}
				if(count == 3)
				{
					return 3;
				}
				count = 0;
			}
		}
	}
	return 0;
}

int gys(int x, int y)
{
	//判断x/y余数是否为0
	int z = x % y;

	//直到余数为0，则跳出循环
	while(z)
	{
		//循环过程中，将除数给x，余数给y，求新的余数z
		x = y;
		y = z;
		z = x % y;
	}
	//除数y为最大公约数
	return y;
}
