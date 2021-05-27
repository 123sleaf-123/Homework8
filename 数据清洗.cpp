/* 本程序 */
#include <stdio.h>
#include <string.h>
int Deletestring_1(char* phone,int condition1);//删除长途拨号标志“+”或“00”或“0” 
int Deletestring_2(char* phone,int country);//删除国家\地区码标志“nums”
int Deletestring_3(char* phone,int j);//删除带服务号的号码的服务号，如96446 


int Deletestring_1(char* phone,int condition1){
	if(condition1 == 3) return 0;
	int i = strlen(phone);
	int j;
	if(condition1 == 11) j = 1;//如果是+开头，从第二位（下标1）开始作为新的开头 
	if(condition1 == 12) j = 2;//如果是00开头，从第三位（下标2）开始作为新的开头 
	if(condition1 == 2) j = 1;//如果是0开头，从第二位（下标1）开始作为新的开头 
	int k;
	for( k = 0 ; j < i ; k++ , j++){
		phone[k] = phone[j];
	}
	phone[k] = '\0';
	return 0;
}

int Deletestring_2(char* phone,int country){
	if(country == 0) return 1;//如果是其他开头，直接返回1以结束程序 
	int i = strlen(phone);
	int j;
	//if(country == 0) j = 3;如果是其他开头，默认从第四位（下标3）开始作为新的开头
	if(country == 1) j = 2;//如果是86开头，从第三位（下标2）开始作为新的开头 
	if(country == 2) j = 3;//如果是852开头，从第四位（下标3）开始作为新的开头 
	if(country == 3) j = 3;//如果是853开头，从第四位（下标3）开始作为新的开头 
	if(country == 4) j = 3;//如果是886开头，从第四位（下标3）开始作为新的开头 
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
	for( k = 0 ; j < i ; k++ , j++){//服务号诸如96446开头，从第7位（下标6），即964460的下一位开始作为新的开头 
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
		condition1 = 11;//国际长途 +nums 
	}
	else if(pre4[0] == '0'){
		if(pre4[1] == '0'){
			condition1 = 12;//国家长途 00nums 
		}
		else{
			condition1 = 2;//国内长途 0 phonenums 
		}
	}
	else{
		condition1 = 3;//市内电话 
	}
	
	Deletestring_1(phone,condition1); 
	printf("%s\n",phone);
	strncpy(pre3,phone,3);//取出删除了长途标记的电话号码的前三位 
	//printf("%s\n",pre3);
	
	if(condition1 > 10){ //当拨号类型为国家长途时 
		if(pre3[0] == '8'){
			if(pre3[1] == '6'){
				country = 1;//记1为中国大陆 86
			}
			else if(pre3[1] == '5'){
				if(pre3[2] == '2'){
					country = 2;//记2为中国香港 852
				}
				else if(pre3[2] == '3'){
						country = 3;//记3为中国澳门 853
				}
				else country = 0;//记0为未知地区或国家
			}
			else if(pre3[1] == '8'){
				if(pre3[2] == '6'){
					country = 4;//记4为中国台湾 886
				}
				else country = 0;//记0为未知地区或国家
			}
			else country = 0;//记0为未知地区或国家
		}
		else country = 0;//记0为未知地区或国家 
		if(Deletestring_2(phone,country)){
		printf("不允许查询非中国地区电话号码%c",7);
		return 1;//非中国号码而退出返回值设为1，与正常退出的0形成对比提醒用户 
		}
	} 
	
	printf("%s\n",phone);
	length = strlen(phone);
	printf("%d\n",length);
	
	if(length == 17){//处理带特殊服务手机电话号码 
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
			strncpy(MAC,phone,3); //储存移动接入码 
			Deletestring_3(phone,3); //删除接入码段三个字符 
		}
		else {
			condition2 = 2;
			char SSSS[4]; 
			strncpy(SSSS,phone,3); //储存区号 
			Deletestring_3(phone,3); //删除区号段三个字符 
			SSSS[3] = '\0' ;
		}
	}
	else if(length == 10){
		condition2 = 2;
		char SSSS[3]; 
		strncpy(SSSS,phone,3); //储存区号 
		Deletestring_3(phone,3); //删除区号段两个字符 
		SSSS[2] = '\0';
	}
	else if(length <= 5 && length >= 3){
		condition2 = 3;//删去长途标记后长度为3~5的号码就是我们的特殊号码了 
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
	
	如果删除了 长途标记号 和 国家\地区号 后号需要区分是特殊号、手机号码还是座机号码 
	
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
