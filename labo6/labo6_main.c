#include<zmq.h>
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include "help.h"


int main() {
	void *context;
	void *publisher;
	void *context_help;
	void *publisher_help;
	int * tree_in_arr = malloc(sizeof(int) * 4);	
	// Атлишна, //сделать когда Атлишна 
	// Пока не могу сразу проверять строки, но уже нужный нод получает ключ и строку.

	int len = 4;
	int index_of_last = 0;
	char a[20];
	while (scanf("%s",a) != EOF) {

		if (!strcmp (a, "exec")) {
		printf ("Какому id дать работу\n");
			if (scanf("%s",a) != EOF){
				int c = atoi(a);
				int v = 0;
				for (int z =  0; z < index_of_last; z ++){
					if (tree_in_arr[z] == c) {
						v = 1;
					} 
				}
				if (v == 0) {
					printf("Такого id нет\n");
					continue;
				}
				int len = 0;
				int capacity = 1;
				char *s = (char*) malloc(sizeof(char));
				int c2 = getchar();
				c2 = getchar();
				while (c2 != '\n') { 
					if (c2 == EOF){
						break;
					}
					//printf("%c", c2);
					s[(len)++] = c2;
					if (len >= capacity) {
						capacity *= 2;
						s = (char*) realloc(s, capacity * sizeof(char));
					}
					c2 = getchar();
				}
				int len1 = 0;
				int capacity1 = 1;
				char *s1 = (char*) malloc(sizeof(char));
				int c1 = getchar();
				while (c1 != '\n') { 
					if (c1 == EOF){
						break;
					}
					//printf("%c", c1);
					s1[(len1)++] = c1;
					if (len1 >= capacity1) {
						capacity1 *= 2;
						s1 = (char*) realloc(s1, capacity1 * sizeof(char));
					}
					c1 = getchar();
				}
				/*for (int r = 0; r < len; r++) {
					//printf ("%c", s[r]);
				}
				printf("\n");
				for (int e = 0; e < len1; e++) {
					//printf ("%c", s1[e]);
				}*/
				printf("\nВот\n");
				// Сначала передать ключ по которому искать
				//Дальше уже искать в нем 
				char message_to_s_k[15]= "123";
				char message [15] = "";
				char message1 [15] = "";
				message_to_s_k[0] = 'v';
				message_to_s_k[14] = 'u';
				// Это id нужно в вид 02345
				int ss = c;
				char q5[6] = "00000";
				//printf("Тут должно быть записанное %s \n",q5);
				for (int y = 4; y > 0; y--){
					q5[y] = ss%10 + '0';
					//printf("|%d %d\n",q5[y], ss);
					ss = ss /10;
				}
				q5[6] = '\n';
				int w = 0;
				//printf("Тут должно быть записанное %s \n",q5);
				sprintf(message_to_s_k, "v%su", q5);
				//printf("Тут было %s\n ", message_to_s_k);
				message_to_s_k[14] = 'u';
				for (int o = 0; o < len1; o++){
					message_to_s_k[(o%7)+7] = s1[o];
					if (o%7== 6 ){
						if (o == (len1-1)) {
							message_to_s_k[(o%7)+8] = '$';
						}						
						req_get_ans (message_to_s_k, publisher,message1);						
						printf("в главной ключ часть %s\n", message1);	
						continue;
					}
					if  (o == (len1-1)) {
						message_to_s_k[(o%7)+8] = '$';
						req_get_ans (message_to_s_k, publisher,message1);					
						printf("в главной ключ часть %s\n", message1);	
					}
				}
				//printf("%s", message_to_s_k);
				//////////////////////////////////////////////////////////////////////////////////////// Теперь надо и саму строку, не только ключ
				char message_to_s_k2[15]= "123";
				char message_2 [15] = "";
				char message1_2 [15] = "";
				message_to_s_k[14]= 'u';
				w = 0;
				//printf("Тут должно быть записанное %s \n",q5);
				sprintf(message_to_s_k2, "x%su", q5);
				//printf("Тут было %s\n ", message_to_s_k);
				message_to_s_k2[14] = 'u';
				for (int o = 0; o < len; o++){
					message_to_s_k2[(o%7)+7] = s[o];
					if (o%7== 6 ){
						if (o == (len-1)) {
							message_to_s_k2[(o%7)+8] = '$';
						}						
						req_get_ans (message_to_s_k2, publisher,message1_2);						
						printf("в главной слово часть %s\n", message1_2);	
						continue;
					}
					if  (o == (len1-1)) {
						message_to_s_k[(o%7)+8] = '$';
						req_get_ans (message_to_s_k2, publisher,message1_2);					
						printf("в главной слово часть %s\n", message1_2);	
					}
				}
				char message_to_s_k3[15]= "";
				sprintf(message_to_s_k3, "i%su", q5);
				char message1_3 [15] = "";
				req_get_ans (message_to_s_k3, publisher,message1_3);					
				printf("Отправил узнать ключ  %s\n", message1_3);
			}
		}
		if (!strcmp (a, "del")) {
			printf ("Вводи id:");
			if (scanf("%s",a) != EOF){
				int y = 0 ;
				int c = atoi(a);
				int v = 0;
				for (int z =  0; z < index_of_last; z ++){
					if (tree_in_arr[z] == c) {
						y = z;
						v = 1;
					} 
				}
				if (v == 0) {
					printf ("Такого нет вообще\n");
					continue;
				}
				char to[7];	
				sprintf(to, "d%du", tree_in_arr[y]); // Это кто удаляется 
				char to1[7];	 
				sprintf(to1, "%de", tree_in_arr[index_of_last - 1]); // Это к кому подключаться детям
				char to2[7];	
				sprintf(to2, "s%du", tree_in_arr[y/2]); //  Это родитель удаляемого
				char to3[7];	
				sprintf(to3, "%du", tree_in_arr[index_of_last - 1]); // y Это последний 
				char to4[7];	
				if (y*2 + 1 < index_of_last){
					sprintf(to4, "%du", tree_in_arr[y*2 + 1]); //  Это родитель удаляемого
				}
				else {
					sprintf(to4, "%du", 0);
				}
				char to5[7];	
				if (y*2 + 2 < index_of_last){
					sprintf(to5, "%de", tree_in_arr[y*2 + 2]); //  Это родитель удаляемого
				}
				else {
					sprintf(to5, "%de", 0);
				}
    			char message[15] = "";
				char message1[15] = "";
				req_get_ans (strncat(strncat(to2, to3, 30), strncat(to4, to5, 30), 30), publisher,message); // Тут надо добавить детей первого
				printf ("В Главной Q получил %s\n", message);
				req_get_ans ( strncat(to, to1, 30), publisher,message1);
				printf ("В Главной Q получил %s\n", message1);
				tree_in_arr[y] = tree_in_arr[index_of_last - 1];
				index_of_last = index_of_last - 1;
			}
		}
		if (!strcmp (a, "po")) {
			printf ("OK:");
			for (int e =  0; e < index_of_last; e ++){
				char message[15] = "";
				char to0[7] = "";	
				sprintf(to0, "o%de", tree_in_arr[e]);
				req_get_ans (to0, publisher,message);
				if (!strcmp (message, "fail") || (!strcmp (message, "tmout in rec_snd"))) { 					
					printf ("%d ,", tree_in_arr[e]);
				}
			}	
			printf ("\n");
		}

		if (!strcmp (a, "o")) {
			char message[15] = "";
			printf("Вводи Кого найти\n");
			int c;
			if (scanf("%s",a) != EOF){
				c = atoi(a);
				char to0[7];	
				sprintf(to0, "o%de", c);
				req_get_ans (to0, publisher,message);
				printf ("PING вернул в Главной %s\n", message);
			}
		}
		if (!strcmp (a, "p")) {
			for (int e =  0; e < index_of_last; e ++){
				printf("%d id %d|",e, tree_in_arr[e]);
			}	
			printf("\n");
		}

		if (!strcmp (a, "c")) {
			printf("Вводи id\n");
			int c;
			if (scanf("%s",a) != EOF){
				c = atoi(a);
				int v = 0;
				for (int z =  0; z < index_of_last; z ++){
					if (tree_in_arr[z] == c) {
						printf ("уже есть такой id!!!  <<< \n");
						v = 1;
					} 
				}
				if (v == 1) {
					continue;
				}
				tree_in_arr[index_of_last] = c;
				index_of_last ++;
				if (index_of_last >= len) {
					len = len * 2;
					tree_in_arr = realloc (tree_in_arr, sizeof(int) * len);
				}
			}
			int v = c;
			int id = fork();
			if (id == -1) {
				perror ("fork");
				return -1;
			}
			int parent_port;
			if (index_of_last == 1) {
				parent_port = 0;
			}
			else{
				parent_port = tree_in_arr[(index_of_last/2)-1];
			}
			if (id == 0){
    			char id_str[10];
				sprintf(id_str, "%d", v);
    			char prnt_port[10];
				sprintf(prnt_port, "%d", parent_port);
				execl("calc_node.out", "calc_node.out",id_str ,prnt_port, NULL);
				perror ("execl");
			}
			else {
				if (index_of_last == 1){
					context = zmq_ctx_new();
    				publisher = zmq_socket(context, ZMQ_REQ);
						int timeout = 1500;
						size_t timeout_size = sizeof timeout;
						zmq_setsockopt(publisher, ZMQ_RCVTIMEO, &timeout, timeout_size);		
					if (bind_for_req (publisher, parent_port) == -1) {
						printf("bind req err\n");
					}
    				char message[15] = "";
					req_get_ans ("cre", publisher,message);
					printf ("В Главной Q получил %s\n", message);	
				}
				else {
					char par[7];	
					sprintf(par, "c%du", tree_in_arr[(index_of_last/2)-1]);
					char to[7];	
					sprintf(to, "%de", c);
    				char message[15] = "";
					req_get_ans (strncat(par, to, 30), publisher,message);
					printf ("В Главной Q получил %s\n", message);
				}
			}
		}
	}
}
