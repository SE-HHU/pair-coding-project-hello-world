//�������ݣ�100 1 100 1 100 1 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int SetPositionByLine(FILE *fp, int nLine);    //����Ƕ�λ������copy������ 
void sort(int *a);	//������������򣬱�������,aΪ����ָ��
int check(int this_item,int result,int all_ch,FILE *Checks,int *num);	//check����Ϊ���غ�������������������������һ�� 
int gys(int x, int y);	//�����Լ����copy���� 

int main(void)
{
	int num_items,n_number_range_down,n_number_range_up,t_number_range_down,t_number_range_up,brackets;	
	//num_itemsΪ��Ŀ����,n_number_rangeΪ��Ȼ����Χ,t_number_rangeΪ�������ĸ��Χ,bracketsΪ�Ƿ�����ţ�0��1�ǣ��� 
	int num_M[4],num_S[4],ch[3],i,j,k,num_sign,all_ch,count1 = 0,count2 = 0;
	//num_M[4]Ϊ��ĸ�б�(������ĸΪ1),num_S=[4]Ϊ�����б�,ch[3]Ϊ�����б�,num_sign��ŷ��Ÿ���,all_cl������źͱ�����֤,count���ڼ���
	//ch�������:+-*/:0,1,2,3,�շ���:3,������Ϊ0 
	int YN,result_M = 1,result_S = 0,this_item = 0;  
	//YN���ڴ�Ų�����,result_MΪ��ĸ��,result_SΪ��ĸ��,this_itemΪ������ǰΪ�ڼ���
	FILE *Exercises,*Answers,*Checks;
	//Exercises����Ŀ,Answers�Ŵ�,Check��(����1 ��ĸ1 ��1 ���� ����� ���ĸ)��˳��,+-*/�ֱ�Ϊ0123,�շ���:-1,����Ϊ-1,ÿ13�з�һ����Ӧ��Ŀ 
	//���޷�2����3����10(��2)��0(��3)��Ӧ;
	
	printf("��ӭʹ�ü��������������\n���������������Ŀ���ɸ�����");
	while(scanf("%d",&num_items) != 1 || num_items <= 0) 
		printf("�����������������һ������0������:"); 
	printf("�������������������Ŀ����Ȼ�������޺����ޣ�");
	while(scanf("%d %d",&n_number_range_down,&n_number_range_up) != 2 || n_number_range_down < 0 || n_number_range_down >= n_number_range_up) 
		printf("����������ϸ�����Ȼ����������������Ŀ����Ȼ�������޺����ޣ�"); 
	printf("������������Ȼ������������Ŀ���������ĸ�����޺����ޣ�");
	while(scanf("%d %d",&t_number_range_down,&t_number_range_up) != 2 || t_number_range_down <= 0 || t_number_range_down >= t_number_range_up) 
		printf("����������ϸ�����Ȼ����������������Ŀ���������ĸ�����޺����ޣ�"); 
	printf("��������Ŀ���Ƿ�����ţ�1Ϊ�ǣ�0Ϊ�񣩣�");
	while(1)
	{
		if(scanf("%d",&brackets) == 1)
		{
			if(brackets == 1 || brackets == 0)
				break;
		}
		printf("�����������������1��0��1Ϊ�����ţ�0Ϊ�������ţ���"); 
	}
	Exercises = fopen("Exercises.txt","w+");
	Answers = fopen("Answers.txt","w+");
	Checks = fopen("Checks.txt","w+");
	srand((unsigned)time(NULL));	//����������ʱ���������ӣ�[a,b]�����Ϊint(rand()%(b-a+1)+a)
	for(k = 0;k < num_items;k++) //ÿ��ѭ������һ����Ŀ 
	{
		num_sign = rand()%(3)+1;	//ȷ���������ɸ���(1��2��3) 
		for(i = 0;i < 4;i++)	//������� 
		{
			if(i < num_sign)	//�˴�Ϊ�ж��������
			{
				YN =  rand()%3 + 10;
				if(YN % 3 != 0)		//YN�ж�Ϊ����
				{
					num_S[i] = rand()%(n_number_range_up - n_number_range_down + 1) + n_number_range_down;		//�������
					num_M[i] = 1; 
					if(i < 3)
						ch[i] = rand()%(4);		//��ӷ���
				} 
				else
				{
					num_S[i] = rand()%(t_number_range_up - t_number_range_down - 1) + t_number_range_down;		//��ӷ���
					num_M[i] = rand()%(t_number_range_up - num_S[i]) + num_S[i] +1;		//��ӷ�ĸ 
					if(i < 3)
						ch[i] = rand()%(4);		//��ӷ���
				}
			}
			if(i == num_sign)	//�˴����β��,������ӷ��� 
			{
				YN = (rand()%(3))+10;
				if(YN % 3 != 0)		//YN�ж�Ϊ����
				{
					num_S[i] = rand()%(n_number_range_up - n_number_range_down + 1) + n_number_range_down;		//�������
					num_M[i] = 1; 
				} 
				else
				{
					num_S[i] = rand()%(t_number_range_up - t_number_range_down - 1) + t_number_range_down;		//��ӷ���
					num_M[i] = rand()%(t_number_range_up - num_S[i]) + num_S[i] + 1;		//��ӷ�ĸ  
				} 
			}
			if(i > num_sign)
			{
				if(i-1 < 3)
					ch[i-1] = -1;		//��ӿշ���
				num_S[i] = -1;
				num_M[i] = -1;	//��ӿ���
			}
		}   
		for(i = 0;i < 4;i++)	//�����Ŀ
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
					fprintf(Exercises,"��  ");
					fprintf(Checks,"2\n");
					break;
				case 3:
					fprintf(Exercises,"��  ");
					fprintf(Checks,"3\n");
					break;
				case -1:
					break;
				}
			} 
		} 
		fprintf(Exercises,"=\n");
		for(i = 0;i < 3;i++)	//Ԥ����,���ڼ��� 
		{
			if(ch[i] == -1)
				break;
			if(ch[i] == 2)	//��i������Ϊ* 
			{
				num_S[i+1] *= num_S[i];
				num_M[i+1] *= num_M[i];
				num_S[i] = 0;
				num_M[i] = 1;
				ch[i] = 0;
				//���˷�a/b * c/d��Ϊ1/1 * (a*c / b*d),�ٸ�Ϊ0/1 + (a*c / b*d),ʹ��������ʱȫΪ�Ӽ��� 
			}
			if(ch[i] == 3)	//��i������Ϊ/,��Ϊ*,ѭ����һ�� 
			{
				count1 = num_S[i+1];
				num_S[i+1] = num_M[i+1];
				num_M[i+1] = count1;
				ch[i] = 2; 
				i--;
				count1 = 0;
			}
		}
		for(i = 0;i < 4;i++)	//����ԭʼ��ĸ
		{
			if(num_M != 0)
				result_M *= num_M[i];
		}
		result_S = num_S[0] * result_M / num_M[0];
		for(i = 0;i < 3;i++)	//����ԭʼ����
		{
			if(ch[i] == -1)
				break;
			if(ch[i] == 0)
				result_S += num_S[i+1] * result_M / num_M[i+1];
			else
				result_S -= num_S[i+1] * result_M / num_M[i+1];
		}
		count1 = gys(result_M,result_S);	//������Լ��
		result_M /= count1; 
		result_S /= count1;		//���������ķ��Ӻͷ�ĸ 
		if(result_M == 1)	//������
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
		/*if(this_item > 0)  //�ж��Ƿ��ظ�
		{
			count = check(this_item,result,all_ch,Checks,num);
			if(count == 3)
			{
				k--;
				continue;
			}
		}*/
		result_M = 1;
		result_S = 0;		//��ʼ����
		all_ch = 0;		//��ʼ�����ź� 
		this_item++; 	//����+1 
	}
	fclose(Exercises);
	fclose(Answers); 
	fclose(Checks);
	printf("������ɣ�");
	remove("Checks.txt");	//ɾ������ļ� 

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
            if(a[i] > a[j])//��ǰ��ıȺ���Ĵ��򽻻���
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
	char buffer[7];		//��ʱ��Ŷ�ȡ�ļ����ַ���
	int history[3],temporary[3],count = 0,i,j;		//temporary��ʱ����num[3],history[3]Ϊÿ��ѭ����ÿ����ʷ��Ŀ�Ĳ���
	
	for(i = 0;i < this_item;i++)	//�ȶ�ȡÿ����ʷ�𰸣����д���ͬ���ȡ��������֮�ͣ�����ͬ��Ƚ�ÿ����������ͬ������Ŀ�ظ� 
	{
		SetPositionByLine(Checks, 5+i*6);	//46~48�ж�ȡ��i��𰸲��Ƚ� 
		fgets(buffer, 6, Checks); 
		if(atoi(buffer) == result);
		{
			SetPositionByLine(Checks, 1+i*6);	//50~55�ж�ȡ��i��1��2�����ţ�����Ͳ��Ƚ� 
			fgets(buffer, 6, Checks);
			history[0] = atoi(buffer); 
			SetPositionByLine(Checks, 3+i*6);
			history[0] += atoi(buffer);
			if(history[0] == all_ch);
			{
				SetPositionByLine(Checks, 0+i*6);	//57~81�ж�ȡ��i��1��2��3���������бȽϣ�ÿһ����ͬ��j+1��j=3ʱ��Ŀ�ظ�
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
	//�ж�x/y�����Ƿ�Ϊ0
	int z = x % y;

	//ֱ������Ϊ0��������ѭ��
	while(z)
	{
		//ѭ�������У���������x��������y�����µ�����z
		x = y;
		y = z;
		z = x % y;
	}
	//����yΪ���Լ��
	return y;
}
