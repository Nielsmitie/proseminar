pthread_mutex_t mlock;
int best_cost = 100;
main(){
	int input[2] = {75, 50}
	pthread_t p_threads[2];
	pthread_mutex_init(&minimum_values_lock);
	for(i=0; i < num_threads; i++){
		pthread_create(&p_threads[i], do_sth, 
			(void *)  &input[i]);
	}
	/* Join threads */
}
