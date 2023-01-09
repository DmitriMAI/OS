#include <zmq.h>
#include <sys/time.h>


void rep_recv_part_first (void *  socket, char * m_get ){
    zmq_msg_t reply;
    zmq_msg_init_size (&reply, 15);
	zmq_msg_init(&reply);
	int t = zmq_msg_recv(&reply, socket, 0);
	if ( t == -1) {
		memcpy (m_get, "fail", 5);
		zmq_msg_close (&reply);
		return;
	}
	memcpy(m_get,zmq_msg_data( &reply), zmq_msg_size( &reply));
	zmq_msg_close (&reply);
	return;
}

void rep_send_part_second (void *  socket, char * m_send ){
    zmq_msg_t reply;
    zmq_msg_init_size (&reply, 15);
    memcpy (zmq_msg_data (&reply), m_send, 15);
    zmq_msg_send (&reply, socket, 0);
	zmq_msg_close (&reply);
}

int connect_for_rep (void *  socket, int v) {
	char dest[5];
	sprintf(dest, "%d", v+4900);
	char str1[20];
	strcpy(str1, "tcp://127.0.0.1:");
   	return zmq_connect(socket, strncat(str1, dest, 30));
}

int disconnect_for_rep (void *  socket, int v) {
	char dest[5];
	sprintf(dest, "%d", v+4900);
	char str1[20];
	strcpy(str1, "tcp://127.0.0.1:");
   	return zmq_disconnect(socket, strncat(str1, dest, 30));
}

int bind_for_req (void *  socket, int v) {
	char dest[5];
	sprintf(dest, "%d", v+4900);
	char str1[20];
	strcpy(str1, "tcp://127.0.0.1:");
   	return zmq_bind(socket, strncat(str1, dest, 30));
}

int unbind_for_req (void *  socket, int v) {
	char dest[5];
	sprintf(dest, "%d", v+4900);
	char str1[20];
	strcpy(str1, "tcp://127.0.0.1:");
   	return zmq_unbind(socket, strncat(str1, dest, 30));
}

int req_rcv_timout(void *  socket){
	int timeout = 100;
	size_t timeout_size = sizeof timeout;
	return zmq_setsockopt(socket, ZMQ_RCVTIMEO, &timeout, timeout_size);
}



void req_get_ans (char * m_send, void *  socket, char * m_get ) {
        zmq_msg_t reply;
		zmq_msg_t reply2;
        zmq_msg_init_size (&reply, 15);
		zmq_msg_init_size (&reply2, 15);
        memcpy (zmq_msg_data (&reply), m_send, 15);
		int timeout = 500;
		size_t timeout_size = sizeof timeout;
	    zmq_setsockopt(socket, ZMQ_SNDTIMEO, &timeout, timeout_size);
        int z = zmq_msg_send (&reply, socket, 0);
		if (z == -1) {
			//printf("tmout in rec_snd\n");
			memcpy (m_get, "fail", 5);
			zmq_msg_close (&reply);
			zmq_msg_close (&reply2);
		}
		int t = zmq_msg_recv(&reply2, socket, 0);
		if ( t == -1) {
			memcpy (m_get, "fail", 5);
			zmq_msg_close (&reply);
			zmq_msg_close (&reply2);
			return;
		}
		memcpy(m_get,zmq_msg_data( &reply2), zmq_msg_size (&reply2));
		zmq_msg_close (&reply);
		zmq_msg_close (&reply2);
		return;
}
