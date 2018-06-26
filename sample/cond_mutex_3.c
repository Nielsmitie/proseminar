void *consumer(void *consumer_thread_data){
	while(!done()){
		pthread_mutex_lock(&task_queue_lock);
		while(task_available == 0){
			pthread_cond_wait(&cond_queue_full,
				&task_queue_lock);
		}
		data = take_data();
		task_available = 0;
		pthread_cond_signal(&cond_queue_empty);
		pthread_mutex_unlock(&tasK_queue_lock);
		process(data)
	}
}
