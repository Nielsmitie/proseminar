void *do_sth (void *s){
	int *number = (int *) s;
	// do work
	for(int j = 0; j < 10000; j++){
		*number += 1;
	}

	p_thread_exit(0);
}
