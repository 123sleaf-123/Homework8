/* ������ */
#include <stdio.h>
#include <string.h>
int Deletestring_1(char* phone,int condition1);//ɾ����;���ű�־��+����00����0�� 
int Deletestring_2(char* phone,int country);//ɾ������\�������־��nums��
int Deletestring_3(char* phone,int j);//ɾ��������ŵĺ���ķ���ţ���96446 


int Deletestring_1(char* phone,int condition1){
	if(condition1 == 3) return 0;
	int i = strlen(phone);
	int j;
	if(condition1 == 11) j = 1;//�����+��ͷ���ӵڶ�λ���±�1����ʼ��Ϊ�µĿ�ͷ 
	if(condition1 == 12) j = 2;//�����00��ͷ���ӵ���λ���±�2����ʼ��Ϊ�µĿ�ͷ 
	if(condition1 == 2) j = 1;//�����0��ͷ���ӵڶ�λ���±�1����ʼ��Ϊ�µĿ�ͷ 
	int k;
	for( k = 0 ; j < i ; k++ , j++){
		phone[k] = phone[j];
	}
	phone[k] = '\0';
	return 0;
}

int Deletestring_2(char* phone,int country){
	if(country == 0) return 1;//�����������ͷ��ֱ�ӷ���1�Խ������� 
	int i = strlen(phone);
	int j;
	//if(country == 0) j = 3;�����������ͷ��Ĭ�ϴӵ���λ���±�3����ʼ��Ϊ�µĿ�ͷ
	if(country == 1) j = 2;//�����86��ͷ���ӵ���λ���±�2����ʼ��Ϊ�µĿ�ͷ 
	if(country == 2) j = 3;//�����852��ͷ���ӵ���λ���±�3����ʼ��Ϊ�µĿ�ͷ 
	if(country == 3) j = 3;//�����853��ͷ���ӵ���λ���±�3����ʼ��Ϊ�µĿ�ͷ 
	if(country == 4) j = 3;//�����886��ͷ���ӵ���λ���±�3����ʼ��Ϊ�µĿ�ͷ 
	int k;
	for( k = 0 ; j < i ; k++ , j++){
		phone[k] = phone[j];
	}
	phone[k] = '\0';
	return 0;
}

int Deletestring_3(char* phone,int j){
	int i = strlen(phone);
	int k;
	for( k = 0 ; j < i ; k++ , j++){//���������96446��ͷ���ӵ�7λ���±�6������964460����һλ��ʼ��Ϊ�µĿ�ͷ 
		phone[k] = phone[j];
	}
	phone[k] = '\0';
	return 0;
} 

int main (void){
	//sscanf(,"$%d",buf);
	char phone[] = "+86110" ;//008695132013828081666,07506679820
	int condition1 = 0, condition2 = 0, condition3 = 0, country = 0, length = 0;
	char pre5[5],pre4[4],pre3[3],pre2[2],pre1[1];
	strncpy(pre4,phone,4);
	
	if(pre4[0] == '+'){
		condition1 = 11;//���ʳ�; +nums 
	}
	else if(pre4[0] == '0'){
		if(pre4[1] == '0'){
			condition1 = 12;//���ҳ�; 00nums 
		}
		else{
			condition1 = 2;//���ڳ�; 0 phonenums 
		}
	}
	else{
		condition1 = 3;//���ڵ绰 
	}
	
	Deletestring_1(phone,condition1); 
	printf("%s\n",phone);
	strncpy(pre3,phone,3);//ȡ��ɾ���˳�;��ǵĵ绰�����ǰ��λ 
	//printf("%s\n",pre3);
	
	if(condition1 > 10){ //����������Ϊ���ҳ�;ʱ 
		if(pre3[0] == '8'){
			if(pre3[1] == '6'){
				country = 1;//��1Ϊ�й���½ 86
			}
			else if(pre3[1] == '5'){
				if(pre3[2] == '2'){
					country = 2;//��2Ϊ�й���� 852
				}
				else if(pre3[2] == '3'){
						country = 3;//��3Ϊ�й����� 853
				}
				else country = 0;//��0Ϊδ֪���������
			}
			else if(pre3[1] == '8'){
				if(pre3[2] == '6'){
					country = 4;//��4Ϊ�й�̨�� 886
				}
				else country = 0;//��0Ϊδ֪���������
			}
			else country = 0;//��0Ϊδ֪���������
		}
		else country = 0;//��0Ϊδ֪��������� 
		if(Deletestring_2(phone,country)){
		printf("�������ѯ���й������绰����%c",7);
		return 1;//���й�������˳�����ֵ��Ϊ1���������˳���0�γɶԱ������û� 
		}
	} 
	
	printf("%s\n",phone);
	length = strlen(phone);
	printf("%d\n",length);
	
	if(length == 17){//�������������ֻ��绰���� 
		char id[6];
		strncpy(id,phone,5);
		Deletestring_3(phone,6); 
		id[5] = '\0';
	}
	printf("%s\n",phone);
	
	if(length == 11){
		if(phone[0] == '1'){
			condition2 = 1;
			char MAC[4];
			strncpy(MAC,phone,3); //�����ƶ������� 
			Deletestring_3(phone,3); //ɾ��������������ַ� 
		}
		else {
			condition2 = 2;
			char SSSS[4]; 
			strncpy(SSSS,phone,3); //�������� 
			Deletestring_3(phone,3); //ɾ�����Ŷ������ַ� 
			SSSS[3] = '\0' ;
		}
	}
	else if(length == 10){
		condition2 = 2;
		char SSSS[3]; 
		strncpy(SSSS,phone,3); //�������� 
		Deletestring_3(phone,3); //ɾ�����Ŷ������ַ� 
		SSSS[2] = '\0';
	}
	else if(length <= 5 && length >= 3){
		condition2 = 3;//ɾȥ��;��Ǻ󳤶�Ϊ3~5�ĺ���������ǵ���������� 
	}
	else{
		printf("Invalid phone numbers.%c\n",7);
		return 2;
	}
	//printf("%s\n",phone);
	
	/*if(length >=3 || length <= 5){
		if(phone[2])
	}*/
	
	/*
	
	���ɾ���� ��;��Ǻ� �� ����\������ �����Ҫ����������š��ֻ����뻹���������� 
	
	if(length > 11 || length < 10){
		printf("Phone number Error!%c",7);
		return 0; 
	}
	*/
	//printf("%d\n",country);
	
	/*if (pre3 == "+86") return 1;
	else return 0;*/
	/*char pre1[2] = "+";
	printf("%s\n",pre1[1]);*/
	//printf("%s\n",pre1[0]);
	//printf("%c\n",pre1[0]);
	/*
	printf("%s\n",pre3);
	printf("%d\n",pre3 == "+86");
	printf("%d\n",pre1[0] == '+');
	*/
	return 0;
} 
