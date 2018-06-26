void *producer(void *producer_thread_data){
	while(!done()){
		produce();
		pthread_mutex_lock(&task_queue_lock)
		while(task_available == 1){
			pthread_cond_wait(&cond_queue_empty,
				&task_queue_lock);
		}
		insert_into_queue();
		task_available = 1;
		pthread_cond_signal(&cond_queue_full);
		pthread_mutex_unlock(&task_queue_cond_lock);
	}
}
