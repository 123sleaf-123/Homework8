/* 本程序旨在清洗出号码的原本的号码段并予以呈现，目前仅支持查询中国的手机号，连接上外部程序即可呈现手机号码归属 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Aphone{
	char phone[30];//008695132013828081666,07506679820
	char MAC[5];
	char SSSS[5];
	char ser[6];
	char pn[12];
	char nums1[5];
	char nums2[5];
	char log[200];//生成的日志，可以随时查看 
	//int position;
	//struct Aphone *next;
};//Phonenumbers,*Phonenumbers_fun

struct Dictionary{
	struct Dictionary *left;
	struct Dictionary *right;
};

int Movesignal_1(char* phone,int condition1);//删除长途拨号标志“+”或“00”或“0” 
int Movesignal_2(char* phone,int country);//删除国家\地区码标志“nums” 
int FormatInput(char opt);//格式化的判断输入 
void Main_DictionaryTree(struct Aphone *phones);
void DictionaryTree(struct Aphone *phones);
void Showphonenumbers(struct Aphone *phones);//专门用于查看已输入的手机号 

void Showphonenumbers(struct Aphone *phones,int i){
	int j = 0;
	for(j = 0 ; j <= i ; j++){
		printf("No.%02d Phone information is:\n",j);//%02d可输出00~99的编号，非常好用，但我之前不会，看起来还是基础不牢，地动山摇啊 
		printf("%s\n",phones[j].log);
	}
}

void Main_DictionaryTree(struct Aphone *phones){
	int i = '0';
} 

int FormatInput(char opt)
{
	while (1)
	{
		if (opt == 'Y' || opt == 'N')
		{
			if(opt == 'Y')
			{
				return 1;
				break;
			}
			else
			{
				printf("\n\n\n\n\n\n");
				return 0;
				break;
			}
		}
		else
		{
			while(getchar() != 10);// delete meaningless strings
			printf ("\n=============================\n       INVALID DATA ! \n=============================\n");
			printf("Enter valid data (Y or N) to make your choice.\n");
			printf("\nYour choice:");
			scanf("%c",&opt);
		}
	}
}


int Movesignal_1(char* phone,int condition1){
	if(condition1 == 3) return 0;
	int i = strlen(phone);
	int j;
	char opt; 
	if(condition1 == 11) j = 1;//如果是+开头，从第二位（下标1）开始作为新的开头 
	if(condition1 == 12) j = 2;//如果是00开头，从第三位（下标2）开始作为新的开头 
	if(condition1 == 2) j = 1;//如果是0开头，从第二位（下标1）开始作为新的开头 
	int k;
	return j;
}

int Movesignal_2(char* phone,int country){
	if(country == 0) return 1;//如果是其他开头，直接返回1以结束程序 
	int i = strlen(phone);
	int j;
	//if(country == 0) j = 3;如果是其他开头，默认从第四位（下标3）开始作为新的开头
	if(country == 1) j = 2;//如果是86开头，从第三位（下标2）开始作为新的开头 
	if(country == 2) j = 3;//如果是852开头，从第四位（下标3）开始作为新的开头 
	if(country == 3) j = 3;//如果是853开头，从第四位（下标3）开始作为新的开头 
	if(country == 4) j = 3;//如果是886开头，从第四位（下标3）开始作为新的开头 
	return j;
}

int main (void){
	struct Aphone phones[100] = {0} ,*head;//未知的原因导致 *phones 无法被使用 
	int condition1 = 0, condition2 = 0, condition3 = 0, country = 3, length = 0;
	int i,j;
	char opt = 'Y';
	char pre5[6],pre4[5],pre3[4],pre2[3],pre1[2];
	head = &phones[0];
	
	for(i = 0 ; opt == 'Y' && i < 100; i++){
		printf("Please input the phone numbers:");
		scanf("%s",phones[i].phone);
		
		strncpy(pre4,phones[i].phone,4);
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
		
		j = Movesignal_1(phones[i].phone,condition1); 
		strncpy(pre3,phones[i].phone + j,3);//取出长途标记码后的电话号码的前三位 
		
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
			if(j += Movesignal_2(phones[i].phone,country)){
			printf("NOT ALLOW CONSULTING NON-CHINA REGIONS' PHONENUMBERS!%c\n",7);
			i--;
			continue;//非中国号码而退出返回值设为1，与正常退出的0形成对比提醒用户 
			}
		} 
		
		length = strlen(phones[i].phone + j);
	
		if(length == 17){//处理带特殊服务手机电话号码 
			strncpy(phones[i].ser,phones[i].phone + j,5);//读取服务号 
			j += 6;//取号标记向后移动6位 
			condition2 = 3;
			strncpy(phones[i].SSSS,phones[i].phone + j,11);//读取号码 
		}
		//printf("%s\n",phones[i].phone);
		
		else if(length == 11){
			condition2 = 1;
			strncpy(phones[i].MAC,phones[i].phone + j,3); //储存移动接入码 
			j += 3;//取号标记向后移动3位 
		}
		else if(length == 10){	//如果长度为10，说明是固定电话号码 
			if(phones[i].phone[j] == '1' || phones[i].phone[j] == '2'){		//如果当前位置为1或2，说明他是大城市级别的号码 
				condition2 = 21;
				strncpy(phones[i].SSSS,phones[i].phone + j,2); //储存区号 
				j += 2;//取号标记向后移动2位
			}
			else {
				condition2 = 2; 
				strncpy(phones[i].SSSS,phones[i].phone + j,3); //储存区号 
				j += 3;//取号标记向后移动3位
			}
		}
		else if(length == 7){
			condition2 = 2;
		}
		else if(length <= 5 && length >= 3){
			condition2 = 3;//删去长途标记后长度为3~5的号码就是我们的特殊号码了 
			strncpy(phones[i].SSSS,phones[i].phone + j,length);
		}
		else{
			printf("Invalid phone numbers.%c\n",7);
			i--;
			continue;
		}
		
		//printf("%s\n",phones[i].phone);
		if(condition2 == 22){
			strncpy(phones[i].nums1,phones[i].phone + j,3); //储存中间四位 
			j += 3;//取号标记向后移动4位
			strncpy(phones[i].nums2,phones[i].phone + j,4); //储存最后四位 
			j += 4;//取号标记向后移动4位
		}
		else{
			strncpy(phones[i].nums1,phones[i].phone + j,4); //储存中间四位 
			j += 4;//取号标记向后移动4位
			strncpy(phones[i].nums2,phones[i].phone + j,4); //储存最后四位 
			j += 4;//取号标记向后移动4位
		}
		//char information[200]; 
		
		if(condition2 == 1) 
		sprintf(phones[i].log,"The phone number:%s %s %s\nThis is a smartphone number\nregion type: %d\nZone:%d",phones[i].MAC,phones[i].nums1,phones[i].nums2,condition1,country);
		//printf("The phone number:%s %s %s\nis a smartphone number\nRegion type: %d\nZone:%d",phones[i].MAC,phones[i].nums1,phones[i].nums2,condition1,country);
		if(condition2 > 20) {
			//printf("The phone number:%s %s\nis a fixed phone number\nRegion code: %d\nZone Code: %d\nCounty Code: 0%s",phones[i].nums1,phones[i].nums2,condition1,country,phones[i].SSSS);
			sprintf(phones[i].log,"The phone number:%s %s %s\nThis is a fixed phone number\nRegion type: %d\nZone:%d\nCounty Code: 0%s",phones[i].nums1,phones[i].nums2,condition1,country,phones[i].SSSS);
		}
		//sprintf(phones[i].log,"The phone number:%s %s %s\nis a fixed phone number\nregion type: %d\nZone:%d\nCounty Code: 0%s",phones[i].nums1,phones[i].nums2,condition1,country,phones[i].SSSS);
		if(condition2 == 3)
		//printf("The phone number:%s \nis a special number\nregion type: %d\nZone:%d\nService Code: %s",phones[i].SSSS,condition1,country,phones[i].ser);
		sprintf(phones[i].log,"The phone number:%s \nThis is a special number\nRegion type: %d\nZone:%d\nService Code: %s",phones[i].SSSS,condition1,country,phones[i].ser);
		//printf("%s\n",phones[i].log);
		while(getchar() != '\n');//消除字符 
		printf("Do you want to continue?\n'Y' or 'N'?\n");
		opt = getchar();//输入判断 
		FormatInput(opt);//格式化后判断，套用旧作业函数 
	}
	printf("Input finished!\n\n");
	Showphonenumbers(head,i);
	return 0;
} 
