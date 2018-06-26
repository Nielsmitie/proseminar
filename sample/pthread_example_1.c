main(){
	int input[num_threads];
	pthread_t p_threads[num_threads];
	for(i=0; i < num_threads; i++){
		pthread_create(&p_threads[i], do_sth, 
			(void *)  &input[i]);
	}
	for(i=0; I < num_threads; i++){
		pthread_join(&p_threads[i], NULL);
	}
}
