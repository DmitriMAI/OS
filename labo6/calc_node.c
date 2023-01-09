#include<zmq.h>
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<assert.h>
#include"help.h"


int main (int argc, char **argv){
	int k = 0;
	int c = atoi(argv[1]); // тут первое это его id, он оттуда принимает 
	int port_to_conn = atoi(argv[2]); //Куда надо приконектиться 	
	void *context_s = zmq_ctx_new();
    void *subscriber = zmq_socket(context_s, ZMQ_REP);
    if (connect_for_rep (subscriber, port_to_conn) == -1) {
		printf("conn rep err in s\n");
	}
	char simbol;
	void *context_p;
	void *publisher;
	int ch1 = 0;
	int ch2 = 0;
	char message[15] = "";
	char message3[15] = "";


				context_p = zmq_ctx_new();
    			publisher = zmq_socket(context_p, ZMQ_REQ);
				if (req_rcv_timout(publisher) == -1) {
					printf("tm add err\n");
				}
				if (bind_for_req (publisher, c) == -1) {
					printf("bind req err тут %d\n", c);
				}
		int len1 = 0;
		int capacity1 = 1;
		char *s1 = (char*) malloc(sizeof(char));
		int len = 0;
		int capacity = 1;
		char *s = (char*) malloc(sizeof(char));
	while (1) {
		memcpy (message, "", 15);
		rep_recv_part_first (subscriber, message);
		if (!strcmp(message, "cre")) {
			printf ("Я получил cre\n");
			rep_send_part_second(subscriber, "ok");
			continue;
		}
		simbol = message[0];
		int y = 1;
		int who = 0;
		int cr = 0;
		int m_father = 0;
		int m_chld1 = 0;
		int m_chld2 = 0;
		if (message[0] == 'i') {
			printf("Я сейчас в %d \n",c);
			char message1[15]= "";
			char message2[15]= "";
			while (message[y] != 'u'){ //Это кто будет у нас
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			//printf("Я сейчас в %d %d\n",c, who);
			if (who == c){
				printf("ВОТТ ВОТ\n");
				printf("Строка %s Ключ %s\n",s,s1);
				int q = 0;
				int y = 0;
				int r = 0;
				while(s[q]!='\n'){
						if (s1[y] == s[q]){
							y++;
							if(s1[y] == '\n'){
								printf("Совпадение %d\n",r);
							}
						}
						else{
							r++;							
							q = r; ///123415 15
							y = 0;				
						}
						q++;
					}
				rep_send_part_second(subscriber, "ok");
			}
			else {
			if (ch1 != 0) {
				req_get_ans (message, publisher,message1);
				//printf ("Отправил сыну %d \n", ch1);
			}
			if (ch2 != 0){				
				req_get_ans (message, publisher,message2);
				//printf ("Отправил сыну %d \n", ch2);	
			}
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}
			}
		}
		if (message[0] == 'x') { // Теперь задача потихоньку сравнивать нужное
			char message1[15]= "";
			char message2[15]= "";
			while (message[y] != 'u'){ //Это кто будет у нас
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			if (who == c) {
				int c1 =  message[y];
				while (c1 != 'u') { 
					if (c1 == '$'){
						break;
					}
					if (c1 == EOF){
						break;
					}
					printf("|%c|", c1);
					s[(len)++] = c1;
					if (len >= capacity) {
						capacity *= 2;
						s = (char*) realloc(s, capacity * sizeof(char));
					}
					y++;

					c1 =  message[y];
				}
				rep_send_part_second(subscriber, "ok");
				printf ("Я %d Строка  %s | %s \n", c, s,message);
				continue;
			}
			else {
			if (ch1 != 0) {
				req_get_ans (message, publisher,message1);
				//printf ("Отправил сыну %d \n", ch1);
			}
			if (ch2 != 0){				
				req_get_ans (message, publisher,message2);
				//printf ("Отправил сыну %d \n", ch2);	
			}
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}
			}
		}
			
		if (message[0] == 'v') { //Тут только для ключа или паттерна 
			char message1[15]= "";
			char message2[15]= "";
			while (message[y] != 'u'){ //Это кто будет у нас
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			if (who == c) {
				int c1 =  message[y];
				while (c1 != 'u') { 
					if (c1 == '$'){
						s1[(len1)++] = '\0';
						break;
					}
					if (c1 == EOF){
						break;
					}
					printf("|%c|", c1);
					s1[(len1)++] = c1;
					if (len1 >= capacity1) {
						capacity1 *= 2;
						s1 = (char*) realloc(s1, capacity1 * sizeof(char));
					}
					y++;

					c1 =  message[y];
				}
				rep_send_part_second(subscriber, "ok");
				printf ("Я %d Ключ мой  %s | %s \n", c, s1,message);
				continue;
			}
			else {
			if (ch1 != 0) {
				req_get_ans (message, publisher,message1);
				//printf ("Отправил сыну %d \n", ch1);
			}
			if (ch2 != 0){				
				req_get_ans (message, publisher,message2);
				//printf ("Отправил сыну %d \n", ch2);	
			}
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}
			}
			
		}


		if (message[0] == 's') {  // Мне дали два параметра s Кого удалить u присоед e 
			char message1[15] =  "fail";
			char message2[15] =  "fail";
			int ch1_1 = 0;
			int ch2_1 = 0;
			while (message[y] != 'u'){ //Это родитель кого удалить
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			while (message[y] != 'u'){ // Последний
				cr = cr * 10;
				cr = cr + message[y] - '0';
				y++;
			}
			y++;
			while (message[y] != 'u'){ // Последний
				ch1_1 = ch1_1 * 10;
				ch1_1 = ch1_1 + message[y] - '0';
				y++;
			}
			y++;
			while (message[y] != 'e'){ // Последний
				ch2_1 = ch2_1 * 10;
				ch2_1 = ch2_1 + message[y] - '0';
				y++;
			}
			y++;
			printf ("ЯЯ %d в переключении получил %d %d %d %d ", c, who, cr, ch1_1, ch2_1);
			if (cr == c){
				if (ch2_1 != c) {
					k++;
					ch2 = ch2_1;			
				}
				if (ch1_1 != c) {
					k++;
					ch1 = ch1_1;			
				}
				rep_send_part_second(subscriber, "ok");
				if (disconnect_for_rep (subscriber, port_to_conn) == -1) {
					printf("DISconn rep err in s\n");
				}
	   			zmq_close(subscriber);
				zmq_ctx_destroy(context_s);

				context_s = zmq_ctx_new();
				subscriber = zmq_socket(context_s, ZMQ_REP);
				if (connect_for_rep (subscriber, who) == -1) {
					printf("conn rep err in s\n");
				}
				continue;
			}
			else {
			char to0[7];	
			sprintf(to0, "s%du", who);
			char to1[7];	
			sprintf(to1, "%du", cr);
			char to2[7];	
			sprintf(to2, "%du", ch1_1);
			char to3[7];	
			sprintf(to3, "%de", ch2_1);

			if (ch1 != 0) {
				req_get_ans (strncat(strncat(to0, to1, 30), strncat(to2, to3, 30), 30), publisher,message1);
				//printf ("Отправил сыну %d \n", ch1);
			}
			if (ch2 != 0){				
				req_get_ans (strncat(strncat(to0, to1, 30), strncat(to2, to3, 30), 30), publisher,message2);
				//printf ("Отправил сыну %d \n", ch2);	
			}
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}
			}
			if (ch1 == cr) {
				ch1 = 0;
			}
			if (ch2 == cr) {
				ch2 = 0;
			}

		}
////////////////////////////////////////////////////////////////////////////////////	\/
		if (message[0] == 'q') {
			while (message[y] != 'e'){
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
				rep_send_part_second(subscriber, "ok");
				if (disconnect_for_rep (subscriber, port_to_conn) == -1) {
					printf("DISconn rep err in s\n");
				}
	   			zmq_close(subscriber);
				zmq_ctx_destroy(context_s);

				context_s = zmq_ctx_new();
				subscriber = zmq_socket(context_s, ZMQ_REP);
				if (connect_for_rep (subscriber, who) == -1) {
					printf("conn rep err in s\n");
				}

		}

		if (message[0] == 'd') {
			printf("Жив %d кто пинг принял %s Дети %d %d \n", c, message, ch1 , ch2);
			char message1[15] =  "fail";
			char message2[15] =  "fail";
			while (message[y] != 'u'){
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			while (message[y] != 'e'){
				cr = cr * 10;
				cr = cr + message[y] - '0';
				y++;
			}
			y++;
			if (who == c ) {
				rep_send_part_second(subscriber, "ok");
				char to0[7] = "";
				sprintf(to0, "q%de", cr);
				req_get_ans (to0, publisher,message1);	
				if (disconnect_for_rep (subscriber, port_to_conn) == -1) {
					printf("DISconn rep err in d\n");
				}
	   			zmq_close(subscriber);
				zmq_ctx_destroy(context_s);
				if (unbind_for_req (publisher, c) == -1) {
					printf("UNbind del err in d\n");
				}
	   			zmq_close(publisher);
				zmq_ctx_destroy(context_p);
				return 0;
			}
			if (k == 0){
				rep_send_part_second(subscriber, "fail");	
				continue;
			}
			char to0[7];	
			sprintf(to0, "d%du%de", who, cr);
			req_get_ans (to0, publisher,message1);			
			req_get_ans (to0, publisher,message2);
			printf ("В ping %d msg1 %s msg2 %s \n" , c , message1, message2);
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}
		}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  /\

		if (message[0] == 'o') {
			printf("Жив %d кто пинг принял %s Дети %d %d \n", c, message, ch1 , ch2);
			char message1[15] =  "fail";
			char message2[15] =  "fail";
			while (message[y] != 'e'){
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			if (who == c ) {
				rep_send_part_second(subscriber, "ok");
				continue;
			}
			if (k == 0){
				rep_send_part_second(subscriber, "fail");	
				continue;
			}
			char to0[7];	
			sprintf(to0, "o%de", who);
			req_get_ans (to0, publisher,message1);			
			req_get_ans (to0, publisher,message2);
			printf ("В ping %d msg1 %s msg2 %s \n" , c , message1, message2);
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}	
		}

		if (message[0] == 'c'){
			printf("ID %d кто принял \ns", c);
			while (message[y] != 'u'){
				who = who * 10;
				who = who + message[y] - '0';
				y++;
			}
			y++;
			while (message[y] != 'e'){
				cr = cr * 10;
				cr = cr + message[y] - '0';
				y++;
			}
			char message1[15] = "";
			char message2[15] = "";
			if ((who!= c ) && (k !=0)) {
				char par[7];	
				sprintf(par, "c%du", who);
				char to[7];	
				sprintf(to, "%de", cr);
				req_get_ans (strncat(par, to, 30), publisher,message1);
				//printf ("отправил из дальше из %d в %d\n", c, ch1);
				if (k == 2){
					req_get_ans (strncat(par, to, 30), publisher,message2);
					//printf ("отправил из дальше из %d в %d\n", c, ch1);
				}
			}
			if ((who == c)&& (k ==1)) {
				printf("Нашелся у %d --------- \n", c);
				k++;
				ch2 = cr;
				memcpy (message2, "", 15);
				req_get_ans ("cre", publisher,message2);
			}
			if ((who == c)&& (k ==0)) {
				printf("Нашелся у %d --------- \n", c);
				k++;
				ch1 = cr;
				memcpy (message1, "", 15);
				req_get_ans ("cre", publisher,message1);
			}
			//printf ("msg1 %s, msg2 %s\n" , message1, message2);
			if ( !(strcmp(message1, "ok")) || !(strcmp(message2, "ok")) ) {
				rep_send_part_second(subscriber, "ok");
			}
			else {
				rep_send_part_second(subscriber, "fail");
			}		
		}


	}
}
