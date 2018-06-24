for(row= 0; row < n; row++)
for(column = 0; column < n; column++)
	create_thread(
		c[row][column] = dot_product(
			get_row(a, row),
			get_row(b, col)));
