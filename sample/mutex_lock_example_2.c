void *do_sth (void *s){
	int *my_cost = (int *) s;

	pthread_mutex_lock(&mlock);

	if(*my_cost < best_cost)
		best_cost = *my_cost;
		
	pthread_mutex_unlock(&mlock)

	p_thread_exit(0);
}
