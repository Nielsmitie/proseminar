pthread_mutex_t mlock;
main(){
	int input;
	pthread_t p_threads[MAX_num_threads];
	pthread_mutex_init(&minimum_values_lock);
	for(i=0; i < num_threads; i++){
		pthread_create(&p_threads[i], do_sth, 
			(void *)  &input);
	}
	for(i=0; i < num_threads; i++){
		pthread_join(&p_threads[i], NULL);
	}
}
