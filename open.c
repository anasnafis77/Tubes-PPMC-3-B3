void open(int n, int m){
	FILE * fptr;
	char filename[20];
	int i, j;
	char c;
	
	printf("Masukkan nama file yang ingin dibuka: ");
	do{
		scanf("%s", &filename);
		strcat(filename, ".csv");
		fptr = fopen(filename, "r+");
		if(fptr == NULL){
			printf("File tidak tersedia.\n");
		}
	}while(fptr == NULL);
	
	//Memasukkan dari file eksternal ke program
	for(i = 0; i < n; i++){
		if(i == 0){
			for(j = 0; j < m; j++){
				printf("%d\t", j);
			}	
		}
		printf("\n");
		for(j = 0; j < m; j++){
			printf("%d\t", i);
			fscanf(fptr, "%c" &c);
			//Jika isinya huruf, berarti layout, kalau bukan berarti routing
			while(!feof(fptr)){
				if(isalpha(c)){
					printf("%c", c);
					fscanf(fptr, "%c", &c);
					printf("%c\t", c);
				}
				else{
					printf("%c", c);
				}
		}
	}		
	
	return;
}
