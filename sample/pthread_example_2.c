void *do_sth (void *s){
	int *number = (int *) s;
	// do work
	local = 0;
	for(int j = 0; j < 10000; j++){
		local += 1;
	}

	*number = local;

	p_thread_exit(0);
}
