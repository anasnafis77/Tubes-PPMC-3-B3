void open(){
	FILE * fptr;
	char filename[20];
	
	printf("Masukkan nama file yang ingin dibuka: ");
	do{
		scanf("%s", &filename);
		strcat(filename, ".csv");
		fptr = fopen(filename, "r+");
		if(fptr == NULL){
			printf("File tidak tersedia.\n");
		}
	}while(fptr == NULL);
	
	return;
}
