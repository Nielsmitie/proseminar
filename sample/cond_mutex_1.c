pthread_cond_t cond_queue_empty, cond_queue_full;
pthread_mutex_t task_queue_lock;

main(){
	/* initialising */
	task_available = 0;
	pthread_cond_init(&cond_queue_empty)
	pthread_cond_init(&cond_queue_full)
	pthread_mutex_init(&task_queue_lock);
	/* create and join producer and consumer*/
}
